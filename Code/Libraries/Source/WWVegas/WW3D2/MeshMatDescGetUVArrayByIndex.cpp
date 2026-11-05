// cl: /DNDEBUG /MD /Ob2 /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Get_UV_Array_By_Index@MeshMatDescClass@@QAEPAVVector2@@H_N@Z @0x000D1F40 125B
// Create-gated UV buffer accessor with legacy Get_UV_Array fallback.
// Evidence: retail EH_prolog, new 0x1c plus UVBuffer ctor with
// "MeshMatDescClass::UV" and VertexCount+0x04, table+0x10, array+0x0C,
// rowed Get_UV_Array at 0x000D1F1A, callers 0x000D2057 0x000D239A 0x000DDF36
// 0x000E5521 0x0014436F 0x0018CE74; donor ZH meshmatdesc.h Get_UV_Array_By_Index.

class Vector2;

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

class UVBufferClass : public ShareBufferClass<Vector2>
{
public:
	UVBufferClass(int count, const char *msg);

private:
	unsigned int m_crc; // +0x18 (sizeof 0x1C)
};

// Use BFME2 debug declarations before the WWLib ownership include closure.
#include "../../debug/debug.h"
#include "MeshMatDescClass.h"

inline Vector2 *MeshMatDescClass::Get_UV_Array_By_Index(int index, bool create)
{
	if (create && !UV[index])
		UV[index] = new UVBufferClass(VertexCount, "MeshMatDescClass::UV");
	if (!create && field_0C != 0 && index < 2)
		return Get_UV_Array(0, index);
	if (UV[index])
		return UV[index]->Get_Array();
	return 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
Vector2 * (MeshMatDescClass::*_bfmeInlineAnchor_MeshMatDescGetUVArrayByIndex_0)(int index, bool create) = &MeshMatDescClass::Get_UV_Array_By_Index;
