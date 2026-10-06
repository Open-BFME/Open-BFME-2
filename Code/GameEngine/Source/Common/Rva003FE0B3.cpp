// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva003FE0B3@Rva003FE0B3@@QAEXUTreeHintRef00217D4C@@@Z @0x003FE0B3 56B: TreeHintRef setter copying to +0x4C via rowed operator= then releasing input on non-null. Evidence: callees rowed TreeHintRef op= 0x002174A4 and Release 0x0007DEEF plus caller 0x0031A0AB; same shape as rowed setter 0x005C96A9.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
		if (m_ptr) ++m_ptr->references;
	}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C() {
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva003FE0B3 {
	char m_pad[0x4C];
	TreeHintRef00217D4C m_hint;
public:
	void rva003FE0B3(TreeHintRef00217D4C hint);
};

void Rva003FE0B3::rva003FE0B3(TreeHintRef00217D4C hint)
{
	m_hint = hint;
}
