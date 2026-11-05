// cl: /O1 /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native6B3F3..6B4CC full217 including EH2; BFME1 f989
// BaseHeightMapRva006CB080 gives scorch buffer/texture initialization purpose.
// ActualVB/IB CC/D0 owned texture D4 counters D8/DC/3794 and existing
// EF966 one-pointer constructor /424D0 counted assignment independently verified.
// Same-valued receiver PHI in the inline slot accessor keeps the native
// LEA-before-PUSH assignment order. No condition load survives optimization.
//
// ?rva0006B3F3@BaseHeightMapRenderObjClass@@QAEXXZ, retail 0x0006B3F3, 217 bytes.
// Chain lane: calls 0x00067878 just landed; allocates VB/IB at +0xCC/+0xD0
// then sets texture at +0xD4 via BNH helper. Same class as BaseHeightMapRenderObjClass.
// Evidence: same +CC/D0/D4 offsets, rowed callees, EH new states.

typedef unsigned int Uint;
typedef unsigned short UShort;
// WWLib always.h defines the array placement forms itself.
#define __PLACEMENT_VEC_NEW_INLINE
#include <new>

#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

class BfmeDynamicNativeVB : public RefCountClass
{
public:
	BfmeDynamicNativeVB(Uint a, UShort b, Uint c, Uint d);
private:
	char _t[0x18];
};

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8IndexBufferClass.h"

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template<class T>
class RefCountPtr
{
public:
	__declspec(noinline) RefCountPtr(int kind);
	T *Referent;
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}
	const RefCountPtr &operator=(const RefCountPtr &other);
};

class Rva0006B3F3ScorchTexture:public RefCountPtr<TextureClass>{public:Rva0006B3F3ScorchTexture(int);};
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
#define REFCOUNT_H
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// The header keeps +0xCC as VertexBufferClass*; this body allocates the
// dynamic native VB that the constructor 0x0006C9CF stores there.
static __forceinline BfmeDynamicNativeVB *&scorchVertexBuffer(BaseHeightMapRenderObjClass *self)
{
	return *reinterpret_cast<BfmeDynamicNativeVB **>(&self->m_vertexScorch);
}

// +0xD4 is the scorch texture holder (opaque word in the header).
static __forceinline RefCountPtr<TextureClass> &scorchSlot(BaseHeightMapRenderObjClass *self)
{
	return self ? *reinterpret_cast<RefCountPtr<TextureClass> *>(&self->field00D4)
	            : *reinterpret_cast<RefCountPtr<TextureClass> *>(&self->field00D4);
}

void BaseHeightMapRenderObjClass::rva0006B3F3()
{
	if (m_vertexScorch != 0 || m_indexScorch != 0)
		rva00067878();
	scorchVertexBuffer(this) = new BfmeDynamicNativeVB(0x142, 0x2002, 0, 0);
	m_indexScorch = new DX8IndexBufferClass(0xC00C, DX8IndexBufferClass::USAGE_DEFAULT);
	scorchSlot(this)=Rva0006B3F3ScorchTexture(3);
	m_scorchesInBuffer = 0;
	m_curNumScorchVertices = 0;
	m_curNumScorchIndices = 0;
}
