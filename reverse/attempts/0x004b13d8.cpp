// ?rva004B13D8@Rva004B13D8@@QAEPAVRva004DD018@@XZ
// partial score=0.84 date=2026-10-07
// ?rva004B13D8@Rva004B13D8@@QAEPAVRva004DD018@@XZ @0x004B13D8 470B.
// Walks the entry vector at +0x90. Relationship masks 3 and 4 from the
// controlling player's index become shroud cell sums at the object's
// position, then each live entry is offered those sums plus the object
// named by its slot. A set +0xB4 flag clears and the scan repeats.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct BfmePointFD;

class Player
{
public:
	unsigned char m_pad00[0x54];
	int m_playerIndex;
};

class PlayerList
{
public:
	int getPlayersWithRelationship(int srcPlayerIndex, unsigned int allowedRelationships, bool reverse);
};
extern PlayerList *ThePlayerList;

class ThingTemplate
{
public:
	char m_pad00[0x10b];
	unsigned char m_10b;
};

class ExperienceTracker
{
public:
	char m_pad00[0x24];
	int m_level;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	int rva0028B511() const;

	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_pos;
	char m_pad44[0x94 - 0x44];
	unsigned m_94;
	char m_pad98[0x264 - 0x98];
	ExperienceTracker *m_tracker;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class PartitionManager;
extern PartitionManager *TheShroudManager;

class Rva00739830
{
public:
	int rva00739830(const BfmePointFD *pt, int a, unsigned int b) const;
};
#define TheShroudManager (*(Rva00739830 **)&TheShroudManager)

struct EntryInner
{
	char m_pad00[4];
	int m_4;
	char m_pad08[4];
	int m_c;
};

class Rva004DD018
{
public:
	bool rva004DD018(void *a, void *b, Object *other);

	char m_pad00[4];
	EntryInner *m_4;
};

class ModuleData
{
public:
	char m_pad00[0x2c];
	unsigned char m_2c;
	char m_pad2d[3];
	int m_30;
};

class Rva004B13D8
{
public:
	Rva004DD018 *rva004B13D8();

private:
	char m_pad00[4];
	ModuleData *m_data;
	Object *m_8;
	char m_pad0c[0x24 - 0x0c];
	unsigned char m_bytes[0x3c];
	unsigned m_ids[7];
	char m_pad7c[0x90 - 0x7c];
	Rva004DD018 **m_begin;
	Rva004DD018 **m_end;
	char m_pad98[4];
	Rva004DD018 *m_9c;
	char m_pada0[0xb0 - 0xa0];
	int m_b0;
	int m_b4;
};

struct Rva004B13D8Frame
{
	int mine;
	Rva004DD018 **cursor;
	int level;
	int slotA;
	int slotB;
};

Rva004DD018 *Rva004B13D8::rva004B13D8()
{
	Rva004B13D8Frame frame;

restart:
	frame.slotA = 0;
	frame.slotB = 0;
	Player *player = m_8 ? m_8->getControllingPlayer() : 0;
	if (player != 0)
	{
		int index = player->m_playerIndex;
		int rel3 = ThePlayerList->getPlayersWithRelationship(index, 3, false);
		int index4 = player->m_playerIndex;
		int rel4 = ThePlayerList->getPlayersWithRelationship(index4, 4, false);
		Object *host = m_8;
		frame.slotA = TheShroudManager->rva00739830((const BfmePointFD *)&host->m_pos, 1, (unsigned int)rel4);
		host = m_8;
		frame.slotB = TheShroudManager->rva00739830((const BfmePointFD *)&host->m_pos, 1, (unsigned int)rel3);
	}

	frame.level = 0;
	ExperienceTracker *tracker = m_8->m_tracker;
	if (tracker)
		frame.level = tracker->m_level;

	for (frame.cursor = m_begin; frame.cursor != m_end; ++frame.cursor)
	{
		Rva004DD018 *entry = *frame.cursor;
		if (!entry)
			continue;

		if (entry == m_9c)
		{
			EntryInner *inner = entry->m_4;
			if (inner->m_c != 0)
			{
				int index = inner->m_4;
				Object *found = TheGameLogic->findObjectByID((ObjectID)m_ids[index]);
				if (entry->rva004DD018((void *)frame.slotA, (void *)frame.slotB, found))
					return entry;
			}
		}

		int flag = m_b4;
		int kind = entry->m_4->m_4;
		if (flag)
		{
			if (kind != m_b0)
				continue;
		}
		else if (m_bytes[kind] == 0)
		{
			continue;
		}

		if (!flag)
		{
			if (m_data->m_2c == (unsigned char)flag && frame.level >= m_data->m_30)
			{
				if (kind == 4)
					continue;
				if (kind == 5)
					continue;
				if (kind == 6)
					continue;
			}
		}

		if (kind == 6)
		{
			Object *other = TheGameLogic->findObjectByID((ObjectID)m_ids[6]);
			if (other)
			{
				unsigned char bit = (unsigned char)(other->m_94 >> 6);
				if ((other->m_template->m_10b & 2) == 0 && (bit & 1) == 0)
				{
					frame.mine = m_8->rva0028B511();
					if (frame.mine != other->rva0028B511())
						continue;
				}
			}
		}

		kind = entry->m_4->m_4;
		Object *found = TheGameLogic->findObjectByID((ObjectID)m_ids[kind]);
		if (entry->rva004DD018((void *)frame.slotA, (void *)frame.slotB, found))
			return entry;
	}

	if (m_b4)
	{
		m_b4 = 0;
		goto restart;
	}
	return 0;
}
