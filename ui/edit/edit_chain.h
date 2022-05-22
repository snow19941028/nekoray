#pragma once

#include <QWidget>
#include "profile_editor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EditChain; }
QT_END_NAMESPACE

class EditChain : public QWidget, public ProfileEditor {
Q_OBJECT

public:
    explicit EditChain(QWidget *parent = nullptr);

    ~EditChain() override;

    void onStart(QSharedPointer<NekoRay::ProxyEntity> _ent) override;

    bool onEnd() override;

private:
    Ui::EditChain *ui;
    QSharedPointer<NekoRay::ProxyEntity> ent;

    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void on_select_profile_clicked();
};
