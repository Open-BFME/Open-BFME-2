// ?rva002AC43F@Player@@QAE_NPAH@Z
// partial score=0.86225 date=2026-10-09
// ?rva002AC43F@Player@@QAE_NPAH@Z
// partial score=0.97 date=2026-10-05
// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHs
//
// ?rva002AC43F@Player@@QAE_NPAH@Z @0x002AC43F (149B): find this player's
// skirmish side. Zeroes *index, then walks TheSidesList's skirmish sides
// (count at SidesList+0x7C0 read once, entries through the
// getSkirmishSideInfo bounds check at 0x002A98D1: +0x7C4, stride 0x60) and
// compares each side dict's playerName (NameKey cache 0x00DBDE24 via rowed
// get 0x00148F5E, rowed Dict::getAsciiString 0x0031359F) with the player's
// AsciiString at +0x4C through the rowed StringBase compare 0x000069D6. On a
// hit it stores the side index and returns true. ZH's SidesList keeps the
// skirmish sides after the twenty regular ones (count +0x3C, array +0x40 in
// the matched findSideInfo), which fixes the getSkirmishSideInfo identity.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();

private:
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache g_00DBDE24;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists = 0) const;

private:
	void *m_data;
};

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }

private:
	void *m_pBuildList;
	Dict m_dict;
	unsigned char m_pad[0x60 - 8];
};

class SidesList
{
public:
	int getNumSkirmishSides() const { return m_numSkirmishSides; }
	SidesInfo *getSkirmishSideInfo(int ndx);

private:
	unsigned char m_pad[0x7C0];
	int m_numSkirmishSides;
};

extern SidesList *TheSidesList;

class Player
{
public:
	bool rva002AC43F(int *index);

private:
	unsigned char m_pad[0x4C];
	AsciiString m_4c;
};

bool Player::rva002AC43F(int *index)
{
	int count = TheSidesList->getNumSkirmishSides();
	*index = 0;
	for (int i = 0; i < count; i++) {
		Dict *dict=TheSidesList->getSkirmishSideInfo(i)->getDict();
		AsciiString name=dict->getAsciiString(g_00DBDE24.get());
		if (name.compare(m_4c) == 0) {
			*index = i;
			return true;
		}
	}
	return false;
}
