// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: scratch adapter at 0x1DF8F8 (35B). Passes a by-value
// record to the 0x1DF88C grower; the record is built by the rowed
// Rva001DE6E1 default ctor (0x1DE6E1). Codegen view only (opaque members,
// declared copy/dtor force in-place construction - the same device as the
// other adapters). Address-derived names.

class Rva001DE6E1
{
	char m_bytes[48];
public:
	Rva001DE6E1();
	Rva001DE6E1(const Rva001DE6E1 &other);
	~Rva001DE6E1();
};
class Rva001DF88C
{
public:
	void rva001DF88C(int n, Rva001DE6E1 rec);
};
class Rva001DF8F8
{
public:
	void rva001DF8F8(int n);
};

// ?rva001DF8F8@Rva001DF8F8@@QAEXH@Z
void Rva001DF8F8::rva001DF8F8(int n)
{
	((Rva001DF88C *)this)->rva001DF88C(n, Rva001DE6E1());
}
