// cl: /O1 /DNDEBUG /MD
//
// DllHandle::LoadFailure, retail 0x00203EA8 (18 bytes).
// The thrown object of DllHandle::DllHandle on LoadLibrary failure; throw
// info 0x00D11F4C names DllHandle::LoadFailure over DllHandle::Exception
// over exception, which proves the name. Retail base-constructs through
// the rowed ??0FunctorNotSet@@QAE@XZ at 0x002035E2 (shared 0x0C-byte
// std::exception child, same vtable 0x00BD3B54) and then installs that
// vtable explicitly over the novtable model, mirroring FunctorNotSetCtor.
// Shard (not graft): the home DllHandle TU carries /EHsc, which would wrap
// this frameless leaf.

class __declspec(dllimport) exception
{
public:
	exception();
};

class __declspec(novtable) FunctorNotSet : public exception
{
public:
	FunctorNotSet();
};

class DllHandle
{
public:
	class LoadFailure : public FunctorNotSet
	{
	public:
		LoadFailure();
	};
};

// ??0LoadFailure@DllHandle@@QAE@XZ @0x203EA8
DllHandle::LoadFailure::LoadFailure()
	: FunctorNotSet()
{
	*(unsigned int *)this = 0x00BD3B54;
}
