// cl: /EHsc
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

// HMODULE/FARPROC and the dllimport LoadLibraryA/GetProcAddress come from
// <windows.h>; the local class exception below is the game's own catchable
// type (throw info 0x00D11F4C), not std::exception.
#include <windows.h>

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
	// The copy constructors the throw info names are rowed in
	// ScriptEngine_DllHandleExceptionCopies.cpp (0x0020426C, 0x00204285):
	// declared only, so this unit emits no implicit copies of its own.
	class Exception : public exception
	{
	public:
		Exception(const Exception &other);
	};

	class LoadFailure : public Exception
	{
	public:
		LoadFailure();
		LoadFailure(const LoadFailure &other);
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
