// cl: /MD /EHs /DNDEBUG /Ireference/shims/moduledata
//
// ??1TeamRelationMap@@MAE@XZ, retail 0x003A2563, 72 bytes (Ghidra
// boundary), pinned under this name: the scalar deleting destructor
// 0x003A2A8A (slot 0 of vtable 0x00C1ADFC, unique TeamRelationMap name
// getter) calls it, and the body re-stores vtable 0x00C1ADFC.
//
// Donor: GeneralsMD Team.cpp ~TeamRelationMap, `m_map.clear();`, in the
// same shape as the byte-verified ~PlayerRelationMap 0x002AD078. BFME 2
// keeps the relations in a hash map at +4. Its shared bucket clear is
// 0x001DBCDC; the inner destructor at 0x003A2470 is defined here and the
// outer cleanup at 0x003A255E is identified by the native unwind graph.
// The inlined Snapshot base stores vtable 0x00BBB554. /EHs preserves the
// native cleanup-state transition before the bucket allocation is freed.

#include "Common/Snapshot.h"

class Rva004DFC20 { public: void clear(); };
extern "C" void __cdecl free(void *);

struct BfmeTeamRelationBuckets
{
	void *m_begin;
	void *m_end;
	void *m_storageEnd;
	__forceinline ~BfmeTeamRelationBuckets() { if (m_begin) free(m_begin); }
};

class TeamRelationHashMap
{
public:
	~TeamRelationHashMap();
	void clear();
private:
	unsigned m_unknown00;
	BfmeTeamRelationBuckets m_buckets;
	unsigned m_count;
	unsigned char m_unknown14[8];
};

// Native 0x003A2470 uses the same table layout and cleanup-state transition
// as 0x002ACF51, with its own handler at 0x0078170D. Keep the existing
// opaque tail while recovering clear-then-free ownership of the +4 bucket.
TeamRelationHashMap::~TeamRelationHashMap()
{
	reinterpret_cast<Rva004DFC20 *>(this)->clear();
}

// Native FuncInfo 0x0092C610 state 1 reaches action 0x0078171F:
// destroy owner+4 through 0x003A255E, then the inner table at 0x003A2470.
// ZH's TeamRelationMapType is a hash_map. This descriptive lifetime view
// preserves the held table storage without asserting an original type name.
class BfmeTeamRelationMapMember
{
public:
	~BfmeTeamRelationMapMember() {}
	void clear() { reinterpret_cast<Rva004DFC20 *>(&m_table)->clear(); }
private:
	TeamRelationHashMap m_table;
};

class TeamRelationMap : public Snapshot
{
protected:
	virtual ~TeamRelationMap();

	BfmeTeamRelationMapMember m_map;
};

TeamRelationMap::~TeamRelationMap()
{
	// make sure the data is cleared
	m_map.clear();
}
