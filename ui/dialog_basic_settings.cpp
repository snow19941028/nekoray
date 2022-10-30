#include "dialog_basic_settings.h"
#include "ui_dialog_basic_settings.h"

#include "qv2ray/v2/ui/widgets/editors/w_JsonEditor.hpp"
#include "fmt/Preset.hpp"
#include "ui/ThemeManager.hpp"
#include "main/GuiUtils.hpp"
#include "main/NekoRay.hpp"

#include <QStyleFactory>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

class ExtraCoreWidget : public QWidget {
public:
    QString coreName;

    QLabel *label_name;
    MyLineEdit *lineEdit_path;
    QPushButton *pushButton_pick;

    explicit ExtraCoreWidget(QJsonObject *extraCore, const QString &coreName_,
                             QWidget *parent = nullptr)
            : QWidget(parent) {
        coreName = coreName_;
        label_name = new QLabel;
        label_name->setText(coreName);
        lineEdit_path = new MyLineEdit;
        lineEdit_path->setText(extraCore->value(coreName).toString());
        pushButton_pick = new QPushButton;
        pushButton_pick->setText(QObject::tr("Select"));
        auto layout = new QHBoxLayout;
        layout->addWidget(label_name);
        layout->addWidget(lineEdit_path);
        layout->addWidget(pushButton_pick);
        setLayout(layout);
        setContentsMargins(0, 0, 0, 0);
        //
        connect(pushButton_pick, &QPushButton::clicked, this, [=] {
            auto fn = QFileDialog::getOpenFileName(this, QObject::tr("Select"), QDir::currentPath(),
                                                   "", nullptr, QFileDialog::Option::ReadOnly);
            if (!fn.isEmpty()) {
                lineEdit_path->setText(fn);
            }
        });
        connect(lineEdit_path, &QLineEdit::textChanged, this, [=](const QString &newTxt) {
            extraCore->insert(coreName, newTxt);
        });
    }
};

DialogBasicSettings::DialogBasicSettings(QWidget *parent)
        : QDialog(parent), ui(new Ui::DialogBasicSettings) {
    ui->setupUi(this);

    // Common

    if (IS_NEKO_BOX) {
        ui->groupBox_mux->hide();
        ui->groupBox_http->hide();
        ui->inbound_socks_port_l->setText(ui->inbound_socks_port_l->text().replace("Socks", "Mixed"));
        ui->hlayout_l2->addWidget(ui->groupBox_log);
        ui->log_level->addItems(QString("trace debug info warn error fatal panic").split(" "));
    } else {
        ui->log_level->addItems({"debug", "info", "warning", "none"});
    }

    ui->socks_ip->setText(NekoRay::dataStore->inbound_address);
    ui->log_level->setCurrentText(NekoRay::dataStore->log_level);
    CACHE.custom_inbound = NekoRay::dataStore->custom_inbound;
    D_LOAD_INT(inbound_socks_port)
    D_LOAD_INT_ENABLE(inbound_http_port, http_enable)
    D_LOAD_INT_ENABLE(mux_cool, mux_cool_enable)
    D_LOAD_INT(test_concurrent)
    D_LOAD_STRING(test_url)

    connect(ui->custom_inbound_edit, &QPushButton::clicked, this, [=] {
        C_EDIT_JSON_ALLOW_EMPTY(custom_inbound)
    });

#ifdef Q_OS_WIN
    connect(ui->sys_proxy_format, &QPushButton::clicked, this, [=] {
        bool ok;
        auto str = QInputDialog::getItem(this, ui->sys_proxy_format->text() + " (Windows)",
                                         tr("Advanced system proxy settings. Please select a format."),
                                         Preset::Windows::system_proxy_format,
                                         Preset::Windows::system_proxy_format.indexOf(
                                                 NekoRay::dataStore->system_proxy_format),
                                         false, &ok
        );
        if (ok) NekoRay::dataStore->system_proxy_format = str;
    });
#else
    ui->sys_proxy_format->hide();
#endif

    // Style
    if (IS_NEKO_BOX) {
        ui->connection_statistics_box->setDisabled(true);
    }
    //
    D_LOAD_BOOL(start_minimal)
    D_LOAD_BOOL(check_include_pre)
    D_LOAD_BOOL(connection_statistics)
    //
    if (NekoRay::dataStore->traffic_loop_interval == 500) {
        ui->rfsh_r->setCurrentIndex(0);
    } else if (NekoRay::dataStore->traffic_loop_interval == 1000) {
        ui->rfsh_r->setCurrentIndex(1);
    } else {
        ui->rfsh_r->setCurrentIndex(2);
    }
    //
    ui->language->setCurrentIndex(NekoRay::dataStore->language);
    connect(ui->language, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
        CACHE.needRestart = true;
    });
    //
    int built_in_len = ui->theme->count();
    ui->theme->addItems(QStyleFactory::keys());
    //
    bool ok;
    auto themeId = NekoRay::dataStore->theme.toInt(&ok);
    if (ok) {
        ui->theme->setCurrentIndex(themeId);
    } else {
        ui->theme->setCurrentText(NekoRay::dataStore->theme);
    }
    //
    connect(ui->theme, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
        if (index + 1 <= built_in_len) {
            themeManager->ApplyTheme(Int2String(index));
            NekoRay::dataStore->theme = Int2String(index);
        } else {
            themeManager->ApplyTheme(ui->theme->currentText());
            NekoRay::dataStore->theme = ui->theme->currentText();
        }
        repaint();
        mainwindow->repaint();
        NekoRay::dataStore->Save();
    });

    // Subscription

    ui->user_agent->setText(NekoRay::dataStore->user_agent);
    D_LOAD_BOOL(sub_use_proxy)
    D_LOAD_BOOL(sub_clear)

    // Core

    ui->groupBox_core->setTitle(software_core_name);
    ui->core_v2ray_asset->setText(NekoRay::dataStore->v2ray_asset_dir);
    //
    CACHE.extraCore = QString2QJsonObject(NekoRay::dataStore->extraCore->core_map);
    if (!CACHE.extraCore.contains("naive")) CACHE.extraCore.insert("naive", "");
    if (!CACHE.extraCore.contains("hysteria")) CACHE.extraCore.insert("hysteria", "");
    //
    auto extra_core_layout = ui->extra_core_box->layout();
    for (const auto &s: CACHE.extraCore.keys()) {
        extra_core_layout->addWidget(new ExtraCoreWidget(&CACHE.extraCore, s));
    }
    //
    connect(ui->core_v2ray_asset, &QLineEdit::textChanged, this, [=] {
        CACHE.needRestart = true;
    });
    connect(ui->core_v2ray_asset_pick, &QPushButton::clicked, this, [=] {
        auto fn = QFileDialog::getExistingDirectory(this, tr("Select"), QDir::currentPath(),
                                                    QFileDialog::Option::ShowDirsOnly | QFileDialog::Option::ReadOnly);
        if (!fn.isEmpty()) {
            ui->core_v2ray_asset->setText(fn);
        }
    });
    connect(ui->extra_core_add, &QPushButton::clicked, this, [=] {
        bool ok;
        auto s = QInputDialog::getText(nullptr, tr("Add"),
                                       tr("Please input the core name."),
                                       QLineEdit::Normal, "", &ok).trimmed();
        if (s.isEmpty() || !ok) return;
        if (CACHE.extraCore.contains(s)) return;
        extra_core_layout->addWidget(new ExtraCoreWidget(&CACHE.extraCore, s));
        CACHE.extraCore.insert(s, "");
    });
    connect(ui->extra_core_del, &QPushButton::clicked, this, [=] {
        bool ok;
        auto s = QInputDialog::getItem(nullptr, tr("Delete"),
                                       tr("Please select the core name."),
                                       CACHE.extraCore.keys(), 0, false, &ok);
        if (s.isEmpty() || !ok) return;
        for (int i = 0; i < extra_core_layout->count(); i++) {
            auto item = extra_core_layout->itemAt(i);
            auto ecw = dynamic_cast<ExtraCoreWidget *>(item->widget());
            if (ecw != nullptr && ecw->coreName == s) {
                ecw->deleteLater();
                CACHE.extraCore.remove(s);
                return;
            }
        }
    });

    // switch core
    ui->switch_core_v2ray->setChecked(!IS_NEKO_BOX);
    ui->switch_core_sing_box->setChecked(IS_NEKO_BOX);
    auto switch_core_on_click = [=] {
        int neko_core_new;
        if (sender() == ui->switch_core_sing_box) {
            if (IS_NEKO_BOX) return;
            neko_core_new = NekoRay::CoreType::SING_BOX;
        } else {
            if (!IS_NEKO_BOX) return;
            neko_core_new = NekoRay::CoreType::V2RAY;
        }
        QString core_name_new = dynamic_cast<QRadioButton *>(sender())->text();
        if (QMessageBox::question(this, tr("Confirmation"),
                                  tr("Switching the core to %1, click \"Yes\" to complete the switch and the program will restart. This feature may be unstable, please do not switch frequently.")
                                          .arg(core_name_new)
        ) == QMessageBox::StandardButton::Yes) {
            QFile file;
            file.setFileName("groups/coreType");
            file.open(QIODevice::ReadWrite | QIODevice::Truncate);
            file.write(Int2String(neko_core_new).toUtf8());
            file.close();
            dialog_message("", "RestartProgram");
        }
    };
    connect(ui->switch_core_v2ray, &QRadioButton::clicked, this, switch_core_on_click);
    connect(ui->switch_core_sing_box, &QRadioButton::clicked, this, switch_core_on_click);

    // Security

    D_LOAD_BOOL(insecure_hint)
    D_LOAD_BOOL(skip_cert)
}

DialogBasicSettings::~DialogBasicSettings() {
    delete ui;
}

void DialogBasicSettings::accept() {
    if (CACHE.needRestart) MessageBoxWarning(tr("Settings changed"), tr("Restart nekoray to take effect."));

    // Common

    NekoRay::dataStore->inbound_address = ui->socks_ip->text();
    NekoRay::dataStore->log_level = ui->log_level->currentText();
    NekoRay::dataStore->custom_inbound = CACHE.custom_inbound;
    D_SAVE_INT(inbound_socks_port)
    D_SAVE_INT_ENABLE(inbound_http_port, http_enable)
    D_SAVE_INT_ENABLE(mux_cool, mux_cool_enable)
    D_SAVE_INT(test_concurrent)
    D_SAVE_STRING(test_url)

    // Style

    NekoRay::dataStore->language = ui->language->currentIndex();
    D_SAVE_BOOL(start_minimal)
    D_SAVE_BOOL(connection_statistics)
    D_SAVE_BOOL(check_include_pre)

    if (ui->rfsh_r->currentIndex() == 0) {
        NekoRay::dataStore->traffic_loop_interval = 500;
    } else if (ui->rfsh_r->currentIndex() == 1) {
        NekoRay::dataStore->traffic_loop_interval = 1000;
    } else {
        NekoRay::dataStore->traffic_loop_interval = 0;
    }

    // Subscription

    NekoRay::dataStore->user_agent = ui->user_agent->text();
    D_SAVE_BOOL(sub_use_proxy)
    D_SAVE_BOOL(sub_clear)

    // Core

    NekoRay::dataStore->v2ray_asset_dir = ui->core_v2ray_asset->text();
    NekoRay::dataStore->extraCore->core_map = QJsonObject2QString(CACHE.extraCore, true);

    // Security

    D_SAVE_BOOL(insecure_hint)
    D_SAVE_BOOL(skip_cert)

    dialog_message(Dialog_DialogBasicSettings, "UpdateDataStore");
    QDialog::accept();
}

void DialogBasicSettings::on_set_custom_icon_clicked() {
    auto title = ui->set_custom_icon->text();
    QString user_icon_path = "./" + software_name.toLower() + ".png";
    auto c = QMessageBox::question(this, title, tr("Please select a PNG file."),
                                   tr("Select"), tr("Reset"), tr("Cancel"), 2, 2);
    if (c == 0) {
        auto fn = QFileDialog::getOpenFileName(this, QObject::tr("Select"), QDir::currentPath(),
                                               "*.png", nullptr, QFileDialog::Option::ReadOnly);
        QImage img(fn);
        if (img.isNull() || img.height() != img.width()) {
            MessageBoxWarning(title, tr("Please select a valid square image."));
            return;
        }
        QFile::copy(fn, user_icon_path);
    } else if (c == 1) {
        QFile::remove(user_icon_path);
    } else {
        return;
    }
    dialog_message(Dialog_DialogBasicSettings, "UpdateIcon");
}
