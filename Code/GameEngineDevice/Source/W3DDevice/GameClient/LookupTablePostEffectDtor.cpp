// cl: /O1 /DNDEBUG /MD /EHsc
// ??1LookupTablePostEffect@@UAE@XZ @ 0x00111B9A 79B: dtor installs vtable 0x00BCFAC8,
// calls row 0x00116496 then Field08 inline release at +0x08 via dec and virtual slot0
// then base dtor at 0x0011647B. Prev ctor proves class and vtable. Next slot3 proves +0x08.
class Rva00116496
{
public:
    void rva00116496();
};


class AsciiString;
class Rva00111C05Effect;

// LookupTablePostEffect's base: retail vftable 0x00BCFB24 holds __purecall
// in slots 0 and 2-4 and the deleting dtor 0x001164B6 in slot 1; ctor
// 0x0011646E, empty virtual dtor 0x0011647B.
class Rva001164B6
{
public:
	Rva001164B6();
	virtual AsciiString rva00111BE9() const = 0;
	virtual ~Rva001164B6();
	virtual void rva00111DB6() = 0;
	virtual void rva00111D65() = 0;
	virtual void doApply() = 0;

private:
	int m_04;
};

struct RefCounted
{
	virtual void Release();
	int m_ref;
};

// +0x08: the ref-counted effect handle; the ctor nulls it, the dtor
// releases it inline (its out-of-line copy is the ICF fold 0x0007B724).
struct Field08
{
	RefCounted *m_ptr;
	Field08() : m_ptr(0) {}
	~Field08()
	{
		RefCounted *refCounted = m_ptr;
		if (refCounted && --refCounted->m_ref == 0)
			refCounted->Release();
	}
	Rva00111C05Effect *get() const { return (Rva00111C05Effect *)m_ptr; }
};

// Retail vftable 0x00BCFAC8: slot 0 rva00111BE9, slot 1 the deleting dtor
// 0x00111D9A, slot 2 0x00111DB6 (rowed as Rva00111DB6::rva00111DB6 in
// another unit, so it stays the base's pure slot here), slot 3 rva00111D65,
// slot 4 doApply.
class LookupTablePostEffect : public Rva001164B6
{
public:
	LookupTablePostEffect();
	virtual AsciiString rva00111BE9() const;
	virtual ~LookupTablePostEffect();
	virtual void rva00111D65();
	virtual void doApply();

private:
	Field08 m_08;
};

LookupTablePostEffect::~LookupTablePostEffect()
{
    ((Rva00116496 *)this)->rva00116496();
}
