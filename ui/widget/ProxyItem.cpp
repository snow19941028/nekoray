#include "ProxyItem.h"
#include "ui_ProxyItem.h"

ProxyItem::ProxyItem(QWidget *parent, const QSharedPointer<NekoRay::ProxyEntity> &ent, QListWidgetItem *item) :
        QWidget(parent), ui(new Ui::ProxyItem) {
    ui->setupUi(this);
    this->item = item;
    this->ent = ent;
    if (ent == nullptr) return;

    ui->type->setText(ent->bean->DisplayType());
    ui->name->setText(ent->bean->DisplayName());
    ui->address->setText(ent->bean->DisplayAddress());
    ui->traffic->setText(ent->traffic_data->DisplayTraffic());
    ui->test_result->setText(ent->DisplayLatency());
}

ProxyItem::~ProxyItem() {
    delete ui;
}

void ProxyItem::on_remove_clicked() {
    if (QMessageBox::question(this, tr("Confirmation"), tr("Remove %1?").arg(ent->bean->DisplayName())) ==
        QMessageBox::StandardButton::Yes) {
        // TODO do remove (or not) -> callback
        delete item;
    }
}
