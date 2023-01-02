#pragma once

#include "Const.hpp"
#include "NekoRay_Utils.hpp"
#include "NekoRay_ConfigItem.hpp"
#include "NekoRay_DataStore.hpp"

// Switch core support

namespace NekoRay {
    inline int coreType = NekoRay::CoreType::V2RAY;

    QString FindCoreAsset(const QString &name);
} // namespace NekoRay

#define IS_NEKO_BOX (NekoRay::coreType == NekoRay::CoreType::SING_BOX)
#define ROUTES_PREFIX_NAME QString(IS_NEKO_BOX ? "routes_box" : "routes")
#define ROUTES_PREFIX QString(ROUTES_PREFIX_NAME + "/")
