// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BBC61Set@@YGX_N@Z @0x003BBC61 32B leaf caller 0x003CBF60 globals TheAudio slots 0x40 0x44 args 0x10 1 1
// Evidence: cmp [esp+4],0 mov ecx,[TheAudio] mov eax,[ecx] push 1 push 1 push 0x10 je slot 0x44 else slot 0x40 ret 4.
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
	virtual void s16(int, int, int);
	virtual void s17(int, int, int);
};
extern AudioManager *TheAudio;
void __stdcall Rva003BBC61Set(bool b)
{
	if (b)
		TheAudio->s16(0x10, 1, 1);
	else
		TheAudio->s17(0x10, 1, 1);
}
