#pragma once
// Saitama version — update before each release
#define OPS_VERSION_MAJOR 1
#define OPS_VERSION_MINOR 6
#define OPS_VERSION_PATCH 5
#define OPS_VERSION_PRE   ""
#define OPS_VERSION_STRING "1.6.5"

// Builds with the Bitchat bridge say so beside the version on the device.
#ifdef WITH_BITCHAT_BRIDGE
#define OPS_VERSION_SUFFIX " +Bitchat 9"
#else
#define OPS_VERSION_SUFFIX ""
#endif
