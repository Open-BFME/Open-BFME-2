// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1HordeMeleeFormation@@UAE@XZ, retail 0x00586E51 53B.
// Dtor of HordeMeleeFormation (ctor rowed 0x00586D8E 49B in Rva00586D8ECtor.cpp):
// base Rva005D6FCC (vptr+held at +0 vtbl 0x00C75C38 base dtor pin ??1Rva005D6FCC at 0x005D6FDE twin of apply)
// then vector at +8 via rowed vector dtor ??1Rva00586C17 at 0x00586C17 bool at +0x14 ptr at +0x18.
// Caller 0x00586E35 28B is ??_G (vtable 0x0086FD90 slot0). EH_prolog with states 0/-1 around member dtor.
// Same recipe as sibling ??1Rva00587F69 in Rva00587F69Dtor.cpp (novtable base twin).
class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

struct Rva00586C17
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva00586C17();
};

class __declspec(novtable) HordeMeleeFormation : public Rva005D6FCC
{
public:
	virtual ~HordeMeleeFormation();
private:
	Rva00586C17 m_vec; // +8
	bool m_flag; // +0x14
	void *m_other; // +0x18
};

HordeMeleeFormation::~HordeMeleeFormation()
{
}
