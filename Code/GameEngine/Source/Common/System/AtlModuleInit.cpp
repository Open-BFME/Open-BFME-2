// cl: /MD
//
// CRT static initializer and atexit cleanup for ATL CInitGDIPlus.
//
// 0x007B5542 (22B): constructs ATL::CImage::s_initGDIPlus and registers rva007B9AEA via atexit.
// 0x007B9AEA (22B): atexit callback: calls ReleaseGDIPlus() then DeleteCriticalSection(&m_sect).

// platformsdk
#include <windows.h>
#undef near
#undef far
// atexit goes straight to the CRT thunk (REL32), not the IAT: read
// <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

void rva007B9AEA();
void rva007B5542();

namespace ATL
{

class CImage
{
public:
	class CInitGDIPlus
	{
	public:
		CInitGDIPlus();
		void ReleaseGDIPlus();
		unsigned long m_dwToken;
		CRITICAL_SECTION m_sect;
		long m_nCImageObjects;
	};

private:
	// Defined in Code/Libraries/Source/ATL/atlimage.cpp (ATL 7.1 atlimage.h).
	static CInitGDIPlus s_initGDIPlus;
	friend void ::rva007B9AEA();
	friend void ::rva007B5542();
};

}

// 0x007B9AEA (22B): CInitGDIPlus atexit teardown.
void rva007B9AEA()
{
	ATL::CImage::s_initGDIPlus.ReleaseGDIPlus();
	DeleteCriticalSection(&ATL::CImage::s_initGDIPlus.m_sect);
}

// 0x007B5542 (22B): CInitGDIPlus static initializer.
void rva007B5542()
{
	ATL::CImage::CInitGDIPlus *p = &ATL::CImage::s_initGDIPlus;
	p->ATL::CImage::CInitGDIPlus::CInitGDIPlus();
	atexit(rva007B9AEA);
}
