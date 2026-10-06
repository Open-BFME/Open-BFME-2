// ?rva0043F20C@Rva0043F20C@@QAEXUTreeHintRef00217D4C@@@Z @0x0043F20C 56B.
// Assigns a TreeHintRef into this+0x6c: the operator= loads the source pointer,
// releases the incumbent when non-null, and stores the new one. The target's
// reference-counted base is the stlport rb_tree hint layout; the class here is
// an honest address-named view (offset 0x6c proven by the add ecx).
// cl: /DNDEBUG /MD /EHsc
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
class Rva0043F20C
{
public:
	void rva0043F20C(TreeHintRef00217D4C arg);
private:
	char m_pad00[0x6C];
	TreeHintRef00217D4C m_holder;
};

void Rva0043F20C::rva0043F20C(TreeHintRef00217D4C arg)
{
	TreeHintRef00217D4C *const holder = &m_holder;
	*holder = arg;
}