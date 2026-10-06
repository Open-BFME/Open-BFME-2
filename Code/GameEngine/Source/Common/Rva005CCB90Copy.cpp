// cl: /MD
// ?rva005CCB90@Rva005CCB90@@QAEXPBX@Z @0x005CCB90 24B evidence: no calls; tail callers 0x005D1DCB 0x005D2184; copies 12B then sets flag
// Copies 12 bytes from arg into inner struct at +8+0x14 then sets byte +8+0x20 to 1.
struct Twelve {
	int a;
	int b;
	int c;
};
class Rva005CCB90Inner {
public:
	char m_pad[0x14];
	Twelve m_data;
	unsigned char m_flag;
};
class Rva005CCB90 {
public:
	void rva005CCB90(void const *src);
	char m_lead[8];
	Rva005CCB90Inner *m_ptr;
};
void Rva005CCB90::rva005CCB90(void const *src)
{
	Rva005CCB90Inner *p = m_ptr;
	p->m_data = *(Twelve const *)src;
	p->m_flag = 1;
}
