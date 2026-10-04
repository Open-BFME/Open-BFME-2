// cl: /O1 /MD
// ?rva0041FE63@Rva00420110@@UAEXXZ @0x0041FE63 35B
// Vslot 31 of vtable 0x0083BA28 (class Rva00420110). Evidence: byte at +0x10
// gates DWORD delta at +0x14 via winmm timeGetTime against 0x1b58 timeout
// then tail-jmps vtable slot 24 (offset 0x60).

extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();

class Rva00420110
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
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void slot24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void rva0041FE63();
private:
	unsigned char m_pad0[12];
	unsigned char m_10;
	unsigned char m_pad11[3];
	unsigned int m_14;
};

void Rva00420110::rva0041FE63()
{
	if (m_10 == 0)
		return;
	unsigned int t = timeGetTime();
	if (t - m_14 <= 0x1b58)
		return;
	slot24();
}
