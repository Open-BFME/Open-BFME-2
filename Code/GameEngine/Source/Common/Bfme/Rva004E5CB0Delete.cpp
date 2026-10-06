// cl: /MD
// ?Rva004E5CB0Delete@@YGXPAX@Z @0x004E5CB0 (27B)
// __stdcall null-checked deleter for Rva004E5A78: calls its rowed dtor then
// operator delete. Evidence: chain lane calls 0x004E5A78 which just landed;
// caller 0x004E5D4D pushes one pointer arg; ret 4 confirms __stdcall.
class Rva004E5A78
{
public:
	~Rva004E5A78();
};

void __stdcall Rva004E5CB0Delete(void *p)
{
	if (p != 0) {
		((Rva004E5A78 *)p)->~Rva004E5A78();
		::operator delete(p);
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??RRva004E5CB0Deleter@@QBEXPAVRva004E5A78@@@Z=?Rva004E5CB0Delete@@YGXPAX@Z")
