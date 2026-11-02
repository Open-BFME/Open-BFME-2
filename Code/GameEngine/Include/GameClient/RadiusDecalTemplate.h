// Target facts (retail RVAs): ctor 0x00330E5D constructs AsciiStrings at +0/+4 through 0x000365F0, writes scalars at +8..+0x30 and a bool at +0x1C, and stores no vptr; RadiusDecalTemplate has no bases or virtual functions. W3DTornadoDrawModuleData ctor 0x000D16B4 places it at +8 and the next member at +0x3C, proving sizeof 0x34 together with the final +0x30 dword. No named template destructor or vftable exists in the ledger.
// Target facts (retail RVAs): assignment 0x00330CDD copies two strings, five dwords at +8..+0x18, the +0x1C byte and five dwords at +0x20..+0x30; 0x00330D3E and 0x00331578 prove the tail float/float/unsigned/float/float types. Parser 0x00330D91 uses VA 0x00C0DC20 (Texture/+0, Texture2/+4, Style/+8, OpacityMin/+0xC, OpacityMax/+0x10, OpacityThrobTime/+0x14, Color/+0x18, OnlyVisibleToOwningPlayer/+0x1C, MinRadius/+0x20, MaxRadius/+0x24, MaxSelectedUnits/+0x28, RotationsPerMinute/+0x2C, SpiralAcceleration/+0x30); 0x00330EE0 transfers the same fields.
// Target facts (retail RVAs): selection creator 0x0033121F, death creator 0x0033132D and const creator 0x00331459 establish their rowed signatures; callers 0x000B3271/0x000B508A call 0x00330CDD out of line, and that body leaves EAX holding the +0x30 word rather than returning this. Donor facts: Zero Hour GameClient/RadiusDecal.h supplies the class and seven original member names; the added fields retain neutral names. The rowed methods are declarations only.
#pragma once

#ifndef __BFME2_RADIUSDECALTEMPLATE_H_
#define __BFME2_RADIUSDECALTEMPLATE_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct Coord3D;
class INI;
class Player;
class RadiusDecal;
class Xfer;

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	void rva00330CDD(const RadiusDecalTemplate &other);
	float rva00330D3E(unsigned int index);
	bool rva00331578(const RadiusDecalTemplate &other) const;
	void xferRadiusDecalTemplate(Xfer *xfer);
	void createSelectionRadiusDecal(Coord3D pos, unsigned int selected, int color, RadiusDecal *out, float scale);
	void createDeathDecal(const Coord3D *pos, float angle, const unsigned int *color, RadiusDecal *out);
	void createRadiusDecal(const Coord3D &pos, float radius, const Player *player, RadiusDecal &out) const;
	static void parseRadiusDecalTemplate(INI *ini, void *instance, void *store, const void *userData);

	AsciiString m_name;
	AsciiString m_secondName;
	int m_shadowType;
	float m_minOpacity;
	float m_maxOpacity;
	float m_opacityThrobTime;
	int m_color;
	bool m_onlyVisibleToOwningPlayer;
	float m_unmodelled20;
	float m_unmodelled24;
	unsigned int m_unmodelled28;
	float m_unmodelled2C;
	float m_unmodelled30;
};

#endif
