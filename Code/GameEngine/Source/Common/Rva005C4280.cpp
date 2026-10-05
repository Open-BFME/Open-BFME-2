// cl: /O1 /EHsc /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

struct Helper005C4D4B {
	void *m_00;
	AsciiString m_str;
	int m_08;
	int m_0c;
	Helper005C4D4B(void *);
	~Helper005C4D4B() {}
};

struct SubAC005C4B56 {
	char pad[0x60];
	char m_flag60;
};

class Rva005C41C9 {
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

class Rva005C4B56 : public Rva005C41C9 {
public:
	virtual void rva005C4B96(unsigned char);

	char pad_base[0xa8];
	SubAC005C4B56 *m_ac; // +0xac
	void *m_b0;          // +0xb0
	int m_b4;
	int m_b8;

	Rva005C4B56(const Helper005C4D4B &, int, int);
};

struct Rva004E06FBPtrChase32Field {
	int get() const;
};

struct Arg1Host005C4280 {
	char pad[0x38];
	Rva004E06FBPtrChase32Field *m_field38;
};

class Rva002D3627Host {
public:
	void method_002BFFD4(void *, int, void *);
};
extern Rva002D3627Host *g_00DFEF18;

class Rva005C4230 : public Rva005C4B56 {
public:
	Arg1Host005C4280 *m_bc;
	int m_c0;
	bool m_c4;
	bool m_c5;

	Rva005C4230(void *arg0, Arg1Host005C4280 *arg1);
	virtual ~Rva005C4230();
};

Rva005C4230::Rva005C4230(void *arg0, Arg1Host005C4280 *arg1)
	: Rva005C4B56(Helper005C4D4B(arg0), 1, 0)
{
	m_c0 = -1;
	m_bc = arg1;
	m_c4 = true;
	m_c5 = false;
	if (arg1) {
		if (arg1->m_field38) {
			m_c0 = arg1->m_field38->get();
		}
		if (m_ac->m_flag60) {
			g_00DFEF18->method_002BFFD4(this, 4, m_b0);
		}
		rva005C4B96(v17());
	}
}
