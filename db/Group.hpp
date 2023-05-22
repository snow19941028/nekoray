#pragma once

#include "main/NekoGui.hpp"
#include "ProxyEntity.hpp"

namespace NekoGui {
    class Group : public JsonStore {
    public:
        int id = -1;
        bool archive = false;
        QString name = "";
        QString url = "";
        QString info = "";
        qint64 sub_last_update = 0;

        // list ui
        bool manually_column_width = false;
        QList<int> column_width;
        QList<int> order;

        Group();

        // 按 id 顺序
        [[nodiscard]] QList<std::shared_ptr<ProxyEntity>> Profiles() const;

        // 按 显示 顺序
        [[nodiscard]] QList<std::shared_ptr<ProxyEntity>> ProfilesWithOrder() const;
    };
} // namespace NekoGui
