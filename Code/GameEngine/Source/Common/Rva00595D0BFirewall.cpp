// cl: /MD
// ?rva00595D0B@FirewallHelperClass@@UAEPAXI@Z @0x00595D0B 34B: store vtable 0x00870A2C then rowed clear 0x0059515C plus conditional delete. Evidence: vtable slot 0 of 0x00870A2C class FirewallHelperClass ctor 0x00594CDD; calls row 0x0059515C and rowed delete 0x0002FD60.
class Rva0059515C
{
public:
	void rva0059515C();
};

extern const void *const g_00C70A2C[];
void __cdecl operator delete(void *p);

class FirewallHelperClass
{
public:
	virtual void *rva00595D0B(unsigned int flags);
};

void *FirewallHelperClass::rva00595D0B(unsigned int flags)
{
	*(const void **)this = g_00C70A2C;
	((Rva0059515C *)this)->rva0059515C();
	if (flags & 1)
		::operator delete(this);
	return this;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00C70A2C@@3QBQBXB=??_7FirewallHelperClass@@6B@")
