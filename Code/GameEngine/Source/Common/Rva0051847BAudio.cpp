// cl: /O1 /MD /EHsc /arch:SSE
// ?rva0051847B@Rva0051847B@@QAEXH@Z @0x0051847B 220B
// Audio options apply: if m_27c==2 and m_284==0 set 1 and tail to rowed
// rva00518359 else build OptionPreferences local, drive Display via 0x009FE9D8
// slot 0x64, loop 5 volumes via getVolume/ftol/scale, then UseEAX3 slot 0x184
// plus just-landed Rva00518262Enable. Evidence: callers in next TU; rowed
// OptionPreferences ctor/getVolume/getUseEAX3 plus Rva002E4272 dtor; globals
// 0x009FE758 0x009FE9D8 0x009FE6E8 0x007CF628; precedent Miles openDevice.
class Rva00518359
{
public:
	void rva00518359();
};
class Rva00222479ByteOneSetter
{
public:
	void enable();
};
void __cdecl Rva00518262Enable(void);
class Rva002E4272
{
public:
	virtual ~Rva002E4272();
	char m_body[0x10];
};
class OptionPreferences : public Rva002E4272
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	float getVolume(int index);
	bool getUseEAX3();
};
class Display
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24();
	virtual void v64(float a, float b, float c, int d);
};
class Global9FE758
{
public:
	char m_pad[0xBCC];
	float m_BCC;
};
extern Global9FE758 *g_Va009FE758;
extern Display *TheDisplay;
class AudioManager
{
public:
	virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
	virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
	virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
	virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
	virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
	virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
	virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
	virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
	virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43();
	virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
	virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51();
	virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55();
	virtual void a56(); virtual void a57();
	virtual void slotE8(int idx, float vol);
	virtual void a59(); virtual void a60(); virtual void a61(); virtual void a62();
	virtual void a63(); virtual void a64(); virtual void a65(); virtual void a66();
	virtual void a67(); virtual void a68(); virtual void a69(); virtual void a70();
	virtual void a71(); virtual void a72(); virtual void a73(); virtual void a74();
	virtual void a75(); virtual void a76(); virtual void a77(); virtual void a78();
	virtual void a79(); virtual void a80(); virtual void a81(); virtual void a82();
	virtual void a83(); virtual void a84(); virtual void a85(); virtual void a86();
	virtual void a87(); virtual void a88(); virtual void a89(); virtual void a90();
	virtual void a91(); virtual void a92(); virtual void a93(); virtual void a94();
	virtual void a95(); virtual void a96();
	virtual void slot184(bool useEAX);
};
extern AudioManager *TheAudio;
class Rva0051847B
{
	char m_pad[0x27C];
	int m_27C;
	char m_pad2[0x284 - 0x280];
	unsigned char m_284;
public:
	void rva0051847B(int unused);
};
void Rva0051847B::rva0051847B(int unused)
{
	if (m_27C == 2 && m_284 == 0)
	{
		m_27C = 1;
		((Rva00518359 *)this)->rva00518359();
		return;
	}
	OptionPreferences prefs;
	TheDisplay->v64(g_Va009FE758->m_BCC, 0.0f, 1.0f, 0);
	for (int i = 0; i < 5; ++i)
	{
		int iv = (int)prefs.getVolume(i);
		TheAudio->slotE8(i, (float)iv * 0.01f);
	}
	TheAudio->slot184(prefs.getUseEAX3());
	Rva00518262Enable();
}
// ?g_Va009FE758@@3PAVGlobal9FE758@@A: the global at VA 0xdfe758 is ?TheGlobalData@@3PAVGlobalData@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE758@@3PAVGlobal9FE758@@A=?TheGlobalData@@3PAVGlobalData@@A")
