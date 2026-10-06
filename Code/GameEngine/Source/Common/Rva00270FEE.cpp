// cl: /DNDEBUG /MD
// ?rva00270FEE@Rva00270FEE@@QAEPADXZ @0x00270FEE 26B
// If ptr at +0xFC is set returns its dword at +0x104 else returns ptr at +0x04 plus 0xA0.
// Evidence: caller at 0x0027100C uses return plus 0x14 as float; no donor; honest Rva name.
//
// ?rva00271008@Rva00270FEE@@QAEMXZ @0x00271008 55B: the float at +0x14 of
// that pointer, plus vslot +0xC8 of the first module in the array at +0x14C
// when present. Caller 0x00239220 adds the float return. Retail keeps this in
// ecx across the rva00270FEE call, which cl only does when the callee was
// compiled earlier in the same TU, so both bodies share this file.
struct Rva00270FEEInner
{
	unsigned char m_pad[0x104];
	char *m_104;
};

class BfmeFloatModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual float getC8(); // +0xC8
};

class Rva00270FEE
{
public:
	char *rva00270FEE();
	float rva00271008();
private:
	unsigned char m_pad0[4];
	char *m_04;
	unsigned char m_pad8[0xfc - 8];
	Rva00270FEEInner *m_fc;
	unsigned char m_pad100[0x14c - 0x100];
	BfmeFloatModule **m_14c;
};

char *Rva00270FEE::rva00270FEE()
{
	if (m_fc)
		return m_fc->m_104;
	return m_04 + 0xa0;
}

float Rva00270FEE::rva00271008()
{
	char *p = rva00270FEE();
	float base = *(float *)(p + 0x14);
	BfmeFloatModule **arr = m_14c;
	if (arr && *arr)
		return base + (*arr)->getC8();
	return base;
}
