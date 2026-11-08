// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BfmeThingDGD constructor, retail 0x007F7FA0, 228 bytes. The matched
// allocator wrapper at 0x007F86A0 allocates 0x6E0 bytes and calls this body,
// and the scalar deleting destructor at 0x007F86D0 frees the same 0x6E0 after
// calling the destructor at 0x007F8090. The layout matches the destructor
// source beside this one.
//
// The two base levels are what order the five vftable stores. Retail writes
// the pair at +4 and +8 first, then all three again, which is what a base
// constructor followed by a derived one produces. The four child records and
// the two small members construct themselves, so the compiler places the edi
// save between them the way retail does. The root pair writes through a
// volatile cast, because the derived constructor overwrites both words and
// the optimiser drops a plain store it can see overwritten. The derived
// three stay plain, which is what lets the zero constant materialise ahead
// of them.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];  // folded vftable 0x00C1C780 (49 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@")[];  // folded vftable 0x00C6FFFC (10 classes), by its data-ledger name

// The retail table at RVA 0x008E3018: 36 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GGen007F86D0@@UAEPAXI@Z")();
void __identifier("?Set_Y_Translation@Matrix3D@@QAEXM@Z")();
void __identifier("?setValue@Rva007F5700ValueAndState@@QAEXH@Z")();
void __identifier("?setList0@Rva007F8200Owner@@QAEXPAPAXH@Z")();
void __identifier("?setList1@Rva007F8200Owner@@QAEXPAPAXH@Z")();
void __identifier("?setList2@Rva007F8200Owner@@QAEXPAPAXH@Z")();
void __identifier("?rva007F8400@BfmeThingDGD@@UAEXEHPAX@Z")();
void __identifier("?request@Rva007F7030@@QAEXHH@Z")();
void __identifier("?isReadyAtThree@Rva007F57C0ThresholdPredicate@@QBEHXZ")();
void __identifier("?isReady@Rva007F57C0ThresholdPredicate@@QBEHXZ")();
void __identifier("?bfmeIsThree@Gen_007F57E0@@QBEHXZ")();
void __identifier("?bfmeIsFive@Gen_007F57E0@@QBEHXZ")();
void __identifier("?reset@Rva007F70D0Owner@@QAEXXZ")();
void __identifier("?requestRegionCount@Rva007F7A00Browser@@QAEXXZ")();
void __identifier("?get@Rva00661FD0DwordField@@QBEHXZ")();
void __identifier("?get@Rva007F70F0@@QAEPAXH@Z")();
void __identifier("?bfmeFind@Gen_007F7110@@QBEPAVBfmeSlotDV@@PAX@Z")();
void __identifier("?reset@Rva007F7140Owner@@QAEXXZ")();
void __identifier("?request@Rva007F7AE0Owner@@QAEXHHHHHHHHPB_JIPAPBDI@Z")();
void __identifier("?get@Rva0066D5D0DwordField@@QBEHXZ")();
void __identifier("?get@Rva007F7160@@QAEPAXH@Z")();
void __identifier("?bfmeFind@Gen_007F7180@@QBEPAVBfmeSlotEH@@PAX@Z")();
void __identifier("?rva006638A0@BfmeThingDGD@@QAEXHH@Z")();
void __identifier("?requestEntry@BfmeThingZI@@QAEXHH@Z")();
void __identifier("?get@Rva0066F540DwordField@@QBEHXZ")();
void __identifier("?bfmeGoVJP@GameBrowser@@QAEXHHHHHHH_NHHHHH@Z")();
void __identifier("?bfmeGoVJU@BfmeThingVJU@@QAEXXZ")();
void __identifier("?request@Rva007F8650Owner@@QAEXXZ")();
void __identifier("?bfmeGoVJS@BfmeThingVJS@@QAEXHHH@Z")();
void __identifier("?rva007F5E00@Rva007F5D10GameBrowser@@QAEXHPBD@Z")();
void __identifier("?bfmeGoVJO@BfmeThingVJO@@QAEXH@Z")();
void __identifier("?wrap@Rva007F5FB0@@UAEXPAX000@Z")();
void __identifier("?bfmeGoVJN@BfmeThingVJN@@QAEXHHHHH@Z")();
void __identifier("?bfmeGoVJR@BfmeThingVJR@@QAEXHHHH@Z")();
void __identifier("?bfmeGoVJQ@BfmeThingVJQ@@QAEXH@Z")();
void __identifier("?requestHostedGame@Rva007F5920Owner@@QAEXHH@Z")();
}
extern const void *const g_00CE3018[36] = {
	(const void *)&__identifier("??_GGen007F86D0@@UAEPAXI@Z"), // slot 0 0x00664D50
	(const void *)&__identifier("?Set_Y_Translation@Matrix3D@@QAEXM@Z"), // slot 1 0x00665600
	(const void *)&__identifier("?setValue@Rva007F5700ValueAndState@@QAEXH@Z"), // slot 2 0x00661EB0
	(const void *)&__identifier("?setList0@Rva007F8200Owner@@QAEXPAPAXH@Z"), // slot 3 0x00664880
	(const void *)&__identifier("?setList1@Rva007F8200Owner@@QAEXPAPAXH@Z"), // slot 4 0x00664920
	(const void *)&__identifier("?setList2@Rva007F8200Owner@@QAEXPAPAXH@Z"), // slot 5 0x006649C0
	(const void *)&__identifier("?rva007F8400@BfmeThingDGD@@UAEXEHPAX@Z"), // slot 6 0x00664A80
	(const void *)&__identifier("?request@Rva007F7030@@QAEXHH@Z"), // slot 7 0x00663720
	(const void *)&__identifier("?isReadyAtThree@Rva007F57C0ThresholdPredicate@@QBEHXZ"), // slot 8 0x00661F50
	(const void *)&__identifier("?isReady@Rva007F57C0ThresholdPredicate@@QBEHXZ"), // slot 9 0x00661F70
	(const void *)&__identifier("?bfmeIsThree@Gen_007F57E0@@QBEHXZ"), // slot 10 0x00661F90
	(const void *)&__identifier("?bfmeIsFive@Gen_007F57E0@@QBEHXZ"), // slot 11 0x00661FB0
	(const void *)&__identifier("?reset@Rva007F70D0Owner@@QAEXXZ"), // slot 12 0x006637C0
	(const void *)&__identifier("?requestRegionCount@Rva007F7A00Browser@@QAEXXZ"), // slot 13 0x00664080
	(const void *)&__identifier("?get@Rva00661FD0DwordField@@QBEHXZ"), // slot 14 0x00661FD0
	(const void *)&__identifier("?get@Rva007F70F0@@QAEPAXH@Z"), // slot 15 0x006637E0
	(const void *)&__identifier("?bfmeFind@Gen_007F7110@@QBEPAVBfmeSlotDV@@PAX@Z"), // slot 16 0x00663800
	(const void *)&__identifier("?reset@Rva007F7140Owner@@QAEXXZ"), // slot 17 0x00663830
	(const void *)&__identifier("?request@Rva007F7AE0Owner@@QAEXHHHHHHHHPB_JIPAPBDI@Z"), // slot 18 0x00664160
	(const void *)&__identifier("?get@Rva0066D5D0DwordField@@QBEHXZ"), // slot 19 0x0066D5D0
	(const void *)&__identifier("?get@Rva007F7160@@QAEPAXH@Z"), // slot 20 0x00663850
	(const void *)&__identifier("?bfmeFind@Gen_007F7180@@QBEPAVBfmeSlotEH@@PAX@Z"), // slot 21 0x00663870
	(const void *)&__identifier("?rva006638A0@BfmeThingDGD@@QAEXHH@Z"), // slot 22 0x006638A0
	(const void *)&__identifier("?requestEntry@BfmeThingZI@@QAEXHH@Z"), // slot 23 0x00663A50
	(const void *)&__identifier("?get@Rva0066F540DwordField@@QBEHXZ"), // slot 24 0x0066F540
	(const void *)&__identifier("?bfmeGoVJP@GameBrowser@@QAEXHHHHHHH_NHHHHH@Z"), // slot 25 0x00662320
	(const void *)&__identifier("?bfmeGoVJU@BfmeThingVJU@@QAEXXZ"), // slot 26 0x00663AB0
	(const void *)&__identifier("?request@Rva007F8650Owner@@QAEXXZ"), // slot 27 0x00664CD0
	(const void *)&__identifier("?bfmeGoVJS@BfmeThingVJS@@QAEXHHH@Z"), // slot 28 0x006623D0
	(const void *)&__identifier("?rva007F5E00@Rva007F5D10GameBrowser@@QAEXHPBD@Z"), // slot 29 0x006625A0
	(const void *)&__identifier("?bfmeGoVJO@BfmeThingVJO@@QAEXH@Z"), // slot 30 0x006626A0
	(const void *)&__identifier("?wrap@Rva007F5FB0@@UAEXPAX000@Z"), // slot 31 0x00662750
	(const void *)&__identifier("?bfmeGoVJN@BfmeThingVJN@@QAEXHHHHH@Z"), // slot 32 0x00662780
	(const void *)&__identifier("?bfmeGoVJR@BfmeThingVJR@@QAEXHHHH@Z"), // slot 33 0x006627F0
	(const void *)&__identifier("?bfmeGoVJQ@BfmeThingVJQ@@QAEXH@Z"), // slot 34 0x006628C0
	(const void *)&__identifier("?requestHostedGame@Rva007F5920Owner@@QAEXHH@Z"), // slot 35 0x00662980
};
// The retail table at RVA 0x008E3010: 1 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?request@Rva007F62F0ConnectRequest@@QAEXHPAXPAH@Z")();
}
extern const void *const g_00CE3010[1] = {
	(const void *)&__identifier("?request@Rva007F62F0ConnectRequest@@QAEXHPAXPAH@Z"), // slot 0 0x00662A80
};
// The retail table at RVA 0x008E3008: 2 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva00664370@Rva00664370@@UAEXHPAURva00664370Probe@@@Z")();
void __identifier("?set@Rva007F63D0@@QAEXPAHPBURva007F63D0Src@@H@Z")();
}
extern const void *const g_00CE3008[2] = {
	(const void *)&__identifier("?rva00664370@Rva00664370@@UAEXHPAURva00664370Probe@@@Z"), // slot 0 0x00664370
	(const void *)&__identifier("?set@Rva007F63D0@@QAEXPAHPBURva007F63D0Src@@H@Z"), // slot 1 0x00662B60
};

struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

class Rva007F6BA0
{
public:
	Rva007F6BA0()
	{
		m_00 = 0;
		m_04 = 0;
	}

private:
	unsigned m_00;
	unsigned m_04;
};

class Rva007F6C60
{
public:
	Rva007F6C60()
	{
		m_00 = 0;
		m_04 = 0;
	}

private:
	unsigned m_00;
	unsigned m_04;
};

class Rva007F78E0Block
{
public:
	Rva007F78E0Block()
	{
		m_00 = 0;
		m_04 = 0;
	}

private:
	unsigned m_00;
	unsigned m_04;
};

// One 0x94-byte record of the four the holder owns at this+0x58. Its
// constructor is the still unnamed body at retail 0x007F6D60.
class Rva007F6D60Child
{
public:
	Rva007F6D60Child();

private:
	unsigned char m_unmodelled[ 0x94 ];
};

class BfmeThingECKb
{
public:
	void *bfmeGoECKb( void );
};

class Rva007F8090Root
{
public:
	Rva007F8090Root()
	{
		// BFME2 vtable VAs measured from retail (BFME1 donor holds 0x01118e58/0x0112b680).
		*(volatile unsigned *)&m_v4 = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
		*(volatile unsigned *)&m_v8 = ((unsigned int)__identifier("??_7?$CategoryModuleClass@$04@FXParticleSystem@@6B@"));
	}

	unsigned m_v0;
	unsigned m_v4;
	unsigned m_v8;
};

class Rva007F8090Base : public Rva007F8090Root
{
public:
	Rva007F8090Base()
	{
		// BFME2 vtable VAs measured from retail (BFME1 donor holds 0x0112b800/0x0112b7f8/0x0112b7f0).
		m_v0 = ((unsigned int)g_00CE3018);
		m_v4 = ((unsigned int)g_00CE3010);
		m_v8 = ((unsigned int)g_00CE3008);
	}
};

class BfmeThingDGD : public Rva007F8090Base
{
public:
	BfmeThingDGD( void *owner );

	void *m_0c;											///< retail this+0x0c
	void *m_10;
	unsigned m_14;
	unsigned m_18;
	unsigned m_1c;
	unsigned m_20;
	unsigned m_24;
	unsigned m_28;
	unsigned m_2c;
	unsigned m_30;
	unsigned char m_34;
	unsigned char m_35;
	unsigned char m_36;
	unsigned char m_37;
	Rva007F6BA0 m_38;									///< retail this+0x38
	unsigned m_40;
	unsigned m_44;
	Rva007F6C60 m_48;									///< retail this+0x48
	unsigned m_50;
	unsigned m_54;
	Rva007F6D60Child m_children[ 4 ];					///< retail this+0x58
	Rva007F78E0Block m_2a8;								///< retail this+0x2a8
	Rva007F78E0Block m_2b0;								///< retail this+0x2b0
	Rva007F78E0Block m_2b8;								///< retail this+0x2b8
	unsigned m_2c0;
	unsigned m_2c4;
	unsigned m_2c8;
	unsigned m_2cc;
	unsigned m_2d0;
	unsigned m_2d4;
	unsigned m_2d8;
	unsigned char m_tail[ 0x400 ];
	unsigned m_6dc;										///< retail this+0x6dc
};

// ??0BfmeThingDGD@@QAE@PAX@Z
BfmeThingDGD::BfmeThingDGD( void *owner )
{
	m_2c0 = 0;
	m_2c4 = 0;
	m_2c8 = 0;
	m_2cc = 0;
	m_2d0 = 0;
	m_2d4 = 0;
	m_0c = owner;
	m_10 = ((BfmeThingECKb *)m_0c)->bfmeGoECKb();
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_50 = 0;
	m_2c = 0;
	m_28 = 0;
	m_2d8 = 0;
	m_36 = 0;
	m_44 = 0;
	m_54 = 0;
	m_24 = 0;
	m_30 = 0;
	m_6dc = 0x2710;
}

typedef char BfmeThingDGDSize[ ( sizeof( BfmeThingDGD ) == 0x6e0 ) ? 1 : -1 ];
