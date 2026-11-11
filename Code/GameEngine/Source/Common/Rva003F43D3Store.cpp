// cl: /MD

class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

// 0x00213171 is rowed as LivingWorldManager::CreateBeaconObject (623B; WB
// twin B602E0) - same (int, Coord2D*, int) shape with the 8-byte m_28 as
// the coord, so this resolves to the rowed body instead of the unrowed
// spelling (sole U on this unit).
class Coord2D;
#include "../../Include/GameLogic/LivingWorldManager.h"

#include "../../Include/Common/Rva003F409F.h"

struct Rva003F43D3Holder {
	char m_pad[0x2C];
	int m_2c;
};

struct RvaLogicHolder {
	char m_pad[0xB0];
	Rva003F43D3Holder *m_holder;
};

class Rva003F43D3 {
public:
	void rva003F43D3();
private:
	char m_pad[0x28];
	char m_28[8];
	int m_30;
};

void Rva003F43D3::rva003F43D3()
{
	RvaLogicHolder *logic = (RvaLogicHolder *)TheLivingWorldLogic;
	Rva003F43D3Holder *holder = logic->m_holder;
	int value = ++holder->m_2c;
	m_30 = value;
	((LivingWorldManager *)TheLivingWorldManager)->CreateBeaconObject(value, (const Coord2D *)m_28, 0);
	((Rva003F409F *)this)->rva003F409F(true);
}
