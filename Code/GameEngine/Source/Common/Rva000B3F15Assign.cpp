// cl: /DNDEBUG /MD
// ??4Rva000B3F15@@QAEAAV0@ABV0@@Z @0x000B3F15 46B
// Ref-counted smart-pointer assignment: self-check on object addresses, inc
// new Payload TargetRef references at +0x2c, release old via rowed
// ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z with ecx=old+0x28,
// copy Payload* at +0, return *this. Callers 0x000B4520 (member at +0x14) and
// 0x000C4AA1 prove this/arg are smart-pointers; +0x28/+0x2c layout from the
// release helper TargetRef00217D4C (references at +4).
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva000B3F15Payload
{
	char m_pad[0x28];
	TargetRef00217D4C m_ref;
};

class Rva000B3F15
{
public:
	Rva000B3F15 &operator=(const Rva000B3F15 &o);
private:
	Rva000B3F15Payload *m_ptr;
};

Rva000B3F15 &Rva000B3F15::operator=(const Rva000B3F15 &o)
{
	if (this != &o) {
		if (o.m_ptr)
			++o.m_ptr->m_ref.references;
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ref);
		m_ptr = o.m_ptr;
	}
	return *this;
}
