// cl: /MD
// ?Rva006DE210@Rva006DE2B0@@UAEPAXHABVEAStringC@@@Z @0x006DE210 34B.
// Virtual slot 7 (offset 0x1C) of vtable 0x008EB150 (class of rowed dtor
// ??1Rva006DE2B0@@UAE@XZ in Rva006D63C0Derived.cpp). Returns the AptValue
// slot at +0x1C when the name equals "__constructor__" via rowed
// EAStringC compare ?rva006D3490@EAStringC@@QBE_NPBD@Z, else null.
// Base vtable 0x008EAED0 slot 7 is the empty xor-eax ret-8 stub at
// 0x0003FD80; this derived class overrides it. No donor; retail-shaped.
// ?Rva006DE240@Rva006DE2B0@@UAE_NHABVEAStringC@@PAVAptRef@@@Z @0x006DE240 64B.
// Virtual slot 8 (offset 0x20) of the same vtable. Sets the +0x1C slot with
// AddRef of the new value (slot 0) and Release of the old (slot 1) when the
// name equals "__constructor__" via the same rowed compare, else false.
// Base slot 8 is the empty xor-al ret-C stub at 0x006C8770.
class EAStringC
{
public:
	bool rva006D3490(const char *text) const;
};

class AptRef
{
public:
	virtual void AddRef();
	virtual void Release();
};

class Rva006DE2B0
{
public:
	char m_pad[0x18];
	AptRef *m_ctor;
	virtual void *Rva006DE210(int unused, const EAStringC &name);
	virtual bool Rva006DE240(int unused, const EAStringC &name, AptRef *value);
};

void *Rva006DE2B0::Rva006DE210(int, const EAStringC &name)
{
	if (name.rva006D3490("__constructor__"))
		return m_ctor;
	return 0;
}

bool Rva006DE2B0::Rva006DE240(int, const EAStringC &name, AptRef *value)
{
	if (name.rva006D3490("__constructor__")) {
		AptRef *old = m_ctor;
		m_ctor = value;
		if (value)
			value->AddRef();
		if (old)
			old->Release();
		return true;
	}
	return false;
}
