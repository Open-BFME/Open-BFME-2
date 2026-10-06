// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva001517DE@@UAE@XZ at 0x001517DE (136B). Dtor storing vtable 0x007D3AA8,
// deletes +8 holder via rowed 0x00153D16 plus delete, releases +4 via vtable
// slot 2 __stdcall then nulls under lock rows 0x0011F520/0x00120F50, frees
// +0x18 via rowed free 0x00030830, tears down +0x0C vector via rowed
// 0x0007C5D5. Caller 0x00151899 deleting dtor proves ??1. Layout mirrors
// holder plus vector plus strdup shape.
#include <vector>

extern "C" void __cdecl free(void *block);

class Rva001517DEString
{
public:
	~Rva001517DEString() { if (m_data != 0) free(m_data); }
private:
	void *m_data;
};

struct Rva0007BB16Record
{
	~Rva0007BB16Record();
	Rva001517DEString m_00;
	int m_04;
	Rva001517DEString m_08;
	int m_tail0C[6];
};

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

class Rva001517DE
{
public:
	virtual ~Rva001517DE();
private:
	void *m_comPtr; // +4
	Rva00153D16 *m_holder; // +8
	_STL::vector<Rva0007BB16Record> m_vec; // +0x0C
	Rva001517DEString m_str; // +0x18
};

Rva001517DE::~Rva001517DE()
{
	{
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
}
