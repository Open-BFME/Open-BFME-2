// cl: /EHsc /MD
//
// ?Rva005CD841Find@@YA_NPAX@Z retail 0x005CD841 54B visit list via stack Visitor with bool result.
// Evidence: callee 0x005CCD36 rowed visit caller 0x005CD8C2 tests al sibling of 0x005CD813 vtable 0x0087500C bool at +4.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
struct Visitor005CCCD0
{
	virtual bool visit(TargetRef00217D4C *p) = 0;
	virtual ~Visitor005CCCD0() {}
};
class Rva005CCD36
{
public:
	void rva005CCD36(Visitor005CCCD0 *v);
};
class Rva005CD841Visitor : public Visitor005CCCD0
{
public:
	Rva005CD841Visitor();
	virtual ~Rva005CD841Visitor() {}
	virtual bool visit(TargetRef00217D4C *p) { m_found = true; return true; }
	bool m_found;
};
// ??0Rva005CD841Visitor@@QAE@XZ @0x005CD801 9B: the visitor's default
// constructor, storing its vtable 0x00C7500C; retail keeps this standalone
// copy (no direct caller) and inlines it into Rva005CD841Find.
Rva005CD841Visitor::Rva005CD841Visitor()
{
}
bool __cdecl Rva005CD841Find(void *p)
{
	Rva005CD841Visitor v;
	v.m_found = false;
	((Rva005CCD36 *)p)->rva005CCD36(&v);
	return v.m_found;
}
