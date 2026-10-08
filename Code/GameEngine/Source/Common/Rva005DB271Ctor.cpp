// cl: /EHsc /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
// ??0Rva005DB271@@QAE@PAXPAUArg1Host005DB271@@@Z @0x005DB271 168B
// ctor modeled on Rva005C4230::Rva005C4230 (Code/GameEngine/Source/Common/Rva005C4280.cpp):
// base Rva005C4B56 via Helper005C4D4B temp with (1,0), vtable 0x00C766B8, +0xBC arg ptr,
// +0xC4 int via 0x38->0x1c->0x13c chase, +0xAC flag at +0x58, notify 5 via g_00DFEF18,
// then rva005C4B96(v17). Caller 0x0059E10F unclaimed. No donor name proven.
#include "ascii_string.h"

struct Helper005C4D4B {
	void *m_00;
	AsciiString m_str;
	int m_08;
	int m_0c;
	Helper005C4D4B(void *);
	~Helper005C4D4B() {}
};

struct SubAC005DB271 {
	char pad[0x58];
	unsigned char m_flag58;
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
	unsigned char rva005C4B26();
};

class Rva005C4B56 : public Rva005C41C9 {
public:
	virtual void rva005C4B96(unsigned char);

	char pad_base[0xa8];
	SubAC005DB271 *m_ac; // +0xac
	void *m_b0;          // +0xb0
	int m_b4;
	int m_b8;

	Rva005C4B56(const Helper005C4D4B &, int, int);
};

struct Inner2005DB271 {
	char pad[0x13c];
	int m_13c;
};

struct Inner1005DB271 {
	char pad[0x1c];
	Inner2005DB271 *m_1c;
};

struct Arg1Host005DB271 {
	char pad[0x38];
	Inner1005DB271 *m_field38;
};

class Rva002D3627Host {
public:
	void method_002BFFD4(void *, int, void *);
};
extern Rva002D3627Host *g_00DFEF18;

class LivingWorldBuildPlotIconSubObject : public Rva005C4B56 {
public:
	Arg1Host005DB271 *m_bc; // +0xbc
	int m_padC0;            // +0xc0
	int m_c0;               // +0xc4

	LivingWorldBuildPlotIconSubObject(void *arg0, Arg1Host005DB271 *arg1);
	virtual ~LivingWorldBuildPlotIconSubObject();
};

LivingWorldBuildPlotIconSubObject::LivingWorldBuildPlotIconSubObject(void *arg0, Arg1Host005DB271 *arg1)
	: Rva005C4B56(Helper005C4D4B(arg0), 1, 0)
{
	m_bc = arg1;
	m_c0 = -1;
	if (arg1) {
		if (arg1->m_field38) {
			m_c0 = arg1->m_field38->m_1c->m_13c;
		}
		if (m_ac->m_flag58) {
			g_00DFEF18->method_002BFFD4(this, 5, m_b0);
		}
		rva005C4B96(rva005C4B26());
	}
}
