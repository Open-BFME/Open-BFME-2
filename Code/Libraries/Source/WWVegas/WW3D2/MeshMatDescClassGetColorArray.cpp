// cl: /DNDEBUG /MD /Ob2 /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// MeshMatDescClass::Get_Color_Array, retail 0x00D1FBD (105 bytes). BFME1
// header-inline shape (reference/.../meshmatdesclayout/meshmatdesc.h in this
// tree): create-gated allocation of a ShareBufferClass<unsigned> over
// VertexCount, then the Array (+0x0C) or 0. Retail keeps it out of line
// (dx8renderer Define_FVF calls it cross-TU at 0x144286/0x14429E). Retail
// touches ColorArray at this+0x50 and VertexCount at +0x04, as declared
// by the canonical BFME2 descriptor header. The allocator (??2 at 0x2FDA0) resolves via
// its pin and the ShareBuffer<unsigned> ctor via its matched row; the
// "MeshMatDescClass::ColorArray" literal is verified against 0x7CE358.
// Like its ctor dependency, this unit builds at /O1 for the ebp-frame
// __EH_prolog prologue.

#include "../WWLib/RefCountData.h"

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment = 0);
	T *Get_Array() { return m_array; }

protected:
	T *m_rawBuffer; // +0x08
	T *m_array; // +0x0C
	int m_count; // +0x10
	int m_alignment; // +0x14
};

// Use BFME2 debug declarations before the WWLib ownership include closure.
#include "../../debug/debug.h"
#include "MeshMatDescClass.h"

inline unsigned *MeshMatDescClass::Get_Color_Array(int index, bool create)
{
	if (create && !ColorArray[index]) {
		ColorArray[index] = new ShareBufferClass<unsigned>(VertexCount, "MeshMatDescClass::ColorArray");
	}
	if (ColorArray[index]) {
		return ColorArray[index]->Get_Array();
	}
	return 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
unsigned * (MeshMatDescClass::*_bfmeInlineAnchor_MeshMatDescClassGetColorArray_0)(int index, bool create) = &MeshMatDescClass::Get_Color_Array;
