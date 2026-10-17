// cl: /MD /EHs /DNDEBUG /Ireference/shims/moduledata
//
// ??1PlayerRelationMap@@MAE@XZ, retail 0x002AD078, 72 bytes (Ghidra
// boundary), pinned under this name.
//
// Donor: GeneralsMD Player.cpp ~PlayerRelationMap, `m_map.clear();`. BFME 2
// keeps the relations in a hash map at +4. Its shared bucket clear is
// 0x001DBCDC; the inner destructor at 0x002ACF51 is defined here and the
// outer cleanup at 0x002AD073 is identified by the native unwind graph.
// The inlined Snapshot base stores vtable 0x00BBB554. /EHs preserves the
// native cleanup-state transition before the bucket allocation is freed.

#include "Common/Snapshot.h"

// Shared scalar-payload bucket clear, already rowed at 0x001DBCDC.
class Rva004DFC20 { public: void clear(); };
extern "C" void __cdecl free(void *);

struct BfmePlayerRelationBuckets
{
	void *m_begin;
	void *m_end;
	void *m_storageEnd;
	__forceinline ~BfmePlayerRelationBuckets() { if (m_begin) free(m_begin); }
};

class PlayerRelationHashMap
{
public:
	~PlayerRelationHashMap();
	void clear();
private:
	unsigned m_unknown00;
	BfmePlayerRelationBuckets m_buckets;
	unsigned m_count;
	unsigned char m_unknown14[8];
};

// Native 0x002ACF51 clears the table, then releases its bucket allocation
// at +4 on both normal and exceptional exits. This follows the byte-exact
// 57-byte sibling at 0x004271D9; the trailing opaque storage is retained.
PlayerRelationHashMap::~PlayerRelationHashMap()
{
	reinterpret_cast<Rva004DFC20 *>(this)->clear();
}

// Native FuncInfo 0x0091CFFC state 1 reaches action 0x00775A1F:
// destroy owner+4 through 0x002AD073, then the inner table at 0x002ACF51.
// ZH's PlayerRelationMapType is a hash_map. Keep the held table view and
// represent its outer container lifetime separately; this is a descriptive
// view name, not an original C++ type assertion.
class BfmePlayerRelationMapMember
{
public:
	~BfmePlayerRelationMapMember() {}
	void clear() { reinterpret_cast<Rva004DFC20 *>(&m_table)->clear(); }
private:
	PlayerRelationHashMap m_table;
};

class PlayerRelationMap : public Snapshot
{
protected:
	virtual ~PlayerRelationMap();

	BfmePlayerRelationMapMember m_map;
};

PlayerRelationMap::~PlayerRelationMap()
{
	// make sure the data is cleared
	m_map.clear();
}
