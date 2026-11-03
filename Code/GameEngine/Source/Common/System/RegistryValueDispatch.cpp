// cl: /DNDEBUG /MD

// Registry-value dispatcher at 0x0002F720 (288B). No BFME1 twin: the key
// set (SkuName, GameName, GameRegPath, InstallerRegPath, OnlineServer,
// UserDataLeafName, G1..G4) is BFME2-new. The sole caller walks a
// double-null-terminated registry block, splits each entry at '=', and calls
// here with (key, value); the matching global keeps the value pointer.
//
// The comparator address is loaded once from the _strcmpi IAT slot into EDI
// and reused for all ten calls, so the source caches it in a local: taking
// the address of the dllimport emits exactly that load. Each match stores
// the value and returns; no match falls through.

#include <string.h>

const char *g_SkuNameValue = "GI.DAT ERROR";
const char *g_GameNameValue = "GI.DAT ERROR";
const char *g_GameRegPathValue = "GI.DAT ERROR";
const char *g_InstallerRegPathValue = "GI.DAT ERROR";
const char *g_OnlineServerValue = "GI.DAT ERROR";
const char *g_UserDataLeafNameValue = "GI.DAT ERROR";
const char *g_G1Value = "GI.DAT ERROR";
const char *g_G2Value = "GI.DAT ERROR";
const char *g_G3Value = "GI.DAT ERROR";
const char *g_G4Value = "GI.DAT ERROR";

void __cdecl Rva0002F720(const char *key, const char *value)
{
    const char *k = key;
    int (__cdecl *compare)(const char *, const char *) = _strcmpi;
    if (compare(k, "SkuName") == 0)
    {
        g_SkuNameValue = value;
        return;
    }
    if (compare(k, "GameName") == 0)
    {
        g_GameNameValue = value;
        return;
    }
    if (compare(k, "GameRegPath") == 0)
    {
        g_GameRegPathValue = value;
        return;
    }
    if (compare(k, "InstallerRegPath") == 0)
    {
        g_InstallerRegPathValue = value;
        return;
    }
    if (compare(k, "OnlineServer") == 0)
    {
        g_OnlineServerValue = value;
        return;
    }
    if (compare(k, "UserDataLeafName") == 0)
    {
        g_UserDataLeafNameValue = value;
        return;
    }
    if (compare(k, "G1") == 0)
    {
        g_G1Value = value;
        return;
    }
    if (compare(k, "G2") == 0)
    {
        g_G2Value = value;
        return;
    }
    if (compare(k, "G3") == 0)
    {
        g_G3Value = value;
        return;
    }
    if (compare(k, "G4") == 0)
    {
        g_G4Value = value;
        return;
    }
}

// Once-flag for the cached registry block below. The ten lazy getters share
// it with the block loader at 0x0002F840 (pinned, not yet converted): the
// first getter through the gate loads the block, the rest use the cache.
bool g_registryValuesLoaded;

void LoadRegistryValues();

// ?GetRegistrySkuName@@YAPBDXZ, retail 0x0002F9C0, 27 bytes.
// Lazy SkuName reader: loads the registry block on first use, then returns
// the cached SkuName pointer the dispatcher stored at 0x00DA7578.
const char *GetRegistrySkuName()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_SkuNameValue;
}

// ?GetRegistryGameName@@YAPBDXZ, retail 0x0002F9E0, 27 bytes.
// Lazy GameName reader: same once-gate, cached pointer at 0x00DA757C.
// Called from bfmeGetMainWindowTitle in WinMain.cpp.
const char *GetRegistryGameName()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_GameNameValue;
}

// ?GetRegistryGameRegPath@@YAPBDXZ, retail 0x0002FA00, 27 bytes.
// Lazy GameRegPath reader: same once-gate, cached pointer at 0x00DA7580.
const char *GetRegistryGameRegPath()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_GameRegPathValue;
}

// ?GetRegistryInstallerRegPath@@YAPBDXZ, retail 0x0002FA20, 27 bytes.
// Lazy InstallerRegPath reader: same once-gate, cached pointer at 0x00DA7584.
// Called from bfmeGetMainWindowTitle in WinMain.cpp.
const char *GetRegistryInstallerRegPath()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_InstallerRegPathValue;
}

// ?GetRegistryOnlineServer@@YAPBDXZ, retail 0x0002FA40, 27 bytes.
// Lazy OnlineServer reader: same once-gate, cached pointer at 0x00DA7588.
const char *GetRegistryOnlineServer()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_OnlineServerValue;
}

// ?GetRegistryUserDataLeafName@@YAPBDXZ, retail 0x0002FA60, 27 bytes.
// Lazy UserDataLeafName reader: same once-gate, cached pointer at 0x00DA758C.
const char *GetRegistryUserDataLeafName()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_UserDataLeafNameValue;
}

// ?GetRegistryG1@@YAPBDXZ, retail 0x0002FA80, 27 bytes.
// Lazy G1 reader: same once-gate, cached pointer at 0x00DA7590.
const char *GetRegistryG1()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_G1Value;
}

// ?GetRegistryG2@@YAPBDXZ, retail 0x0002FAA0, 27 bytes.
// Lazy G2 reader: same once-gate, cached pointer at 0x00DA7594.
const char *GetRegistryG2()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_G2Value;
}

// ?GetRegistryG3@@YAPBDXZ, retail 0x0002FAC0, 27 bytes.
// Lazy G3 reader: same once-gate, cached pointer at 0x00DA7598.
const char *GetRegistryG3()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_G3Value;
}

// ?GetRegistryG4@@YAPBDXZ, retail 0x0002FAE0, 27 bytes.
// Lazy G4 reader: same once-gate, cached pointer at 0x00DA759C.
const char *GetRegistryG4()
{
    if (!g_registryValuesLoaded)
    {
        g_registryValuesLoaded = true;
        LoadRegistryValues();
    }
    return g_G4Value;
}
