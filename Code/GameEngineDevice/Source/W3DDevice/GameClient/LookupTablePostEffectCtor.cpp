// cl: /DNDEBUG /MD
//
// ??0LookupTablePostEffect@@QAE@XZ, retail 0x00111B84, 22 bytes.
// Target identity: the body calls the base ctor 0x0011646E (pinned as
// Rva001164B6), installs vtable 0x00BCFAC8 and zeroes +0x08.
// That vtable's slot 0 (0x00111BE9) returns the AsciiString
// "LookupTablePostEffect" (literal 0x00BCFADC); its dtor 0x00111B9A installs
// the same vtable. The row previously named this body W3DPropDrawModuleData
// by masked byte search against the BFME1 donor; retail's ModuleFactory
// registration puts the W3DPropDrawModuleData ctor at 0x000CEF2B (vtable
// 0x00BCD420) instead. Class layout beyond +0x08 is unknown.

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

// ??0LookupTablePostEffect@@QAE@XZ
LookupTablePostEffect::LookupTablePostEffect()
{
}
