// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BA96F@@YGXMMMMM@Z @0x003BA96F 64B: free stdcall five floats null-guarded to AudioManager slot 0xf4 with int 0.
// Evidence: ret 20 five float args; mov ecx TheAudio test je; five fld-fstp push 0 call [eax+0xf4]; caller 0x003CAA80.
class AudioManager
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
	virtual void slot61(float a0, float a1, float a2, float a3, float a4, int a5);
};
extern AudioManager *TheAudio;

void __stdcall Rva003BA96F(float a0, float a1, float a2, float a3, float a4)
{
	AudioManager *p = TheAudio;
	if (p)
		p->slot61(a0, a1, a2, a3, a4, 0);
}
