// cl: /Ireference/shims/bfme2_ascii /EHsc

// Evidence: retail 0x0037BA62 (53 bytes) references the string literal
// "GUI:LastReplay" -- the anchor also used by ZH's Recorder.cpp (line ~577,
// "replayName = TheGameText->fetch(\"GUI:LastReplay\");") and by the
// ReplayMenu.cpp / PopupReplay.cpp call sites that compare a replay's
// filename against TheRecorder->getLastReplayFileName() to decide whether to
// show the localized "last replay" label instead of the raw file name.
//
// The retail body itself is a small standalone accessor:
//   if (TheGameText) return TheGameText->fetch("GUI:LastReplay");
//   else              return UnicodeString(L"00000000");
// -- TheGameText's storage VA (0xDFF0BC) and its fetch() vtable slot (+0x3C)
// are already established by the matched Code/GameEngine/Source/Common/VersionUnicode.cpp
// (see reverse/functions.csv notes for ?getUnicodeBuildTime@Version@@...).
// The L"00000000" fallback mirrors Recorder.cpp's own narrow sentinel
// (`const char *lastReplayFileName = "00000000";  // a name the user is
// unlikely to ever type, but won't cause panic & confusion`) reused here as
// a wide default when the text subsystem isn't up yet. No exact ZH source
// text exists for this specific wide-string wrapper (BFME2 addition), so it
// is named for its observable role rather than presented as a ported ZH name.

typedef unsigned short WideChar;

#include "unicode_string.h"


// Retail fetch call uses vtable offset 0x3c (see VersionUnicode.cpp for the
// slot derivation); the thirteen preceding non-destructor methods are not
// needed by this body and are left as unreconstructed placeholders.
class GameTextInterface
{
public:
    virtual ~GameTextInterface() {}
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2c() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// RecorderClass's "last replay" display name: the localized label when the
// text subsystem is available, else a safe wide-string placeholder.
UnicodeString GetLastReplayDisplayName()
{
    if (TheGameText)
        return TheGameText->fetch("GUI:LastReplay");
    return UnicodeString(L"00000000");
}
