// cl: /MD
// ?rva001EB0CA@Rva001EB0CAHolder@@QAEXXZ @0x001EB0CA 15B: null-checked byte set.
// Loads pointer at this+0x10 and stores 1 at pointee+0xC1. Callers at
// 0x003BE6F5 0x003BE7C6 0x003BE8C0. No donor; honest address names.
struct Rva001EB0CAPointee
{
	unsigned char m_pad[0xC0];
	unsigned char m_flagC0;
	unsigned char m_flagC1;
};
class Rva001EB0CAHolder
{
public:
	void rva001EB0CA();
	unsigned char rva001EB0D9();
private:
	char m_pad[0x10];
	Rva001EB0CAPointee *m_ptr;
};
void Rva001EB0CAHolder::rva001EB0CA()
{
	if (m_ptr)
		m_ptr->m_flagC1 = 1;
}

// ?rva001EB0D9@Rva001EB0CAHolder@@QAEEXZ @0x001EB0D9 17B: null-checked byte get.
// Loads pointer at this+0x10 and returns pointee+0xC0, 0 when null. Sibling
// of rva001EB0CA above (same holder, same pointee; that body stores 1 at
// +0xC1). Callers at 0x005208AE 0x0052127F 0x0052129D test al. No donor.
unsigned char Rva001EB0CAHolder::rva001EB0D9()
{
	if (m_ptr)
		return m_ptr->m_flagC0;
	return 0;
}
