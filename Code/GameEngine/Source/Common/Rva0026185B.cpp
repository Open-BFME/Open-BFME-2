// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0026185B@Rva0026185B@@QAE_NPAVObject@@@Z, retail 0x0026185B, 71 bytes.
// Chain from Object::rva002931BA (rowed 0x002931BA): if arg Object template
// dword +0x108 low byte carries 0x80 or 0x04 return false; else if
// arg->rva002931BA() return false; else if arg AI (+0x258) null return false;
// else return (AI vslot 0x1B8 byte == this +0x08 byte). Evidence: arg
// offsets template +0x04 (Object_isAbleToAttack) and AI +0x258
// (Object_isAbleToAttack), template +0x108 gate and AI slot match retail
// immediates; this +0x08 byte read from caller context; no callers yet.

typedef bool Bool;
typedef unsigned char UByte;

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	unsigned int m_flags108;
};

class Object;

class AI110
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void slot89() = 0;
	virtual void slot90() = 0;
	virtual void slot91() = 0;
	virtual void slot92() = 0;
	virtual void slot93() = 0;
	virtual void slot94() = 0;
	virtual void slot95() = 0;
	virtual void slot96() = 0;
	virtual void slot97() = 0;
	virtual void slot98() = 0;
	virtual void slot99() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual UByte slot110() = 0;
};

class Object
{
public:
	Bool rva002931BA();

public:
	unsigned char m_pad00[4];
	ThingTemplate *m_template;
	unsigned char m_pad08[0x258 - 0x08];
	AI110 *m_ai;
};

class Rva0026185B
{
public:
	Bool rva0026185B(Object *obj);

private:
	unsigned char m_pad00[8];
	UByte m_unk08;
};

Bool Rva0026185B::rva0026185B(Object *obj)
{
	unsigned int flags108 = obj->m_template->m_flags108;
	if ((flags108 & 0x80) != 0)
		return false;
	if ((flags108 & 4) != 0)
		return false;
	if (obj->rva002931BA())
		return false;
	AI110 *ai = obj->m_ai;
	if (ai == 0)
		return false;
	return ai->slot110() == m_unk08;
}
