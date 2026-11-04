// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep -ICode/Libraries/Source/WWVegas/WW3D2
// ?ReAcquireResources@W3DProjectedShadowManager@@QAE_NXZ @0x0010716D 127B
// Target evidence: retail checks [this+0] then [this+4] for null, creates
// BfmeDynamicNativeVB(2 0x7530 1 0) size 0x20 and DX8IndexBufferClass(0x7530 1)
// size 0x18 via operator new 0x0002FDA0, always returns true. Called from
// W3DShadowManager::ReAcquireResources 0x0009A3A5.
// Donor evidence: BFME1 W3DProjectedShadowManager::ReAcquireResources names
// the owner; BFME2 body uses BfmeDynamicNativeVB + DX8IndexBufferClass.
// Inference: two buffer members at +0/+4, no vtable in this layout.
typedef unsigned int Uint;
typedef unsigned short UShort;
void *__cdecl operator new(Uint s);
#include <new>
#include "../../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
class BfmeDynamicNativeVB : public RefCountClass
{
public:
	BfmeDynamicNativeVB(unsigned fvf, unsigned short count, unsigned usage, unsigned fvfSize);
private:
	char _t[0x18]; // +0x08
};
#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8IndexBufferClass.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/VertexBufferClass.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/IndexBufferClass.h"
class W3DProjectedShadowManager
{
public:
	bool ReAcquireResources();
	void rva001072C9();
private:
	BfmeDynamicNativeVB *m_vertexBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	char _pad08[4];
	VertexBufferClass::WriteLockClass *m_vertexLock;
	IndexBufferClass::WriteLockClass *m_indexLock;
	int m_14;
	int m_18;
};
bool W3DProjectedShadowManager::ReAcquireResources()
{
	if (!m_vertexBuffer)
		m_vertexBuffer = new BfmeDynamicNativeVB(2, 0x7530, 1, 0);
	if (!m_indexBuffer)
		m_indexBuffer = new DX8IndexBufferClass(0x7530, DX8IndexBufferClass::USAGE_DYNAMIC);
	return true;
}
void W3DProjectedShadowManager::rva001072C9()
{
	m_vertexLock = new VertexBufferClass::WriteLockClass((VertexBufferClass *)m_vertexBuffer, 0x2800);
	m_indexLock = new IndexBufferClass::WriteLockClass((IndexBufferClass *)m_indexBuffer, 0x2800);
	m_14 = 0x7530;
	m_18 = 0x7530;
}
