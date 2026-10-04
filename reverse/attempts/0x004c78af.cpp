// ?rva004C78AF@ManTheWallsSpecialPower@@QAE_NPAVRva004C78AFList@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

class Object;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateAllObjects(Rva000421C8 *filters);	// 0x006256F0
};
extern PartitionManager *ThePartitionManager;

struct BfmeE16 { float x, y, z, w; };

// An object and a vector (ctor 0x004BA1B2).
class Rva004BA1B2
{
public:
	Rva004BA1B2();	// 0x004BA1B2
	Object *m_00;
	_STL::vector<BfmeE16> m_04;
};

// The vector<Rva004BA1B2> the scan fills.
class Rva004C78AFList
{
public:
	void push_back(const Rva004BA1B2 &entry);	// 0x004C7878
	int size() const { return m_finish - m_start; }
	Rva004BA1B2 *m_start;
	Rva004BA1B2 *m_finish;
	Rva004BA1B2 *m_end;
};

class ModuleData;
class ManTheWallsSpecialPower
{
public:
	bool rva004C78AF(Rva004C78AFList *out);
private:
	void *m_vtable;
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

bool ManTheWallsSpecialPower::rva004C78AF(Rva004C78AFList *out)
{
	BfmeWideResult hits = ThePartitionManager->iterateAllObjects(
		Rva00260EB1Filter(m_object, 4, false).link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 115),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)));
	for (Object *other = hits.next(); other; other = hits.next()) {
		Rva004BA1B2 entry;
		entry.m_00 = other;
		out->push_back(entry);
	}
	return out->size() != 0;
}
