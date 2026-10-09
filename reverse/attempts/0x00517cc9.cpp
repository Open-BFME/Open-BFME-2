// ?rva00517CC9@AptOnline@@QAEXABURva00516F3F@@@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?rva00517CC9@AptOnline@@QAEXABURva00516F3F@@@Z
// Retail 0x00517CC9..0x00517EA2 (473 bytes); called from 0x00417777.
// Buddy invite prompt of the online shell: only while the shell is up
// (+0x27C) and idle (mode +0x2B0 zero) and when the inviting profile is in
// TheGameSpyInfo's buddy map (vslot 24) and the current sub-screen (+0x290)
// agrees (vslot 8), it stores the invite (+0x298), enters mode 1 and shows a
// two-button message box: the "APT:BuddyInviteTitle" title and the
// "APT:BuddyInviteTextStrategic" / "APT:BuddyInviteTextOpenPlay" text (by
// shell kind +0x2AC) formatted with the buddy's name, answered by the
// shell's 0x005177EB / 0x005170B4 handlers.
// Evidence (target): strings above; rowed callees map<int BuddyInfo>
// _M_find (pinned fold 0x00388F63) Rva00516F3F::rva00516F63 0x00516F63
// UnicodeString(const AsciiString &) 0x006CB6D0 UnicodeString::format
// 0x006CB660 Rva0057BC63FunctorHolder 0x0057BC63 Rva0044BA4E ctor 0x0044BCAB
// / dtor 0x0044BA4E Rva004C5DD0::set 0x0044BD00 Rva0044BF40::rva0044BF40
// 0x0044BF40 message box Rva00437F61 0x00437F61 and the wide releaseBuffer
// 0x00036E70; AptOnlineShellCallbacks.cpp binds 0x005170B4 as the answer to
// these prompts. Binding / holder views follow AptQuitMenuCallbacks.cpp.
// The method name is address-derived.
// NEAR (banked; same size, ~0.85): everything through the format call and
// the two holder/pair constructions matches except frame placement (retail
// overlaps the first binding with the pair: frame 0x40 vs 0x44, so the
// binding/pair slots sit 4 bytes apart and the in-place-argument markers use
// [ebp-0x18]/[ebp-0x1C] instead of [ebp+8]/[ebp-0x18]); and retail builds
// the by-value callback argument (set 0x0044BD00 into rva0044BF40 0x0044BF40)
// before fetching the title temporary into [ebp+8], while this source
// fetches the title first. Tried: explicit/implicit callback conversion, a
// callback copy ctor, a named callback, direct FunctorBinding temporaries.
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}
	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount;
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	FunctorWrapperHead *m_ptr;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct Rva004F6986Member : public Rva0057BC63FunctorHolder
{
	Rva004F6986Member(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~Rva004F6986Member()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

struct Rva004C5DD0Pair;
class Rva004C5DD0
{
public:
	Rva004C5DD0 &set(const Rva004C5DD0Pair *pair);
};

struct Rva0044BA4E
{
	Rva0044BA4E(Rva004F6986Member first, Rva004F6986Member second);
	Rva0044BA4E(const Rva0044BA4E &other) { ((Rva004C5DD0 *)this)->set((const Rva004C5DD0Pair *)&other); }
	~Rva0044BA4E();
	void *m_00;
	void *m_04;
};

struct Rva0044BF40
{
	Rva0044BF40 *rva0044BF40(Rva0044BA4E pair);
	void *m_ptr;
};

struct Rva00437F61Callback
{
	__forceinline Rva00437F61Callback(const Rva0044BA4E &pair) { ((Rva0044BF40 *)this)->rva0044BF40(pair); }
	void *m_ptr;
};

extern "C" void __cdecl Rva00437F61(int type, const UnicodeString &message, const UnicodeString &title,
	Rva00437F61Callback callback);

class GameTextInterface
{
public:
#define V(n) virtual void slot##n() = 0;
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14)
#undef V
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual void slot16() = 0;
	virtual const UnicodeString *fetchRef(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class BuddyInfo
{
public:
	int m_id;
	AsciiString m_name; // +0x04
};
typedef _STL::map<int, BuddyInfo> BuddyInfoMap;

class GameSpyInfoInterface
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23)
#undef V
	virtual BuddyInfoMap *getBuddyMap() = 0;
};
extern GameSpyInfoInterface *TheGameSpyInfo;

struct Rva00516F3F
{
	Rva00516F3F *rva00516F63(const Rva00516F3F &other);
	int getProfileID() const { return m_profileID; }
	int m_profileID;
};

struct AptOnlineSubScreen
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual bool acceptsInvites();
};

// AptOnline is a multiple-inheritance class: its handlers bind as eight-byte
// member pointers ({function, 0} at binding +8). The two bases only carry the
// observed members at their native offsets.
struct AptOnlinePrimaryView
{
	unsigned char m_pad000[0x27C];
};

struct AptOnlineShellStateView
{
	bool m_shown;                    // +0x27C
	unsigned char m_pad27D[0x290 - 0x27D];
	AptOnlineSubScreen *m_current;   // +0x290
	unsigned char m_pad294[0x298 - 0x294];
	Rva00516F3F m_invite;            // +0x298
	unsigned char m_pad29C[0x2AC - 0x29C];
	int m_kind;                      // +0x2AC
	int m_mode;                      // +0x2B0
};

class AptOnline : public AptOnlinePrimaryView, public AptOnlineShellStateView
{
public:
	void rva00517CC9(const Rva00516F3F &invite);
	void rva005170B4();
	void rva005177EB();
};

void AptOnline::rva00517CC9(const Rva00516F3F &invite)
{
	if (!m_shown || m_mode != 0)
		return;
	BuddyInfoMap *buddies = TheGameSpyInfo->getBuddyMap();
	BuddyInfoMap::iterator it = buddies->find(invite.getProfileID());
	if (it == buddies->end())
		return;
	if (m_current && !m_current->acceptsInvites())
		return;
	m_invite.rva00516F63(invite);
	m_mode = 1;
	UnicodeString name(it->second.m_name);
	UnicodeString text;
	if (m_kind == 1)
		text.format(TheGameText->fetchRef("APT:BuddyInviteTextStrategic"), name.str());
	else
		text.format(TheGameText->fetchRef("APT:BuddyInviteTextOpenPlay"), name.str());
	Rva0044BA4E answers(
		MakeBinding(reinterpret_cast<FunctorMethod>(&AptOnline::rva005177EB), reinterpret_cast<FunctorTarget *>(this)),
		MakeBinding(reinterpret_cast<FunctorMethod>(&AptOnline::rva005170B4), reinterpret_cast<FunctorTarget *>(this)));
	Rva00437F61(2, TheGameText->fetch("APT:BuddyInviteTitle"), text, answers);
}
