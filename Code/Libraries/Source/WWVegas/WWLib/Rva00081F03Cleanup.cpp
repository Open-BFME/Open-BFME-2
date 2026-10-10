// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00081F03@Rva00081F03@@QAEXXZ 0x00081F03 218B: thread-locked release of refcounted handles in vectors +0x70/+0x88 then erase of 4 vectors; evidence callers 0x8297D/0x8305F, callees Thread_Lock 0x11F520 Thread_Assert 0x120F50 erase 0x31BD55 x4, EH prolog scope 0x75F5E9.
#include <vector>

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
}

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class IndexBufferRef
{
public:
	virtual void destroy();
	int m_refCount;
};

class Rva00081F03
{
public:
	void rva00081F03();
private:
	char m_pad[0x70];
	_STL::vector<void *> m_vec70;
	_STL::vector<void *> m_vec7C;
	_STL::vector<void *> m_vec88;
	_STL::vector<void *> m_vec94;
};

void Rva00081F03::rva00081F03()
{
	BFMEDX8DeviceLock guard;
	for (unsigned int i = 0; i < m_vec70.size(); ++i)
	{
		if (m_vec70[i] != 0)
		{
			IndexBufferRef *p0 = (IndexBufferRef *)m_vec70[i];
			if (--p0->m_refCount == 0)
				p0->destroy();
			m_vec70[i] = 0;
		}
		if (m_vec88[i] != 0)
		{
			IndexBufferRef *p1 = (IndexBufferRef *)m_vec88[i];
			if (--p1->m_refCount == 0)
				p1->destroy();
			m_vec88[i] = 0;
		}
	}
	_STL::vector<void *> *v70 = &m_vec70;
	v70->erase(v70->begin(), v70->end());
	_STL::vector<void *> *v88 = &m_vec88;
	v88->erase(v88->begin(), v88->end());
	_STL::vector<void *> *v7c = &m_vec7C;
	v7c->erase(v7c->begin(), v7c->end());
	_STL::vector<void *> *v94 = &m_vec94;
	v94->erase(v94->begin(), v94->end());
}
