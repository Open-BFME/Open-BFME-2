// cl: /Ireference/shims/bfme2_ascii
// ?Rva003BC4FFForward@@YAXXZ @0x003BC4FF 17B: script forwards to TheAudio slot 0xbc with 0.
// Evidence: mov ecx,[0xDFE6E8]=TheAudio mov eax,[ecx] push 0 call [eax+0xbc] ret; caller 0x003CD1C6; sibling TacticalView forwarders same tail shape.
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
	virtual void s47(int);
};
extern AudioManager *TheAudio;

void __cdecl Rva003BC4FFForward()
{
	TheAudio->s47(0);
}
