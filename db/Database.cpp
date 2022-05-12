#include "db/Database.hpp"
#include "sub/RawUpdater.hpp"

namespace NekoRay {

    void ProfileManager::LoadManager() {
        for (auto id: _profiles) {
            profiles[id] = LoadProxyEntity(QString("profiles/%1.json").arg(id));
        }
        for (auto id: _groups) {
            groups[id] = LoadGroup(QString("groups/%1.json").arg(id));
        }
    }

    void ProfileManager::SaveManager() {
    }

    QSharedPointer<ProxyEntity> ProfileManager::LoadProxyEntity(const QString &jsonPath) {
        // Load type
        auto ent0 = ProxyEntity(nullptr, nullptr);
        ent0.fn = jsonPath;
        auto validJson = ent0.Load();
        auto type = ent0.type;

        // Load content
        QSharedPointer<ProxyEntity> ent;
        bool validType = validJson;

        if (validType) {
            ent = NewProxyEntity(type);
            validType = ent->bean->version != -114514;
        }

        if (validType) {
            // 加载前设置好 fn
            ent->load_control_force = true;
            ent->fn = jsonPath;
            ent->Load();
            return ent;
        } else {
            // 返回一个假的？
            ent->bean->name = "[Load Error]";
            return ent;
        }
    }

    //  新建的不给 fn 和 id

    QSharedPointer<ProxyEntity> ProfileManager::NewProxyEntity(const QString &type) {
        fmt::AbstractBean *bean;

        if (type == "socks") {
            bean = new fmt::SocksBean();
        } else if (type == "shadowsocks") {
            bean = new fmt::ShadowSocksBean();
        } else if (type == "chain") {
            bean = new fmt::ChainBean();
        } else if (type == "vmess") {
            bean = new fmt::VMessBean();
        } else if (type == "trojan") {
            bean = new fmt::TrojanBean();
        } else {
            bean = new fmt::AbstractBean(-114514);
        }

        auto ent = QSharedPointer<ProxyEntity>(new ProxyEntity(bean, type));
        return ent;
    }

    QSharedPointer<Group> ProfileManager::NewGroup() {
        auto ent = QSharedPointer<Group>(new Group());
        return ent;
    }

    // Profile

    int ProfileManager::NewProfileID() const {
        if (profiles.empty()) { return 0; } else { return profiles.lastKey() + 1; }
    }

    bool ProfileManager::AddProfile(const QSharedPointer<ProxyEntity> &ent, int gid) {
        if (ent->id >= 0) {
            return false;
        }

        ent->group_id = gid < 0 ? dataStore->current_group : gid;
        ent->id = NewProfileID();
        profiles[ent->id] = ent;
        _profiles.push_back(ent->id);
        Save();

        ent->fn = QString("profiles/%1.json").arg(ent->id);
        ent->Save();
        return true;
    }

    void ProfileManager::DeleteProfile(int id) {
        if (!profiles.contains(id)) return;
        profiles.remove(id);
        if (!_profiles.contains(id)) return;
        _profiles.removeAll(id);
        Save();
        QFile(QString("profiles/%1.json").arg(id)).remove();
    }

    QSharedPointer<ProxyEntity> ProfileManager::GetProfile(int id) {
        if (profiles.contains(id)) {
            return profiles[id];
        }
        return nullptr;
    }

    //Group

    QSharedPointer<Group> ProfileManager::LoadGroup(const QString &jsonPath) {
        QSharedPointer<Group> ent = QSharedPointer<Group>(new Group());
        ent->load_control_force = false;
        ent->fn = jsonPath;
        ent->Load();
        return ent;
    }

    int ProfileManager::NewGroupID() const {
        if (groups.empty()) { return 0; } else { return groups.lastKey() + 1; }
    }

    bool ProfileManager::AddGroup(const QSharedPointer<Group> &ent) {
        if (ent->id >= 0) {
            return false;
        }

        ent->id = NewGroupID();
        groups[ent->id] = ent;
        _groups.push_back(ent->id);
        Save();

        ent->fn = QString("groups/%1.json").arg(ent->id);
        ent->Save();
        return true;
    }

    void ProfileManager::DeleteGroup(int id) {
        if (id == 0) return;
        if (!groups.contains(id)) return;
        groups.remove(id);
        for (const auto &profile: profileManager->profiles) {
            if (profile->group_id == id) profileManager->DeleteProfile(profile->id);
        }
        if (!_groups.contains(id)) return;
        _groups.removeAll(id);
        Save();
        QFile(QString("groups/%1.json").arg(id)).remove();
    }

    QSharedPointer<Group> ProfileManager::GetGroup(int id) {
        if (groups.contains(id)) {
            return groups[id];
        }
        return nullptr;
    }

    QSharedPointer<Group> ProfileManager::CurrentGroup() {
        return NekoRay::profileManager->GetGroup(NekoRay::dataStore->current_group);
    }

    QList<QSharedPointer<ProxyEntity>> Group::Profiles() const {
        QList<QSharedPointer<ProxyEntity>> ret;
        for (const auto &profile: profileManager->profiles) {
            if (id == profile->group_id) ret += profile;
        }
        return ret;
    }

    // 订阅

    void ProfileManager::AsyncUpdateSubscription(int gid) {
        auto group = GetGroup(gid);
        sub::rawUpdater->AsyncUpdate(group->url, gid);
    }

}