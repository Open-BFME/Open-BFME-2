// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BBFFBSet@@YGXHM@Z @0x003BBFFB 77B leaf caller 0x003CC50F globals 0xBCF628 0xBBB8D8 TheAudio slot 0xEC
// Evidence: float clamp of arg2 scaled by g_Va00BCF628 into 0..g_Va00BBB8D8 then TheAudio virtual 0xEC with (clamped, arg1, 0).
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
	virtual void s59(float v, int a, int b);
};
extern AudioManager *TheAudio;
extern float g_Va00BCF628;
extern float g_Va00BBB8D8;
void __stdcall Rva003BBFFBSet(int a, float b)
{
	float v = *(const volatile float *)&b * g_Va00BCF628;
	if (v < 0.0f)
		v = 0.0f;
	else if (v > g_Va00BBB8D8)
		v = g_Va00BBB8D8;
	TheAudio->s59(v, a, 0);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_Va00BCF628@@3MA=__real@3c23d70a")
