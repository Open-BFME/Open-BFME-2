// cl: /O1 /DNDEBUG /MD /EHsc
//
// BfmeDualVtableReleaseDtor::BfmeDualVtableReleaseDtor(int), retail
// 0x0020429D (120 bytes; exact Ghidra extent). The FX particle-editor loader built in
// ScriptEngine::init: base-constructs the rowed DllHandle with
// "FXParticleEditorI.dll", installs the loader vtable 0x00BE3994, then
// resolves GetFXParticleEditor via GetProcAddress, builds the release
// target through the resolved factory, and pokes its slot-0 virtual.
// Either failure throws DllHandle::LoadFailure through the shared cold
// pad at 0x002042F7. The int argument is unused (ret 4).
//
// The pad builds its temp through std::exception plus the 0x00BD3B54
// vtable directly, so this TU models LoadFailure minimally over
// std::exception with an inline vtable-storing ctor (the rowed 18B ctor
// over FunctorNotSet would emit a call instead of the pad). Shard: the
// dtor TU carries /O1 without EH shaping, which would recolor this frame.

extern "C" const void *const vtbl_00BE3994[];  // ??_7BfmeDualVtableReleaseDtor@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE3994=??_7BfmeDualVtableReleaseDtor@@6B@")
extern const void *const g_00BD3B54[];

typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *name);

class __declspec(dllimport) exception
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
	DllHandle(const char *name);
	~DllHandle();
	virtual void bfmeKeepVtable(void);

protected:
	HMODULE m_module; // +0x04
};

class BfmeReleaseTarget
{
public:
	virtual void bfmeSlot0(void);
};

class BfmeDualVtableReleaseDtor : public DllHandle
{
public:
	BfmeDualVtableReleaseDtor(int /*unused*/);

private:
	BfmeReleaseTarget *m_target; // +0x08
};

class LoadFailure : public exception
{
public:
	LoadFailure()
	{
		*(const void **)this = g_00BD3B54;
	}
};

typedef BfmeReleaseTarget *(__stdcall *BfmeReleaseFactory)(void);

// ??0BfmeDualVtableReleaseDtor@@QAE@H@Z @0x20429D
BfmeDualVtableReleaseDtor::BfmeDualVtableReleaseDtor(int /*unused*/)
	: DllHandle("FXParticleEditorI.dll")
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BE3994);
	HMODULE module = m_module;
	FARPROC factory = GetProcAddress(module, "GetFXParticleEditor");
	if (!factory || !(m_target = ((BfmeReleaseFactory)factory)()))
		throw LoadFailure();
	m_target->bfmeSlot0();
}
