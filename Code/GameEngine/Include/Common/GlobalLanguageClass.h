// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x001EA9B5 calls SubsystemInterface at 0x001EA9C9, then stores 0x00BDEFC8 at 0x001EA9DA. Destructor 0x001EABAB stores the same table at 0x001EABBC and calls the base destructor at 0x001EAD57. The parent's 0x00BD77A0 stores at 0x001B4E65/0x001B4E74 belong to the base lifetime. The base occupies +0..+0x0B (byte +4, AsciiString +8), with no virtual base. GlobalLanguage is polymorphic.
// Table 0x00BDEFC8 has fourteen slots, followed by "Language" at 0x00BDF000: 0=0x001EADD4 (deleting destructor), 1=0x001EA55A (init), 2=0x001B5384 (SubsystemInterface::loadIniFilesFromLegend), 3/8/9/10/12=0x000B3FD0 (ret), 4/11=0x005CB9FF (false; ret 4), 5=0x0047A699 (false; ret), 6=0x000D43D0 (zero; ret), 7/13=0x0047A69C (ret 4). The registered parent contract names slots 3, 9 and 10 postProcessLoad, reset and update; the other unnamed inherited slots retain vslotNN spellings. No primary slots are added.
// GameEngine::init pushes 0x13C at 0x0022E645, calls operator new at 0x0022E64A and this constructor at 0x0022E65D, then registers the result against TheGlobalLanguageData (VA 0x00DFDC84) at 0x0022E684. Thus sizeof is 0x13C.
// Constructor 0x001EA9B5 builds separator strings at +0x0C/+0x10/+0x14, clears string storage +0x18/+0x1C, builds GetRegistryLanguage's result at +0x20, clears byte +0x24 and int +0x28, calls FontDesc's constructor at +0x2C through +0x128 in 0x0C strides, stores float +0x134, and constructs the list at +0x138 through 0x0035C9A6. That list constructor stores its node pointer at +0; the list's representation is retained as an opaque pointer here. Destructor 0x001EABAB destroys the list and these strings in reverse order.
// Retail field parser table VA 0x00BDEAA0 names DecimalSeparator +0x0C, ThousandSeparator +0x10, TimeMinuteToSecondSeparator +0x14, UnicodeFontName +0x18, AudioLanguage +0x20, UseHardWordWrap +0x24, MilitaryCaptionSpeed +0x28 and ResolutionFontAdjustment +0x134. Its 22 parseFontDesc entries name the font members below, in offset order; AudioSubtitleFont is +0x5C and the four HelpBox fonts occupy +0x104/+0x110/+0x11C/+0x128. The unparsed +0x1C string keeps a neutral name.
// FontDesc constructor 0x00376900 initializes AsciiString +0, int +4 and bool +8; parser 0x0037691C writes the same fields. Assignment 0x002216DD calls the string assignment and copies int +4 and byte +8. Constructor and assignment are declared out of line. Zero Hour's GameClient/FontDesc.h supplies name/size/bold; GameClient/GlobalLanguage.h supplies the shared member and method spellings, not BFME2 offsets.
// GlobalLanguage's remaining rowed methods are adjustFontSize 0x001EA40D, onGameEngineExit 0x001EA77F and static parseFontDesc 0x0037691C. Its constructor, destructor, init and these methods are declarations only, preserving retail's out-of-line calls.
#pragma once

#ifndef BFME2_COMMON_GLOBALLANGUAGECLASS_H
#define BFME2_COMMON_GLOBALLANGUAGECLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class INI;

struct FontDesc
{
    FontDesc();
    FontDesc &operator=(const FontDesc &other);

    AsciiString name;
    int size;
    bool bold;
};

class GlobalLanguage : public SubsystemInterface
{
public:
    GlobalLanguage();
    virtual ~GlobalLanguage();
    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset() {}
    virtual void update() {}
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

    int adjustFontSize(int theFontSize);
    void onGameEngineExit();
    static void parseFontDesc(INI *ini, void *instance, void *store, const void *userData);

    AsciiString m_decimalSeparator;
    AsciiString m_thousandSeparator;
    AsciiString m_timeSeparator;
    AsciiString m_unicodeFontName;
    AsciiString field01C;
    AsciiString m_audioLanguage;
    bool m_useHardWrap;
    int m_militaryCaptionSpeed;
    FontDesc m_copyrightFont;
    FontDesc m_messageFont;
    FontDesc m_militaryCaptionTitleFont;
    FontDesc m_militaryCaptionFont;
    FontDesc m_audioSubtitleFont;
    FontDesc m_superweaponCountdownNormalFont;
    FontDesc m_superweaponCountdownReadyFont;
    FontDesc m_namedTimerCountdownNormalFont;
    FontDesc m_namedTimerCountdownReadyFont;
    FontDesc m_drawableCaptionFont;
    FontDesc m_defaultWindowFont;
    FontDesc m_defaultDisplayStringFont;
    FontDesc m_tooltipFontName;
    FontDesc m_nativeDebugDisplay;
    FontDesc m_drawGroupInfoFont;
    FontDesc m_creditsTitleFont;
    FontDesc m_creditsPositionFont;
    FontDesc m_creditsNormalFont;
    FontDesc m_helpBoxNameFont;
    FontDesc m_helpBoxCostFont;
    FontDesc m_helpBoxShortcutFont;
    FontDesc m_helpBoxDescriptionFont;
    float m_resolutionFontSizeAdjustment;
    void *field138;
};

extern GlobalLanguage *TheGlobalLanguageData;

#endif
