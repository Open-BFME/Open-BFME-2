// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva000E6D94@Rva000EC9C6@@QAEXH@Z, retail 0x000E6D94..0x000E6EE9 (341 bytes, EH, RET 4).
// Zero Hour's W3DTreeBuffer::allocateTreeBuffers in BFME2's per-batch form, the counterpart
// of the rowed free step 0x000E6B99 (WB 0x008C2830, "Vegetation.fx" string lead): free, size
// the four parallel lists (all through the folded pointer-vector resize 0x000E6D39), then
// under the DirectX thread lock give every batch a dynamic native vertex buffer (FVF 0x252,
// 0x7534 vertices) and a dynamic 0xEA64-index buffer with zero counts, bind the
// "Vegetation.fx" Default setup into the +0x34 method holder and finish in virtual slot 5.
#include <vector>

#include <cstddef>

namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

class Drawable;
_STLP_BEGIN_NAMESPACE
template <>
class vector<Drawable *, allocator<Drawable *> > : public _Vector_base<Drawable *, allocator<Drawable *> >
{
public:
	void resize(unsigned int n, Drawable *x);
};
_STLP_END_NAMESPACE
typedef _STL::vector<Drawable *> Rva000E6D39PointerList;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

struct Rva000E6B99DeviceLock
{
	Rva000E6B99DeviceLock() { BFME_DX8_Thread_Lock(); }
	~Rva000E6B99DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned int fvf, unsigned short count, unsigned int usage, unsigned int flags);
private:
	char m_storage[0x20];
};

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8IndexBufferClass.h"

struct Rva0007BB16Record;
#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/FXShaderSetup.h"
template<class T> class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &refCountPtr) : m_ptr(refCountPtr.m_ptr) { if (m_ptr) m_ptr->Add_Ref(); }
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};
#include "../../../Include/W3DDevice/GameClient/Rva00072A94.h"
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char *, const char *, const _STL::vector<Rva0007BB16Record> *, int);

class Rva000EC9C6
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	void rva000E6B99();
	void rva000E6D94(int numBatches);

private:
	_STL::vector<void *> m_vertexBuffers;		// +0x04
	_STL::vector<void *> m_vertexCounts;		// +0x10
	_STL::vector<void *> m_indexBuffers;		// +0x1C
	_STL::vector<void *> m_indexCounts;		// +0x28
	Rva00072A94 m_method;				// +0x34
};

void Rva000EC9C6::rva000E6D94(int numBatches)
{
	rva000E6B99();
	((Rva000E6D39PointerList *)&m_vertexBuffers)->resize(numBatches, 0);
	((Rva000E6D39PointerList *)&m_vertexCounts)->resize(numBatches, 0);
	((Rva000E6D39PointerList *)&m_indexBuffers)->resize(numBatches, 0);
	((Rva000E6D39PointerList *)&m_indexCounts)->resize(numBatches, 0);
	Rva000E6B99DeviceLock lock;
	for (unsigned int i = 0; i < m_vertexBuffers.size(); i++) {
		m_vertexBuffers[i] = new BfmeDynamicNativeVB(0x252, 0x7534, 1, 0);
		m_indexBuffers[i] = new DX8IndexBufferClass(0xEA64, DX8IndexBufferClass::USAGE_DYNAMIC);
		m_vertexCounts[i] = 0;
		m_indexCounts[i] = 0;
	}
	m_method = reinterpret_cast<const Rva00072A94 &>(Rva00152C47_CreateFXShaderSetup("Vegetation.fx", "Default", 0, 4));
	slot14();
}
