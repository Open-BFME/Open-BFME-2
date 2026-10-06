// cl: /DNDEBUG /MD /EHsc
// ?Rva0043A31ECleanup@@YAXXZ, retail 0x0043A31E, 34 bytes.
// Free cleanup: release Bfme VM0 mutexes via rva0025D9CB(false), then
// TheAudio slot 0x8c with (2, 1, 0).
// Evidence: rowed callee 0x0025D9CB (BfmeStrVM0::rva0025D9CB bool) with push 0;
// TheAudio data 0x009FE6E8 precedent Rva0033FF2BDtor slot 0x6c; first global
// 0x009FE9D8; caller 0x0043A351 ctor calls here; chain lane.
extern class Display *TheDisplay;

class BfmeStrVM0
{
public:
	void rva0025D9CB(bool flag);
};

#define g_bfmeVM0 (*(BfmeStrVM0 **)&TheDisplay)

class AudioManager
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void _pad03();
	virtual void _pad04();
	virtual void _pad05();
	virtual void _pad06();
	virtual void _pad07();
	virtual void _pad08();
	virtual void _pad09();
	virtual void _pad10();
	virtual void _pad11();
	virtual void _pad12();
	virtual void _pad13();
	virtual void _pad14();
	virtual void _pad15();
	virtual void _pad16();
	virtual void _pad17();
	virtual void _pad18();
	virtual void _pad19();
	virtual void _pad20();
	virtual void _pad21();
	virtual void _pad22();
	virtual void _pad23();
	virtual void _pad24();
	virtual void _pad25();
	virtual void _pad26();
	virtual void _pad27();
	virtual void _pad28();
	virtual void _pad29();
	virtual void _pad30();
	virtual void _pad31();
	virtual void _pad32();
	virtual void _pad33();
	virtual void _pad34();
	virtual void audioSlot8c(int a, int b, int c);
};
extern AudioManager *TheAudio;


void __cdecl Rva0043A31ECleanup(void)
{
	g_bfmeVM0->rva0025D9CB(false);
	TheAudio->audioSlot8c(2, 1, 0);
}
