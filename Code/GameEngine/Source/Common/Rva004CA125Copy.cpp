// cl: /DNDEBUG /MD /EHsc
// ??0Rva004CA125@@QAE@ABV0@@Z, retail 0x004CA125, 24 bytes.
// Derived copy ctor: calls rowed ??0Rva004C9FBF at 0x004C9FBF then installs
// vptr 0xBEFE48 (Rva00252B68 vtable, DIR32). No extra members beyond the
// 12-byte base (vptr plus two ints), so 24B (base call plus vptr plus return).
// Precedent is V3PolyDerivedCopyCtors.cpp (0x004C9FBF, 33B, same flags).
// Evidence: callees all rowed; sole caller at 0x004CA1D7 in FUN_008CA1C1
// (AnimationSoundClientBehavior copy-like, same C5EE80/C5EE74 vptrs as ctor
// 0x004CA05A); prev 0x004C9FBF in V3PolyDerivedCopyCtors.cpp.

typedef int Int;

class Rva004C9F61
{
public:
	Rva004C9F61(const Rva004C9F61 &other);
	virtual ~Rva004C9F61();

	Int m_field04;
};

class Rva004C9FBF : public Rva004C9F61
{
public:
	Rva004C9FBF(const Rva004C9FBF &other);
	virtual ~Rva004C9FBF();

	Int m_field08;
};

class Rva004CA125 : public Rva004C9FBF
{
public:
	Rva004CA125(const Rva004CA125 &other);
	virtual ~Rva004CA125();
};

Rva004CA125::Rva004CA125(const Rva004CA125 &other)
	: Rva004C9FBF(other)
{
}
