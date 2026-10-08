#pragma once

// Storage view of the native MainMenuUtils statics at VA E06558..E06574.
// This groups independent statics for their existing single data owner; it
// does not assert an original application class. WB158CC80/158DAF0 and the
// complete native startOnline/MOTD/decline bodies establish each used offset.
// The first word is the pre-existing startup flag cleared by 79FB9C.
// End exactly at E06575: the DNS owner independently defines its flag there.
// Tail padding must not consume the neighbouring owner's two flag bytes.
#pragma pack(push, 1)
struct MainMenuOnlineState
{
    unsigned flags;
    bool checking;
    unsigned char padding5[3];
    int checks, run;
    bool mustDownload, cantConnect;
    unsigned char padding12[2];
    char *motd, *config;
    bool cancel;
};
#pragma pack(pop)
typedef char MainMenuOnlineStorageExtent[(sizeof(MainMenuOnlineState) == 29) ? 1 : -1];
extern MainMenuOnlineState g_mainMenuOnlineState;
