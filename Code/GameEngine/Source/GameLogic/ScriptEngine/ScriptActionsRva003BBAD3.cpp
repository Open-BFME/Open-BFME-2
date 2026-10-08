// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BBAD3Set@@YAXXZ @0x003BBAD3 99B unlock callers 0x003BD5AC 0x003BE5EC 0x003BE6FC 0x003CBF32 callees setInputEnabled setVisibility appendBooleanArgument rva00405AA7 clearFlags slots 0x48 0x110
// Evidence: InGameUI+Mouse disables then MessageStream 0x3EC boolean then InGameUI slot 0x110 and 0x8B0 clear then tail clearFlags.
class InGameUI
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
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
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	void setInputEnabled(bool v);
};
extern InGameUI *TheInGameUI;
class Mouse
{
public:
	void setVisibility(bool v);
};
extern Mouse *TheMouse;
class GameMessage
{
public:
	void appendBooleanArgument(bool v);
};
class MessageStream
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void m04();
	virtual void m05();
	virtual void m06();
	virtual void m07();
	virtual void m08();
	virtual void m09();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual GameMessage *m18(int v);
};
extern class MessageStream *TheMessageStream;
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;
class Rva00405AA7
{
public:
	void rva00405AA7();
};
class BfmeOwnVVD;
extern BfmeOwnVVD *g_bfmeSingletonVVD;
class Rva005B5440
{
public:
	void clearFlags();
};
void Rva003BBAD3Set()
{
	TheInGameUI->setInputEnabled(false);
	TheMouse->setVisibility(false);
	GameMessage *m = TheMessageStream->m18(0x3ec);
	m->appendBooleanArgument(true);
	TheInGameUI->s68();
	((char *)TheInGameUI)[0x8b0] = 0;
	((Rva00405AA7 *)(*(BfmeWorldRV **)&TheControlBar))->rva00405AA7();
	return ((Rva005B5440 *)g_bfmeSingletonVVD)->clearFlags();
}

// ?Rva003BBB36Enable@@YAXXZ @0x003BBB36 27B leaf caller 0x003CBF3E globals TheInGameUI TheMouse callees setInputEnabled setVisibility
// Evidence: mov ecx,[TheInGameUI] push 1 call setInputEnabled mov ecx,[TheMouse] push 1 call setVisibility ret.
void Rva003BBB36Enable()
{
	TheInGameUI->setInputEnabled(true);
	TheMouse->setVisibility(true);
}
