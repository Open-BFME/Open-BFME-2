// cl: /O1
// Open-BFME5 conversions.

// BFME1 imports this helper under its own slot name; retail BFME2 slot
// 0x00BBABEC is ole32!CoInitializeEx, so the import is spelled as such here.
extern "C" __declspec(dllimport) long __stdcall CoInitializeEx(void *reserved, unsigned long flags);

typedef unsigned short *BSTR;
typedef short VARIANT_BOOL;
typedef long HRESULT;

extern "C" __declspec(dllimport) BSTR __stdcall SysAllocString(const unsigned short *value);
extern "C" __declspec(dllimport) unsigned int __stdcall SysStringLen(BSTR value);
extern "C" __declspec(dllimport) void __stdcall SysFreeString(BSTR value);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct Rva005B7032ComObject;

typedef HRESULT (__stdcall *Rva005B7032Release)(Rva005B7032ComObject *self);
typedef HRESULT (__stdcall *Rva005B7032GetAuthorizedApplications)(Rva005B7032ComObject *self,
	Rva005B7032ComObject **applications);
typedef HRESULT (__stdcall *Rva005B7032AuthorizedApplicationItem)(Rva005B7032ComObject *self,
	BSTR imageFileName, Rva005B7032ComObject **application);
typedef HRESULT (__stdcall *Rva005B7032GetEnabled)(Rva005B7032ComObject *self,
	VARIANT_BOOL *enabled);

struct Rva005B7032ComVtable
{
	void *m_00[2];
	Rva005B7032Release release;                         // IUnknown::Release, +0x08
	void *m_0c[7];
	Rva005B7032AuthorizedApplicationItem item;          // collection::Item, +0x28
	void *m_2c[6];
	Rva005B7032GetEnabled getEnabled;                   // application::get_Enabled, +0x44
	void *m_48[2];
	Rva005B7032GetAuthorizedApplications getApplications; // profile::get_AuthorizedApplications, +0x50
};

struct Rva005B7032ComObject
{
	Rva005B7032ComVtable *vtable;
};

class BfmeThingTTD
{
public:
	BfmeThingTTD();
	bool rva005B7032();
	const unsigned short *m_name;
	const unsigned short *m_imageFileName;
	bool m_initialized;
	bool m_enabled;
	bool m_added;
	char m_pad0b;
	long m_comResult;
	Rva005B7032ComObject *m_profile;
};

BfmeThingTTD::BfmeThingTTD()
{
	m_name = 0;
	m_imageFileName = 0;
	m_initialized = 0;
	m_enabled = 0;
	m_added = 0;
	m_comResult = 0x80004005;
	m_profile = 0;
	m_comResult = CoInitializeEx(0, 6);
}

// NOTE: the donor also defines BfmeThingTTE::bfmeGoTTE (bfmeOpenTTE /
// bfmeBindTTE imports). No byte-identical BFME2 body was served for it, and
// the ledger hook forbids undeclared definitions, so it is trimmed here
// rather than carried unverified.

// Donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24
// game/GameEngine/Source/Common/BfmeThingTTDAppIsEnabled.cpp, recompiled /O1.
// Target Ghidra entry005B7032/213B independently proves imported BSTR
// allocation/length/free, COM slots08/28/44/50 and fields04/09/10.
// Firewall interpretation and interface slot names come from donor source;
// exact original method and application class names remain unknown.
// ?rva005B7032@BfmeThingTTD@@QAE_NXZ
bool BfmeThingTTD::rva005B7032()
{
	Rva005B7032ComObject *application = 0;
	Rva005B7032ComObject *applications = 0;
	VARIANT_BOOL enabled;
	m_enabled = false;

	HRESULT result = m_profile->vtable->getApplications(m_profile, &applications);
	if (result < 0)
	{
		if (applications != 0)
			applications->vtable->release(applications);
		return false;
	}

	BSTR imageFileName = SysAllocString(m_imageFileName);
	if (SysStringLen(imageFileName) == 0)
	{
		if (applications != 0)
			applications->vtable->release(applications);
		_ReadWriteBarrier();
		return false;
	}

	result = applications->vtable->item(applications, imageFileName, &application);
	if (result >= 0)
	{
		result = application->vtable->getEnabled(application, &enabled);
		if (result < 0 || enabled == 0)
		{
			if (application != 0)
				application->vtable->release(application);
			if (applications != 0)
				applications->vtable->release(applications);
			SysFreeString(imageFileName);
			return false;
		}

		m_enabled = true;
		_ReadWriteBarrier();
	}

	SysFreeString(imageFileName);
	if (application != 0)
		application->vtable->release(application);
	if (applications != 0)
		applications->vtable->release(applications);
	return m_enabled;
}
