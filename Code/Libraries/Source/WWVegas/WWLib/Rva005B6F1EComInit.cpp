// cl: /O1 /G7 /MD /DNDEBUG
// ?rva005B6F1E@Rva005B6F1E@@QAEXPBG0@Z @ 0x005B6F1E (242B): init two wide strings then CoCreateInstance chain.
// Evidence: ret 8 two wchar args; wcslen/new[]/wcscpy prefix; CoCreateInstance IAT 0x00BBABE4 with GUID VAs
// 0x00C73770/0x00C73780; vtable calls +0x1c/+0x1c/+0x20 with Release at +8; flags at +8/+0xa; com ptr at +0x10.
// Caller 0x00516211 unclaimed 2802B. Class from honest-address convention (owner unknown).

struct GUID
{
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
};
typedef long HRESULT;
typedef unsigned long DWORD;
typedef unsigned long ULONG;

struct ISecond
{
	virtual HRESULT __stdcall QueryInterface(const GUID &id, void **out) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
	virtual HRESULT __stdcall E1() = 0;
	virtual HRESULT __stdcall E2() = 0;
	virtual HRESULT __stdcall E3() = 0;
	virtual HRESULT __stdcall E4() = 0;
	virtual HRESULT __stdcall GetThird(void **out) = 0;
};

struct IFirst
{
	virtual HRESULT __stdcall QueryInterface(const GUID &id, void **out) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
	virtual HRESULT __stdcall D1() = 0;
	virtual HRESULT __stdcall D2() = 0;
	virtual HRESULT __stdcall D3() = 0;
	virtual HRESULT __stdcall D4() = 0;
	virtual HRESULT __stdcall GetSecond(void **out) = 0;
};

struct IThird
{
	virtual HRESULT __stdcall QueryInterface(const GUID &id, void **out) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
	virtual HRESULT __stdcall F1() = 0;
	virtual HRESULT __stdcall F2() = 0;
	virtual HRESULT __stdcall F3() = 0;
	virtual HRESULT __stdcall F4() = 0;
	virtual HRESULT __stdcall F5() = 0;
	virtual HRESULT __stdcall GetFlag(unsigned short *out) = 0;
};

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short *s);
extern "C" __declspec(dllimport) unsigned short *__cdecl wcscpy(unsigned short *dst, const unsigned short *src);
extern "C" __declspec(dllimport) HRESULT __stdcall CoCreateInstance(const GUID &clsid, void *outer, DWORD ctx, const GUID &iid, void **out);
void *__cdecl operator new[](unsigned int size);

extern "C" const GUID g_00C73770;
extern "C" const GUID g_00C73780;

class Rva005B6F1E
{
	unsigned short *m_a;
	unsigned short *m_b;
	bool m_ok1;
	unsigned char _p1;
	bool m_ok2;
	unsigned char _p2[5];
	IThird *m_com;
public:
	void rva005B6F1E(const unsigned short *a1, const unsigned short *a2);
};

void Rva005B6F1E::rva005B6F1E(const unsigned short *a1, const unsigned short *a2)
{
	IFirst *p1 = 0;
	IFirst *p2 = 0;
	unsigned short v;
	m_a = new unsigned short[wcslen(a1) + 1];
	m_b = new unsigned short[wcslen(a2) + 1];
	wcscpy(m_a, a1);
	wcscpy(m_b, a2);
	m_ok1 = false;
	m_ok2 = false;
	HRESULT hr = CoCreateInstance(g_00C73770, 0, 1, g_00C73780, (void **)&p1);
	if (hr < 0) {
		if (p1 != 0)
			p1->Release();
		return;
	}
	hr = p1->GetSecond((void **)&p2);
	if (hr < 0) {
		if (p1 != 0)
			p1->Release();
		if (p2 != 0)
			p2->Release();
		return;
	}
	hr = p2->GetSecond((void **)&m_com);
	if (hr < 0) {
		if (p1 != 0)
			p1->Release();
		if (p2 != 0)
			p2->Release();
		return;
	}
	m_ok1 = true;
	if (p2 != 0)
		p2->Release();
	if (p1 != 0)
		p1->Release();
	hr = m_com->GetFlag(&v);
	if (hr < 0)
		return;
	if (v != 0)
		m_ok2 = true;
}
// ?rva005B7010@Rva005B7010@@QAEXXZ @0x005B7010 34B
// COM cleanup adjacent to 0x005B6F1E: releases IUnknown at +0x10 via Release slot +8 then CoUninitialize if HRESULT at +0xC >= 0.
// Evidence: retail mov eax [esi+0x10] test je mov ecx [eax] push eax call [ecx+8] and [esi+0x10] 0 cmp [esi+0xC] 0 jl jmp IAT CoUninitialize 0x00BBABE0; caller 0x00514EE1; same TU same flags.
struct IUnknown005B7010
{
	virtual HRESULT __stdcall QueryInterface(const GUID &id, void **out) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
};
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();
class Rva005B7010
{
public:
	void rva005B7010();
private:
	char m_pad[0x0C];
	HRESULT m_hr;
	IUnknown005B7010 *m_com;
};
void Rva005B7010::rva005B7010()
{
	if (m_com != 0)
	{
		m_com->Release();
		m_com = 0;
	}
	if (m_hr < 0)
		return;
	CoUninitialize();
}
