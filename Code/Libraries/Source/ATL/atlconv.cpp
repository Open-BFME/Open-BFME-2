// cl: /O1 /EHsc
// Microsoft Visual C++ .NET 2003 ATL 7.1 atlconv.h members.
//
// CA2WEX keeps a t_nBufferLength-wide-character buffer inside the object and
// only reaches for malloc when the converted string does not fit, so the
// constructor that primes m_psz with m_szBuffer is what leaves Init free to
// overwrite the pointer on the heap path. AtlThrow and AtlThrowLastWin32 are
// ATL_NOINLINE, which is why both stay out of line here.

typedef const char *LPCSTR;
typedef char *LPSTR;
typedef unsigned short *LPWSTR;
typedef const unsigned short *LPCWSTR;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long HRESULT;

#define NULL 0
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define HRESULT_FROM_WIN32(x) 	((HRESULT)(x) <= 0 ? ((HRESULT)(x)) 			   : ((HRESULT)(((x) & 0x0000FFFF) | 0x80070000)))

extern "C" __declspec(dllimport) int __stdcall lstrlenA(LPCSTR string);
extern "C" __declspec(dllimport) int __stdcall lstrlenW(LPCWSTR string);
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
		UINT code_page, DWORD flags, LPCSTR multi_byte, int multi_byte_chars,
		LPWSTR wide, int wide_chars);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(
        UINT code_page, DWORD flags, LPCWSTR wide, int wide_chars,
        LPSTR multi_byte, int multi_byte_chars, LPCSTR default_char,
        int *used_default_char);
extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int size);
extern "C" __declspec(dllimport) void __cdecl free(void *block);
extern "C" __declspec(dllimport) DWORD __stdcall GetLastError();
// Not GetACP. Both constructors call through the code-page slot at
// 0x00DA5E40, which retail initialises to the dispatcher at 0x000010CF: that
// body calls GetVersionExA and installs either the four-byte NT5+ path at
// 0x0044827C, which is push 3 / pop eax / ret and so returns CP_THREAD_ACP,
// or the downlevel path at 0x0000107F, which reads LOCALE_IDEFAULTANSICODEPAGE
// for the thread locale and falls back to GetACP only if that yields zero.
// The slot holds 0x004010CF to begin with, so the first call replaces itself.
//
// Spelling it GetACP() compiled to the same bytes, because both are ff 15
// against a DIR32 the comparison masks - the byte check cannot see which
// function an indirect call goes to, and the gate's DIR32 consistency check
// cannot either, since a wrong name that is used consistently is consistent.
// Modelling it as the pointer it is keeps the bytes and fixes the name.
extern "C" UINT(__stdcall *_AtlGetConversionACP)();

LPWSTR __stdcall AtlA2WHelper(LPWSTR lpw, LPCSTR lpa, int nChars, UINT acp)
{
    if (lpw == 0 || lpa == 0)
        return 0;

    lpw[0] = 0;
    int ret = MultiByteToWideChar(acp, 0, lpa, -1, lpw, nChars);
    if (ret == 0)
        return 0;

    return lpw;
}

LPSTR __stdcall AtlW2AHelper(LPSTR lpa, LPCWSTR lpw, int nChars, UINT acp)
{
    if (lpa == 0 || lpw == 0)
        return 0;

    lpa[0] = '\0';
    int ret = WideCharToMultiByte(acp, 0, lpw, -1, lpa, nChars, 0, 0);
    if (ret == 0)
        return 0;

    return lpa;
}

namespace ATL
{

class CAtlException
{
public:
	CAtlException(HRESULT hr) throw() :
		m_hr(hr)
	{
	}

	operator HRESULT() const throw()
	{
		return (m_hr);
	}

public:
	HRESULT m_hr;
};

__declspec(noinline) __declspec(noreturn) inline void __stdcall AtlThrow(HRESULT hr)
{
	throw CAtlException(hr);
}

__declspec(noinline) __declspec(noreturn) inline void __stdcall AtlThrowLastWin32()
{
	DWORD dwError = ::GetLastError();
	AtlThrow(HRESULT_FROM_WIN32(dwError));
}

template <int t_nBufferLength = 128>
class CA2WEX
{
public:
	CA2WEX(LPCSTR psz) : m_psz(m_szBuffer)
	{
		Init(psz, _AtlGetConversionACP());
	}
	CA2WEX(LPCSTR psz, UINT nCodePage) : m_psz(m_szBuffer)
	{
		Init(psz, nCodePage);
	}
	~CA2WEX()
	{
		if (m_psz != m_szBuffer)
			free(m_psz);
	}

	operator LPWSTR() const { return m_psz; }

private:
	void Init(LPCSTR psz, UINT nCodePage);

public:
	LPWSTR m_psz;
	unsigned short m_szBuffer[t_nBufferLength];

private:
	CA2WEX(const CA2WEX &);
	CA2WEX &operator=(const CA2WEX &);
};

template <int t_nBufferLength = 128>
class CW2AEX
{
public:
    CW2AEX(LPCWSTR psz) : m_psz(m_szBuffer)
    {
        Init(psz, _AtlGetConversionACP());
    }
    ~CW2AEX();

    __declspec(noinline) void deallocate()
    {
        free(m_psz);
    }

private:
    void Init(LPCWSTR psz, UINT nCodePage);

public:
    char *m_psz;
    char m_szBuffer[t_nBufferLength];
};

template <int t_nBufferLength>
void CW2AEX<t_nBufferLength>::Init(LPCWSTR psz, UINT nCodePage)
{
	if (psz == NULL)
	{
		m_psz = NULL;
		return;
	}
	int nLengthW = lstrlenW(psz) + 1;
	int nLengthA = nLengthW * 2;

	if (nLengthA > t_nBufferLength)
	{
		m_psz = static_cast<LPSTR>(malloc(nLengthA * sizeof(char)));
		if (m_psz == NULL)
		{
			AtlThrow(E_OUTOFMEMORY);
		}
	}

	if (::WideCharToMultiByte(nCodePage, 0, psz, nLengthW, m_psz, nLengthA, NULL, NULL) == 0)
	{
		AtlThrowLastWin32();
	}
}

template <int t_nBufferLength>
CW2AEX<t_nBufferLength>::~CW2AEX()
{
    if (m_psz != m_szBuffer)
        deallocate();
}

template <int t_nBufferLength>
void CA2WEX<t_nBufferLength>::Init(LPCSTR psz, UINT nCodePage)
{
	if (psz == NULL)
	{
		m_psz = NULL;
		return;
	}
	int nLengthA = lstrlenA(psz) + 1;
	int nLengthW = nLengthA;

	if (nLengthW > t_nBufferLength)
	{
		m_psz = static_cast<LPWSTR>(malloc(nLengthW * sizeof(unsigned short)));
		if (m_psz == NULL)
		{
			AtlThrow(E_OUTOFMEMORY);
		}
	}

	if (::MultiByteToWideChar(nCodePage, 0, psz, nLengthA, m_psz, nLengthW) == 0)
	{
		AtlThrowLastWin32();
	}
}

template CA2WEX<128>::~CA2WEX();
template CA2WEX<128>::CA2WEX(LPCSTR psz);
template void CA2WEX<128>::Init(LPCSTR psz, UINT nCodePage);
template void CW2AEX<128>::Init(LPCWSTR psz, UINT nCodePage);
template CW2AEX<128>::CW2AEX(LPCWSTR psz);
template CW2AEX<128>::~CW2AEX();

}
