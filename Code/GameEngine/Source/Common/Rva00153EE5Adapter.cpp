// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: scratch adapter at 0x153EE5 (35B). Passes a by-value
// 76-byte scratch to the 0x153E6F grower; the scratch is initialized inline
// through the 0x1538A8 builder. Opaque copy/dtor (declared, never defined
// here) forces MSVC to construct the temporary in place - the same device
// as the 0x150C74 and 0x152DC6 adapters. Address-derived names.

class Rva001538A8
{
public:
	void *rva001538A8();
};
struct Rva00153EE5Tmp
{
	char m_bytes[76];
	Rva00153EE5Tmp()
	{
		((Rva001538A8 *)this)->rva001538A8();
	}
	Rva00153EE5Tmp(const Rva00153EE5Tmp &other);
	~Rva00153EE5Tmp();
};
class Rva00153E6F
{
public:
	void rva00153E6F(int n, Rva00153EE5Tmp tmp);
};
class Rva00153EE5
{
public:
	void rva00153EE5(int n);
};

// ?rva00153EE5@Rva00153EE5@@QAEXH@Z
void Rva00153EE5::rva00153EE5(int n)
{
	((Rva00153E6F *)this)->rva00153E6F(n, Rva00153EE5Tmp());
}
