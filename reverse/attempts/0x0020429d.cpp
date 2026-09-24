// ??0BfmeDualVtableReleaseDtor@@QAE@H@Z
// partial score=0.6 date=2026-09-24
// cl: /O1 /EHsc

typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *name);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *name);

class exception
{
public:
	exception();
	exception(const exception &that);
	virtual ~exception();

private:
	const char *m_what;
	int m_doFree;
};

class DllHandle
{
public:
	class Exception : public exception
	{
	};

	class LoadFailure : public Exception
	{
	public:
		LoadFailure();
	};

	DllHandle(const char *name);
	__forceinline ~DllHandle(void) {}
	virtual void bfmeKeepVtable(void) {}

protected:
	HMODULE m_module; // +0x04
};

DllHandle::DllHandle(const char *name)
{
	m_module = LoadLibraryA(name);
	if (!m_module)
		throw LoadFailure();
}

class BfmeReleaseTarget
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeRelease(void) = 0;
};

class BfmeDualVtableReleaseDtor : public DllHandle
{
public:
	BfmeDualVtableReleaseDtor(int unused);
	virtual ~BfmeDualVtableReleaseDtor(void);

private:
	BfmeReleaseTarget *m_target; // +0x08
};

BfmeDualVtableReleaseDtor::BfmeDualVtableReleaseDtor(int unused)
	: DllHandle("FXParticleEditorI.dll")
{
	typedef BfmeReleaseTarget *(__cdecl *GetEditorProc)();
	GetEditorProc proc = (GetEditorProc)GetProcAddress(m_module, "GetFXParticleEditor");
	if (proc) {
		m_target = proc();
		if (m_target)
			m_target->bfmeSlot0();
	}
}
