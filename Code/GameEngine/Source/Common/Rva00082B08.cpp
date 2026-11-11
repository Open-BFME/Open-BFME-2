// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// stlport
// ?rva00082B08@Rva00082B08@@QAEXXZ @0x00082B08 127B: triple conditional Rva002B7250 erase plus two vector range erases plus conditional tail to WaterTracksRenderSystem move drain. Evidence: three Rva002B7250 row calls plus two 0x819EC vector erase row calls plus tail jmp to 0xFE188 row plus caller 0x91CF2.
#include <vector>
class CreateAHeroData { public: void *m_p; };
#include "../../Include/Common/Rva002B7250.h"
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
// Retail's erase is the rowed copy in Rva004F92E3Rva004F92E3.cpp.
namespace _STL { template <> TreeHintRef00217D4C *vector<TreeHintRef00217D4C, allocator<TreeHintRef00217D4C> >::erase(TreeHintRef00217D4C *, TreeHintRef00217D4C *); }
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/WaterTracksRenderSystem.h"
class Rva00082B08
{
public:
	void rva00082B08();
private:
	char m_pad0[0xc8];
	CreateAHeroData m_aC8;
	CreateAHeroData m_bCC;
	CreateAHeroData m_cD0;
	char m_pad1[0x100 - 0xd4];
	WaterTracksRenderSystem *m_fe100;
	Rva002B7250 *m_p104;
	_STL::vector<TreeHintRef00217D4C> m_v108;
	Rva002B7250 *m_p114;
	_STL::vector<TreeHintRef00217D4C> m_v118;
	Rva002B7250 *m_p124;
};
void Rva00082B08::rva00082B08()
{
	if (m_p104) {
		m_p104->rva002B7250(&m_aC8);
		m_p104 = 0;
		m_p114->rva002B7250(&m_bCC);
		m_p114 = 0;
		m_p124->rva002B7250(&m_cD0);
		m_p124 = 0;
	}
	_STL::vector<TreeHintRef00217D4C> *pV0 = &m_v108;
	pV0->erase(pV0->begin(), pV0->end());
	_STL::vector<TreeHintRef00217D4C> *pV1 = &m_v118;
	pV1->erase(pV1->begin(), pV1->end());
	if (m_fe100)
		m_fe100->rva000FE188();
}
