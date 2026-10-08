// cl: /MD /EHs
//
// Destructors of STLport red-black trees, one per instantiation, with the shape
// of the rowed ??1Rva0046A93E (56 bytes: clear the tree through its rowed clear,
// then free the header through the inline holder). Found by searching .text for
// that shape with call displacements and the EH handler record masked; the clear
// each calls names its owner, whose tree is not otherwise recovered.

extern "C" void __cdecl free(void *block);

struct RvaTreeFamilyHeader;
struct RvaTreeFamilyHolder
{
	RvaTreeFamilyHeader *m_ptr;
	~RvaTreeFamilyHolder()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};

// ??1Rva00053DC5@@QAE@XZ @0x000554FA 56B -> Rva00053DC5::rva00054B9A
class Rva00053DC5
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00054B9A();
	~Rva00053DC5();
};

Rva00053DC5::~Rva00053DC5()
{
	rva00054B9A();
}

// ??1Rva00056CF8@@QAE@XZ @0x000589FB 56B -> Rva00056CF8::rva00057B74
class Rva00056CF8
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00057B74();
	~Rva00056CF8();
};

Rva00056CF8::~Rva00056CF8()
{
	rva00057B74();
}

// ??1Rva00072FE6@@QAE@XZ @0x000730DE 56B -> Rva00072FE6::rva00072FE6
class Rva00072FE6
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00072FE6();
	~Rva00072FE6();
};

Rva00072FE6::~Rva00072FE6()
{
	rva00072FE6();
}

class Rva00073116
{
public:
	void rva00073116();
};

void Rva00073116::rva00073116()
{
	((Rva00072FE6 *)this)->~Rva00072FE6();
}


// ??1Rva0007E971@@QAE@XZ @0x0007FE1B 56B -> Rva0007E971::rva0007FAC1
class Rva0007E971
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0007FAC1();
	~Rva0007E971();
};

Rva0007E971::~Rva0007E971()
{
	rva0007FAC1();
}

// ??1Rva0006F318@@QAE@XZ @0x0008A612 56B -> Rva0006F318::rva0006FA70
class Rva0006F318
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0006FA70();
	~Rva0006F318();
};

Rva0006F318::~Rva0006F318()
{
	rva0006FA70();
}

// ??1Rva000B646B@@QAE@XZ @0x000BB65C 56B -> Rva000B646B::rva000B92FB
class Rva000B646B
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva000B92FB();
	~Rva000B646B();
};

Rva000B646B::~Rva000B646B()
{
	rva000B92FB();
}

// ??1Rva001DD70F@@QAE@XZ @0x001DD9BB 56B -> Rva001DD70F::rva001DD846
class Rva001DD70F
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva001DD846();
	~Rva001DD70F();
};

Rva001DD70F::~Rva001DD70F()
{
	rva001DD846();
}

// ??1Rva001E6731@@QAE@XZ @0x001E6F27 56B -> Rva001E6731::rva001E6731
class Rva001E6731
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva001E6731();
	~Rva001E6731();
};

Rva001E6731::~Rva001E6731()
{
	rva001E6731();
}

// ??1Rva001F050B@@QAE@XZ @0x001F0657 56B -> Rva001F050B::rva001F050B
class Rva001F050B
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva001F050B();
	~Rva001F050B();
};

Rva001F050B::~Rva001F050B()
{
	rva001F050B();
}

// ??1Rva00206667@@QAE@XZ @0x002076E7 56B -> Rva00206667::rva00206F6B
class Rva00206667
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00206F6B();
	~Rva00206667();
};

Rva00206667::~Rva00206667()
{
	rva00206F6B();
}

// ??1Rva00206706@@QAE@XZ @0x0020779E 56B -> Rva00206706::rva00206FE6
class Rva00206706
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00206FE6();
	~Rva00206706();
};

Rva00206706::~Rva00206706()
{
	rva00206FE6();
}

// ??1Rva0021119B@@QAE@XZ @0x00211F05 56B -> Rva0021119B::rva00211DD2
class Rva0021119B
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00211DD2();
	~Rva0021119B();
};

Rva0021119B::~Rva0021119B()
{
	rva00211DD2();
}

// ??1Rva002294A3@@QAE@XZ @0x0022C917 56B -> Rva002294A3::rva0022C409
class Rva002294A3
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0022C409();
	~Rva002294A3();
};

Rva002294A3::~Rva002294A3()
{
	rva0022C409();
}

// ??1Rva002294D0@@QAE@XZ @0x0022C94F 56B -> Rva002294D0::rva0022C432
class Rva002294D0
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0022C432();
	~Rva002294D0();
};

Rva002294D0::~Rva002294D0()
{
	rva0022C432();
}

// ??1Rva00439325@@QAE@XZ @0x002418E2 56B -> Rva00439325::rva00240C60
class Rva00439325
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00240C60();
	~Rva00439325();
};

Rva00439325::~Rva00439325()
{
	rva00240C60();
}

// ??1Rva00255CA8@@QAE@XZ @0x00256429 56B -> Rva00255CA8::rva00255CA8
class Rva00255CA8
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00255CA8();
	~Rva00255CA8();
};

Rva00255CA8::~Rva00255CA8()
{
	rva00255CA8();
}

// ??1Rva00255CD1@@QAE@XZ @0x00256461 56B -> Rva00255CD1::rva00255CD1
class Rva00255CD1
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00255CD1();
	~Rva00255CD1();
};

Rva00255CD1::~Rva00255CD1()
{
	rva00255CD1();
}

// ??1Rva0027F4CB@@QAE@XZ @0x002819CE 56B -> Rva0027F4CB::rva00280AB6
class Rva0027F4CB
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00280AB6();
	~Rva0027F4CB();
};

Rva0027F4CB::~Rva0027F4CB()
{
	rva00280AB6();
}

// ??1Rva0028881C@@QAE@XZ @0x00288B51 56B -> Rva0028881C::rva002889BB
class Rva0028881C
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002889BB();
	~Rva0028881C();
};

Rva0028881C::~Rva0028881C()
{
	rva002889BB();
}

// ??1Rva002913EB@@QAE@XZ @0x002923A7 56B -> Rva002913EB::rva002913EB
class Rva002913EB
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002913EB();
	~Rva002913EB();
};

Rva002913EB::~Rva002913EB()
{
	rva002913EB();
}

// ??1Rva0029B63A@@QAE@XZ @0x0029FAB7 56B -> Rva0029B63A::rva0029E015
class Rva0029B63A
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0029E015();
	~Rva0029B63A();
};

Rva0029B63A::~Rva0029B63A()
{
	rva0029E015();
}

// ??1Rva0029B667@@QAE@XZ @0x0029FB03 56B -> Rva0029B667::rva0029E03E
class Rva0029B667
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0029E03E();
	~Rva0029B667();
};

Rva0029B667::~Rva0029B667()
{
	rva0029E03E();
}

// ??1Rva002A8B8C@@QAE@XZ @0x002A8CD0 56B -> Rva002A8B8C::rva002A8BEE
class Rva002A8B8C
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002A8BEE();
	~Rva002A8B8C();
};

Rva002A8B8C::~Rva002A8B8C()
{
	rva002A8BEE();
}

// ??1Rva002D394B@@QAE@XZ @0x002D50AD 56B -> Rva002D394B::rva002D43C6
class Rva002D394B
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002D43C6();
	~Rva002D394B();
};

Rva002D394B::~Rva002D394B()
{
	rva002D43C6();
}

// ??1Rva002E15E6@@QAE@XZ @0x002E1E19 56B -> Rva002E15E6::rva002E15E6
class Rva002E15E6
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002E15E6();
	~Rva002E15E6();
};

Rva002E15E6::~Rva002E15E6()
{
	rva002E15E6();
}

// ??1Rva002EE9B7@@QAE@XZ @0x002F0B52 56B -> Rva002EE9B7::rva002EE9B7
class Rva002EE9B7
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002EE9B7();
	~Rva002EE9B7();
};

Rva002EE9B7::~Rva002EE9B7()
{
	rva002EE9B7();
}

// ??1Rva0032EAA1@@QAE@XZ @0x0032EC26 56B -> Rva0032EAA1::rva0032EB5E
class Rva0032EAA1
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0032EB5E();
	~Rva0032EAA1();
};

Rva0032EAA1::~Rva0032EAA1()
{
	rva0032EB5E();
}

// ??1Rva00372F00@@QAE@XZ @0x00372FBC 56B -> Rva00372F00::rva00372F56
class Rva00372F00
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00372F56();
	~Rva00372F00();
};

Rva00372F00::~Rva00372F00()
{
	rva00372F56();
}

// ??1Rva0038404A@@QAE@XZ @0x00385BE1 56B -> Rva0038404A::rva00384E8E
class Rva0038404A
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00384E8E();
	~Rva0038404A();
};

Rva0038404A::~Rva0038404A()
{
	rva00384E8E();
}

// ??1Rva00388EAE@@QAE@XZ @0x00389354 56B -> Rva00388EAE::rva00389129
class Rva00388EAE
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00389129();
	~Rva00388EAE();
};

Rva00388EAE::~Rva00388EAE()
{
	rva00389129();
}

// ??1Rva00395CEB@@QAE@XZ @0x003968D3 56B -> Rva00395CEB::rva0039611E
class Rva00395CEB
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0039611E();
	~Rva00395CEB();
};

Rva00395CEB::~Rva00395CEB()
{
	rva0039611E();
}

// ??1Rva00395D18@@QAE@XZ @0x0039690B 56B -> Rva00395D18::rva00396147
class Rva00395D18
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00396147();
	~Rva00395D18();
};

Rva00395D18::~Rva00395D18()
{
	rva00396147();
}

// ??1Rva00397C94@@QAE@XZ @0x00399278 56B -> Rva00397C94::rva00398257
class Rva00397C94
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00398257();
	~Rva00397C94();
};

Rva00397C94::~Rva00397C94()
{
	rva00398257();
}

// ??1Rva0039F56E@@QAE@XZ @0x0039FB11 56B -> Rva0039F56E::rva0039F56E
class Rva0039F56E
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0039F56E();
	~Rva0039F56E();
};

Rva0039F56E::~Rva0039F56E()
{
	rva0039F56E();
}

// ??1Rva004070D4@@QAE@XZ @0x004075A8 56B -> Rva004070D4::rva0040748D
class Rva004070D4
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0040748D();
	~Rva004070D4();
};

Rva004070D4::~Rva004070D4()
{
	rva0040748D();
}

// ??1Rva0041331E@@QAE@XZ @0x00413396 56B -> Rva0041331E::rva0041334B
class Rva0041331E
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0041334B();
	~Rva0041331E();
};

Rva0041331E::~Rva0041331E()
{
	rva0041334B();
}

// ??1Rva00421BF7@@QAE@XZ @0x0042263D 56B -> Rva00421BF7::rva00421EEA
class Rva00421BF7
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00421EEA();
	~Rva00421BF7();
};

Rva00421BF7::~Rva00421BF7()
{
	rva00421EEA();
}

// ??1Rva00421C24@@QAE@XZ @0x00422675 56B -> Rva00421C24::rva00421F13
class Rva00421C24
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00421F13();
	~Rva00421C24();
};

Rva00421C24::~Rva00421C24()
{
	rva00421F13();
}

// ??1Rva00421CE9@@QAE@XZ @0x00422717 56B -> Rva00421CE9::rva00421FDE
class Rva00421CE9
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00421FDE();
	~Rva00421CE9();
};

Rva00421CE9::~Rva00421CE9()
{
	rva00421FDE();
}

// ??1Rva0043EA9C@@QAE@XZ @0x0043FE62 56B -> Rva0043EA9C::rva0043F124
class Rva0043EA9C
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0043F124();
	~Rva0043EA9C();
};

Rva0043EA9C::~Rva0043EA9C()
{
	rva0043F124();
}

// ??1Rva00448E3B@@QAE@XZ @0x00448FA6 56B -> Rva00448E3B::rva00448E3B
class Rva00448E3B
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00448E3B();
	~Rva00448E3B();
};

Rva00448E3B::~Rva00448E3B()
{
	rva00448E3B();
}

// ??1Rva004D0545@@QAE@XZ @0x004D1AC3 56B -> Rva004D0545::rva004D0F82
class Rva004D0545
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004D0F82();
	~Rva004D0545();
};

Rva004D0545::~Rva004D0545()
{
	rva004D0F82();
}

// ??1Rva004D0572@@QAE@XZ @0x004D1B00 56B -> Rva004D0572::rva004D0FAB
class Rva004D0572
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004D0FAB();
	~Rva004D0572();
};

Rva004D0572::~Rva004D0572()
{
	rva004D0FAB();
}

// ??1Rva004E7B13@@QAE@XZ @0x004E7C52 56B -> Rva004E7B13::rva004E7BAF
class Rva004E7B13
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004E7BAF();
	~Rva004E7B13();
};

Rva004E7B13::~Rva004E7B13()
{
	rva004E7BAF();
}

// ??1Rva004E9419@@QAE@XZ @0x004E9597 56B -> Rva004E9419::rva004E94A1
class Rva004E9419
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004E94A1();
	~Rva004E9419();
};

Rva004E9419::~Rva004E9419()
{
	rva004E94A1();
}

// ??1Rva004EA149@@QAE@XZ @0x004EA28D 56B -> Rva004EA149::rva004EA264
class Rva004EA149
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004EA264();
	~Rva004EA149();
};

Rva004EA149::~Rva004EA149()
{
	rva004EA264();
}

// Target identity: each five-byte boundary forwards the unchanged this
// pointer to its rowed destructor. Keep both wrapper types address-derived.
class Rva004E95CF
{
public:
	void rva004E95CF();
};

void Rva004E95CF::rva004E95CF()
{
	((Rva004E9419 *)this)->~Rva004E9419();
}

class Rva004EA2FC
{
public:
	void rva004EA2FC();
};

void Rva004EA2FC::rva004EA2FC()
{
	((Rva004EA149 *)this)->~Rva004EA149();
}

// ??1Rva004FCA9C@@QAE@XZ @0x004FCC48 56B -> Rva004FCA9C::rva004FCBCD
class Rva004FCA9C
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004FCBCD();
	~Rva004FCA9C();
};

Rva004FCA9C::~Rva004FCA9C()
{
	rva004FCBCD();
}

// ??1Rva004FCAC9@@QAE@XZ @0x004FCC80 56B -> Rva004FCAC9::rva004FCBF6
class Rva004FCAC9
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004FCBF6();
	~Rva004FCAC9();
};

Rva004FCAC9::~Rva004FCAC9()
{
	rva004FCBF6();
}

// ??1Rva004FCAF6@@QAE@XZ @0x004FCCB8 56B -> Rva004FCAF6::rva004FCC1F
class Rva004FCAF6
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva004FCC1F();
	~Rva004FCAF6();
};

Rva004FCAF6::~Rva004FCAF6()
{
	rva004FCC1F();
}

// ??1Rva0053BAE1@@QAE@XZ @0x0053BCED 56B -> Rva0053BAE1::rva0053BCC4
class Rva0053BAE1
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0053BCC4();
	~Rva0053BAE1();
};

Rva0053BAE1::~Rva0053BAE1()
{
	rva0053BCC4();
}

// ??1AptMapPreview@@QAE@XZ @0x0057CF0B 56B -> AptMapPreview::rva0057CD78
class AptMapPreview
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0057CD78();
	~AptMapPreview();
};

AptMapPreview::~AptMapPreview()
{
	rva0057CD78();
}

// ??1Rva005980F3@@QAE@XZ @0x005981CA 56B -> Rva005980F3::rva00598120
class Rva005980F3
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00598120();
	~Rva005980F3();
};

Rva005980F3::~Rva005980F3()
{
	rva00598120();
}

// ??1Rva00599FAA@@QAE@XZ @0x0059A281 56B -> Rva00599FAA::rva0059A258
class Rva00599FAA
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0059A258();
	~Rva00599FAA();
};

Rva00599FAA::~Rva00599FAA()
{
	rva0059A258();
}

// ??1Rva0059BD58@@QAE@XZ @0x0059BDE2 56B -> Rva0059BD58::rva0059BDB9
class Rva0059BD58
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0059BDB9();
	~Rva0059BD58();
};

Rva0059BD58::~Rva0059BD58()
{
	rva0059BDB9();
}

// ??1Rva005ACF0B@@QAE@XZ @0x005AD0AE 56B -> Rva005ACF0B::rva005AD085
class Rva005ACF0B
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva005AD085();
	~Rva005ACF0B();
};

Rva005ACF0B::~Rva005ACF0B()
{
	rva005AD085();
}

// ??1Rva005C45FE@@QAE@XZ @0x005C4690 56B -> Rva005C45FE::rva005C4667
class Rva005C45FE
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva005C4667();
	~Rva005C45FE();
};

Rva005C45FE::~Rva005C45FE()
{
	rva005C4667();
}

// ??1Rva005C8C73@@QAE@XZ @0x005C8D2E 56B -> Rva005C8C73::rva005C8CDA
class Rva005C8C73
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva005C8CDA();
	~Rva005C8C73();
};

Rva005C8C73::~Rva005C8C73()
{
	rva005C8CDA();
}

// ??1Rva005F20C5@@QAE@XZ @0x005F21F8 56B -> Rva005F20C5::rva005F20F2
class Rva005F20C5
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva005F20F2();
	~Rva005F20C5();
};

Rva005F20C5::~Rva005F20C5()
{
	rva005F20F2();
}

// ??1Rva006007A5@@QAE@XZ @0x00600959 56B -> Rva006007A5::rva0060082B
class Rva006007A5
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0060082B();
	~Rva006007A5();
};

Rva006007A5::~Rva006007A5()
{
	rva0060082B();
}

// ??1Rva00079A0C@@QAE@XZ @0x00079E55 56B -> Rva00079A0C::rva00079C8D
class Rva00079A0C
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00079C8D();
	~Rva00079A0C();
};

Rva00079A0C::~Rva00079A0C()
{
	rva00079C8D();
}

// ??1Rva001363CC@@QAE@XZ @0x0013660A 56B -> Rva001363CC::rva001364CE
class Rva001363CC
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva001364CE();
	~Rva001363CC();
};

Rva001363CC::~Rva001363CC()
{
	rva001364CE();
}

// ??1Rva00170AE4@@QAE@XZ @0x00170D47 56B -> Rva00170AE4::rva00170BAD
class Rva00170AE4
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00170BAD();
	~Rva00170AE4();
};

Rva00170AE4::~Rva00170AE4()
{
	rva00170BAD();
}

// ??1Rva00170B19@@QAE@XZ @0x00170D7F 56B -> Rva00170B19::rva00170BD6
class Rva00170B19
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00170BD6();
	~Rva00170B19();
};

Rva00170B19::~Rva00170B19()
{
	rva00170BD6();
}

// ??1Rva002177CD@@QAE@XZ @0x00217C2E 56B -> Rva002177CD::rva002179D9
class Rva002177CD
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002179D9();
	~Rva002177CD();
};

Rva002177CD::~Rva002177CD()
{
	rva002179D9();
}

// ??1Rva00217A02@@QAE@XZ @0x00217FB2 56B -> Rva00217A02::rva00217C66
class Rva00217A02
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00217C66();
	~Rva00217A02();
};

Rva00217A02::~Rva00217A02()
{
	rva00217C66();
}

// ??1Rva00217A37@@QAE@XZ @0x00217FEA 56B -> Rva00217A37::rva00217C8F
class Rva00217A37
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00217C8F();
	~Rva00217A37();
};

Rva00217A37::~Rva00217A37()
{
	rva00217C8F();
}

// ??1Rva0022115A@@QAE@XZ @0x002212F1 56B -> Rva0022115A::rva00221234
class Rva0022115A
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00221234();
	~Rva0022115A();
};

Rva0022115A::~Rva0022115A()
{
	rva00221234();
}

// ??1Rva0022E121@@QAE@XZ @0x0022E1F1 56B -> Rva0022E121::rva0022E177
class Rva0022E121
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0022E177();
	~Rva0022E121();
};

Rva0022E121::~Rva0022E121()
{
	rva0022E177();
}

// ??1Rva00240CAB@@QAE@XZ @0x00242EAF 56B -> Rva00240CAB::rva0024191A
class Rva00240CAB
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0024191A();
	~Rva00240CAB();
};

Rva00240CAB::~Rva00240CAB()
{
	rva0024191A();
}

// ??1Rva002A4281@@QAE@XZ @0x002A583E 56B -> Rva002A4281::rva002A47E1
class Rva002A4281
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva002A47E1();
	~Rva002A4281();
};

Rva002A4281::~Rva002A4281()
{
	rva002A47E1();
}

// ??1Rva003ED68D@@QAE@XZ @0x003ED879 56B -> Rva003ED68D::rva003ED6E4
class Rva003ED68D
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva003ED6E4();
	~Rva003ED68D();
};

Rva003ED68D::~Rva003ED68D()
{
	rva003ED6E4();
}

// ??1Rva003ED94FDtor@@QAE@XZ @0x003ED94F 58B -> bfmeClearMembers (0x003ED7A2)
// The same shape (and the same EH record, 0x00B8373D) as 0x003ED879 above,
// but the clear is the free helper the LargeGroupAudio map code calls with
// the map, not a member of it.
class LGA_MemberObj;
void bfmeClearMembers(LGA_MemberObj *map);

class Rva003ED94FDtor
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	~Rva003ED94FDtor();
};

Rva003ED94FDtor::~Rva003ED94FDtor()
{
	bfmeClearMembers((LGA_MemberObj *)this);
}


// ??1Rva0041090E@@QAE@XZ @0x00410CB9 56B -> Rva0041090E::rva00410A14
class Rva0041090E
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00410A14();
	~Rva0041090E();
};

Rva0041090E::~Rva0041090E()
{
	rva00410A14();
}

// ??1Rva00463782@@QAE@XZ @0x00464391 56B -> Rva00463782::rva00463D72
class Rva00463782
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva00463D72();
	~Rva00463782();
};

Rva00463782::~Rva00463782()
{
	rva00463D72();
}

// ??1Rva005B3751@@QAE@XZ @0x005B3C91 56B -> Rva005B3751::rva005B3947
class Rva005B3751
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva005B3947();
	~Rva005B3751();
};

Rva005B3751::~Rva005B3751()
{
	rva005B3947();
}

// ??1Rva0032D3D3@@QAE@XZ @0x0032E4E3 56B -> Rva0032D3D3::rva0032DCB7
class Rva0032D3D3
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva0032DCB7();
	~Rva0032D3D3();
};

Rva0032D3D3::~Rva0032D3D3()
{
	rva0032DCB7();
}

// ??1Rva0060126D@@QAE@XZ @0x0060137F 56B -> Rva0060126D::rva006012C4
class Rva0060126D
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva006012C4();
	~Rva0060126D();
};

Rva0060126D::~Rva0060126D()
{
	rva006012C4();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva002076E7Map@@QAE@XZ=??1Rva00206667@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0020779EMap@@QAE@XZ=??1Rva00206706@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00256461Member@@QAE@XZ=??1Rva00255CD1@@QAE@XZ")

class Rva0008AACF
{
public:
	void rva0008AACF();
};

void Rva0008AACF::rva0008AACF()
{
	((Rva0006F318 *)this)->~Rva0006F318();
}

class Rva002A8E76
{
public:
	void rva002A8E76();
};

void Rva002A8E76::rva002A8E76()
{
	((Rva002A8B8C *)this)->~Rva002A8B8C();
}

class Rva0032EC5E
{
public:
	void rva0032EC5E();
};

void Rva0032EC5E::rva0032EC5E()
{
	((Rva0032EAA1 *)this)->~Rva0032EAA1();
}

class Rva00396994
{
public:
	void rva00396994();
};

void Rva00396994::rva00396994()
{
	((Rva00395CEB *)this)->~Rva00395CEB();
}

class Rva004491A9
{
public:
	void rva004491A9();
};

void Rva004491A9::rva004491A9()
{
	((Rva00448E3B *)this)->~Rva00448E3B();
}

class Rva00598202
{
public:
	void rva00598202();
};

void Rva00598202::rva00598202()
{
	((Rva005980F3 *)this)->~Rva005980F3();
}

class Rva0059A2B9
{
public:
	void rva0059A2B9();
};

void Rva0059A2B9::rva0059A2B9()
{
	((Rva00599FAA *)this)->~Rva00599FAA();
}

class Rva0059BE1A
{
public:
	void rva0059BE1A();
};

void Rva0059BE1A::rva0059BE1A()
{
	((Rva0059BD58 *)this)->~Rva0059BD58();
}

class Rva005C8D66
{
public:
	void rva005C8D66();
};

void Rva005C8D66::rva005C8D66()
{
	((Rva005C8C73 *)this)->~Rva005C8C73();
}

class Rva005F2273
{
public:
	void rva005F2273();
};

void Rva005F2273::rva005F2273()
{
	((Rva005F20C5 *)this)->~Rva005F20C5();
}

class Rva0007A225
{
public:
	void rva0007A225();
};

void Rva0007A225::rva0007A225()
{
	((Rva00079A0C *)this)->~Rva00079A0C();
}

class Rva001F0778
{
public:
	void rva001F0778();
};

void Rva001F0778::rva001F0778()
{
	((Rva001F050B *)this)->~Rva001F050B();
}

class Rva00211FA3
{
public:
	void rva00211FA3();
};

void Rva00211FA3::rva00211FA3()
{
	((Rva0021119B *)this)->~Rva0021119B();
}

class Rva002213C0
{
public:
	void rva002213C0();
};

void Rva002213C0::rva002213C0()
{
	((Rva0022115A *)this)->~Rva0022115A();
}

class Rva00243B4D
{
public:
	void rva00243B4D();
};

void Rva00243B4D::rva00243B4D()
{
	((Rva00240CAB *)this)->~Rva00240CAB();
}

class Rva0025674A
{
public:
	void rva0025674A();
};

void Rva0025674A::rva0025674A()
{
	((Rva00255CA8 *)this)->~Rva00255CA8();
}

class Rva00281D47
{
public:
	void rva00281D47();
};

void Rva00281D47::rva00281D47()
{
	((Rva0027F4CB *)this)->~Rva0027F4CB();
}

class Rva00288BF4
{
public:
	void rva00288BF4();
};

void Rva00288BF4::rva00288BF4()
{
	((Rva0028881C *)this)->~Rva0028881C();
}

class Rva002928B0
{
public:
	void rva002928B0();
};

void Rva002928B0::rva002928B0()
{
	((Rva002913EB *)this)->~Rva002913EB();
}

class Rva0029FCD4
{
public:
	void rva0029FCD4();
};

void Rva0029FCD4::rva0029FCD4()
{
	((Rva0029B63A *)this)->~Rva0029B63A();
}

class Rva002A0D0C
{
public:
	void rva002A0D0C();
};

void Rva002A0D0C::rva002A0D0C()
{
	((Rva0029B667 *)this)->~Rva0029B667();
}

class Rva002D537B
{
public:
	void rva002D537B();
};

void Rva002D537B::rva002D537B()
{
	((Rva002D394B *)this)->~Rva002D394B();
}

class Rva002E1F83
{
public:
	void rva002E1F83();
};

void Rva002E1F83::rva002E1F83()
{
	((Rva002E15E6 *)this)->~Rva002E15E6();
}

class Rva002F0F02
{
public:
	void rva002F0F02();
};

void Rva002F0F02::rva002F0F02()
{
	((Rva002EE9B7 *)this)->~Rva002EE9B7();
}

class Rva00385D20
{
public:
	void rva00385D20();
};

void Rva00385D20::rva00385D20()
{
	((Rva0038404A *)this)->~Rva0038404A();
}

class Rva003896AD
{
public:
	void rva003896AD();
};

void Rva003896AD::rva003896AD()
{
	((Rva00388EAE *)this)->~Rva00388EAE();
}

class Rva003979F6
{
public:
	void rva003979F6();
};

void Rva003979F6::rva003979F6()
{
	((Rva00395D18 *)this)->~Rva00395D18();
}

class Rva0039934F
{
public:
	void rva0039934F();
};

void Rva0039934F::rva0039934F()
{
	((Rva00397C94 *)this)->~Rva00397C94();
}

class Rva0039FD93
{
public:
	void rva0039FD93();
};

void Rva0039FD93::rva0039FD93()
{
	((Rva0039F56E *)this)->~Rva0039F56E();
}

class Rva003ED94A
{
public:
	void rva003ED94A();
};

void Rva003ED94A::rva003ED94A()
{
	((Rva003ED68D *)this)->~Rva003ED68D();
}

class Rva004079D0
{
public:
	void rva004079D0();
};

void Rva004079D0::rva004079D0()
{
	((Rva004070D4 *)this)->~Rva004070D4();
}

class Rva00440012
{
public:
	void rva00440012();
};

void Rva00440012::rva00440012()
{
	((Rva0043EA9C *)this)->~Rva0043EA9C();
}

class Rva0053BD61
{
public:
	void rva0053BD61();
};

void Rva0053BD61::rva0053BD61()
{
	((Rva0053BAE1 *)this)->~Rva0053BAE1();
}

class Rva005AD14D
{
public:
	void rva005AD14D();
};

void Rva005AD14D::rva005AD14D()
{
	((Rva005ACF0B *)this)->~Rva005ACF0B();
}

class Rva005B3D4B
{
public:
	void rva005B3D4B();
};

void Rva005B3D4B::rva005B3D4B()
{
	((Rva005B3751 *)this)->~Rva005B3751();
}

class Rva00600BB9
{
public:
	void rva00600BB9();
};

void Rva00600BB9::rva00600BB9()
{
	((Rva006007A5 *)this)->~Rva006007A5();
}

class Rva00217FAD
{
public:
	void rva00217FAD();
};

void Rva00217FAD::rva00217FAD()
{
	((Rva002177CD *)this)->~Rva002177CD();
}

class Rva002A5B2B
{
public:
	void rva002A5B2B();
};

void Rva002A5B2B::rva002A5B2B()
{
	((Rva002A4281 *)this)->~Rva002A4281();
}

class Rva00413456
{
public:
	void rva00413456();
};

void Rva00413456::rva00413456()
{
	((Rva0041331E *)this)->~Rva0041331E();
}

class Rva005C46D4
{
public:
	void rva005C46D4();
};

void Rva005C46D4::rva005C46D4()
{
	((Rva005C45FE *)this)->~Rva005C45FE();
}

class Rva00601452
{
public:
	void rva00601452();
};

void Rva00601452::rva00601452()
{
	((Rva0060126D *)this)->~Rva0060126D();
}




