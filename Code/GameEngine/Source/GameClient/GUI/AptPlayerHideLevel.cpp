// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
//
// ?rva0022277D@Rva00222A8BTarget@@QAE_NH@Z retail 0x0022277D, 98 B.
// WorldBuilder names it AptPlayer::HideLevel (AptPlayer.cpp); the callers
// spell the Apt player as the Rva00222A8BTarget placeholder. Target
// evidence: levels 0..13 only (unsigned compare); clears the mouse tooltip
// (TheMouse 0x001EEA6D with a copy of UnicodeString::TheEmptyString, 0,
// null and 1.0f); unloads the level through 0x00222481 (WB
// AptPlayer::UnloadLevel) when its 0x28-byte slot at +0xCC has flag bit 1,
// returning that result, else false. The bool result is AL; the level is
// an int (cmp/imul). /G7 gives retail's imul for the 0x28 stride.
#include "ascii_string.h"
#include "unicode_string.h"

struct RGBColor;

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);	// 0x001EEA6D
};
extern Mouse *TheMouse;

struct Rva0022277DLevel
{
	unsigned char m_pad00[0x24];
	unsigned int m_flags;			// +0x24, bit 1: loaded
};

class Rva00222A8BTarget
{
public:
	bool rva0022277D(int level);
	bool UnloadLevel(int level);		// 0x00222481

private:
	unsigned char m_pad[0xCC];
	Rva0022277DLevel m_levels[14];		// +0xCC
};

bool Rva00222A8BTarget::rva0022277D(int level)
{
	if ((unsigned int)level >= 14)
		return false;
	Rva0022277DLevel *entry = &m_levels[level];
	if (TheMouse)
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, 0, 0, 1.0f);
	if ((entry->m_flags & 2) == 0)
		return false;
	return UnloadLevel(level);
}

class Rva000427195
{
public:
	int rva00223429(const AsciiString *name);	// 0x00223429
};

class Rva0022494F
{
public:
	void rva0022494F();				// 0x0022494F
};

struct Rva00224B7DLevel
{
	unsigned char m_pad00[0xC];
	int m_movie;					// +0x0C, -1 when empty
	unsigned char m_pad10[0x24 - 0x10];
	unsigned int m_flags;				// +0x24, bit 1: loaded
};

// ?method@Rva00224B7DTarget@@QAE_NH@Z retail 0x00224B7D, 76 B: WorldBuilder's
// AptPlayer::RemoveLevel, under the pin name its callers use (they spell the
// player Rva00224B7DTarget). Levels 0..13 only; an empty slot (+0x0C == -1)
// gives false; a loaded one (flag bit 1) is unloaded first through
// 0x00222481; then the level's name leaves the player's name list at +0x5C
// (rowed 0x00223429) and the slot is reset (rowed 0x0022494F); true.
class Rva00224B7DTarget
{
public:
	bool method(int level);

private:
	unsigned char m_pad00[0x5C];
	Rva000427195 m_levelNames;			// +0x5C
	unsigned char m_pad5D[0xCC - 0x5D];
	Rva00224B7DLevel m_levels[14];			// +0xCC
};

bool Rva00224B7DTarget::method(int level)
{
	if ((unsigned int)level >= 14)
		return false;
	Rva00224B7DLevel *entry = &m_levels[level];
	if (entry->m_movie == -1)
		return false;
	if (entry->m_flags & 2)
		((Rva00222A8BTarget *)this)->UnloadLevel(level);
	m_levelNames.rva00223429((const AsciiString *)entry);
	((Rva0022494F *)entry)->rva0022494F();
	return true;
}
