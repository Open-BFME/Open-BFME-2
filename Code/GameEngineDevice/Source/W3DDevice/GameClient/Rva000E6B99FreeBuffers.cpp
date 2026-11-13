// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva000E6B99@Rva000EC9C6@@QAEXXZ, retail 0x000E6B99..0x000E6D39 (416
// bytes, EH). Zero Hour's W3DTreeBuffer::freeTreeBuffers in BFME2's
// per-batch form: under the DirectX thread lock every vertex and index
// buffer reference is released (and nulled), the four parallel lists
// (vertex buffers +0x04, vertex counts +0x10, index buffers +0x1C, index
// counts +0x28) are emptied -- all four through the one vector<void *>
// erase retail keeps -- and the +0x34 rendering method reference is
// dropped through the rowed holder release. Receiver evidence: the same
// object whose render step is 0x000E663B and whose per-frame forwarder is
// the rowed 0x000EC9C6.

#include <vector>

#include <cstddef>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
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
// Retail calls the shared out-of-line erase (0x0031BD55, rowed in
// stlport_vector_voidptr_opt.cpp) and inlines clear; declare the former and
// keep the latter inline so no competing erase/clear/__copy_trivial copies.
template <>
void **vector<void*>::erase(void **__first, void **__last);
template <> __declspec(dllimport) __forceinline
void vector<void*>::clear()
{ erase(begin(), end()); }
}

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

struct Rva000E6B99DeviceLock
{
	Rva000E6B99DeviceLock() { BFME_DX8_Thread_Lock(); }
	~Rva000E6B99DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva000E6B99Buffer
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
	int m_refs;
};

#include "../../../../GameEngine/Include/Common/Rva005F2577Holder.h"

class Rva000EC9C6
{
public:
	void rva000E6B99();

private:
	int m_00;
	_STL::vector<void *> m_vertexBuffers;		// +0x04
	_STL::vector<void *> m_vertexCounts;		// +0x10
	_STL::vector<void *> m_indexBuffers;		// +0x1C
	_STL::vector<void *> m_indexCounts;		// +0x28
	Rva005F2577Holder m_method;			// +0x34
};

void Rva000EC9C6::rva000E6B99()
{
	Rva000E6B99DeviceLock lock;
	for (unsigned int i = 0; i < m_vertexBuffers.size(); i++) {
		if (m_vertexBuffers[i]) {
			((Rva000E6B99Buffer *)m_vertexBuffers[i])->Release_Ref();
			m_vertexBuffers[i] = 0;
		}
		if (m_indexBuffers[i]) {
			((Rva000E6B99Buffer *)m_indexBuffers[i])->Release_Ref();
			m_indexBuffers[i] = 0;
		}
	}
	m_vertexBuffers.clear();
	m_vertexCounts.clear();
	m_indexBuffers.clear();
	m_indexCounts.clear();
	m_method.rva005F2577();
}
