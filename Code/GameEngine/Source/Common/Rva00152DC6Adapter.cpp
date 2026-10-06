// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: scratch adapter at 0x152DC6 (35B). Passes a by-value
// 44-byte scratch to the 0x152BDB grower; the scratch is initialized inline
// through the 0x151597 builder. Opaque copy/dtor (declared, never defined
// here) forces MSVC to construct the temporary in place - the same device
// as the 0x150C74 adapter - giving the push-ecx/push-esi/sub prolog with
// the ebp-4 spill. Address-derived names.

class Rva00151597
{
public:
	void *rva00151597();
};
struct Rva00152DC6Tmp
{
	char m_bytes[36];
	Rva00152DC6Tmp()
	{
		((Rva00151597 *)this)->rva00151597();
	}
	Rva00152DC6Tmp(const Rva00152DC6Tmp &other);
	~Rva00152DC6Tmp();
};
class Rva00152BDB
{
public:
	void rva00152BDB(int n, Rva00152DC6Tmp tmp);
};
class Rva00152DC6
{
public:
	void rva00152DC6(int n);
};

// ?rva00152DC6@Rva00152DC6@@QAEXH@Z
void Rva00152DC6::rva00152DC6(int n)
{
	((Rva00152BDB *)this)->rva00152BDB(n, Rva00152DC6Tmp());
}
