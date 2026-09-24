// cl: /O1 /EHsc
//
// DllHandle::DllHandle(const char *), retail 0x00204230 (60 bytes).
// The class name is target evidence: the object it throws on a failed
// LoadLibrary has throw info 0x00D11F4C, and its catchable types name
// DllHandle::LoadFailure, DllHandle::Exception and exception. Retail places
// the class in an anonymous namespace. It is declared at global scope here
// because the ?A0x hash is not reproducible.
//
// This is the base of the particle-editor loader built in ScriptEngine::init
// (derived ctor 0x0020429D; destructor matched as BfmeDualVtableReleaseDtor,
// whose TU names this base BfmeDualVtableReleaseBase). The base vtable
// (0xBE3990) has a single slot.

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
