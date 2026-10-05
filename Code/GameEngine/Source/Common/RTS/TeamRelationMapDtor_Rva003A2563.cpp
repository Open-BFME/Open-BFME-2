// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1TeamRelationMap@@MAE@XZ, retail 0x003A2563, 72 bytes (Ghidra
// boundary), pinned under this name: the scalar deleting destructor
// 0x003A2A8A (slot 0 of vtable 0x00C1ADFC, unique TeamRelationMap name
// getter) calls it, and the body re-stores vtable 0x00C1ADFC.
//
// Donor: GeneralsMD Team.cpp ~TeamRelationMap, `m_map.clear();`, in the
// same shape as the byte-verified ~PlayerRelationMap 0x002AD078. BFME 2
// keeps the relations in a hash map at +4: its clear is the folded
// hashtable clear at 0x001DBCDC and its destructor the folded 0x003A2470
// (both rowed under other instantiation names; pinned here under this
// TU's view of the member), then the inlined Snapshot base stores vtable
// 0x00BBB554.

#include "Common/Snapshot.h"

class TeamRelationHashMap
{
public:
	~TeamRelationHashMap();
	void clear();
private:
	unsigned char m_pad[0x1C];
};

class TeamRelationMap : public Snapshot
{
protected:
	virtual ~TeamRelationMap();

	TeamRelationHashMap m_map;
};

TeamRelationMap::~TeamRelationMap()
{
	// make sure the data is cleared
	m_map.clear();
}
