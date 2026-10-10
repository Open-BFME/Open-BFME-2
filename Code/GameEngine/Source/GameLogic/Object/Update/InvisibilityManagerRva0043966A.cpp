// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
// stlport
//
// ?rva0043966A@Rva00439E0C@@QAEHPAVObject@@PBUCoord3D@@PAURva004393D6@@PAURva004389DBInfo@@@Z,
// retail 0x0043966A (307 bytes); called from the per-object update
// 0x0043979D (Rva0043979DUpdate.cpp) with the object, its position, the
// object's detection record and a cleared Rva004389DBInfo.  Receiver is
// TheGameLogic's +0x178 manager (WorldBuilder's InvisibilityManager, see
// InvisibilityManagerRva004389DB.cpp).  WorldBuilder twin 0x012809A0 is
// unnamed (callgraph lead) and agrees on every branch.
//
// Target evidence: the record is the STLport list of 196-byte entries
// (Rva004393D6Copy.cpp) plus three words; its +0x04 and +0x0C words are
// forwarded to the per-entry check 0x00439428.  First the expired entries
// are dropped (0x0043888E); then each entry's active byte (+0xC0) is
// recomputed from its start/duration window (+0xB8 + +0xBC against the
// logic frame) and the per-entry check.  An entry that stays active with a
// zero +0x18 word ends the walk (returns 0, handing a fresh entry's +0xA0 to
// the info); a newly inactive entry merges its +0xA4 word, flag bits
// (+0x9C: 2 info+4, 4 clear window, 8 info+0x20), detector id and +0xA8
// 128-bit mask into the info.  Field names are neutral.
#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include <bitset>

extern GameLogic *TheGameLogic;

struct Rva004393D6Entry
{
	char m_pad00[0x18];
	int m_18;	// +0x18
	char m_pad1c[0x9C - 0x1C];
	unsigned int m_flags;	// +0x9C
	int m_a0;	// +0xA0
	int m_a4;	// +0xA4
	_STL::bitset<128> m_mask;	// +0xA8
	unsigned int m_start;	// +0xB8
	unsigned int m_duration;	// +0xBC
	bool m_active;	// +0xC0
};

struct Rva004393D6Node
{
	Rva004393D6Node *m_next;
	Rva004393D6Node *m_prev;
	Rva004393D6Entry m_entry;
};

struct Rva004393D6
{
	Rva004393D6Node *m_node;
	int m_04;
	int m_08;
	int m_0c;
};

struct Rva004389DBInfo
{
	Object *m_detector;	// +0x00
	bool m_04;	// +0x04
	int m_08;	// +0x08
	int m_0c;	// +0x0C
	_STL::bitset<128> m_mask;	// +0x10
	bool m_20;	// +0x20
};

class Rva00439E0C
{
public:
	int rva0043966A(Object *obj, const Coord3D *pos, Rva004393D6 *record, Rva004389DBInfo *info);
	void rva0043888E(Rva004393D6 *record);
	bool rva00439428(Object *obj, const Coord3D *pos, Rva004393D6Entry *entry, int a, int b, ObjectID *id);
};

int Rva00439E0C::rva0043966A(Object *obj, const Coord3D *pos, Rva004393D6 *record, Rva004389DBInfo *info)
{
	rva0043888E(record);
	int result = 2;
	for (Rva004393D6Node *node = record->m_node->m_next; node != record->m_node; node = node->m_next)
	{
		bool wasActive = node->m_entry.m_active;
		ObjectID id = INVALID_OBJECT_ID;
		node->m_entry.m_active = TheGameLogic->getFrame() <= node->m_entry.m_start + node->m_entry.m_duration
			&& rva00439428(obj, pos, &node->m_entry, record->m_0c, record->m_04, &id);
		if (node->m_entry.m_active)
		{
			if (node->m_entry.m_18 == 0)
			{
				if (!wasActive && node->m_entry.m_a0 != 0 && info->m_08 == 0)
					info->m_08 = node->m_entry.m_a0;
				return 0;
			}
			result = 1;
		}
		else if (wasActive)
		{
			if (node->m_entry.m_flags & 4)
			{
				node->m_entry.m_start = 0;
				node->m_entry.m_duration = 0;
			}
			if (node->m_entry.m_flags & 8)
				info->m_20 = true;
			if (id != INVALID_OBJECT_ID)
			{
				if (node->m_entry.m_flags & 2)
					info->m_04 = true;
				if (info->m_detector == 0)
					info->m_detector = TheGameLogic->findObjectByID(id);
			}
			if (node->m_entry.m_a4 != 0 && info->m_0c == 0)
				info->m_0c = node->m_entry.m_a4;
			info->m_mask |= node->m_entry.m_mask;
		}
	}
	return result;
}
