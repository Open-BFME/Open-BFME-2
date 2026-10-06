// cl: /MD
//
// CRT static initializer and atexit cleanup for ATL CInitGDIPlus.
//
// 0x007B5542 (22B): constructs g_initGDIPlusAtE09E30 and registers rva007B9AEA via atexit.
// 0x007B9AEA (22B): atexit callback: calls ReleaseGDIPlus() then DeleteCriticalSection(&m_sect).

extern "C" int __cdecl atexit(void (__cdecl *callback)());

struct CRITICAL_SECTION
{
	void *d[6];
};

extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(CRITICAL_SECTION *cs);

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
};

}

ATL::CImage::CInitGDIPlus g_initGDIPlusAtE09E30;

// 0x007B9AEA (22B): CInitGDIPlus atexit teardown.
void rva007B9AEA()
{
	g_initGDIPlusAtE09E30.ReleaseGDIPlus();
	DeleteCriticalSection(&g_initGDIPlusAtE09E30.m_sect);
}

// 0x007B5542 (22B): CInitGDIPlus static initializer.
void rva007B5542()
{
	ATL::CImage::CInitGDIPlus *p = &g_initGDIPlusAtE09E30;
	p->ATL::CImage::CInitGDIPlus::CInitGDIPlus();
	atexit(rva007B9AEA);
}
