#include "dialog_manage_routes.h"
#include "ui_dialog_manage_routes.h"

#include "qv2ray/v2/ui/widgets/editors/w_JsonEditor.hpp"
#include "qv2ray/v3/components/GeositeReader/GeositeReader.hpp"
#include "main/GuiUtils.hpp"

#include <QFile>
#include <QMessageBox>
#include <QListWidget>

#define REFRESH_ACTIVE_ROUTING(a, r) \
active_routing = a; \
ui->active_routing->setText("[" + active_routing + "]"); \
setWindowTitle(title_base + " [" + a + "]"); \
SetRouteConfig(*r);

#define SAVE_TO_ROUTING(r) \
r->direct_ip = directIPTxt->toPlainText(); \
r->direct_domain = directDomainTxt->toPlainText(); \
r->proxy_ip = proxyIPTxt->toPlainText(); \
r->proxy_domain = proxyDomainTxt->toPlainText(); \
r->block_ip = blockIPTxt->toPlainText(); \
r->block_domain = blockDomainTxt->toPlainText(); \
r->custom = CACHE.custom_route;

DialogManageRoutes::DialogManageRoutes(QWidget *parent) :
        QDialog(parent), ui(new Ui::DialogManageRoutes) {
    ui->setupUi(this);
    title_base = windowTitle();

    if (IS_NEKO_BOX) {
        ui->enhance_resolve_server_domain->setVisible(false);
        ui->domain_v2ray->setVisible(false);
    } else {
        ui->enhance_resolve_server_domain->setVisible(true);
        ui->domain_v2ray->setVisible(true);
    }
    //
    ui->sniffing_mode->setCurrentIndex(NekoRay::dataStore->sniffing_mode);
    ui->outbound_domain_strategy->setCurrentText(NekoRay::dataStore->outbound_domain_strategy);
    ui->domainMatcherCombo->setCurrentIndex(NekoRay::dataStore->domain_matcher);
    ui->domainStrategyCombo->setCurrentText(NekoRay::dataStore->domain_strategy);
    ui->dns_routing->setChecked(NekoRay::dataStore->dns_routing);
    ui->dns_remote->setText(NekoRay::dataStore->remote_dns);
    ui->dns_direct->setText(NekoRay::dataStore->direct_dns);
    ui->enhance_resolve_server_domain->setChecked(NekoRay::dataStore->enhance_resolve_server_domain);
    D_C_LOAD_STRING(custom_route_global)
    //
    connect(ui->custom_route_edit, &QPushButton::clicked, this, [=] {
        C_EDIT_JSON_ALLOW_EMPTY(custom_route)
    });
    connect(ui->custom_route_global_edit, &QPushButton::clicked, this, [=] {
        C_EDIT_JSON_ALLOW_EMPTY(custom_route_global)
    });
    //
    builtInSchemesMenu = new QMenu(this);
    builtInSchemesMenu->addActions(this->getBuiltInSchemes());
    ui->preset->setMenu(builtInSchemesMenu);

    QString geoipFn = NekoRay::FindCoreAsset("geoip.dat");
    QString geositeFn = NekoRay::FindCoreAsset("geosite.dat");
    //
    const auto sourceStringsDomain = Qv2ray::components::GeositeReader::ReadGeoSiteFromFile(geoipFn);
    directDomainTxt = new AutoCompleteTextEdit("geosite", sourceStringsDomain, this);
    proxyDomainTxt = new AutoCompleteTextEdit("geosite", sourceStringsDomain, this);
    blockDomainTxt = new AutoCompleteTextEdit("geosite", sourceStringsDomain, this);
    //
    const auto sourceStringsIP = Qv2ray::components::GeositeReader::ReadGeoSiteFromFile(geositeFn);
    qDebug() << sourceStringsIP;
    directIPTxt = new AutoCompleteTextEdit("geoip", sourceStringsIP, this);
    proxyIPTxt = new AutoCompleteTextEdit("geoip", sourceStringsIP, this);
    blockIPTxt = new AutoCompleteTextEdit("geoip", sourceStringsIP, this);
    //
    ui->directTxtLayout->addWidget(directDomainTxt, 0, 0);
    ui->proxyTxtLayout->addWidget(proxyDomainTxt, 0, 0);
    ui->blockTxtLayout->addWidget(blockDomainTxt, 0, 0);
    //
    ui->directIPLayout->addWidget(directIPTxt, 0, 0);
    ui->proxyIPLayout->addWidget(proxyIPTxt, 0, 0);
    ui->blockIPLayout->addWidget(blockIPTxt, 0, 0);
    //
    REFRESH_ACTIVE_ROUTING(NekoRay::dataStore->active_routing, NekoRay::dataStore->routing)
}

DialogManageRoutes::~DialogManageRoutes() {
    delete ui;
}

void DialogManageRoutes::accept() {
    NekoRay::dataStore->sniffing_mode = ui->sniffing_mode->currentIndex();
    NekoRay::dataStore->domain_matcher = ui->domainMatcherCombo->currentIndex();
    NekoRay::dataStore->domain_strategy = ui->domainStrategyCombo->currentText();
    NekoRay::dataStore->outbound_domain_strategy = ui->outbound_domain_strategy->currentText();
    NekoRay::dataStore->dns_routing = ui->dns_routing->isChecked();
    NekoRay::dataStore->remote_dns = ui->dns_remote->text();
    NekoRay::dataStore->direct_dns = ui->dns_direct->text();
    NekoRay::dataStore->enhance_resolve_server_domain = ui->enhance_resolve_server_domain->isChecked();
    D_C_SAVE_STRING(custom_route_global)
    bool routeChanged = false;
    if (NekoRay::dataStore->active_routing != active_routing) routeChanged = true;
    SAVE_TO_ROUTING(NekoRay::dataStore->routing)
    NekoRay::dataStore->active_routing = active_routing;
    NekoRay::dataStore->routing->fn = "routes/" + NekoRay::dataStore->active_routing;
    if (NekoRay::dataStore->routing->Save()) routeChanged = true;
    //
    QString info = "UpdateDataStore";
    if (routeChanged) info += "RouteChanged";
    dialog_message(Dialog_DialogManageRoutes, info);
    QDialog::accept();
}

// built in settings

QList<QAction *> DialogManageRoutes::getBuiltInSchemes() {
    QList<QAction *> list;
    list.append(this->schemeToAction(tr("Bypass LAN and China"), routing_cn_lan));
    list.append(this->schemeToAction(tr("Global"), routing_global));
    return list;
}

QAction *DialogManageRoutes::schemeToAction(const QString &name, const NekoRay::Routing &scheme) {
    auto *action = new QAction(this);
    action->setText(name);
    connect(action, &QAction::triggered, [this, &scheme] { this->SetRouteConfig(scheme); });
    return action;
}

void DialogManageRoutes::SetRouteConfig(const NekoRay::Routing &conf) {
    //
    directDomainTxt->setPlainText(conf.direct_domain);
    proxyDomainTxt->setPlainText(conf.proxy_domain);
    blockDomainTxt->setPlainText(conf.block_domain);
    //
    blockIPTxt->setPlainText(conf.block_ip);
    directIPTxt->setPlainText(conf.direct_ip);
    proxyIPTxt->setPlainText(conf.proxy_ip);
    //
    CACHE.custom_route = conf.custom;
}

void DialogManageRoutes::on_load_save_clicked() {
    auto w = new QDialog;
    auto layout = new QVBoxLayout;
    w->setLayout(layout);
    auto lineEdit = new QLineEdit;
    layout->addWidget(lineEdit);
    auto list = new QListWidget;
    layout->addWidget(list);
    for (const auto &name: NekoRay::Routing::List()) {
        list->addItem(name);
    }
    connect(list, &QListWidget::currentTextChanged, lineEdit, &QLineEdit::setText);
    auto bottom = new QHBoxLayout;
    layout->addLayout(bottom);
    auto load = new QPushButton;
    load->setText(tr("Load"));
    bottom->addWidget(load);
    auto save = new QPushButton;
    save->setText(tr("Save"));
    bottom->addWidget(save);
    auto remove = new QPushButton;
    remove->setText(tr("Remove"));
    bottom->addWidget(remove);
    auto cancel = new QPushButton;
    cancel->setText(tr("Cancel"));
    bottom->addWidget(cancel);
    connect(load, &QPushButton::clicked, w, [=] {
        auto fn = lineEdit->text();
        if (!fn.isEmpty()) {
            auto r = std::make_unique<NekoRay::Routing>();
            r->load_control_force = true;
            r->fn = "routes/" + fn;
            if (r->Load()) {
                auto btn = QMessageBox::question(nullptr,
                                                 software_name, tr("Load routing: %1").arg(fn) + "\n" + r->toString());
                if (btn == QMessageBox::Yes) {
                    REFRESH_ACTIVE_ROUTING(fn, r)
                    w->accept();
                }
            }
        }
    });
    connect(save, &QPushButton::clicked, w, [=] {
        auto fn = lineEdit->text();
        if (!fn.isEmpty()) {
            auto r = std::make_unique<NekoRay::Routing>();
            SAVE_TO_ROUTING(r)
            r->fn = "routes/" + fn;
            auto btn = QMessageBox::question(nullptr, software_name,
                                             tr("Save routing: %1").arg(fn) + "\n" + r->toString());
            if (btn == QMessageBox::Yes) {
                r->Save();
                REFRESH_ACTIVE_ROUTING(fn, r)
                w->accept();
            }
        }
    });
    connect(remove, &QPushButton::clicked, w, [=] {
        auto fn = lineEdit->text();
        if (!fn.isEmpty() && NekoRay::Routing::List().length() > 1) {
            auto btn = QMessageBox::question(nullptr, software_name, tr("Remove routing: %1").arg(fn));
            if (btn == QMessageBox::Yes) {
                QFile f("routes/" + fn);
                f.remove();
                if (NekoRay::dataStore->active_routing == fn) {
                    NekoRay::Routing::SetToActive(NekoRay::Routing::List().first());
                    REFRESH_ACTIVE_ROUTING(NekoRay::dataStore->active_routing, NekoRay::dataStore->routing)
                }
                w->accept();
            }
        }
    });
    connect(cancel, &QPushButton::clicked, w, &QDialog::accept);
    connect(list, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) {
        lineEdit->setText(item->text());
        emit load->clicked();
    });
    w->exec();
    w->deleteLater();
}
