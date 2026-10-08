// cl: /MD
// ??0Rva003FE792@@QAE@UTreeHintRef00217D4C@@H@Z @0x003FE792 56B: ctor storing vtable 0x00837E88 plus TreeHintRef at +8 with AddRef plus ints plus Release of input on non-null. Evidence: callees rowed Release 0x0007DEEF plus caller 0x0031A0AB; same TreeHint shape as rowed setter 0x005C96A9.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *) throw();
struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
		if (m_ptr) ++m_ptr->references;
	}
	__forceinline ~TreeHintRef00217D4C() {
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
extern const void *const g_00C37E88[];
class Rva003FE792 {
	const void *m_vtable;
	int m_i04;
	TreeHintRef00217D4C m_hint08;
	bool m_b0C;
	int m_i10;
	int m_i14;
public:
	Rva003FE792(TreeHintRef00217D4C hint, int value);
	~Rva003FE792();
};

Rva003FE792::Rva003FE792(TreeHintRef00217D4C hint, int value)
	: m_vtable(g_00C37E88)
	, m_i04(0)
	, m_hint08(hint)
	, m_b0C(false)
	, m_i10(0)
	, m_i14(value)
{
}
