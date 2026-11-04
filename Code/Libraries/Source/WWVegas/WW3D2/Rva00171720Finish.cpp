// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?rva00171720@MeshModelClass@@QAE_NXZ retail 0x00171720 55B unlock lane.
// MeshModelClass predicate using CurMatDesc fields +0xB8/+0x108 and +0xBC,
// else PolygonRendererList emptiness via +0xA0/+0xA4. Evidence: CurMatDesc
// at +0x94 from sibling meshmdl.cpp Needs_Vertex_Normals; callers 0x14BD10.
// The two material-description gates return m_bc by implicit int-to-bool
// conversion, which is what keeps retail's `cmp [ecx+0xbc],0; setne al`
// free of the register-zeroing `xor eax,eax` an explicit `!= 0` emits.
#include "MeshMatDescClass.h"

class MeshModelClass
{
public:
	bool rva00171720();

private:
	unsigned char m_pad0[0x19];
	unsigned char m_flagByte;
	unsigned char m_pad1[0x94 - 0x1A];
	MeshMatDescClass *CurMatDesc;
	unsigned char m_pad98[0xA0 - 0x98];
	void *m_listHead;
	void *m_listFirst;
	unsigned char m_padA8[0xBC - 0xA8];
	int m_bc;
};

bool MeshModelClass::rva00171720()
{
	if (CurMatDesc->field_B8[0] != 0)
		return m_bc;
	if (CurMatDesc->field_108[0] != 0)
		return m_bc;
	return m_listFirst != (void *)&m_listHead;
}
