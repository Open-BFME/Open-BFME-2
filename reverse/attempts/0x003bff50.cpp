// ?Rva003BFF50Do@@YGXPBVAsciiString@@HPAVRGBColor@@@Z
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003BFF50Do@@YGXPBVAsciiString@@HPAVRGBColor@@@Z @0x003BFF50 156B.
// Team drawable tint loop: team-name copy, getTeamNamed, rowed Team
// hasAnyObjects(false), member loop (rowed iterate 0x00263864 plus advance
// 0x00263526) fetching each member's rowed Object::getDrawable, scaling
// (g_00DBA4E4 * mult) / g_00E02D9C, then storing either the member's rowed
// getIndicatorColor or the override RGBColor's rowed getAsInt (thiscall
// reuses the tested pointer, proving the override type) plus the scaled
// value into the drawable. Globals/override semantics unproven.
#include "ascii_string.h"

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Drawable
{
public:
	char m_pad[0x168];
	int m_168;
	int m_16c;
};

class Object
{
public:
	Drawable *getDrawable() const;
	int getIndicatorColor() const;
};

class Team
{
public:
	bool hasAnyObjects(bool b);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class RGBColor
{
public:
	int getAsInt() const;
};

extern int g_00DBA4E4;
extern int g_00E02D9C;

void __stdcall Rva003BFF50Do(const AsciiString *teamName, int mult, RGBColor *colorOverride)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (!team)
		return;
	if (!team->hasAnyObjects(false))
		return;
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	for (Object *cur = iter.cur(); cur != 0; cur = iter.cur()) {
		iter.advance();
		Drawable *d = cur->getDrawable();
		if (d == 0)
			return;
		int v = (g_00DBA4E4 * mult) / g_00E02D9C;
		int w;
		if (colorOverride == 0)
			w = cur->getIndicatorColor();
		else
			w = colorOverride->getAsInt();
		d->m_16c = w;
		d->m_168 = v;
	}
}
