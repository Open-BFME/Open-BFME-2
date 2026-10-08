// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00438144Update@@YAXPBVObject@@PAE@Z @0x00438144 34B
// Cached Object predicate helper. Evidence: free-function via two stack
// args plus ret (no ret-N, __cdecl); arg1 in ecx to rowed Object
// rva0028C1CC 0x0028C1CC (Object owner proven); arg2 byte flag read plus
// 0-or-1 store; no callers; name stays address-derived.
class Object
{
public:
	bool rva0028C1CC() const;
	class Player *getControllingPlayer() const;
};

void Rva00438144Update(const Object *obj, unsigned char *flag)
{
	int value;
	if (*flag != 0)
		goto set_one;
	if (!obj->rva0028C1CC())
	{
		value = 0;
		goto store;
	}
set_one:
	value = 1;
store:
	*flag = (unsigned char)value;
}

//
// ?Rva004381C4Iterate@@YGXPBVObject@@@Z, retail 0x004381C4, 88 bytes.
// Free __stdcall with one Object* arg (ret 4). Loops players via global
// 0x009FEEE8 (+0x14 count, getNthPlayer rowed), skips null, gets arg's
// controlling player (rowed) plus its Team +0x2EC, keeps enemy (relationship
// rowed ==0) players and iterateObjects (pin) each with callback plus arg.
// Caller 0x438C81. Same TU/flags as neighbour. Honest address name.
class Player;
class Team;
enum Relationship
{
	Rel_Zero = 0
};
class PlayerList
{
public:
	Player *getNthPlayer(int i);
private:
	char m_pad00[0x14];
public:
	int m_count14;
};
extern PlayerList *ThePlayerList;
class Player
{
public:
	typedef int (*ObjectIterateFunc)(Object *, void *);
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
	Relationship getRelationship(const Team *team) const;
};
class Team
{
public:
	char m_pad[0x2EC];
};
#define ThePlayerList004381C4 ThePlayerList
void Rva00373DBEIterateCallback(Object *obj, void *userData);
void __stdcall Rva004381C4Iterate(const Object *obj);

void __stdcall Rva004381C4Iterate(const Object *obj)
{
	int n = ThePlayerList004381C4->m_count14;
	for (int i = 0; i < n; ++i)
	{
		Player *player = ThePlayerList004381C4->getNthPlayer(i);
		if (player == 0)
			continue;
		Player *ctrl = obj->getControllingPlayer();
		const Team *team = *(const Team *const *)((const char *)ctrl + 0x2EC);
		if (player->getRelationship(team) != Rel_Zero)
			continue;
		player->iterateObjects((int (*)(Object *, void *))Rva00373DBEIterateCallback, (void *)obj);
	}
}
