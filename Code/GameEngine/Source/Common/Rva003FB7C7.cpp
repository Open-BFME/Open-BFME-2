// cl: /DNDEBUG /MD
// ?rva003FB7C7@Rva003FB7C7@@QAEXXZ @0x003FB7C7 20B
// Honest address-derived placeholder: method Rva003FB7C7 in new opaque class
// Rva003FB7C7. Same-page adjacency to vslot 0x003FB6C5 (slot 7 of
// Rva005C4B1B) with same this+8 delegate shape; class membership unproven.
// Target: if (this+8) this+8->slot113(1) via vtable+0x1C4; callers
// 0x003F933A/0x003F9346 unclaimed.
class Rva003FB7C7PtrTarget
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
	virtual void slot112();
	virtual void slot113(int arg);
};

class Rva003FB7C7
{
public:
	void rva003FB7C7();
private:
	char m_pad00[8];
	Rva003FB7C7PtrTarget *m_ptr; // +8
};

void Rva003FB7C7::rva003FB7C7()
{
	if (m_ptr)
		m_ptr->slot113(1);
}

class Gen0003AC38
{
public:
	void handle(void *object);
};

extern Gen0003AC38 *g_shadowManager;

class Rva003FB640
{
public:
	void rva003FB640();
private:
	char m_pad00[0xC];
	void *m_ptr0C; // +0xC
};

void Rva003FB640::rva003FB640()
{
	void *p = m_ptr0C;
	if (p)
	{
		g_shadowManager->handle(p);
		m_ptr0C = 0;
	}
}

class Rva003FB65CTarget
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44();
	virtual void slot45(void *a, float b, int c);
};

class Rva003FB65C
{
public:
	void rva003FB65C(int x);
private:
	char m_pad00[8];
	Rva003FB65CTarget *m_ptr08; // +8
	char m_pad0C[12];
	void *m_aux18; // +0x18
};

void Rva003FB65C::rva003FB65C(int x)
{
	if (m_ptr08 && m_aux18)
		m_ptr08->slot45(m_aux18, 0.0f, x);
}

class Rva003FB9C8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	void rva003FB9C8(int a, int b);
	void rva003FB9EB(int a, int b);
private:
	char m_pad04[0x28];
	int m_2c; // +0x2c
	char m_pad30[4];
	int m_34; // +0x34
	int m_38; // +0x38
	char m_pad3C[0x10];
	int m_4c; // +0x4c
	int m_50; // +0x50
};

void Rva003FB9C8::rva003FB9C8(int a, int b)
{
	m_38 = 0;
	m_2c = 2;
	m_4c = 2;
	m_50 = b;
	m_34 = a;
	slot03();
}

void Rva003FB9C8::rva003FB9EB(int a, int b)
{
	m_38 = 0;
	m_2c = 1;
	m_4c = 1;
	m_50 = b;
	m_34 = a;
	slot03();
}

class Rva003FBF38Target
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
	virtual int slot100();
};

class Rva003FBF38
{
public:
	unsigned char rva003FBF38();
private:
	char m_pad00[8];
	Rva003FBF38Target *m_ptr08; // +8
};

unsigned char Rva003FBF38::rva003FBF38()
{
	Rva003FBF38Target *p = m_ptr08;
	if (p)
		return p->slot100() ? 0 : 1;
	return 0;
}
