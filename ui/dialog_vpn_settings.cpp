#include "dialog_vpn_settings.h"
#include "ui_dialog_vpn_settings.h"

#include "main/GuiUtils.hpp"
#include "main/NekoRay.hpp"

DialogVPNSettings::DialogVPNSettings(QWidget *parent) :
        QDialog(parent), ui(new Ui::DialogVPNSettings) {
    ui->setupUi(this);

    ui->fake_dns->setVisible(!IS_NEKO_BOX);
    ui->fake_dns->setChecked(NekoRay::dataStore->fake_dns);
    //
    ui->vpn_implementation->setCurrentIndex(NekoRay::dataStore->vpn_implementation);
    ui->vpn_mtu->setCurrentText(Int2String(NekoRay::dataStore->vpn_mtu));
    ui->vpn_ipv6->setChecked(NekoRay::dataStore->vpn_ipv6);
    ui->hide_console->setChecked(NekoRay::dataStore->vpn_hide_consloe);
#ifndef Q_OS_WIN
    ui->hide_console->setVisible(false);
#endif
    //
    D_LOAD_STRING(vpn_bypass_cidr)
    D_LOAD_STRING(vpn_bypass_process)
}

DialogVPNSettings::~DialogVPNSettings() {
    delete ui;
}

void DialogVPNSettings::accept() {
    //
    auto mtu = ui->vpn_mtu->currentText().toInt();
    if (mtu > 10000 || mtu < 1000) mtu = 9000;
    NekoRay::dataStore->vpn_implementation = ui->vpn_implementation->currentIndex();
    NekoRay::dataStore->fake_dns = ui->fake_dns->isChecked();
    NekoRay::dataStore->vpn_mtu = mtu;
    NekoRay::dataStore->vpn_ipv6 = ui->vpn_ipv6->isChecked();
    NekoRay::dataStore->vpn_hide_consloe = ui->hide_console->isChecked();
    //
    D_SAVE_STRING_QTEXTEDIT(vpn_bypass_cidr)
    D_SAVE_STRING_QTEXTEDIT(vpn_bypass_process)
    //
    MW_dialog_message("", "UpdateDataStore,VPNChanged");
    QDialog::accept();
}
