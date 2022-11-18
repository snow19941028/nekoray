#pragma once

#include <QWidget>
#include <QListWidgetItem>

#include "db/ProxyEntity.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class ProxyItem;
}
QT_END_NAMESPACE

class ProxyItem : public QWidget {
    Q_OBJECT

public:
    explicit ProxyItem(QWidget *parent, const QSharedPointer<NekoRay::ProxyEntity> &ent, QListWidgetItem *item);

    ~ProxyItem() override;

    void refresh_data();

    QSharedPointer<NekoRay::ProxyEntity> ent;
    QListWidgetItem *item;
    bool remove_confirm = false;

private:
    Ui::ProxyItem *ui;

private slots:

    void on_remove_clicked();
};
