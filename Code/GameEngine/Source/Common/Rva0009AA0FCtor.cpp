// cl: /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ??0Rva0009AA0F@@QAE@H@Z @0x0009AA0F 30B: derived constructor taking one
// int/pointer stored at +0x108, then installing vtable 0x00BC8900. Calls
// the rowed 563B base constructor SimpleSceneClass 0x00142960 first. Honest
// address-derived names on both sides; boundary verified (push esi at
// 0x9AA0F, pop esi + ret 4 at end).

#include "../../../Libraries/Source/WWVegas/WW3D2/SimpleSceneClass.h"

class Rva0009AA0F : public SimpleSceneClass
{
public:
	Rva0009AA0F(int v);
	// No user destructor: retail's slot-1 scalar deleting destructor 0x001042CF
	// (shared with the 0x00740555 sibling) calls the 5-byte implicit one that
	// only tail-jumps to ~SimpleSceneClass.

private:
	int m_108;
protected:
	// retail vftable slot: the rowed override
	virtual void Customized_Render(RenderInfoClass &);
};

// ??0Rva0009AA0F@@QAE@H@Z
Rva0009AA0F::Rva0009AA0F(int v)
{
	m_108 = v;
}
