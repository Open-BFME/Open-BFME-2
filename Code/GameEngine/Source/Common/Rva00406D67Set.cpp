// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva00406D67@Rva00406D67@@QAEPAV1@III@Z @0x00406D67 39B.
// Flag-plus-three setter: low two bits of +0 forced to 3 keeping bit 31
// then three args stored at +4 +8 +0xC, returns this (retail opens
// mov eax,ecx and addresses through eax; void return keeps this in ecx).
// Evidence: unlock lane; neighbour
// 0x00406D5F/0x00406D8E same region; caller 0x00408677 in FUN_008083FF;
// ret 0xC three args; same shape as Rva00135E00 0x00135E00 plus return this
// per Rva00547223 fluent-setter precedent.
class Rva00406D67
{
public:
	Rva00406D67 *rva00406D67(unsigned int a, unsigned int b, unsigned int c);
private:
	unsigned int m_0;
	unsigned int m_4;
	unsigned int m_8;
	unsigned int m_c;
};
Rva00406D67 *Rva00406D67::rva00406D67(unsigned int a, unsigned int b, unsigned int c)
{
	unsigned int v = m_0;
	v &= 0x80000003;
	v |= 3;
	m_0 = v;
	m_4 = a;
	m_8 = b;
	m_c = c;
	return this;
}
