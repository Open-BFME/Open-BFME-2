// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00329906@Rva0032989F@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z,
// retail 0x00329906 (104 bytes, RET 8): slot 1 of the "PlayerScriptsList"
// side binding's vtable 0x00C0D8FC (destructor Rva0032989FDtor.cpp, ctor
// 0x0032A082 in SidesListDataChunks.cpp). After the shared chunk reader
// (rowed 0x003B793A) has filled the per-side ScriptLists (+0x18, count
// +0x68), each one, last first, is swapped into its side's script list
// (SidesList +0x14: getSideInfo, the list based at SidesInfo +8, rowed
// ScriptList::swap) while the side exists, and the parsed list is deleted.
// Storage view: no constructor or destructor defined, no vtable emitted.
class DataChunkInput;
struct DataChunkInfo;

#include "../../../Include/GameLogic/SidesInfo.h"
#include "../../../Include/GameLogic/ScriptList.h"

// The parsed lists, deleted through their virtual destructor.
class Rva0032989FItem
{
public:
	virtual ~Rva0032989FItem();
};

#include "../../../Include/Common/SidesList.h"

class Rva003B793A
{
public:
	bool read(DataChunkInput &file, DataChunkInfo *info);
};

class Rva0032989F
{
public:
	virtual ~Rva0032989F();
	virtual bool rva00329906(DataChunkInput &file, DataChunkInfo *info);
private:
	unsigned char m_pad04[0x14 - 0x04];
	SidesList *m_sides;		// +0x14
	Rva0032989FItem *m_lists[20];	// +0x18
	int m_count;			// +0x68
};

bool Rva0032989F::rva00329906(DataChunkInput &file, DataChunkInfo *info)
{
	if (!((Rva003B793A *)this)->read(file, info))
		return false;
	while (m_count > 0)
	{
		--m_count;
		if (m_count < m_sides->m_numSides)
			m_sides->getSideInfo(m_count)->m_scripts.swap((ScriptList *)m_lists[m_count]);
		::delete m_lists[m_count];
		m_lists[m_count] = 0;
	}
	return true;
}
