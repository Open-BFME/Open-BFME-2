// cl: /DNDEBUG /MD
//
// ?rva00262FFF@AIUpdateInterface@@QAEXXZ, retail 0x00262FFF, 38 bytes.
// AIUpdateInterface tail sibling of rva00263025 (same +0x21C/+0x3BC and
// TheGameLogic 0x00DFE78C): call virtual slot 0x1B8; if false return; else
// load TheGameLogic+0x40 into +0x21C and set +0x3BC to 1. Honest
// address-derived name; slot identity unproven. No other callees.

extern class GameLogic *TheGameLogic;

struct GameLogicFrame
{
	char m_pad00[0x40];
	unsigned int m_frame;
};

#define TheGameLogic (*(GameLogicFrame **)&TheGameLogic)

class AIUpdateInterface
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2C();
	virtual void s30();
	virtual void s34();
	virtual void s38();
	virtual void s3C();
	virtual void s40();
	virtual void s44();
	virtual void s48();
	virtual void s4C();
	virtual void s50();
	virtual void s54();
	virtual void s58();
	virtual void s5C();
	virtual void s60();
	virtual void s64();
	virtual void s68();
	virtual void s6C();
	virtual void s70();
	virtual void s74();
	virtual void s78();
	virtual void s7C();
	virtual void s80();
	virtual void s84();
	virtual void s88();
	virtual void s8C();
	virtual void s90();
	virtual void s94();
	virtual void s98();
	virtual void s9C();
	virtual void sA0();
	virtual void sA4();
	virtual void sA8();
	virtual void sAC();
	virtual void sB0();
	virtual void sB4();
	virtual void sB8();
	virtual void sBC();
	virtual void sC0();
	virtual void sC4();
	virtual void sC8();
	virtual void sCC();
	virtual void sD0();
	virtual void sD4();
	virtual void sD8();
	virtual void sDC();
	virtual void sE0();
	virtual void sE4();
	virtual void sE8();
	virtual void sEC();
	virtual void sF0();
	virtual void sF4();
	virtual void sF8();
	virtual void sFC();
	virtual void s100();
	virtual void s104();
	virtual void s108();
	virtual void s10C();
	virtual void s110();
	virtual void s114();
	virtual void s118();
	virtual void s11C();
	virtual void s120();
	virtual void s124();
	virtual void s128();
	virtual void s12C();
	virtual void s130();
	virtual void s134();
	virtual void s138();
	virtual void s13C();
	virtual void s140();
	virtual void s144();
	virtual void s148();
	virtual void s14C();
	virtual void s150();
	virtual void s154();
	virtual void s158();
	virtual void s15C();
	virtual void s160();
	virtual void s164();
	virtual void s168();
	virtual void s16C();
	virtual void s170();
	virtual void s174();
	virtual void s178();
	virtual void s17C();
	virtual void s180();
	virtual void s184();
	virtual void s188();
	virtual void s18C();
	virtual void s190();
	virtual void s194();
	virtual void s198();
	virtual void s19C();
	virtual void s1A0();
	virtual void s1A4();
	virtual void s1A8();
	virtual void s1AC();
	virtual void s1B0();
	virtual void s1B4();
	virtual bool s1B8();
	void rva00262FFF();
	char m_pad04[0x21C - 4];
	unsigned int m_field21C;
	char m_pad220[0x3BC - 0x220];
	unsigned char m_flag3BC;
};

void AIUpdateInterface::rva00262FFF()
{
	if (!s1B8())
		return;
	m_field21C = TheGameLogic->m_frame;
	m_flag3BC = 1;
}
