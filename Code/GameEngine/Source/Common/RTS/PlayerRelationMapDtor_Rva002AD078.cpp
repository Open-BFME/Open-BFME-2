// cl: /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1PlayerRelationMap@@MAE@XZ, retail 0x002AD078, 72 bytes (Ghidra
// boundary), pinned under this name.
//
// Donor: GeneralsMD Player.cpp ~PlayerRelationMap, `m_map.clear();`. BFME 2
// keeps the relations in a hash map at +4: its clear is the folded
// hashtable clear at 0x001DBCDC and its destructor the folded 0x002ACF51
// (both rowed under other instantiation names; pinned here under this
// TU's view of the member), then the inlined Snapshot base stores vtable
// 0x00BBB554.

#include "Common/Snapshot.h"

class PlayerRelationHashMap
{
public:
	~PlayerRelationHashMap();
	void clear();
private:
	unsigned char m_pad[0x1C];
};

// Native FuncInfo 0x0091CFFC state 1 reaches action 0x00775A1F:
// destroy owner+4 through 0x002AD073, then the inner table at 0x002ACF51.
// ZH's PlayerRelationMapType is a hash_map. Keep the held table view and
// represent its outer container lifetime separately; this is a descriptive
// view name, not an original C++ type assertion.
class BfmePlayerRelationMapMember
{
public:
	~BfmePlayerRelationMapMember() {}
	void clear() { m_table.clear(); }
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
