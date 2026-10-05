// ?Rva005FAC2BCreate@@YAPAURva005FAC2BHolder@@PAU1@PBUPayload@Rva005FAAA1@@@Z
// partial score=0.88 date=2026-10-05
// cl: /O1 /MD /Oy-
// ?Rva005FAC2BCreate@@YAPAURva005FAC2BHolder@@PAU1@PBUPayload@Rva005FAAA1@@@Z, RVA 0x005FAC2B, 50 bytes.
// Factory: news 0x10 Rva005FAAA1 with payload, stores into holder at +0, inc ref at +4 if non-null, returns holder.
// Evidence: rowed new 0x0002FDA0 and rowed ctor 0x005FAAA1 in Rva005CE259Ctor.cpp; caller 0x005FAFE8; neighbours 0x005FAB9E 0x005FB204 share /O1 /MD.
struct Rva005FAAA1
{
	struct Payload
	{
		int v[2];
	};
	void *m_vptr;
	int m_ref;
	int m_data[2];
	Rva005FAAA1(const Payload *src) throw();
};
void *__cdecl operator new(unsigned int size) throw();
struct Rva005FAC2BHolder
{
	Rva005FAAA1 *m_ptr;
};
// ?Rva005FAC2BCreate@@YAPAURva005FAC2BHolder@@PAU1@PBUPayload@Rva005FAAA1@@@Z present-unmatched
struct Rva005FAC2BHolder *__cdecl Rva005FAC2BCreate(struct Rva005FAC2BHolder *holder, const struct Rva005FAAA1::Payload *payload)
{
	Rva005FAAA1 *tmp = new Rva005FAAA1(payload);
	holder->m_ptr = tmp;
	if (tmp)
		++tmp->m_ref;
	return holder;
}
