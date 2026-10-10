// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
//
// ?rva004E7E3A@ResourceEntryOwner@@QAEXXZ, retail 0x004e7e3a, 232 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <list>
#include "ascii_string.h"

class Rva004E7A76
{
public:
	void rva004E7A76();
};

struct Rva004E7E3AEntry
{
	int m_key;
	int m_04;
	void *m_ref;
	~Rva004E7E3AEntry() { reinterpret_cast<Rva004E7A76 *>(this)->rva004E7A76(); }
};

class Rva004E7B13
{
public:
	unsigned int rva004E7D29(const int &key);
private:
	void *head;
	int count;
};

class Cb00359D42
{
public:
	virtual void cb(int id, float val, char b);
	~Cb00359D42() {}
};

class Rva004E7E3AClaimantCallback : public Cb00359D42
{
public:
	Rva004E7E3AClaimantCallback(void *owner, _STL::list<Rva004E7E3AEntry> *entries)
		: m_owner(owner), m_entries(entries) {}
	virtual void cb(int id, float val, char b);
	~Rva004E7E3AClaimantCallback() {}
private:
	void *m_owner;
	_STL::list<Rva004E7E3AEntry> *m_entries;
};

class TerrainResourceManager
{
public:
	void enumerateRegisteredClaimants(int playerMask, Cb00359D42 *callback);
};

class GameLogicView
{
public:
	char m_pad[0x170];
	TerrainResourceManager *m_resources;
};
class GameLogic;
extern GameLogic *TheGameLogic;

class Player
{
public:
	char m_pad[0x54];
	int m_index;
};
class PlayerList
{
public:
	int getPlayersWithRelationship(int srcPlayerIndex, unsigned int allowedRelationships, bool flag);
	char m_pad[0x10];
	Player *m_local;
};
extern PlayerList *ThePlayerList;

class ResourceEntryOwner
{
public:
	void rva004E7E3A();
private:
	char unknown00[4];
	int users;
	AsciiString name;
	_STL::list<Rva004E7E3AEntry> list;
	Rva004E7B13 tree;
};

void ResourceEntryOwner::rva004E7E3A()
{
	if (users > 0 && !name.isEmpty())
	{
		_STL::list<Rva004E7E3AEntry> pending;
		pending.swap(list);
		GameLogicView *logic = reinterpret_cast<GameLogicView *>(TheGameLogic);
		if (logic)
		{
			TerrainResourceManager *resources = logic->m_resources;
			if (resources)
			{
				Rva004E7E3AClaimantCallback callback(this, &pending);
				int mask = 0;
				if (ThePlayerList && ThePlayerList->m_local)
				{
					int index = ThePlayerList->m_local->m_index;
					mask = ThePlayerList->getPlayersWithRelationship(index, 3, false);
				}
				resources->enumerateRegisteredClaimants(mask, &callback);
			}
		}
		while (!pending.empty())
		{
			tree.rva004E7D29(pending.back().m_key);
			pending.pop_back();
		}
	}
}

// ?rva004E7F22@Rva004E7F22Owner@@QAEXXZ @0x004E7F22 7B, directly after
// rva004E7E3A: forwards to the ResourceEntryOwner held at +0. Owner and name
// are address-derived.
class Rva004E7F22Owner
{
public:
	void rva004E7F22();
private:
	ResourceEntryOwner *m_owner00;
};

void Rva004E7F22Owner::rva004E7F22()
{
	m_owner00->rva004E7E3A();
}
