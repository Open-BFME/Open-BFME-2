// cl: /DNDEBUG /MD /EHsc
// ?rva00596FF5@Rva00596F18@@QAEXE@Z @0x00596FF5 28B
// Setter on the Rva00596F18 family: stores byte at +0x64, and when the byte
// is 0 clears dwords at +0x24/+0x68 then calls virtual slot 7 (0x1c) with 0.
// Evidence: mov al [esp+4] / mov [ecx+0x64] al / jne skip / mov eax [ecx] /
// push 0 / mov [ecx+0x24] 0 / mov [ecx+0x68] 0 / call [eax+0x1c] / ret 4;
// neighbours 0x00596F18/0x00597011 own the class TU.
struct Rva00596F18
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7(int arg);
	void rva00596FF5(unsigned char v);
	char _pad04[0x20];
	int m_24;
	char _pad28[0x3c];
	unsigned char m_64;
	char _pad65[3];
	int m_68;
};
void Rva00596F18::rva00596FF5(unsigned char v)
{
	m_64 = v;
	if (v != 0)
		return;
	m_24 = 0;
	m_68 = 0;
	s7(0);
}
