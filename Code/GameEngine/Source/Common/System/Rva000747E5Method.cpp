// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva000747E5@Rva000747E5@@QAEXXZ, retail 0x000747E5, 23 bytes.
// Guarded DisplayStringManager factory: if TheDisplayStringManager (VA 0xdfead8)
// then this+0x28 = manager->newDisplayString() at slot 0x38. Manager layout per
// Rva004E5821Method/WinInstanceDataDisplayStrings (new at 0x38 free at 0x3c).
// Evidence: unlock lane, caller 0x00046A50 (also caller of neighbouring
// Rva0007517F ctor/methods), same +0x28 member the ctor zeroes.
// ?rva000748DF@Rva000747E5@@QAEXH@Z, retail 0x000748DF, 23 bytes.
// Setter: this+0x1c = val, then notify DisplayString at +0x28 via slot 0x18.
// Evidence: unlock lane, same +0x1c/+0x28 members as neighbours, caller 0x00046A50.
class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18(int v);
};

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual void s10() = 0;
	virtual void s14() = 0;
	virtual void s18() = 0;
	virtual void s1C() = 0;
	virtual void s20() = 0;
	virtual void s24() = 0;
	virtual void s28() = 0;
	virtual void s2C() = 0;
	virtual void s30() = 0;
	virtual void s34() = 0;
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString(DisplayString *s) = 0;
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva000747E5
{
public:
	void rva000747E5();
	void rva000748DF(int val);
private:
	char m_pad[0x1c];
	int m_1c;
	char m_pad2[0x08];
	DisplayString *m_28;
};

void Rva000747E5::rva000747E5()
{
	if (TheDisplayStringManager != 0)
		m_28 = TheDisplayStringManager->newDisplayString();
}

void Rva000747E5::rva000748DF(int val)
{
	m_1c = val;
	if (m_28 != 0)
		m_28->s18(val);
}

// ??0Rva000748F6@@QAE@XZ, retail 0x000748F6, 25 bytes.
// Ctor: 3x 0x10 elements at +4 via vector ctor iterator with rowed ??0Region3D.
// Evidence: unlock lane, static init caller 0x00074AFF with ecx=0xDE1ED8, size 0x10 count 3 per retail.
struct Region3D
{
	Region3D() throw();
	char m_data[0x10];
};

class Rva000748F6
{
public:
	Rva000748F6();
private:
	char m_00[4];
	Region3D m_arr[3];
};

Rva000748F6::Rva000748F6()
{
}
