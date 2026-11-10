// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?init@LivingWorldLogic@@UAEXXZ, retail 0x002B98AD..0x002B99F8 (331B,
// ends in a tail jump): slot 1 of the subsystem table at 0x00BFE2E4 (the
// SubsystemInterface init slot by Zero Hour's order), a Ghidra-unlisted gap
// body. It clears the logic's turn state and campaign bookkeeping through the
// ledger's rowed members (processArmyDestroyList among them, which fixes the
// receiver as LivingWorldLogic), empties its +0x148 / +0xBC / +0x154 vectors
// and resets the +0x178 / +0x160 containers, then tail-calls 0x002B29BD with
// the logic in ECX. Fields are named by offset: only retail's accesses are
// modelled.
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::begin() { return this->_M_start; } }

struct Gen_p12pod { int m_a, m_b, m_c; };
// Use the byte-verified out-of-line erase owner at 0x002A133B.
namespace _STL {
template <> Gen_p12pod *vector<Gen_p12pod, allocator<Gen_p12pod> >::erase(Gen_p12pod *, Gen_p12pod *);
}
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
// Use the byte-verified out-of-line erase owner at 0x000819EC
// (StlportVectorEraseRangeFamily.cpp) instead of emitting this unit's copy.
namespace _STL {
template <> TreeHintRef00217D4C *vector<TreeHintRef00217D4C, allocator<TreeHintRef00217D4C> >::erase(TreeHintRef00217D4C *, TreeHintRef00217D4C *);
}

#include "../../../../Include/Common/Rva002B254F.h"
#include "../../../../Include/Common/LivingWorldCampaignManager.h"
class Rva003F812C { public: void rva003F812C(); };
class Rva002B5522 { public: void rva002B5522(); };
class Rva002B7B25 { public: void rva002B7B25(); };
class Rva002B7B71 { public: void rva002B7B71(); };
class Rva0020EE29 { public: void rva0020F795(); };
class Glo012F1028Type { public: void rva002B7D91(); };
class Rva002B7C74 { public: void rva002B7C74(); };
class Rva002B6900 { public: void rva002B6900(); };
class Rva002B296F { public: void rva002B296F(); };
class Rva002B9099 { public: void clear(); };
class Rva002BED91 { public: void clear(); };

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;

class LivingWorldLogic
{
public:
	virtual ~LivingWorldLogic();
	virtual void init();
	void processArmyDestroyList();							// 0x002B7BBB
	void rva002B29BD();										// 0x002B29BD
private:
	char m_pad004[0xB0 - 4];
	Rva0020EE29 *m_B0;										// +0xB0
	bool m_B4;
	bool m_B5;
	bool m_B6;
	char m_padB7;
	int m_B8;
	_STL::vector<void *> m_BC;								// +0xBC
	bool m_C8;
	char m_padC9[0xE9 - 0xC9];
	bool m_E9;
	char m_padEA[2];
	int m_EC;
	char m_padF0[4];
	int m_F4;
	int m_F8;
	int m_FC;
	int m_100;
	int m_104;
	bool m_108;
	bool m_109;
	bool m_10A;
	bool m_10B;
	char m_pad10C[0x13C - 0x10C];
	Rva002B5522 m_13C;										// +0x13C
	char m_pad13D[0x148 - 0x13D];
	_STL::vector<Gen_p12pod> m_148;							// +0x148
	_STL::vector<TreeHintRef00217D4C> m_154;				// +0x154
	Rva002BED91 m_160;										// +0x160
	char m_pad161[0x164 - 0x161];
	int m_164;
	bool m_168;
	char m_pad169[0x174 - 0x169];
	bool m_174;
	bool m_175;
	bool m_176;
	bool m_177;
	Rva002B9099 m_178;										// +0x178
};

void LivingWorldLogic::init()
{
	m_F8 = -1;
	m_F4 = 0;
	m_100 = 0;
	m_104 = 0;
	if (m_B4 && (char)((Rva002B254F *)this)->rva002B254F())
		((Rva003F812C *)((LivingWorldCampaignManager *)TheCampaignManager)->rva003B8BAA())->rva003F812C();
	processArmyDestroyList();
	m_13C.rva002B5522();
	((Rva002B7B25 *)this)->rva002B7B25();
	((Rva002B7B71 *)this)->rva002B7B71();
	m_B0->rva0020F795();
	((Glo012F1028Type *)this)->rva002B7D91();
	((Rva002B7C74 *)this)->rva002B7C74();
	{
		_STL::vector<Gen_p12pod> &vr = m_148;
		vr.erase(vr.begin(), vr.end());
	}
	((Rva002B6900 *)this)->rva002B6900();
	m_B4 = false;
	m_B5 = true;
	m_B6 = false;
	((Rva002B296F *)this)->rva002B296F();
	m_B8 = -1;
	m_EC = 1;
	m_E9 = false;
	m_C8 = false;
	{
		_STL::vector<void *> &vr = m_BC;
		vr.erase(vr.begin(), vr.end());
	}
	m_FC = 0;
	m_168 = false;
	m_164 = 0;
	m_10A = false;
	m_108 = false;
	m_10B = true;
	m_109 = false;
	m_174 = false;
	m_175 = false;
	m_176 = false;
	m_177 = false;
	m_178.clear();
	{
		_STL::vector<TreeHintRef00217D4C> &vr = m_154;
		vr.erase(vr.begin(), vr.end());
	}
	m_160.clear();
	rva002B29BD();
}
