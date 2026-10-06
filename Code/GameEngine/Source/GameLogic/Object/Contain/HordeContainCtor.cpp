// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0HordeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0046F543,
// 624 bytes. Donor: BFME 1's HordeContainConstructor.cpp (the member order
// and the grouped tail record are carried from it; BFME 2 is BFME 1 shifted
// by +0x38, then +0xB0 from the banner vector on). Target evidence: the
// body runs the rowed TransportContain ctor 0x00468559 and the implicit ctor
// of the all-_purecall interface at +0x11C (vtable 0x008448B8), then stores
// the eleven vtables the rowed dtor 0x0046F901 restores (0x00845050 primary,
// slot 0 the rowed ??_GHordeContain 0x004704C8). Its members, in the dtor's
// teardown order: the 0x4C-byte bulk-zero member at +0x124 (rowed ctor
// 0x00042526), the ObjectID set at +0x170 (set ctor 0x000D3A71, the dtor's
// Rva002EE9B7 spelling), the int map at +0x17C (rowed map ctor 0x0033C432),
// the 0x1C-byte record vector at +0x188 and its free-index list at +0x194
// (the slots TU's spellings; every vector is built through the ICF-folded
// empty vector base ctor 0x00211E58), the +0x1A0 tree (map ctor 0x00242F01, the
// dtor's Rva0046AB7D), the 0xA0-byte record at +0x1AC (rowed ctor
// 0x00469187), the int maps at +0x24C and +0x258 (the latter the dtor's
// Rva0046A915), the banner vector at +0x270, the vector at +0x2CC (element
// unknown; the dtor only frees its storage) and the +0x2DC bit map
// (Rva00462D35Mapped, as in the dtor). The scalar fields are zeroed except
// +0x298 (-1, BFME 1's m_1f4), +0x2A8 (100, BFME 1's damage percent) and
// +0x2E8 (true); both Coord3Ds are zeroed. Shape: the +0x27C..+0x2AC fields
// are one inlined record (its -1 store is scheduled first), the +0x2B8
// point zeroes itself on construction (address in eax), and +0x2E8..+0x308
// are assigned in the body. New in BFME 2: the
// +0x2C8 helper comes from the module data's +0x258 factory (its slot 1,
// given the contain) or, without one, is a new HordeMeleeSwarm (0x18 bytes,
// rowed ctor 0x005843DA).
#include <list>
#include <map>
#include <vector>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

class Thing;
class ModuleData;

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
protected:
	const ModuleData *getModuleData() const { return *(const ModuleData *const *)((const char *)this + 4); }
};

class TransportExtra { public: virtual void transportExtra(); };

class TransportContain : public OpenContain, public TransportExtra
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	virtual ~TransportContain();
private:
	unsigned char m_pad100[0x11C - 0x100];
};

class HordeContainInterface
{
public:
	virtual void slot0() = 0;
};

// The +0x2C8 helper.
class Rva00468FDCHelper
{
public:
	virtual void slot0();
};

class HordeMeleeSwarm : public Rva00468FDCHelper
{
public:
	HordeMeleeSwarm(void *owner);
private:
	unsigned char m_pad04[0x18 - 0x04];
};

// The module data's +0x258 helper factory.
class Rva0046F543HelperFactory
{
public:
	virtual void slot0();
	virtual Rva00468FDCHelper *create(void *owner);
};

class HordeContainModuleData
{
public:
	unsigned char m_pad000[0x258];
	Rva0046F543HelperFactory *m_helperFactory; // +0x258
};

// The 0x4C-byte bulk-zero member (rowed ctor 0x00042526).
class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	UnsignedInt m_words[0x4C / 4];
};

// The ObjectID set (set ctor 0x000D3A71).
class Rva002EE9B7
{
public:
	Rva002EE9B7();
	~Rva002EE9B7();
private:
	void *m_header;
	Int m_count;
	Int m_compare;
};

// A +0x188 record: the key the module data's +0x1B8 map is searched for.
struct Rva00472329Record
{
	Int m_key; // +0x00
	unsigned char m_pad04[0x1C - 0x04];
};

// The +0x1A0 tree (map ctor 0x00242F01).
class Rva0046AB7D
{
public:
	Rva0046AB7D();
	~Rva0046AB7D();
private:
	void *m_header;
	Int m_count;
	Int m_compare;
};

// The 0xA0-byte record at +0x1AC (rowed ctor 0x00469187).
class Rva00469187
{
public:
	Rva00469187();
private:
	unsigned char m_pad[0xA0];
};

// The +0x258 tree (map ctor 0x0033C432).
class Rva0046A915
{
public:
	Rva0046A915();
	~Rva0046A915();
private:
	void *m_header;
	Int m_count;
	Int m_compare;
};

struct Rva0046F543BannerIndexEntry;
struct Rva0046F543Element2CC;

struct Rva00462D35Mapped
{
	UnsignedInt m_bits;
};

// A Coord3D zeroed on construction.
struct Rva0046F543ZeroedCoord : public Coord3D
{
	Rva0046F543ZeroedCoord() { zeroCoord(*this); }
};

// BFME 1's grouped tail record (its +0x1E4..+0x210).
struct Rva0046F543Tail
{
	Int m_27C; // +0x27C
	Int m_280; // +0x280
	Int m_284; // +0x284
	ObjectID m_288; // +0x288
	UnsignedInt m_28C; // +0x28C
	Int m_290; // +0x290
	Bool m_294; // +0x294
	UnsignedInt m_298; // +0x298
	Int m_29C; // +0x29C
	Int m_2A0; // +0x2A0
	Bool m_2A4; // +0x2A4
	Int m_2A8; // +0x2A8
	Bool m_2AC; // +0x2AC

	__forceinline Rva0046F543Tail()
		: m_27C(0), m_280(0), m_284(0), m_288(0), m_28C(0), m_290(0), m_294(false), m_298((UnsignedInt)-1),
		  m_29C(0), m_2A0(0), m_2A4(false), m_2A8(100), m_2AC(false)
	{
	}
};

class HordeContain : public TransportContain, public HordeContainInterface
{
public:
	HordeContain(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeContain();
	virtual void slot0();
private:
	const HordeContainModuleData *getHordeContainModuleData() const { return (const HordeContainModuleData *)getModuleData(); }

	Bool m_120; // +0x120
	Bool m_121; // +0x121
	Rva0042526Member m_124; // +0x124
	Rva002EE9B7 m_170; // +0x170
	_STL::map<Int, void *> m_17C; // +0x17C
	_STL::vector<Rva00472329Record> m_188; // +0x188
	_STL::list<Int> m_194; // +0x194
	Bool m_198; // +0x198
	Int m_19C; // +0x19C
	Rva0046AB7D m_1A0; // +0x1A0
	Rva00469187 m_1AC; // +0x1AC
	_STL::map<Int, void *> m_24C; // +0x24C
	Rva0046A915 m_258; // +0x258
	Int m_264; // +0x264
	Int m_268; // +0x268
	ObjectID m_26C; // +0x26C
	_STL::vector<Rva0046F543BannerIndexEntry *> m_270; // +0x270
	Rva0046F543Tail m_tail; // +0x27C
	Int m_2B0; // +0x2B0
	Bool m_2B4; // +0x2B4
	Rva0046F543ZeroedCoord m_2B8; // +0x2B8
	Bool m_2C4; // +0x2C4
	Bool m_2C5; // +0x2C5
	Rva00468FDCHelper *m_2C8; // +0x2C8
	_STL::vector<Rva0046F543Element2CC *> m_2CC; // +0x2CC
	Int m_2D8; // +0x2D8
	_STL::map<Int, Rva00462D35Mapped> m_2DC; // +0x2DC
	Bool m_2E8; // +0x2E8
	Real m_2EC; // +0x2EC
	Int m_2F0; // +0x2F0
	Int m_2F4; // +0x2F4
	Coord3D m_2F8; // +0x2F8
	Bool m_304; // +0x304
	Int m_308; // +0x308
};

HordeContain::HordeContain(Thing *thing, const ModuleData *moduleData)
	: TransportContain(thing, moduleData),
	  m_120(false),
	  m_121(false),
	  m_198(false),
	  m_19C(0),
	  m_264(0),
	  m_268(0),
	  m_26C(0),
	  m_2B0(0),
	  m_2B4(false),
	  m_2C4(false),
	  m_2C5(false),
	  m_2D8(0)
{
	m_2E8 = true;
	m_2EC = 0.0f;
	m_2F0 = 0;
	m_2F4 = 0;
	zeroCoord(m_2F8);
	m_304 = false;
	m_308 = 0;

	if (getHordeContainModuleData()->m_helperFactory != 0)
		m_2C8 = getHordeContainModuleData()->m_helperFactory->create(this);
	else
		m_2C8 = new HordeMeleeSwarm(this);
}
