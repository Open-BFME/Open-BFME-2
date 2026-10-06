// cl: /Ireference/shims/bfme2_ascii
// ?Rva003BC510Do@@YGXH@Z @0x003BC510 20B: script forwards int arg to TheAudio vslot 0x68 with 0.
// Evidence: mov ecx,[0xDFE6E8]=TheAudio mov eax,[ecx] push 0 push [esp+8] call [eax+0x68] ret 4; caller 0x003CD1DE.
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
	virtual void s26(int a, int b);
};
extern AudioManager *TheAudio;

void __stdcall Rva003BC510Do(int v)
{
	TheAudio->s26(v, 0);
}
