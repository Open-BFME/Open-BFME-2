// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?CreateInstance@?$_com_ptr_t@V?$_com_IIID@UIFEBrowserEngine2@@$1?_GUID_ee883b17_0778_4b18_a12b_e44c0d298412@@3U__s_GUID@@B@@@@QAEJABU_GUID@@PAUIUnknown@@K@Z
// at retail 0x00176F10 (141B). VS2003 comip.h _com_ptr_t::CreateInstance for
// the browser-engine smart pointer used by DX8WebBrowser::Initialize.
//
// BFME1 near-miss donor (reference/open-bfme-1/.../WebBrowserComCreateInstance.cpp,
// b1 0x00958AB0, 93.6% immediate-only): the logic is the genuine comip.h
// CreateInstance — release any held interface, CoCreateInstance for the class,
// OleRun plus QueryInterface when the context asks for a local or remote
// server, direct CoCreateInstance otherwise, null the slot on failure.
// Immediate-only drift is the two runtime GUID addresses (browser IID
// 0x00BD4E3C, IUnknown IID 0x00BD4E4C) and the ole32 IAT slots
// (CoCreateInstance 0x00BBABE4, OleRun 0x00BBABE8).
//
// The VS2003 toolchain here has no ole2.h, so this TU carries the minimal
// COM declarations (same template names as comip.h, so the mangling matches)
// instead of including <objbase.h>/<comip.h>. BrowserEngine.DLL is absent, so
// the IFEBrowserEngine2 uuid declaration reproduces the type-library IID.

struct _GUID
{
	unsigned long m_data1;
	unsigned short m_data2;
	unsigned short m_data3;
	unsigned char m_data4[8];
};
typedef _GUID GUID;
typedef _GUID IID;
typedef _GUID CLSID;
typedef long HRESULT;
typedef unsigned long DWORD;
typedef unsigned long ULONG;

struct __declspec(uuid("00000000-0000-0000-c000-000000000046")) IUnknown
{
	virtual HRESULT __stdcall QueryInterface(const IID &requestedId, void **result) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
};

struct IDispatch : public IUnknown
{
};

extern "C" __declspec(dllimport) HRESULT __stdcall CoCreateInstance(const CLSID &classId, IUnknown *outer,
	DWORD context, const IID &requestedId, void **result);
extern "C" __declspec(dllimport) HRESULT __stdcall OleRun(IUnknown *unknown);

// g_bfmeIidTSA: matched references place it at VA 0xbd4e3c (.rdata), the
// IFEBrowserEngine2 IID {ee883b17-0778-4b18-a12b-e44c0d298412}; retail bytes.
GUID g_bfmeIidTSA = { 0xee883b17, 0x0778, 0x4b18, { 0xa1, 0x2b, 0xe4, 0x4c, 0x0d, 0x29, 0x84, 0x12 } };
// IID_IUnknown: uuid.lib's {00000000-0000-0000-C000-000000000046}, which retail
// links at VA 0xbd4e4c (.rdata); this toolchain has no uuid.lib.
extern "C" const IID IID_IUnknown = { 0x00000000, 0x0000, 0x0000, { 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };

struct __declspec(uuid("ee883b17-0778-4b18-a12b-e44c0d298412"))
	IFEBrowserEngine2 : public IDispatch
{
};

template<typename BrowserInterface, const IID *BrowserIid>
class _com_IIID
{
public:
	typedef BrowserInterface Interface;

	static const IID &GetIID() throw()
	{
		return *BrowserIid;
	}
};

template<typename BrowserIidBinding>
class _com_ptr_t
{
public:
	typedef BrowserIidBinding ThisIIID;
	typedef typename BrowserIidBinding::Interface Interface;

	static const IID &GetIID() throw()
	{
		return ThisIIID::GetIID();
	}

	HRESULT CreateInstance(const CLSID &classId, IUnknown *outer, DWORD context) throw()
	{
		HRESULT createResult;

		_Release();

		if (context & (4 | 16)) {
			IUnknown *unknownInstance;
			createResult = CoCreateInstance(classId, outer, context, IID_IUnknown,
				reinterpret_cast<void **>(&unknownInstance));

			if (createResult >= 0) {
				createResult = OleRun(unknownInstance);

				if (createResult >= 0) {
					createResult = unknownInstance->QueryInterface(GetIID(),
						reinterpret_cast<void **>(&m_wrappedInterface));
				}

				unknownInstance->Release();
			}
		} else {
			createResult = CoCreateInstance(classId, outer, context, GetIID(),
				reinterpret_cast<void **>(&m_wrappedInterface));
		}

		if (createResult < 0) {
			m_wrappedInterface = 0;
		}

		return createResult;
	}

private:
	Interface *m_wrappedInterface;

	void _Release() throw()
	{
		if (m_wrappedInterface != 0) {
			m_wrappedInterface->Release();
		}
	}
};

// Both browser units bind runtime IID references to these existing owners;
// keep the UUID template argument for the toolchain's type identity.
template <> inline const IID &
_com_IIID<IFEBrowserEngine2, &__uuidof(IFEBrowserEngine2)>::GetIID() throw()
{
	return g_bfmeIidTSA;
}

typedef _com_ptr_t<_com_IIID<IFEBrowserEngine2, &__uuidof(IFEBrowserEngine2)> >
	IFEBrowserEngine2Ptr;

template HRESULT IFEBrowserEngine2Ptr::CreateInstance(
	const CLSID &classId, IUnknown *outer, DWORD context) throw();
