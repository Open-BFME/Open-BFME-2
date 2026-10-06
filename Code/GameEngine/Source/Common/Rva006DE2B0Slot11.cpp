// cl: /MD
// ?Rva0070DF60@Rva006DE2B0@@UAEXXZ @0x0070DF60 30B.
// Virtual slot 11 (offset 0x2C) of vtable 0x008EB150 (class of rowed dtor
// ??1Rva006DE2B0@@UAE@XZ in Rva006D63C0Derived.cpp). Releases the AptRef
// slot at +0x1C via slot-1 Release then tail-jmps to the rowed clear
// ?rva006DE150@Rva006DE150@@QAEXXZ on the same this (flags at +4 table
// at +8 overlap the opaque pad). No donor; retail-shaped.
class AptRef
{
public:
	virtual void AddRef();
	virtual void Release();
};

class Rva006DE150
{
public:
	void rva006DE150();
};

class Rva006DE2B0
{
public:
	char m_pad[0x18];
	AptRef *m_ctor;
	virtual void Rva0070DF60();
};

void Rva006DE2B0::Rva0070DF60()
{
	if (m_ctor)
		m_ctor->Release();
	m_ctor = 0;
	((Rva006DE150 *)this)->rva006DE150();
}
