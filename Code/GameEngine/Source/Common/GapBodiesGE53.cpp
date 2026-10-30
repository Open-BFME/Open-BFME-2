// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (fifty-third
// batch; see GapBodiesGE01.cpp), all from the /O1 /arch:SSE /G7 retail region
// that starts at 0x001D8E99 (reverse/retail_inventory/flag_regions.csv). Each
// begins after its neighbour's padding or ret and ends in its own ret or tail
// jump. Retail bytes establish every shape; owning classes are not
// recovered, so each keeps an address-derived name and a view of only the
// members it touches. Callees and globals use the ledger's existing
// spellings.

class INI;

// --- 0x001FE300 (18B): copy construction through the rowed assignment
// Rva000427195::operator= 0x001FDEBC.
struct Rva000427195
{
	Rva000427195(const Rva000427195 &that);
	Rva000427195 &operator=(const Rva000427195 &that);
};

Rva000427195::Rva000427195(const Rva000427195 &that)
{
	*this = that;
}

// --- 0x001FF547 (24B): push a block onto the free list of the pool at VA
// 0x00DB9440 (its free-node head m_head, VA 0x00DB9448); 0x001FF6EB (24B):
// pop one element from that pool through the rowed 0x002EB448.
#include "../../Include/Common/Rva002E8548Pool.h"

class Rva002EB448
{
public:
	void *rva002EB448();									// 0x002EB448
};

class Rva001FF547
{
public:
	void deallocate(void *block, unsigned int n);
	void *allocate(unsigned int n, const void *hint);
};

void Rva001FF547::deallocate(void *block, unsigned int n)
{
	if (block)
	{
		Rva002E8548 &pool = g_Va00DB9440;
		*(void **)block = pool.m_head;
		pool.m_head = block;
	}
}

void *Rva001FF547::allocate(unsigned int n, const void *hint)
{
	if (n > 1)
		return 0;
	return ((Rva002EB448 *)&g_Va00DB9440)->rva002EB448();
}

// --- 0x00201D34 / 0x00201D3E (10B each): store the 0x00DB5FA0 word / the
// 0x00DEC410 byte.
extern int LODTextureReduction;
extern unsigned char LODMeshCacheSetting;

void setLODTextureReduction(int value)
{
	LODTextureReduction = value;
}

void setLODMeshCacheSetting(unsigned char value)
{
	LODMeshCacheSetting = value;
}

// --- 0x00201DAA (26B): an INI field parser indexing rva00202B6CNames
// through the rowed INI::parseIndexList.
class INI
{
public:
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
};

extern const char *rva00202B6CNames[];

void rva00201DAA(INI *ini, void *instance, void *store, const void *userData)
{
	INI::parseIndexList(ini, instance, store, rva00202B6CNames);
}

// --- 0x0020E312 (17B): the negation of the rowed 0x002E071E test.
class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;	// 0x002E071E
	bool rva0020E312(const Rva002E071E *other) const;
	int rva002E0BC0(int id);							// 0x002E0BC0
	bool rva0020E301(int id);
};

// --- 0x0020E301 (17B): the negation of the rowed 0x002E0BC0 id test. That
// row is spelled int but its callers read only AL, so the byte is negated.
bool Rva002E071E::rva0020E301(int id)
{
	return !(unsigned char)rva002E0BC0(id);
}

bool Rva002E071E::rva0020E312(const Rva002E071E *other) const
{
	return !rva002E071E(other);
}

// --- 0x0020E384 (7B): pre-increment the +0x30 counter.
class Rva0020E384
{
public:
	int rva0020E384();
private:
	char m_pad00[0x30];
	int m_30;
};

int Rva0020E384::rva0020E384()
{
	return ++m_30;
}

// --- 0x0020E3D6 (25B): hand a value to TheLivingWorldLogic's current item
// (rowed 0x002B2B2D then 0x003F15A1).
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva002B3740Item;

class Rva002BA8F1Logic
{
public:
	Rva002B3740Item *rva002B2B2D();							// 0x002B2B2D
};

class Rva003F15A1
{
public:
	void rva003F15A1(void *value);							// 0x003F15A1
};

class Rva0020E3D6
{
public:
	void rva0020E3D6(void *value);
};

void Rva0020E3D6::rva0020E3D6(void *value)
{
	Rva002B3740Item *item = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B2B2D();
	if (item)
		((Rva003F15A1 *)item)->rva003F15A1(value);
}

// --- 0x00210E7C (33B): forward a value to the record g_00DFEF18 finds for a
// key (rowed 0x002BFDAE then 0x003FA7D3); 0x00210E9D (15B): toggle the
// +0x2C8 flag.
class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

class LivingWorld
{
public:
	void *FindClickableObject(void *key);							// 0x002BFDAE
};

class Rva003FA835
{
public:
	void rva003FA7D3(int value);							// 0x003FA7D3
};

class Rva00210E7C
{
public:
	void rva00210E7C(void *key, int value);
	void rva00210E9D();
private:
	char m_pad00[0x2C8];
	bool m_2C8;
};

void Rva00210E7C::rva00210E7C(void *key, int value)
{
	void *record = ((LivingWorld *)((Rva002D3627Host *)TheLivingWorld))->FindClickableObject(key);
	if (record)
		((Rva003FA835 *)record)->rva003FA7D3(value);
}

void Rva00210E7C::rva00210E9D()
{
	bool &flag = m_2C8;
	flag = !flag;
}

// --- 0x0021674F (19B): construct from a by-value DelegateDesc through the
// rowed 0x002165B0 setter.
struct DelegateDesc
{
	int m_00;
	int m_04;
};

class Rva002165B0
{
public:
	Rva002165B0(DelegateDesc desc);
	Rva002165B0 &rva002165B0(const DelegateDesc *desc);	// 0x002165B0
};

Rva002165B0::Rva002165B0(DelegateDesc desc)
{
	rva002165B0(&desc);
}
