// cl: /MD /EHsc
// ?rva005C41C9@Rva005C41C9@@QAEXE@Z retail 0x005C41C9 73B
// Evidence: caller 0x0052B024 forwards one stack arg over vector [ecx+0x2c,0x30); slots 0x44 twice then 0x48; members +0xC5 byte plus +0xAC chase +0x58/+0x5C; neighbours 0x005C4139 0x005C436E
// Structural inference: the second slot-0x44 result reuses the parameter's
// stack slot (retail stores it to [ebp+8] and compares from memory), and the
// +0xAC pointer is loaded into a local before the select, as retail.
struct Inner005C41C9
{
	char m_pad[0x58];
	int m_58;
	int m_5C;
};

class Rva005C41C9
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual unsigned char v17();
	virtual void v18(unsigned char a, unsigned char b, int c);
	void rva005C41C9(unsigned char v);
private:
	char m_pad04[0xA8];
	Inner005C41C9 *m_ac;
	char m_padB0[0x15];
	unsigned char m_c5;
};

void Rva005C41C9::rva005C41C9(unsigned char v)
{
	unsigned char a = v17();
	m_c5 = v;
	v = v17();
	Inner005C41C9 *inner = m_ac;
	int c = v ? inner->m_58 : inner->m_5C;
	v18(a, v, c);
}
