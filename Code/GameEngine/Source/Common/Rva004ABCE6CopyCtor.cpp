// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
//
// ??0Rva001408C0Target@@QAE@ABU0@@Z @0x004ABCE6 24B: copy constructor of the
// registry key base (caller 0x004ABF5D in Rva004ABFD9 copy). Calls the rowed
// base copy 0x004ABB03 then reinstalls vtable 0x0084ED70 (folded s_vtable
// family via data ledger). Base declared only so the call stays outlined.
// Model and flags from the sibling Rva004ABB03CopyCtor TU.

class Rva004ABB03
{
public:
	Rva004ABB03(const Rva004ABB03 &other);
	virtual ~Rva004ABB03();

	int m_04;
};

struct Rva001408C0Target : public Rva004ABB03
{
	Rva001408C0Target(const Rva001408C0Target &other);
	virtual ~Rva001408C0Target();
};

Rva001408C0Target::Rva001408C0Target(const Rva001408C0Target &other) :
	Rva004ABB03((const Rva004ABB03 &)other)
{
}
