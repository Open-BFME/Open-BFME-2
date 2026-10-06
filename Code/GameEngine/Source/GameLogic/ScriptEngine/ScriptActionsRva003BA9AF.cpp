// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BA9AF@@YGXH@Z @0x003BA9AF 27B: free stdcall one int null-guarded to AudioManager slot 0xf8 with int 0.
// Evidence: ret 4 one arg; mov ecx TheAudio test je; mov eax [ecx] push 0 push [esp+8] call [eax+0xf8]; caller 0x003CAA98.
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
	virtual void s61();
	virtual void slot62(int a0, int a1);
};
extern AudioManager *TheAudio;

void __stdcall Rva003BA9AF(int a0)
{
	AudioManager *p = TheAudio;
	if (p)
		p->slot62(a0, 0);
}
