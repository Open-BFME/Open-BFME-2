// cl: /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// dxsdk
// platformsdk
// Open-BFME5 conversions.

#include <d3d9.h>

extern void *g_bfmeVftTDA[];

class BfmeSinkTDA
{
public:
	virtual void bfmeV0TDA() = 0;
	virtual void bfmeV1TDA() = 0;
	virtual void bfmeV2TDA() = 0;
	virtual void bfmeDropTDA(void *p, int f) = 0;
};

class GenAlloc; GenAlloc *Gen007EFFC0();

class BfmeThingTDA
{
public:
	void bfmeGoTDA();
	void *m_vtable;
	char m_bfmePad[8];
	void *m_bfmeItem;
};

void BfmeThingTDA::bfmeGoTDA()
{
	m_vtable = g_bfmeVftTDA;
	((BfmeSinkTDA *)Gen007EFFC0())->bfmeDropTDA(m_bfmeItem, 0);
}

// The ledger's globals this body reaches: DX8Wrapper's device (0x9EDA34),
// the DX8 call counter (0x9EDA98) and ShaderClass's dirty flag (0x9B621C).
// The two class statics are protected, so derived views read them. The device
// keeps its D3D8 type name but is a Direct3D 9 device (SetVertexShader, slot 92).
struct IDirect3DDevice8;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
#include "../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"
extern unsigned number_of_DX8_calls;

