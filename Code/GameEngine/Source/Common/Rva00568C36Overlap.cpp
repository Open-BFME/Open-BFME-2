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

// Native 003EE058..003EE083 tests each pointer in [this+1C,this+20),
// returning on the first overlap. The callee above independently names this
// caller; the existing 003EDDD4 pointer-walk is the source-shape guide.
// The application collection class remains unknown. Keep it with its typed
// overlap provider rather than adding another private AsciiString view to
// the adjacent string-lookup unit.
class Rva003EE058Owner
{
	char m_prefix[0x1c];
	Rva00568C36 **m_begin;
	Rva00568C36 **m_end;
public:
	bool overlaps(const Rva00568C36Provider *arg);
};

bool Rva003EE058Owner::overlaps(const Rva00568C36Provider *arg)
{
	for (Rva00568C36 **p=m_begin; p!=m_end; ++p)
		if ((*p)->rva00568C36(arg))
			return true;
	return false;
}
