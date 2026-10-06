// cl: /O1 /EHsc /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
// ??0Rva0056B89F@@QAE@PAXPAXH@Z @0x0056BA07 156B: ctor Rva0056B89F::Rva0056B89F(void*,void*,int) via Rva005C4B56(Helper(arg0),1,arg2), sets BC=-1 C0=0 C4=arg1 vtable, then if arg1 calls method_002BFFD4 with 0 and rva005C4B96(rva0056B89F()). Evidence: donor Rva005C4280.cpp Rva005C4230 ctor shape, callee pins Helper005C4D4B Rva005C4B56 method_002BFFD4, rowed rva0056B89F rva005C4B96 releaseBuffer, caller 0x003FE50D.
#include "ascii_string.h"

struct Helper005C4D4B
{
	void *m_00;
	AsciiString m_str;
	int m_08;
	int m_0c;
	Helper005C4D4B(void *);
	~Helper005C4D4B() {}
};

struct SubAC0056B89F
{
	char _00[0x5C];
	unsigned char m_flag5C;
};

class Rva005C41C9
{
public:
	virtual ~Rva005C41C9();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual unsigned char v17();
};

class Rva005C4B56 : public Rva005C41C9
{
public:
	virtual void rva005C4B96(unsigned char);

	char pad_base[0xA8];
	SubAC0056B89F *m_ac;
	void *m_b0;
	int m_b4;
	int m_b8;

	Rva005C4B56(const Helper005C4D4B &, int, int);
};

class Rva002D3627Host
{
public:
	void method_002BFFD4(void *, int, void *);
};
extern Rva002D3627Host *g_00DFEF18;

class Rva0056B89F : public Rva005C4B56
{
public:
	int m_bc;
	unsigned char m_c0;
	char _c1[3];
	void *m_c4;

	Rva0056B89F(void *arg0, void *arg1, int arg2);
	unsigned char rva0056B89F();
};

Rva0056B89F::Rva0056B89F(void *arg0, void *arg1, int arg2)
	: Rva005C4B56(Helper005C4D4B(arg0), 1, arg2)
{
	m_bc = -1;
	m_c0 = 0;
	m_c4 = arg1;
	if (arg1) {
		if (m_ac->m_flag5C) {
			g_00DFEF18->method_002BFFD4(this, 0, m_b0);
		}
		rva005C4B96(rva0056B89F());
	}
}
