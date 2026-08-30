// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 atlconv.h members.
//
// CA2WEX keeps a t_nBufferLength-wide-character buffer inside the object and
// only reaches for malloc when the converted string does not fit, so the
// constructor that primes m_psz with m_szBuffer is what leaves Init free to
// overwrite the pointer on the heap path. AtlThrow and AtlThrowLastWin32 are
// ATL_NOINLINE, which is why both stay out of line here.

typedef const char *LPCSTR;
typedef unsigned short *LPWSTR;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long HRESULT;

#define NULL 0
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define HRESULT_FROM_WIN32(x) 	((HRESULT)(x) <= 0 ? ((HRESULT)(x)) 			   : ((HRESULT)(((x) & 0x0000FFFF) | 0x80070000)))

extern "C" __declspec(dllimport) int __stdcall lstrlenA(LPCSTR string);
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
		UINT code_page, DWORD flags, LPCSTR multi_byte, int multi_byte_chars,
		LPWSTR wide, int wide_chars);
extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int size);
extern "C" __declspec(dllimport) void __cdecl free(void *block);
extern "C" __declspec(dllimport) DWORD __stdcall GetLastError();

namespace ATL
{

__declspec(noreturn) void __stdcall AtlThrow(HRESULT hr);

__declspec(noinline) __declspec(noreturn) inline void __stdcall AtlThrowLastWin32()
{
	DWORD dwError = ::GetLastError();
	AtlThrow(HRESULT_FROM_WIN32(dwError));
}

template <int t_nBufferLength = 128>
class CA2WEX
{
public:
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
template void CA2WEX<128>::Init(LPCSTR psz, UINT nCodePage);

}
