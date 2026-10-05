// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
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

class PlayerRelationMap : public Snapshot
{
protected:
	virtual ~PlayerRelationMap();

	PlayerRelationHashMap m_map;
};

PlayerRelationMap::~PlayerRelationMap()
{
	// make sure the data is cleared
	m_map.clear();
}
