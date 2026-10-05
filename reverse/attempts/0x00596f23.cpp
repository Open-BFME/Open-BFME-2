// ?rva00596F23@Rva00596F18@@QAEXXZ
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ?rva00596F23@Rva00596F18@@QAEXXZ @0x00596F23 210B evidence: vtable slot 5 of 0x00870B38 class Rva00596F18; layout from Rva00596FF5 plus base float +0x04; callees pin rva002A8AB1 plus rowed rva002A8F24 bucket_count rva002A8B59 get rva002A7461; globals g_secondsPerLogicFrame g_Va00BC2428 g_00BC26EC g_00BC897C g_00DFEEF8
#include "ascii_string.h"

class Player;

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

struct Rva002A8AB1Record
{
	char pad00[0x160];
	char *m_160raw;
	char pad164[8];
	int m_16C;
};

struct Rva002A8B59Data
{
	char pad00[0x4C];
	float m_4C;
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
	Rva002A8AB1Record *rva002A8AB1(void *key);
	Rva002A8B59Data *rva002A8B59(void *key);
};
extern Rva002A8F24 *g_00DFEEF8;

extern float g_secondsPerLogicFrame;
extern float g_Va00BC2428;
extern float g_00BC26EC;
extern float g_00BC897C;

class Rva002A7389
{
public:
	int get(int v);
};

class Rva002A7461
{
public:
	int rva002A7461();
};

class Rva00573F03
{
public:
	virtual ~Rva00573F03();
};

class Rva00596F18 : public Rva00573F03
{
public:
	void rva00596F23();
private:
	float m_04;
	char m_pad08[0x1C];
	int m_24;
	char m_pad28[0x3C];
	unsigned char m_64;
	char m_pad65[3];
	void *m_68;
};

// ?rva00596F23@Rva00596F18@@QAEXXZ present-unmatched
void Rva00596F18::rva00596F23()
{
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_68);
	if (rec->m_16C <= 0)
		return;
	void *obj = g_00DFEEF8->rva002A8F24((Player *)m_68);
	unsigned int count = (*(IntMap **)((char *)obj + 0xC))->bucket_count();
	if (count < 1)
		count = 1;
	Rva002A8B59Data *data = g_00DFEEF8->rva002A8B59(m_68);
	float interval = g_secondsPerLogicFrame * data->m_4C / (float)count;
	float fa = (float)((Rva002A7389 *)((char *)m_68 + 0x60))->get(0);
	float div = fa / (float)((Rva002A7461 *)((char *)m_68 + 0x60))->rva002A7461();
	float k = div * interval;
	k *= g_Va00BC2428;
	k += interval;
	float nv = m_04 + k;
	if (nv > g_00BC897C)
		nv = g_00BC897C;
	m_04 = nv;
}
