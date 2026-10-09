// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00372DFA@MineshaftPortalBehaviour@@QAEPAVWaypoint@@PBUCoord3D@@@Z,
// retail 0x00372DFA..0x00372ED3 (217B), thiscall ret 4.
//
// Allocates the portal's private Waypoint (0xC0 bytes): id 0x7FFFFFFE, name
// "#mineshaftportal_wp", the given location, three empty labels, not
// bi-directional, 8 and an empty trailing name (rowed
// ??0Waypoint@@QAE@IVAsciiString@@PBUCoord3D@@000_NH0@Z 0x00282212). The
// waypoint then takes the object's +0x74 word at +0xB0 and the module data's
// +0x118 / +0x119 bytes at +0xA8 / +0xA9, and its +0x48 byte is cleared.
//
// Evidence (target): the only caller is MineshaftPortalBehaviour::createWaypoint
// (unrowed 0x003738F6; WorldBuilder twin 0xF3CD30 carries that name) at
// 0x003739E9 with ecx = the behaviour and the result stored at +0x34.
// WorldBuilder twin 0xF3D100 (strings lead) reads the +0x04 module data
// into a local before the new. The string literal is at 0x00817D9C; the
// labels copy AsciiString::TheEmptyString (0x009E0878). Field names stay
// address-derived.
#include "ascii_string.h"

struct Coord3D;

class Waypoint
{
public:
	Waypoint(unsigned int id, AsciiString name, const Coord3D *pLoc, AsciiString label1,
		AsciiString label2, AsciiString label3, bool biDirectional, int bfmeType, AsciiString bfmeName);

	unsigned char m_pad00[0x48];
	unsigned char m_48;		// +0x48
	unsigned char m_pad49[0xA8 - 0x49];
	unsigned char m_A8;		// +0xA8
	unsigned char m_A9;		// +0xA9
	unsigned char m_padAA[0xB0 - 0xAA];
	int m_B0;			// +0xB0
	unsigned char m_padB4[0xC0 - 0xB4];
};

struct MineshaftPortalBehaviourModuleData
{
	unsigned char m_pad00[0x118];
	unsigned char m_118;		// +0x118
	unsigned char m_119;		// +0x119
};

struct Rva00372DFAObject
{
	unsigned char m_pad00[0x74];
	int m_74;			// +0x74
};

class MineshaftPortalBehaviour
{
public:
	Waypoint *rva00372DFA(const Coord3D *pos);

private:
	void *m_vtbl;
	const MineshaftPortalBehaviourModuleData *m_moduleData;	// +0x04
	Rva00372DFAObject *m_object;				// +0x08
};

Waypoint *MineshaftPortalBehaviour::rva00372DFA(const Coord3D *pos)
{
	const MineshaftPortalBehaviourModuleData *data = m_moduleData;
	Waypoint *wp = new Waypoint(0x7FFFFFFE, AsciiString("#mineshaftportal_wp"), pos,
		AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString,
		false, 8, AsciiString::TheEmptyString);
	wp->m_B0 = m_object->m_74;
	wp->m_A8 = data->m_118;
	wp->m_A9 = data->m_119;
	wp->m_48 = 0;
	return wp;
}
