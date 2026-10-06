// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00151744@Rva00151744@@QAEXXZ at 0x00151744 (113B). Link clear: if +4
// null return, else erase voidptr vector at +0x18 via rowed erase 0x0031BD55,
// zero +0x24, lock via row 0x0011F520, delete +8 holder via rowed dtor
// 0x00153D16 plus delete, release +4 via vtable slot 2 __stdcall then null,
// unlock via row 0x00120F50. Called from 0x001517BB in 0x001517B5 slot 7 of
// vtable 0x007D3A6C.
#include <vector>

class Rva00153D16
{
public:
	~Rva00153D16();
};

typedef void (__stdcall *SurfaceRelease)(void *surface);

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva00151744
{
public:
	virtual void *get(int x);
	void rva00151744();
private:
	void *m_comPtr; // +4
	Rva00153D16 *m_holder; // +8
	char m_pad0C[0x0C]; // +0x0C
	_STL::vector<void *> m_vec; // +0x18
	int m_flag24; // +0x24
};

void Rva00151744::rva00151744()
{
	if (m_comPtr == 0)
		return;
	_STL::vector<void *> *vec = &m_vec;
	vec->erase(vec->begin(), vec->end());
	m_flag24 = 0;
	BFMEDX8DeviceLock guard;
	Rva00153D16 *holder = m_holder;
	if (holder != 0) {
		delete holder;
		m_holder = 0;
	}
	void *p = m_comPtr;
	if (p != 0) {
		((SurfaceRelease *)(*(void ***)p))[2](p);
		m_comPtr = 0;
	}
}
