// ?rva00395BCB@Rva00395BCB@@QAEXPBX0@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00395BCB@Rva00395BCB@@QAEXPBX0@Z @0x00395BCB 181B: thiscall with two flag args plus audio event prefix plus TheAudio slots.
// Evidence: callers at 0x00397A82 0x00397ADF; neighbors CastleMemberBehaviorDtor plus Rva00395C80Check; rowed BfmeAudioEventPrefix136 ctor plus BfmeStringTailRecord144 dtor plus TheAudio; vtable offsets +0x64 +0x6c +0xd0; member +0x20 handle plus +4 +0x14 plus +8 +0x74.
struct OpaqueRefElement4 { void *p; };
enum ObjectID { INVALID_ID = 0 };
struct BfmeStringTailRecord144 { virtual ~BfmeStringTailRecord144(); };
struct BfmeAudioEventPrefix136
{
	BfmeAudioEventPrefix136(const OpaqueRefElement4 &ref, ObjectID id);
	BfmeStringTailRecord144 m_head;
	char m_rest[0x88 - 4];
};

struct FlagArg { char m_pad[0x18]; unsigned m_flags; };
struct Ref4Inner { char m_pad[0x14]; OpaqueRefElement4 m_ref; };
struct Ref8Inner { char m_pad[0x74]; int m_id; };

class AudioManager
{
public:
	virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03(); virtual void f04();
	virtual void f05(); virtual void f06(); virtual void f07(); virtual void f08(); virtual void f09();
	virtual void f10(); virtual void f11(); virtual void f12(); virtual void f13(); virtual void f14();
	virtual void f15(); virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23(); virtual void f24();
	virtual int AddEvent(const BfmeAudioEventPrefix136 &ev);
	virtual void f26();
	virtual void RemoveEvent(unsigned handle);
	virtual void f28(); virtual void f29(); virtual void f30(); virtual void f31(); virtual void f32();
	virtual void f33(); virtual void f34(); virtual void f35(); virtual void f36(); virtual void f37();
	virtual void f38(); virtual void f39(); virtual void f40(); virtual void f41(); virtual void f42();
	virtual void f43(); virtual void f44(); virtual void f45(); virtual void f46(); virtual void f47();
	virtual void f48(); virtual void f49(); virtual void f50(); virtual void f51();
	virtual bool IsPlaying(unsigned handle);
};
extern AudioManager *TheAudio;

class Rva00395BCB
{
public:
	virtual void f0();
	void rva00395BCB(const void *a, const void *b);
private:
	void *m_4;
	void *m_8;
	char m_pad0C[0x14];
	unsigned m_20;
};

void Rva00395BCB::rva00395BCB(const void *a_, const void *b_)
{
	const FlagArg *a = (const FlagArg *)a_;
	const FlagArg *b = (const FlagArg *)b_;
	unsigned fb = b->m_flags >> 27;
	if (((fb & 1) != 0)) {
		Ref4Inner *r4 = (Ref4Inner *)m_4;
		OpaqueRefElement4 *ref = &r4->m_ref;
		if (*(void **)ref == 0)
			return;
		if (!TheAudio->IsPlaying(m_20)) {
			Ref8Inner *r8 = (Ref8Inner *)m_8;
			BfmeAudioEventPrefix136 ev(*ref, (ObjectID)r8->m_id);
			m_20 = TheAudio->AddEvent(ev);
		}
		return;
	}
	unsigned fa = a->m_flags;
	fa >>= 27;
	if (((fa & 1) == 0))
		return;
	if (m_20 < 5)
		return;
	TheAudio->RemoveEvent(m_20);
	m_20 = 1;
}
