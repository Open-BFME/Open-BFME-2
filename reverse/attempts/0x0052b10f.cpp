// ?rva0052B10F@Rva0052B10F@@QAEXXZ
// partial score=0.99 date=2026-10-06
// cl: /O1
// ?rva0052B10F@Rva0052B10F@@QAEXXZ, RVA 0x0052B10F size 112.
// Chain lane: calls rowed 0x002DA651 ctor; now ready.
// Evidence: caller at 0x004E0A71 in Rva004E0A58Refresh; vtable slot 0x64 on
// TheAudio (?TheAudio@@3PAVAudioManager@@A); dtor row 0x002D9A43;
// bool callee pin 0x0052B003; neighbours share /O1.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct OpaqueRefElement4
{
	void *referent;
};
struct AudioEvent88
{
	AudioEvent88(const OpaqueRefElement4 &ref, int id);
	virtual ~AudioEvent88();
	char m_pad[0x88 - 4];
};
#pragma comment(linker, "/alternatename:??0AudioEvent88@@QAE@ABUOpaqueRefElement4@@H@Z=??0Rva002DA651@@QAE@ABUOpaqueRefElement4@@H@Z")
#pragma comment(linker, "/alternatename:??1AudioEvent88@@UAE@XZ=??1BfmeStringTailRecord144@@UAE@XZ")
class AudioManager
{
public:
	virtual void vf00();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual void vf04();
	virtual void vf05();
	virtual void vf06();
	virtual void vf07();
	virtual void vf08();
	virtual void vf09();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void vf15();
	virtual void vf16();
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void vf20();
	virtual void vf21();
	virtual void vf22();
	virtual void vf23();
	virtual void vf24();
	virtual void vf25(const void *rec);
};
extern AudioManager *TheAudio;
class Rva0052B278
{
public:
	void rva0052B003(bool flag);
};
struct RefHost14
{
	char m_pad[0x14];
	OpaqueRefElement4 m_elem14;
};
struct ValHost38
{
	char m_pad[0x18];
	int m_val18;
};
class Rva0052B10F
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8(int a, int b);
	void rva0052B10F();
private:
	char m_pad04[0x14 - 0x04];
	RefHost14 *m_ptr14;
	char m_pad18[0x38 - 0x18];
	ValHost38 *m_ptr38;
	char m_pad3C[0x44 - 0x3C];
};
// ?rva0052B10F@Rva0052B10F@@QAEXXZ present-unmatched
void Rva0052B10F::rva0052B10F()
{
	RefHost14 *host = m_ptr14;
	if (host->m_elem14.referent == 0)
		goto skip_audio;
	_ReadWriteBarrier();
	ValHost38 *vh = m_ptr38;
	if (vh == 0)
		goto skip_audio;
	{
		AudioEvent88 tmp(host->m_elem14, vh->m_val18);
		TheAudio->vf25(&tmp);
	}
skip_audio:
	((Rva0052B278 *)this)->rva0052B003(true);
}
