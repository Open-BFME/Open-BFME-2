// cl: /MD
// ?rva005399D0Check@ControlBar@@QAEHPAVObject@@@Z @0x005399D0 67B:
// ControlBar member predicate over Object*: null check then isLocallyControlled
// then isSelectable then rva0028D481==0 then TheInGameUI slot 0x188 call,
// true (1) when all pass else false (0). Caller 0x0042AF97 pushes Object*.
// Evidence: rowed Object preds 0x0028B07A 0x0028D7FD plus int leaf 0x0028D481
// plus TheInGameUI global 0x009FEDF0 slot 98; ret 4 single dword arg.
// Native caller0042AF97 loads TheControlBar into ECX before this call;
// the member receiver is unused within the body. This corrects the earlier
// free-function ABI inference; the target name remains address-derived.
class Object
{
public:
	bool isLocallyControlled() const;
	bool isSelectable() const;
	int rva0028D481() const;
};

class InGameUI
{
public:
	virtual ~InGameUI();
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
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual void s81();
	virtual void s82();
	virtual void s83();
	virtual void s84();
	virtual void s85();
	virtual void s86();
	virtual void s87();
	virtual void s88();
	virtual void s89();
	virtual void s90();
	virtual void s91();
	virtual void s92();
	virtual void s93();
	virtual void s94();
	virtual void s95();
	virtual void s96();
	virtual void s97();
	virtual void s98();
};

extern InGameUI *TheInGameUI;

class ControlBar {public:int rva005399D0Check(Object*);};

int ControlBar::rva005399D0Check(Object *obj)
{
	if (obj == 0)
		return 0;
	if (!obj->isLocallyControlled())
		return 0;
	if (!obj->isSelectable())
		return 0;
	if ((unsigned char)obj->rva0028D481() == 0)
	{
		TheInGameUI->s98();
		return 1;
	}
	return 0;
}
