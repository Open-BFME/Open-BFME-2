// cl: /EHsc /MD
//
// ?Rva005CD877Visit@@YAXPAX@Z retail 0x005CD877 46B visit list via stack Visitor.
// Evidence: callee 0x005CCD36 rowed visit caller 0x005CD8A5 pushes one ptr cdecl void sibling of 0x005CD813 vtable 0x00875010.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
struct Visitor005CCCD0
{
	virtual bool visit(TargetRef00217D4C *p);
	virtual ~Visitor005CCCD0() {}
};
class Rva005CCD36
{
public:
	void rva005CCD36(Visitor005CCCD0 *v);
};
class Rva005CD877Visitor : public Visitor005CCCD0
{
public:
	Rva005CD877Visitor() {}
	virtual ~Rva005CD877Visitor() {}
	virtual bool visit(TargetRef00217D4C *p) { return true; }
};
void __cdecl Rva005CD877Visit(void *p)
{
	Rva005CD877Visitor v;
	((Rva005CCD36 *)p)->rva005CCD36(&v);
}
