// cl: /DNDEBUG /MD /EHsc
// ??0Rva004ABB03@@QAE@ABV0@@Z @0x004ABB03 24B: derived copy calls rowed base 0x004AB7EB copy then reinstalls vptr 0x0084ED70. Base declared only so the E8 stays outlined. Caller at 0x004ABCED. Prev stlport_map_int_ptr_o1 next UpdateModuleDeletingDtors but model and flags from V3Poly family.

typedef int Int;

class Rva004AB7EB
{
public:
	Rva004AB7EB(const Rva004AB7EB &other);
	virtual ~Rva004AB7EB();

	Int m_field04;
};

class Rva004ABB03 : public Rva004AB7EB
{
public:
	Rva004ABB03(const Rva004ABB03 &other);
	virtual ~Rva004ABB03();
};

Rva004ABB03::Rva004ABB03(const Rva004ABB03 &other)
	: Rva004AB7EB(other)
{
}
