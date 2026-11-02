/* Target facts (BFME2 game.dat, RVAs unless marked VA): constructors 0x00380C4E (96 bytes) and 0x00380D30 (79 bytes) store no vptr or vbptr; MultiplayerColorDefinition has no virtual functions or vtable. The default constructor zeros its first word at 0x00380C63 and calls StringBase<char>::releaseBuffer (0x00036410) at 0x00380C6B; the copy calls the string copy worker 0x000365F0 at 0x00380D3B. The nonvirtual destructor 0x0048BA39 (5 bytes) tail-jumps to 0x00036410. These are string-member operations, not constructor/destructor vtable stores; the implicit destructor preserves that cleanup. Zero Hour's plain class declaration has no bases.
The copy constructor 0x00380D30 and assignment 0x00380CAE copy 12-byte RGBColor members at +0x04, +0x14, +0x24 and +0x30, 4-byte integers at +0x10 and +0x20 and a byte at +0x3C. Tree-node construction 0x00380EE6 allocates 0x54 bytes at 0x00380EE9, constructs the pair at node+0x10 (0x00380EF6), and the pair constructors 0x00380DA3 and 0x00380DEA construct this value at pair+4: sizeof 0x40 with 4-byte alignment. FieldParse VA 0x00C18F40 has TooltipName at +0, RGBColor at +4, RGBNightColor at +0x14, LivingWorldColor at +0x24, LivingWorldBannerColor at +0x30 and AvailableInWotR at +0x3C, followed by its null entry at VA 0x00C18FA0; the last three member spellings remain neutral.
The setters 0x00380C1E and 0x00380C36 pass a 12-byte RGBColor to getAsInt (0x00004EA7), set alpha bits 0xFF000000 and store +0x10 and +0x20. RGB getters 0x001EF34E and 0x00098516 copy +4 and +0x14; INI::parseMultiplayerColorDefinition (0x001EF3BF) inlines both copies at 0x001EF437 and 0x001EF449 before calling the setters. Assignment calls getTooltipName (0x002E4336) at 0x00380CC7; pair constructors call the copy at 0x00380DB5 and 0x00380DFC, so these methods stay out of line. The table getter 0x001EF348 returns VA 0x00C18F40. Names and the inline scalar and RGB accessors follow Zero Hour GeneralsMD Common/MultiplayerSettings.h; target accesses establish the BFME2 offsets. */

#pragma once
#ifndef CANONICAL_MULTIPLAYERCOLORDEFINITION_H
#define CANONICAL_MULTIPLAYERCOLORDEFINITION_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"

struct FieldParse;

class MultiplayerColorDefinition
{
public:
    MultiplayerColorDefinition();
    MultiplayerColorDefinition(const MultiplayerColorDefinition &other);
    MultiplayerColorDefinition *operator=(const MultiplayerColorDefinition &other);

    static const FieldParse m_colorFieldParseTable[];
    const FieldParse *getFieldParse() const { return m_colorFieldParseTable; }
    AsciiString getTooltipName() const;
    RGBColor getRGBValue() const { return m_rgbValue; }
    RGBColor getRGBNightValue() const { return m_rgbValueNight; }
    int getColor() const { return m_color; }
    int getNightColor() const { return m_colorNight; }
    void setColor(RGBColor rgb);
    void setNightColor(RGBColor rgb);

    AsciiString m_tooltipName; // +0x00
    RGBColor m_rgbValue; // +0x04
    int m_color; // +0x10
    RGBColor m_rgbValueNight; // +0x14
    int m_colorNight; // +0x20
    RGBColor m_rgbExtra1; // +0x24
    RGBColor m_rgbExtra2; // +0x30
    bool m_extraFlag; // +0x3C
};

#endif
