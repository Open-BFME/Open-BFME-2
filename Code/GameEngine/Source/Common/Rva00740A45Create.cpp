// cl: /MD
// ?Rva00740A45Create@@YAPAVRva00789900Init@@E@Z, retail 0x00740A45, 27 bytes.
// Factory forwarding one byte arg to new Rva00789900Init via rowed operator new.
// Evidence: caller at 0x0041194B pushes byte flag and uses returned vtable slot 1; ctor rowed at 0x0074055A size 0x30.
extern void *g_Rva00789900Table[];
class Rva00789900Init
{
public:
	Rva00789900Init(unsigned char flag) throw();
	void *m_table;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned char m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
};
Rva00789900Init *Rva00740A45Create(unsigned char flag)
{
	return new Rva00789900Init(flag);
}
