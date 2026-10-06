// cl: /MD
//
// ??1DamageFilteredCreateObjectDie@@UAE@XZ, retail 0x00485EC3, 32 bytes.
// Target evidence: the audited scalar deleting dtor 0x00485FC7 calls this
// body; slot 4 -> 0x00485EFD uses class-name string
// "DamageFilteredCreateObjectDie". Shape follows DieModuleDerived.cpp with one
// more empty polymorphic base: vptr restores at +0x00/+0x0C/+0x10/+0x14, then
// a tail jmp to DieModule::~DieModule 0x0045CE54. The empty bases are
// structural stand-ins; their real types are unrecovered.

class DieModule
{
protected:
	virtual ~DieModule();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class DamageFilteredCreateObjectDie_B2
{
public:
	virtual void f2();
};

class DamageFilteredCreateObjectDie_B3
{
public:
	virtual void f3();
};

class DamageFilteredCreateObjectDie : public DieModule, public MiBase1,
	public DamageFilteredCreateObjectDie_B2, public DamageFilteredCreateObjectDie_B3
{
public:
	virtual ~DamageFilteredCreateObjectDie();
};

DamageFilteredCreateObjectDie::~DamageFilteredCreateObjectDie()
{
}
