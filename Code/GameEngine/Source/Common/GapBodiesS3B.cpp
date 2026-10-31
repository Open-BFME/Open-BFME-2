// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small table-reached bodies from .text gaps no ledger row covers (seat-3
// batch B; see GapBodiesS3A.cpp). Each body is reached only through a retail
// table in .rdata; retail bytes establish every shape. Owning classes are not
// recovered, so each keeps an address-derived name and a view of only the
// members it touches. Callees and globals use the ledger's existing spellings.

class AsciiString;
class Object;
struct Coord3D;

// --- 0x001E0301 (32B): find the +0x148 template by name in TheThingFactory
// and ask it for its asset list.
class ThingTemplate
{
public:
	void GetAssetList(int a, int b);						// 0x0033CF34
	bool isEquivalentTo(const ThingTemplate *other) const;	// 0x0033BB04
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};

extern ThingFactory *TheThingFactory;

struct Rva001E0301Name
{
	int m_data;
};

class Rva001E0301
{
public:
	virtual void rva001E0301(int assetList, int b);
private:
	char m_pad04[0x148 - 4];
	Rva001E0301Name m_templateName;							// +0x148
};

void Rva001E0301::rva001E0301(int assetList, int b)
{
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(*(const AsciiString *)&m_templateName);
	if (thingTemplate)
		((ThingTemplate *)thingTemplate)->GetAssetList(assetList, b);
}

// --- 0x00210F27 (22B): run the +0x25C effects manager's rowed 0x003EF008 and
// 0x003EF2FF passes.
class Rva003EF008
{
public:
	void rva003EF008();										// 0x003EF008
};

class LivingWorldRegionEffectsManager
{
public:
	void rva003EF2FF();										// 0x003EF2FF
};

class Rva00210F27
{
public:
	virtual void rva00210F27();
private:
	char m_pad04[0x25C - 4];
	LivingWorldRegionEffectsManager *m_effects;				// +0x25C
};

void Rva00210F27::rva00210F27()
{
	((Rva003EF008 *)m_effects)->rva003EF008();
	m_effects->rva003EF2FF();
}

// --- 0x0029ACFB (23B): the +0x5C4 object's slot 15, or 0 when unset.
class Rva0029ACFBTarget
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual int s15();
};

class Rva0029ACFB
{
public:
	virtual int rva0029ACFB();
private:
	char m_pad04[0x5C4 - 4];
	Rva0029ACFBTarget *m_target;							// +0x5C4
};

int Rva0029ACFB::rva0029ACFB()
{
	if (m_target)
		return m_target->s15();
	return 0;
}

// --- 0x0029B558 / 0x0029B563 / 0x0029B5CD / 0x0029B5D8 (11B each): forward
// to rowed members of the +0x9BC object.
class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();								// 0x001FF3A9
};

class Rva005CB260
{
public:
	void rva005CB260();										// 0x005CB260
};

class Rva005CB26A
{
public:
	int rva005CB26A();										// 0x005CB26A
};

class Rva0029B558
{
public:
	virtual void rva0029B558();
	virtual void rva0029B563();
	virtual int rva0029B5D8();
private:
	char m_pad04[0x9BC - 4];
	Rva001FF3A9 *m_target;									// +0x9BC
};

void Rva0029B558::rva0029B558()
{
	m_target->Rva001FF3A9::rva001FF3A9();
}

void Rva0029B558::rva0029B563()
{
	((Rva005CB260 *)m_target)->rva005CB260();
}

int Rva0029B558::rva0029B5D8()
{
	return ((Rva005CB26A *)m_target)->rva005CB26A();
}

// --- 0x0030B0A3 (64B): print through own slot 24 at the current column
// (+0x04 plus the +0x14 margin) and line (+0x08), then advance them over
// the text.
class Rva0030B0A3
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24(int x, int y, const char *text);
	virtual void print(const char *text);
private:
	int m_col;												// +0x04
	int m_line;												// +0x08
	int m_0C;
	int m_10;
	int m_margin;											// +0x14
};

void Rva0030B0A3::print(const char *text)
{
	s24(m_margin + m_col, m_line, text);
	const char *cursor = text;
	int col = 0;
	char character;
	while ((character = *cursor++) != 0)
	{
		if (character != '\n')
			++col;
		else
		{
			col = 0;
			++m_line;
			m_col = 0;
		}
	}
	m_col += col;
}

// --- 0x003ADE15 (29B): clone into a fresh 0x18-byte copy (rowed copy ctor
// 0x003ADE32).
class Rva003ADE32
{
public:
	Rva003ADE32(const Rva003ADE32 &other) throw();			// 0x003ADE32
	virtual Rva003ADE32 *clone();
private:
	char m_pad04[0x18 - 4];
};

Rva003ADE32 *Rva003ADE32::clone()
{
	return new Rva003ADE32(*this);
}

// --- 0x00466457 / 0x0049A6C7 (16B each): from a +0x0C interface, the
// object's +0xFC / +0x3E4 base (null-checked conversion).
class Rva00466457Base0
{
public:
	virtual void b0();
	int m_04;
	int m_08;
};

class Rva00466457Base3
{
public:
	virtual void b3();
};

class Rva00466457Iface
{
public:
	virtual Rva00466457Base3 *getCaveInterface();
	char m_pad04[0xFC - 0x0C - 4];
};

class Rva00466457 : public Rva00466457Base0, public Rva00466457Iface, public Rva00466457Base3
{
public:
	virtual Rva00466457Base3 *getCaveInterface();
};

class Rva0049A6C7Base3
{
public:
	virtual void b3();
};

class Rva0049A6C7Iface
{
public:
	virtual Rva0049A6C7Base3 *rva0049A6C7();
	char m_pad04[0x3E4 - 0x0C - 4];
};

class Rva0049A6C7 : public Rva00466457Base0, public Rva0049A6C7Iface, public Rva0049A6C7Base3
{
public:
	virtual Rva0049A6C7Base3 *rva0049A6C7();
};

// --- 0x00479CD9 (29B): from a +0x10 interface, copy the object's slot-88
// position into the first argument; always true.
class Rva00479CD9Base0
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual const Coord3D *s88();
	char m_pad04[0x10 - 4];
};

struct Rva00479CD9Pos
{
	int x, y, z;
};

class Rva00479CD9Iface
{
public:
	virtual bool getNaturalRallyPoint(Rva00479CD9Pos *out, int unused);
};

class Rva00479CD9 : public Rva00479CD9Base0, public Rva00479CD9Iface
{
public:
	virtual bool getNaturalRallyPoint(Rva00479CD9Pos *out, int unused);
};

bool Rva00479CD9::getNaturalRallyPoint(Rva00479CD9Pos *out, int)
{
	*out = *(const Rva00479CD9Pos *)s88();
	return true;
}

// --- 0x00481837 (11B): from a +0x20 interface, the object's slot 13; the
// argument is unused.
class Rva00481837Base0
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	char m_pad04[0x20 - 4];
};

class Rva00481837Iface
{
public:
	virtual void rva00481837(int unused);
};

class Rva00481837 : public Rva00481837Base0, public Rva00481837Iface
{
public:
	virtual void rva00481837(int unused);
};

void Rva00481837::rva00481837(int)
{
	s13();
}

// --- 0x00494AC6 (19B): hand the float to slot 15 of the +0x18 base.
class Rva00494AC6Base0
{
public:
	virtual void b0();
	char m_pad04[0x18 - 4];
};

class Rva00494AC6Base18
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(float v);
};

class Rva00494AC6 : public Rva00494AC6Base0, public Rva00494AC6Base18
{
public:
	virtual void rva00494AC6(float v);
};

void Rva00494AC6::rva00494AC6(float v)
{
	s15(v);
}
