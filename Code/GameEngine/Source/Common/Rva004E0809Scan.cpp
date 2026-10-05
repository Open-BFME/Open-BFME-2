// cl: /O1
// ?rva004E0809@Rva004E0809@@QAEXXZ @0x004E0809 60B
// Scan pointer range [+0x30,+0x34) and keep last non-null virtual results:
// slot 0x20 -> [+0x40], slot 0x28 -> [+0x44]. Retail is and [esi+0x40],0 /
// and [esi+0x44],0 / mov ebx,[esi+0x34] / mov edi,[esi+0x30] / loop with two
// vtable calls plus test/je/store and add edi,4 / cmp edi,ebx / jne (60B).
// Evidence: unlock lane; callees are indirect virtuals so gate-ready; callers
// at 0x004E0E78 0x004E119C; neighbours Rva004E0790Release/Rva004E08F6Set share /O1.
struct Rva003F7B22Element
{
	int m_v;
};
class Rva003F7BB4
{
public:
	void rva003F7BB4(const struct Rva003F7B22Element &e);
	int m_0;
	char m_pad[0x28];
};
struct Rva004E0860Flag
{
	char m_pad[9];
	unsigned char m_flag;
};
class Rva004E0809Elem
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5(Rva003F7BB4 *b);
	virtual void vf6();
	virtual void vf7();
	virtual void *vf8();
	virtual void vf9();
	virtual void *vf10();
};
class Rva004E0809
{
public:
	void rva004E0809();
	void rva004E0845();
	void rva004E0860(Rva003F7BB4 *b);
	char m_pad[0x24];
	int m_24;
	Rva004E0860Flag *m_28;
	char m_pad2c[4];
	Rva004E0809Elem **m_begin;
	Rva004E0809Elem **m_end;
	char m_pad38[4];
	int m_3c;
	void *m_40;
	void *m_44;
};
void Rva004E0809::rva004E0809()
{
	m_40 = 0;
	m_44 = 0;
	Rva004E0809Elem **end = m_end;
	for (Rva004E0809Elem **p = m_begin; p != end; ++p) {
		void *a = (*p)->vf8();
		if (a)
			m_40 = a;
		void *b = (*p)->vf10();
		if (b)
			m_44 = b;
	}
}
void Rva004E0809::rva004E0845()
{
	Rva004E0809Elem **p = m_begin;
	Rva004E0809Elem **end = m_end;
	for (; p != end; ++p)
		(*p)->vf4();
}
// ?rva004E0860@Rva004E0809@@QAEXPAVRva003F7BB4@@@Z @0x004E0860 73B
// Loop over [+0x30,+0x34) calling slot 0x14 with bucket arg, then gated push:
// if m_3c==0 return; if m_28->m_flag==0 return; if m_24 != b->m_0 return;
// b->rva003F7BB4((Element&)m_3c). Evidence: chain lane (calls rowed 0x003F7BB4);
// same +0x30/+0x34 as neighbours proves same class Rva004E0809; callers at 0x003F2185.
void Rva004E0809::rva004E0860(Rva003F7BB4 *b)
{
	Rva004E0809Elem **end = m_end;
	for (Rva004E0809Elem **p = m_begin; p != end; ++p)
		(*p)->vf5(b);
	int *pe = &m_3c;
	if (*pe == 0)
		return;
	if (m_28->m_flag == 0)
		return;
	if (m_24 != b->m_0)
		return;
	b->rva003F7BB4((Rva003F7B22Element &)*pe);
}
