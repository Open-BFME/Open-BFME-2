// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z
// partial score=0.96 date=2026-10-05
// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z
// finish attempt for ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z @0x004320B1, 160B.
// cl: /O1 /MD
// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z @0x004320B1 160B.
//
// The global at 0xDFEA3C is a View*: matched sibling Rva0029B4F9Init.cpp
// declares that global as View *TheTacticalView and calls its slots 0x170 and
// 0xC8. Retail's call DWORD PTR [eax+0x168] is therefore View slot 90, which
// is why screenToTerrain sits behind 90 declarations here. The previous bank
// modelled this class as a `TacticalView` with screenToTerrain at slot 0 and
// so emitted call DWORD PTR [eax], which desynchronised the whole tail.
//
// InGameUI is unchanged and was already right: the matched sibling
// Rva004319F2.cpp fixes slot51 at 0xCC, slot54 at 0xD8 and the byte at 0x9B4,
// which is exactly retail's [eax+0xcc], [eax+0xc8] and cmp byte [ecx+0x9b4].
#include <stddef.h>

struct ICoord2D { int m_x; int m_y; };
struct Coord3D { float m_x; float m_y; float m_z; };

union GameMessageArgumentType
{
	int integer;
	struct Pix { int x; int y; } pixel;
};

class GameMessage
{
public:
	char m_pad[0x10];
	int m_10;
	const GameMessageArgumentType *getArgument(int i) const;
};

class Rva00431A4D
{
	char m_00[4];
	unsigned char m_04;
	unsigned char m_05;
public:
	void rva00431A4D(GameMessage *msg);
};

class Rva00431E95
{
public:
	int rva00431E95(void *p);
};

class View
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130();
	virtual void s131();
	virtual void s132();
	virtual void s133();
	virtual void s134();
	virtual void s135();
	virtual void s136();
	virtual void s137();
	virtual void s138();
	virtual void s139();
	virtual void s140();
	virtual void s141();
	virtual void s142();
	virtual void s143();
	virtual void s144();
	virtual void s145();
	virtual void s146();
	virtual void s147();
	virtual void s148();
	virtual void s149();
	virtual void s150();
	virtual void s151();
	virtual void s152();
	virtual void s153();
	virtual void s154();
	virtual void s155();
	virtual void s156();
	virtual void s157();
	virtual void s158();
	virtual void s159();
};

class InGameUI
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49();
	virtual void slot50(Coord3D *pos);
	virtual bool slot51();
	char m_pad[0x9B4 - 4];
	unsigned char m_9b4;
};

struct S12_0029AA27 { int a; int b; int c; };
class Rva0029AA27
{
public:
	void rva0029AA27(const S12_0029AA27 *src);
};

extern View *TheTacticalView;
extern InGameUI *TheInGameUI;
extern Rva0029AA27 *TheRva0029AA27;
extern void *g_ks_30f4ea;

View *TheTacticalView;
InGameUI *TheInGameUI;
Rva0029AA27 *TheRva0029AA27;
void *g_ks_30f4ea;

class Rva004320B1
{
	void *m_00;
	Rva00431A4D *m_04;
public:
	int rva004320B1(GameMessage *msg);
};

// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z present-unmatched
int Rva004320B1::rva004320B1(GameMessage *msg)
{
	switch (msg->m_10)
	{
	case 3:
	{
		const GameMessageArgumentType *a0 = msg->getArgument(0);
		ICoord2D pixel;
		pixel.m_x = a0->pixel.x;
		pixel.m_y = a0->pixel.y;
		Coord3D world;
		TheTacticalView->screenToTerrain(&pixel, &world, false);
		if (TheInGameUI->slot51())
			TheInGameUI->slot50(&world);
		if (TheInGameUI->m_9b4 != 0)
			TheRva0029AA27->rva0029AA27((const S12_0029AA27 *)&world);
		return 0;
	}
	case 6:
	case 0x10:
		m_04->rva00431A4D(msg);
		return ((Rva00431E95 *)this)->rva00431E95(msg);
	default:
		return 0;
	}
}