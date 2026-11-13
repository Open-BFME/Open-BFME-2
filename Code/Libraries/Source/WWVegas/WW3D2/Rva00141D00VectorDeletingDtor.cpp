// cl: /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// Opaque 0x1C-byte array-deleted class for retail 0x00141D00, plus its
// element destructor at 0x00141CA0.
//
// Identity OPEN. Retail-measured facts only: sizeof 0x1C (pushed for the
// ??_M vector destructor iterator), array cookie at [esi-4], per-element
// destructor 0x00141CA0 (`add ecx,4; jmp 0x00141780`, so the class holds a
// BfmeNonRefSceneList at offset 4), scalar ??3@ 0x2FD60, vector ??_V@ 0x2FD80.
// The Zero Hour ??_E bodies that align 63/64 here (NodeMotionStruct,
// ProxyClass, TimeCodedMorphKeysClass, W3DTerrainBackground) only prove the
// shape and flags: NodeMotionStruct is refuted by its proven 0x24 retail
// stride, and none of the others owns a scene list at +4.

// Retail's array branch frees through the vector delete operator; MSVC only
// routes the call through ??_V when a vector-delete is declared in the TU.
// The declaration emits no code.
#include <new>

// Retail 0x00141780 (BfmeNonRefSceneList_dtor.cpp): vtable + 0x14-byte head.
class BfmeNonRefSceneList
{
public:
	virtual ~BfmeNonRefSceneList();

private:
	char m_pad[0x14];
};

#include "../../../../GameEngine/Include/Common/Rva00141D00.h"

Rva00141D00::~Rva00141D00()
{
}

// ?Rva00141D00DeleteArray@@YAXPAVRva00141D00@@@Z absent-from-retail
void Rva00141D00DeleteArray(Rva00141D00 *array)
{
	delete[] array;
}
