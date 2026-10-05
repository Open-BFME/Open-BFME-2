// cl: /O1
// ?Rva003BAA2D@@YGXM@Z @0x003BAA2D 25B: free stdcall one float forwarding to Display slot 0xd0.
// Evidence: ret 4 one float arg; mov ecx TheDisplay fld [esp+4] mov eax [ecx] push ecx fstp [esp] call [eax+0xd0]; caller 0x003CAB22.
class Display
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
	virtual void slot52(float a0);
};
extern Display *TheDisplay;

void __stdcall Rva003BAA2D(float a0)
{
	TheDisplay->slot52(a0);
}
