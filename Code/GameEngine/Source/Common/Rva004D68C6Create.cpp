// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva004D68C6@Rva004D68C6@@QAEPAVGameMessage@@XZ @0x004D68C6 (443B):
// Builds a GameMessage from slot descriptor: validates GameInfo slot,
// resolves player via NameKeyGenerator and PlayerList, allocates
// Rva0030F47A (GameMessage) with +0x24 type, stamps +0x14 from Player+0x54,
// appends typed args from +0x28 list. Evidence: callees getSlot 0x003FF29F,
// nameToKey 0x0009FA65, findPlayerWithNameKey 0x002A7A41, ctor 0x0030F47A,
// append* GameMessage rows; callers 0x0025E5F4 etc; chain unlock of 0x0030F47A.

void *__cdecl operator new(unsigned int) throw();

#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameSlot
{
public:
	char m_pad00[0x34];
	AsciiString m_name;
};

class GameInfo
{
public:
	GameSlot *getSlot(int idx);
};
extern GameInfo *TheGameInfo;

class Player
{
public:
	char m_pad00[0x54];
	void *m_54;
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};
extern PlayerList *ThePlayerList;


enum ObjectID
{
	OBJECTID_INVALID = 0
};

enum DrawableID
{
	DRAWABLEID_INVALID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	int x;
	int y;
	int w;
	int h;
};

class GameMessage
{
public:
	void appendIntegerArgument(int v);
	void appendRealArgument(float v);
	void appendBooleanArgument(bool v);
	void appendObjectIDArgument(ObjectID v);
	void appendDrawableIDArgument(DrawableID v);
	void appendTeamIDArgument(unsigned int v);
	void appendLocationArgument(const Coord3D &v);
	void appendPixelArgument(const ICoord2D &v);
	void appendPixelRegionArgument(const IRegion2D &v);
	void appendTimestampArgument(unsigned int v);
	void appendWideCharArgument(const unsigned short &v);
	char m_pad00[0x14];
	void *m_14;
	char m_pad18[0x0c];
};

class Rva0030F47A
{
public:
	Rva0030F47A(void *arg);
private:
	char m_pad[0x24];
};

struct ArgNode
{
	void *m_00;
	ArgNode *m_next;
	union
	{
		int m_int;
		float m_real;
		bool m_bool;
		ObjectID m_obj;
		DrawableID m_draw;
		unsigned int m_team;
		unsigned int m_timestamp;
		Coord3D m_loc;
		ICoord2D m_pix;
		IRegion2D m_region;
		unsigned short m_wide;
	};
	int m_type;
};

class Rva004D68C6
{
public:
	GameMessage *rva004D68C6();
private:
	char m_pad00[0x0c];
	int m_slot;
	char m_pad10[0x14];
	void *m_msgType;
	ArgNode *m_head;
};

GameMessage *Rva004D68C6::rva004D68C6()
{
	GameInfo *gi = TheGameInfo;
	if (gi == 0)
		return 0;
	if (gi->getSlot(m_slot) == 0)
		return 0;
	GameSlot *slot = TheGameInfo->getSlot(m_slot);
	NameKeyType key = TheNameKeyGenerator->nameToKey(slot->m_name);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	if (player == 0)
		return 0;
	GameMessage *msg = (GameMessage *)new Rva0030F47A(m_msgType);
	if (msg != 0)
	{
		msg->m_14 = player->m_54;
		for (ArgNode *node = m_head; node != 0; node = node->m_next)
		{
			int type = node->m_type;
			if (type == 0)
				msg->appendIntegerArgument(node->m_int);
			else if (type == 1)
				msg->appendRealArgument(node->m_real);
			else if (type == 2)
				msg->appendBooleanArgument(node->m_bool);
			else if (type == 3)
				msg->appendObjectIDArgument(node->m_obj);
			else if (type == 4)
				msg->appendDrawableIDArgument(node->m_draw);
			else if (type == 5)
				msg->appendTeamIDArgument(node->m_team);
			else if (type == 6)
			{
				Coord3D tmp;
				tmp.x = node->m_loc.x;
				tmp.y = node->m_loc.y;
				tmp.z = node->m_loc.z;
				msg->appendLocationArgument(tmp);
			}
			else if (type == 7)
			{
				ICoord2D tmp;
				tmp.x = node->m_pix.x;
				tmp.y = node->m_pix.y;
				msg->appendPixelArgument(tmp);
			}
			else if (type == 8)
				msg->appendPixelRegionArgument(node->m_region);
			else if (type == 9)
				msg->appendTimestampArgument(node->m_timestamp);
			else if (type == 10)
				msg->appendWideCharArgument(node->m_wide);
		}
	}
	return msg;
}
