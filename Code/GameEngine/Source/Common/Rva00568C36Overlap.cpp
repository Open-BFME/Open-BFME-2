// cl: /DNDEBUG /MD
// ?rva00568C36@Rva00568C36@@QAE_NPBVRva00568C36Provider@@@Z @0x00568C36 24B:
// virtual-range overlap wrapper. Calls provider vtable slot 7 (+0x1C) for a
// const Rva003CDDB0Range then tail-calls rowed Rva003CDDB0Range::method at
// 0x00568B81 with this. Caller at 0x003EE067 in 0x003EE058 loops array.
// Prev 0x00568B81 overlap and next 0x00568C4E dtor share page.
struct Rva003CDDB0Range
{
	const int *m_begin;
	const int *m_end;
	bool method(const Rva003CDDB0Range *other);
};
class Rva00568C36Provider
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual const Rva003CDDB0Range *v7() const;
};
class Rva00568C36 : public Rva003CDDB0Range
{
public:
	bool rva00568C36(const Rva00568C36Provider *p);
};
bool Rva00568C36::rva00568C36(const Rva00568C36Provider *p)
{
	return method(p->v7());
}
