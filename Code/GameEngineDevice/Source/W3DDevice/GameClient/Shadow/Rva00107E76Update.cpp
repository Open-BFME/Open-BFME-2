// cl: /DNDEBUG /MD /EHsc
// ?rva00107E76@Rva00107E76Mgr@@QAEXXZ @0x00107E76 277B: walk the 0x18-byte shadow
// entries from the back; an entry flagged, or whose vslot 0x190 reports true while
// the manager flag at +0x9C is set, gets its update sequence. Projected budget at
// the global's +0x14/+0x18 is charged by the 0x18-entry size.
class W3DProjectedShadowManager;
class W3DVolumetricShadowManagerV2
{
public:
	void drawAndRelease(int flag);
};

class Rva00106CF0
{
public:
	void rva00106CF0();
};
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;

class Rva00107E76Sub
{
public:
	char m_pad00[0x24];
	int m_24;
	int m_28;
};

class Rva00107E76Obj
{
public:
	virtual void rva00107E76V00();
	virtual void rva00107E76V01();
	virtual void rva00107E76V02();
	virtual void rva00107E76V03();
	virtual void rva00107E76V04();
	virtual void rva00107E76V05();
	virtual void rva00107E76V06();
	virtual void rva00107E76V07();
	virtual void rva00107E76V08();
	virtual void rva00107E76V09();
	virtual void rva00107E76V10();
	virtual void rva00107E76V11();
	virtual void rva00107E76V12();
	virtual void rva00107E76V13();
	virtual void rva00107E76V14();
	virtual void rva00107E76V15();
	virtual void rva00107E76V16();
	virtual void rva00107E76V17();
	virtual void rva00107E76V18();
	virtual void rva00107E76V19();
	virtual void rva00107E76V20();
	virtual void rva00107E76V21();
	virtual void rva00107E76V22();
	virtual void rva00107E76V23();
	virtual void rva00107E76V24();
	virtual void rva00107E76V25();
	virtual void rva00107E76V26();
	virtual void rva00107E76V27();
	virtual void rva00107E76V28();
	virtual void rva00107E76V29();
	virtual void rva00107E76V30();
	virtual void rva00107E76V31();
	virtual void rva00107E76V32();
	virtual void rva00107E76V33();
	virtual void rva00107E76V34();
	virtual void rva00107E76V35();
	virtual void rva00107E76V36();
	virtual void rva00107E76V37();
	virtual void rva00107E76V38();
	virtual void rva00107E76V39();
	virtual void rva00107E76V40();
	virtual void rva00107E76V41();
	virtual void rva00107E76V42();
	virtual void rva00107E76V43();
	virtual void rva00107E76V44();
	virtual void rva00107E76V45();
	virtual void rva00107E76V46();
	virtual void rva00107E76V47();
	virtual void rva00107E76V48();
	virtual void rva00107E76V49();
	virtual void rva00107E76V50();
	virtual void rva00107E76V51();
	virtual void rva00107E76V52();
	virtual void rva00107E76V53();
	virtual void rva00107E76V54();
	virtual void rva00107E76V55();
	virtual void rva00107E76V56();
	virtual void rva00107E76V57();
	virtual void rva00107E76V58();
	virtual void rva00107E76V59();
	virtual void rva00107E76V60();
	virtual void rva00107E76V61();
	virtual void rva00107E76V62();
	virtual void rva00107E76V63();
	virtual void rva00107E76V64();
	virtual void rva00107E76V65();
	virtual void rva00107E76V66();
	virtual void rva00107E76V67();
	virtual void rva00107E76V68();
	virtual void rva00107E76V69();
	virtual void rva00107E76V70();
	virtual void rva00107E76V71();
	virtual void rva00107E76V72();
	virtual void rva00107E76V73();
	virtual void rva00107E76V74();
	virtual void rva00107E76V75();
	virtual void rva00107E76V76();
	virtual void rva00107E76V77();
	virtual void rva00107E76V78();
	virtual void rva00107E76V79();
	virtual void rva00107E76V80();
	virtual void rva00107E76V81();
	virtual void rva00107E76V82();
	virtual void rva00107E76V83();
	virtual void rva00107E76V84();
	virtual void rva00107E76V85();
	virtual void rva00107E76V86();
	virtual void rva00107E76V87();
	virtual void rva00107E76V88();
	virtual void rva00107E76V89();
	virtual void rva00107E76V90();
	virtual void rva00107E76V91();
	virtual void rva00107E76V92();
	virtual void rva00107E76V93();
	virtual void rva00107E76V94();
	virtual void rva00107E76V95();
	virtual void rva00107E76V96();
	virtual void rva00107E76V97();
	virtual void rva00107E76V98();
	virtual void rva00107E76V99();
	virtual int rva00107E76Probe();

public:
	char m_pad04[0xC4 - 4];
	Rva00107E76Sub *m_c4;
};

class Rva00107E76Elem
{
public:
	void rva00107961();
	void rva00107A50(void *block);
	void rva00106CF0();
	void rva00107B41(int d, short c, int b, void *block);

	Rva00107E76Obj *m_obj;
	char m_pad04[0x0C];
	int m_10;
	unsigned char m_14;
	char m_pad15[3];
};

class Rva00107E76Pair
{
public:
	char m_pad00[4];
	char *m_04;
};

class W3DProjectedShadowManager
{
public:
	void drawAndRelease(int flag);
	void rva001072C9();

	char m_pad00[0xC];
	Rva00107E76Pair *m_0C;
	Rva00107E76Pair *m_10;
	int m_14;
	int m_18;
};

class Rva00107E76Mgr
{
public:
	void rva00107E76();

	char m_pad00[0x78];
	int m_78;
	Rva00107E76Elem *m_7C;
	char m_pad80[0x90 - 0x80];
	char m_90[0x9C - 0x90];
	unsigned char m_9C;
};

// ?rva00107E76@Rva00107E76Mgr@@QAEXXZ @0x00107E76
void Rva00107E76Mgr::rva00107E76()
{
	Rva00107E76Elem *elem = m_7C + m_78;
	if (elem == m_7C)
		return;
	int limit = 0x7530;
	do
	{
		elem = elem - 1;
		if (elem->m_14 == 0)
		{
			if (elem->m_obj->rva00107E76Probe() != 0 && m_9C == 0)
				continue;
		}
		elem->rva00107961();
		elem->rva00107A50((void *)m_90);
		reinterpret_cast<Rva00106CF0 *>(elem)->rva00106CF0();
		int edi = elem->m_obj->m_c4->m_24;
		int eax = (edi + elem->m_10 * 2) * 3;
		if (eax > limit)
			continue;
		if (TheW3DProjectedShadowManager->m_0C != 0)
		{
			if ((unsigned int)TheW3DProjectedShadowManager->m_18 < (unsigned int)eax)
				reinterpret_cast<W3DVolumetricShadowManagerV2 *>(TheW3DProjectedShadowManager)->drawAndRelease(1);
		}
		if (TheW3DProjectedShadowManager->m_0C == 0)
			TheW3DProjectedShadowManager->rva001072C9();
		int x2 = (int)TheW3DProjectedShadowManager->m_10->m_04 + (limit - TheW3DProjectedShadowManager->m_18) * 2;
		short x3 = (short)(limit - TheW3DProjectedShadowManager->m_14);
		int x4 = (limit - TheW3DProjectedShadowManager->m_14) * 0xc + (int)TheW3DProjectedShadowManager->m_0C->m_04;
		elem->rva00107B41(x4, x3, x2, (void *)m_90);
		TheW3DProjectedShadowManager->m_14 += elem->m_obj->m_c4->m_28 * -2;
		int ecx2 = elem->m_10 * 2;
		edi = -edi - ecx2;
		edi *= 3;
		TheW3DProjectedShadowManager->m_18 += edi;
	} while (elem != m_7C);
}
