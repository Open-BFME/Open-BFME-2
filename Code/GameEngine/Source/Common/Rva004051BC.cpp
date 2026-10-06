// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// ?rva004051BC@Rva004051BC@@QAEXHPBUCoord3D@@@Z, retail 0x004051BC, 156 bytes.
// Unlock-lane body called from 0x00405258: player-index guard at this+0x2B
// stride 4 bit 0x80, ThePlayerList range query through the pinned
// ThePartitionManager float-radius overload at 0x00625610 (row
// ?bfmeForwardWideC spells the radius as int), single Rva000421C8 filter
// carrying the getNthPlayer result, then ExperienceTracker level bump
// through the pin-only 0x0039B4EC for each hit whose +0x264 tracker is
// present. The row's int radius and void* next are noted here and the
// float/Object spellings are used as the bytes require. Evidence: caller
// 0x004052F7, prev/next // cl:, ThePlayerList/ThePartitionManager pins,
// vtable-free QAE naming with ret 8.

class Player;
class PlayerList;
class ExperienceTracker;
class Rva000421C8;
class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
};
extern PlayerList *ThePlayerList;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(void *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class Rva004051BCFilter : public Rva000421C8
{
public:
	Rva004051BCFilter(Player *player) : m_player(player) {}
	virtual bool allow(void *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

struct BfmeWideResult
{
	Object *next(); // pin 0x00045623; row ?bfmeGoEOF spells void*
	~BfmeWideResult(); // 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int a,
		Rva000421C8 *filter, int b); // pin 0x00625610; row spells radius as int
};
extern PartitionManager *ThePartitionManager;

class ExperienceTracker
{
public:
	bool rva0039B4EC(int levels, bool flag1, bool flag2); // 0x0039B4EC pin-only
};

class Object
{
public:
	char m_pad00[0x264];
	ExperienceTracker *m_tracker264; // +0x264
};

struct Rva004051BCEntry
{
	unsigned char flag;
	char pad[3];
};

class Rva004051BC
{
public:
	void rva004051BC(int playerIndex, const Coord3D *pos);
private:
	char m_pad00[0x20];
	float m_radius20; // +0x20
	char m_pad24[0x2B - 0x24];
	Rva004051BCEntry m_guards[8]; // +0x2B stride 4, bit 0x80 skips
};

void Rva004051BC::rva004051BC(int playerIndex, const Coord3D *pos)
{
	if ((m_guards[playerIndex].flag & 0x80) != 0)
		return;
	Player *player = ThePlayerList->getNthPlayer(playerIndex);
	Rva004051BCFilter filter(player);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos, m_radius20, 1, &filter, 0);
	for (Object *other = hits.next(); other != 0; other = hits.next()) {
		ExperienceTracker *tracker = other->m_tracker264;
		if (tracker == 0)
			continue;
		tracker->rva0039B4EC(1, true, false);
	}
}
