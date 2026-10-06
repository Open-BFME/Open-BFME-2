// cl: /MD /EHsc /DNDEBUG
// stlport
//
// ??1ProductionQueueHordeContainModuleData@@UAE@XZ, retail 0x004817B6, 62 bytes.
// Virtual dtor over rowed GarrisonContainModuleData base (0x00257507):
// stores vtable 0x00C490F8 (DIR32) then destroys the +0xD4 vector through
// the rowed 0x004815AE plus base call. Layout from the rowed ctor TU
// (size 0xE0 via factory 0x24C1B3; vector at +0xD4) with the HordeGarrison
// 0x28 bytes as pad (direct-Garrison precedent from the behavior dtor).
// Called by the slot-0 ??_G at 0x0048179A. Same EH 0/-1 shape as rowed
// GarrisonContainModuleDataDtor.
#include <vector>

struct Rva0048130E
{
	~Rva0048130E();
};

namespace _STL
{

template <>
vector<Rva0048130E, allocator<Rva0048130E> >::~vector();

}

class GarrisonContainModuleData
{
public:
	virtual ~GarrisonContainModuleData();

private:
	unsigned char m_pad[0xAC - 4];
};

class ProductionQueueHordeContainModuleData : public GarrisonContainModuleData
{
public:
	virtual ~ProductionQueueHordeContainModuleData();

private:
	unsigned char m_padAC[0xD4 - 0xAC];
	_STL::vector<Rva0048130E, _STL::allocator<Rva0048130E> > m_vecD4;
};

ProductionQueueHordeContainModuleData::~ProductionQueueHordeContainModuleData()
{
}
