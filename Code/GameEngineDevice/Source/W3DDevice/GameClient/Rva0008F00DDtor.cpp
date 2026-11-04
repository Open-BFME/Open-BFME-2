// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ??1Rva008F00D@@UAE@XZ, retail 0x0008F00D..0x0008F0BB (174 bytes, EH):
// by shape Zero Hour's W3DInGameUI::~W3DInGameUI (W3DInGameUI.cpp; name kept
// address-derived to agree with the opaque pin of 0x0008F379): release every
// move-hint render object and animation (MAX_MOVE_HINTS = 25, arrays at
// +0x9F0 and +0xA54), then the building placement anchor (+0xAB8) and
// arrow (+0xABC), and run the rowed InGameUI destructor (0x002A5B30, the
// unwind map's only state). Tables 0x00BC7A88, 0x00BC7A78 (+0xC) and
// 0x00BC7A64 (+0x10).
#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

class HAnimClass
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--NumRefs == 0) Delete_This(); }
private:
	int NumRefs;
};

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

enum { MAX_MOVE_HINTS = 25 };

class InGameUIPrimary
{
public:
	virtual void s0();
private:
	int m_04;
	int m_08;
};

class InGameUISecond
{
public:
	virtual void s0();
};

class InGameUIThird
{
public:
	virtual void s0();
};

class InGameUI : public InGameUIPrimary, public InGameUISecond, public InGameUIThird
{
public:
	virtual ~InGameUI();
private:
	unsigned char m_pad14[0x9F0 - 0x14];
};

class Rva008F00D : public InGameUI
{
public:
	virtual ~Rva008F00D();
private:
	RenderObjClass *m_moveHintRenderObj[MAX_MOVE_HINTS];	// +0x9F0
	HAnimClass *m_moveHintAnim[MAX_MOVE_HINTS];		// +0xA54
	RenderObjClass *m_buildingPlacementAnchor;		// +0xAB8
	RenderObjClass *m_buildingPlacementArrow;		// +0xABC
};

Rva008F00D::~Rva008F00D()
{
	int i;
	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		REF_PTR_RELEASE(m_moveHintRenderObj[i]);
		REF_PTR_RELEASE(m_moveHintAnim[i]);
	}
	REF_PTR_RELEASE(m_buildingPlacementAnchor);
	REF_PTR_RELEASE(m_buildingPlacementArrow);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?s0@InGameUIPrimary@@UAEXXZ=??_GRva008F00D@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?s0@InGameUISecond@@UAEXXZ=??_ERva008F00D@@WM@AEPAXI@Z")
#pragma comment(linker, "/alternatename:?s0@InGameUIThird@@UAEXXZ=?rva0029B558@Rva0029B558@@UAEXXZ")
