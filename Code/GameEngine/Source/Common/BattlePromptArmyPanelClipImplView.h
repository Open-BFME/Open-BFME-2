#ifndef BFME2_BATTLE_PROMPT_ARMY_PANEL_CLIP_IMPL_VIEW_H
#define BFME2_BATTLE_PROMPT_ARMY_PANEL_CLIP_IMPL_VIEW_H
#include "ascii_string.h"
#include "unicode_string.h"
// Retail005FF675 initializes owner00 level04 string08 and flags3C/3D;
// the enclosing factory allocates64 bytes. Matched methods prove caches2C/30,
// eight-byte icon slots and the string-buffer name prefix used by APT calls.
// Untouched command-map prefix0C and image/cache region18 remain opaque.
// The parent interface declares only observed call ABIs, not original names.
struct BfmePod8 { int a[2]; };
class BfmePod8Vector {
public:
    void resize(unsigned int n, BfmePod8 x);
    BfmePod8 *m_begin;
    BfmePod8 *m_end;
private:
    void *m_alloc;
};
// Borrowed receiver interface: only invoked slots04/05 have known ABIs.
class BattlePromptArmyPanelClipEvents {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04(int);
    virtual void slot05(int);
};
class Image;
namespace StrategicHUD {
class BattlePromptArmyPanelMovieClip {
public:
    class Impl;
};
}
class StrategicHUD::BattlePromptArmyPanelMovieClip::Impl {
public:
    void SetUnitIconProperties(int, const Image *, int);
    void rva005FF5C0(const UnicodeString &);
    void SetUnitIconString(int, const char *, const UnicodeString &);
    void SetArmyNameString(const UnicodeString &);
    void SetUnitIconCount(int);
    void SetSelected(bool);
    void SetMouseOver(bool);
    void OnUnitIconRollOver(const char *);
    void OnUnitIconRollOut(const char *);
private:
    BattlePromptArmyPanelClipEvents *m_parent00;
    unsigned int m_level;
    AsciiString m_name08;
    char m_pad0C[12];
    char m_images18[20];
    UnicodeString m_cached2C;
    BfmePod8Vector m_icons;
    bool m_selected3C;
    bool m_over3D;
    char m_tail3E[2];
};

#endif
