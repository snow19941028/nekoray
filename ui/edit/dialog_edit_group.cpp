#include "dialog_edit_group.h"
#include "ui_dialog_edit_group.h"

#include "db/Database.hpp"

#include <QClipboard>

DialogEditGroup::DialogEditGroup(const QSharedPointer<NekoRay::Group> &ent, QWidget *parent) :
        QDialog(parent), ui(new Ui::DialogEditGroup) {
    ui->setupUi(this);

    connect(ui->type, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
        ui->cat_sub->setHidden(index == 0);
    });

    ui->name->setText(ent->name);
    ui->archive->setChecked(ent->archive);
    ui->url->setText(ent->url);
    ui->type->setCurrentIndex(ent->url.isEmpty() ? 0 : 1);
    ui->type->currentIndexChanged(ui->type->currentIndex());
    ui->copy_links->setVisible(false);
    ui->copy_links_nkr->setVisible(false);
    if (ent->id >= 0) { // already a group
        ui->type->setDisabled(true);
        if (!ent->Profiles().isEmpty()) {
            ui->copy_links->setVisible(true);
            ui->copy_links_nkr->setVisible(true);
        }
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [=] {
        if (ent->id >= 0) { // already a group
            if (!ent->url.isEmpty() && ui->url->text().isEmpty()) {
                MessageBoxWarning(tr("Warning"), tr("Please input URL"));
                return;
            }
        }
        ent->name = ui->name->text();
        ent->url = ui->url->text();
        ent->archive = ui->archive->isChecked();
        QDialog::accept();
    });

    connect(ui->copy_links, &QPushButton::clicked, this, [=] {
        QStringList links;
        for (const auto &profile: NekoRay::profileManager->profiles) {
            if (profile->gid != ent->id) continue;
            links += profile->bean->ToShareLink();
        }
        QApplication::clipboard()->setText(links.join("\n"));
        MessageBoxInfo(software_name, tr("Copied"));
    });
    connect(ui->copy_links_nkr, &QPushButton::clicked, this, [=] {
        QStringList links;
        for (const auto &profile: NekoRay::profileManager->profiles) {
            if (profile->gid != ent->id) continue;
            links += profile->bean->ToNekorayShareLink(profile->type);
        }
        QApplication::clipboard()->setText(links.join("\n"));
        MessageBoxInfo(software_name, tr("Copied"));
    });
}

DialogEditGroup::~DialogEditGroup() {
    delete ui;
}
