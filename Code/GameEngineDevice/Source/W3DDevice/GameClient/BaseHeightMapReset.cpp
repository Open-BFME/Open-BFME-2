// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?reset@BaseHeightMapRenderObjClass@@UAEXXZ, retail 0x0006D5A7..0x0006D6D9
// (306 bytes, no direct callers: a vtable slot). Zero Hour's
// BaseHeightMapRenderObjClass::reset (BaseHeightMap.cpp) in its BFME2 form:
// every vegetation/road/bridge/bib/prop buffer cleared through its rowed reset
// (null-checked), the scorch ring emptied inline (+0x3790/+0x3794/+0x3798 and a
// new count at +0x37AC), the two visibility vectors (+0x37EC/+0x3800)
// cleared, both shroud-like layers (+0x3878/+0x387C) reset and given their
// border level from GlobalData (+0xBEA / +0xC04), and the second terrain
// texture reloaded from the empty name while the first (+0x381C/+0x3820) is
// released. Receiver evidence: all the buffer pointers are the ones the
// neighbouring draw/update steps (0x0006B895, 0x0006669F) use.
#include <vector>
#include "ascii_string.h"

namespace _STL { template<> void vector<bool, allocator<bool> >::clear(); }

class Rva000EA24D { public: void rva000EA24D(); };
class Rva000D3A17 { public: void rva000D3A17(); };
class Rva000E7016 { public: void rva000E7016(); };
class Rva000EE198Owner { public: void rva000EE198(); };
class W3DRoadBuffer { public: void clearAllRoads(); };
class W3DBridgeBuffer { public: void clearAllBridges(); };
class W3DFloorBuffer { public: void rva000E598B(); };
class W3DBibBuffer { public: void clearAllBibs(); };
class Rva000731AE { public: void rva000731AE(); };
class Rva000729CC { public: void rva000729CC(bool level); };
class Rva00073C7A { public: void rva00073C7A(); };
class BfmeResetTextureRef { public: void clear(); };

class GlobalData
{
public:
	char m_pad000[0xBEA];
	bool m_shroudAlphaA;	// +0xBEA
	char m_padBEB[0xC04 - 0xBEB];
	bool m_shroudAlphaB;	// +0xC04
};
extern GlobalData *TheWritableGlobalData;

class BaseHeightMapRenderObjClass
{
public:
	virtual void reset();
	void rva0006ABE7(AsciiString name, bool flag);

private:
	char m_pad04[0x3790 - 4];
	int m_numScorches;		// +0x3790
	int m_scorchesInBuffer;		// +0x3794
	int m_nextScorch;		// +0x3798
	char m_pad379C[0x37AC - 0x379C];
	int m_37AC;
	char m_pad37B0[0x37EC - 0x37B0];
	_STL::vector<bool> m_visibleCliff;	// +0x37EC
	_STL::vector<bool> m_cliff2;		// +0x3800
	char m_pad3814[0x381C - 0x3814];
	BfmeResetTextureRef m_381C;
	AsciiString m_3820;
	char m_pad3824[0x3850 - 0x3824];
	Rva000EA24D *m_treeBuffer;		// +0x3850
	Rva000E7016 *m_shrubBuffer;		// +0x3854
	Rva000EE198Owner *m_propBuffer;		// +0x3858
	W3DBibBuffer *m_bibBuffer;		// +0x385C
	W3DFloorBuffer *m_floorBuffer;		// +0x3860
	char m_pad3864[0x386C - 0x3864];
	W3DRoadBuffer *m_roadBuffer;		// +0x386C
	W3DBridgeBuffer *m_bridgeBuffer;	// +0x3870
	Rva000D3A17 *m_3874;
	Rva000731AE *m_shroud;			// +0x3878
	Rva00073C7A *m_387C;
	bool m_3880;
};

void BaseHeightMapRenderObjClass::reset()
{
	m_3880 = true;
	if (m_treeBuffer)
		m_treeBuffer->rva000EA24D();
	if (m_3874)
		m_3874->rva000D3A17();
	if (m_shrubBuffer)
		m_shrubBuffer->rva000E7016();
	if (m_propBuffer)
		m_propBuffer->rva000EE198();
	m_numScorches = 0;
	m_scorchesInBuffer = 0;
	m_nextScorch = 0;
	m_37AC = 0;
	if (m_roadBuffer)
		m_roadBuffer->clearAllRoads();
	if (m_bridgeBuffer)
		m_bridgeBuffer->clearAllBridges();
	if (m_floorBuffer)
		m_floorBuffer->rva000E598B();
	if (m_bibBuffer)
		m_bibBuffer->clearAllBibs();
	m_visibleCliff.clear();
	m_cliff2.clear();
	if (m_shroud) {
		m_shroud->rva000731AE();
		((Rva000729CC *)m_shroud)->rva000729CC(TheWritableGlobalData->m_shroudAlphaA);
	}
	if (m_387C) {
		m_387C->rva00073C7A();
		((Rva000729CC *)m_387C)->rva000729CC(TheWritableGlobalData->m_shroudAlphaB);
	}
	rva0006ABE7(AsciiString(""), false);
	m_381C.clear();
	m_3820.clear();
}
