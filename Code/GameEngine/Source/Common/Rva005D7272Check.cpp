// ?Rva005D7272Get@@YG_NPAVObject@@@Z
// cl: /MD
//
// ?Rva005D7272Get@@YG_NPAVObject@@@Z, retail 0x005D7272 118B: slot 6 (offset 0x18) of
// vtable 0x00875CA4 (class Rva005D724B). Stances gate (2) else victim gate, then speed
// check via locomotor float vs g_Va007C26F0.
//
// Evidence: gap lane same TU/flags; callees Stances namekey 0x0045EE2C findModule 0x0028B6D6
// Stances 0x0045ED4B victim 0x00268D71 Object 0x0028C197 float slots 0x264/0x14;
// global g_Va007C26F0.
typedef int Bool;
enum NameKeyType
{
	NK_UNKNOWN = 0
};
NameKeyType __cdecl Rva0045EE2CGet(void);
class Module;
class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend bool __stdcall Rva005D7272Get(Object *obj);
public:
	void *rva0028C197() const;
};
class StancesBehavior
{
public:
	int rva0045ED4B() const;
};
class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};
class Rva264Float
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
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
	virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
	virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95();
	virtual void s96(); virtual void s97(); virtual void s98(); virtual void s99();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110(); virtual void s111();
	virtual void s112(); virtual void s113(); virtual void s114(); virtual void s115();
	virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123();
	virtual void s124(); virtual void s125(); virtual void s126(); virtual void s127();
	virtual void s128(); virtual void s129(); virtual void s130(); virtual void s131();
	virtual void s132(); virtual void s133(); virtual void s134(); virtual void s135();
	virtual void s136(); virtual void s137(); virtual void s138(); virtual void s139();
	virtual void s140(); virtual void s141(); virtual void s142(); virtual void s143();
	virtual void s144(); virtual void s145(); virtual void s146(); virtual void s147();
	virtual void s148(); virtual void s149(); virtual void s150(); virtual void s151();
	virtual void s152();
	virtual float slot153();
};
class Rva14Float
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04();
	virtual float slot5();
};
extern float g_Va007C26F0;
bool __stdcall Rva005D7272Get(Object *obj)
{
	NameKeyType key = Rva0045EE2CGet();
	StancesBehavior *st = (StancesBehavior *)obj->findModule(key);
	if (st->rva0045ED4B() == 2
		|| (*(AIUpdateInterface **)((char *)obj + 0x258))->getCurrentVictim() == 0)
		return false;
	unsigned char *b = *(unsigned char **)((char *)obj + 4);
	float f;
	if ((b[0x115] & 0x20) != 0)
	{
		void *p = obj->rva0028C197();
		f = ((Rva264Float *)p)->slot153();
	}
	else
	{
		void *q = *(void **)((char *)obj + 0x254);
		f = ((Rva14Float *)q)->slot5();
	}
	return f > g_Va007C26F0;
}
