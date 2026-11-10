// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Rva003F012F::rva003F018E, retail 0x003F018E (115 B): for a living-world
// region (owner id +0x13C) owned by the given player (id +0x14), the sum of
// virtual slot 14 over the armies in its +0x170 list that have a +0x20 entry
// and are not flagged (+0x34), each entry resolved through the rowed
// 0x004E0625; 0 for any other player. Names are structural (the region
// class keeps its ledger placeholder 0x003F012F).
// Codegen: the army pointer is NOT kept in a local; each use reads the vector element
// again (m_armies[i]) as retail does between its virtual calls.
#include <vector>

class ArmyValue
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13();
	virtual int value();			// slot 14 (+0x38)
};

#include "../../Include/Common/Rva004E0625.h"

struct Rva003F018EArmy
{
	bool isActive() const { return m_entry != 0 && !m_excluded; }
	Rva004E0625 *getEntry() const { return m_entry; }
	char m_pad00[0x20];
	Rva004E0625 *m_entry;		// +0x20
	char m_pad24[0x34 - 0x24];
	bool m_excluded;			// +0x34
};

struct Rva003F018EPlayer
{
	char m_pad00[0x14];
	int m_id;					// +0x14
};

class Rva003F012F
{
public:
	int rva003F018E(Rva003F018EPlayer *player);
private:
	char m_pad000[0x13C];
	int m_ownerID;									// +0x13C
	char m_pad140[0x170 - 0x140];
	_STL::vector<Rva003F018EArmy *> m_armies;		// +0x170
};

int Rva003F012F::rva003F018E(Rva003F018EPlayer *player)
{
	if (m_ownerID != player->m_id)
		return 0;
	int total = 0;
	for (unsigned int i = 0; i < m_armies.size(); ++i)
	{
		if ((m_armies[i])->isActive())
		{
			ArmyValue *value = (ArmyValue *)(m_armies[i])->getEntry()->rva004E0625();
			if (value)
				total += value->value();
		}
	}
	return total;
}
