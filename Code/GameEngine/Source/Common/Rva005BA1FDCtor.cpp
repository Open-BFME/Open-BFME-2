// cl: -GR- -EHsc-
// ??0Rva005BA1FDBox@@QAE@H@Z @0x005BA1FD 55B: composing constructor. Builds
// the base with (0, arg) through the pinned base ctor, installs the three
// polymorphic tables (all DIR32, copied from retail by the gate), publishes
// this to the 0xE06544 global when clear, and returns this. Targets from
// retail REL32/DIR32; table symbols declared never defined.
class Rva005BA1FDBase
{
public:
	Rva005BA1FDBase(int x, int y);
	virtual void BaseVirt();
};

struct Rva005BA1FDM60
{
	virtual void M60Virt();
	char pad[8];
};

struct Rva005BA1FDM6C
{
	virtual void M6CVirt();
};

class Rva005BA1FDBox;
extern Rva005BA1FDBox *g_rva005BA1FDInst;

class Rva005BA1FDBox : public Rva005BA1FDBase
{
	char pad[0x60 - 4];
	Rva005BA1FDM60 m_60;
	Rva005BA1FDM6C m_6c;

public:
	Rva005BA1FDBox(int arg);
	virtual void BoxVirt();
};

Rva005BA1FDBox::Rva005BA1FDBox(int arg)
	: Rva005BA1FDBase(arg, 0)
{
	if (g_rva005BA1FDInst == 0)
		g_rva005BA1FDInst = this;
}
