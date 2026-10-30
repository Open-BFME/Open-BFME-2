// cl: /MD /EHsc
// ?rva006FB910@AptAnimationPoolData@@QAEAAXXZ @0x006FB910 70B.
//
// A member of the Apt object reached through the global at VA 0x00E176D0, the
// same pool pointer Rva006CC950Mouse.cpp and Rva006CD2A0Cluster.cpp establish.
// It is vtable-referenced: no direct caller in .text reaches 0x006FB910, the
// sibling 0x006FB860 or the callee 0x006F9EF0.
//
// Retail body, decoded from game.dat:
//   esi = this;
//   if (!((AptValue *)this + 0x44)->isUndefined())   // 0x006DC010, rowed
//       Rva006F9EF0(this);                           // 0x006F9EF0, unnamed
//   for (i = 0; i < this->mListCount; ++i)            // +0x3C
//       rva006FB860(this, this->aList[i], i == 0);   // +0x40, dword elements
//   this->mListCount = 0;
//
// The +0x3C count / +0x40 element-list / +0x44 AptValue triple is read here
// directly and is a different block from the BIL count/list pair at
// +0x10/+0x14 modelled in AptAnimationPoolDataBIL.cpp, although both sit in
// the object behind the one global.
//
// 0x006FB860 is a `ret 8` thiscall taking (this, int value, int isFirst), which
// fixes the two right-to-left pushes and the `sete al` predicate for i == 0.
// Its own body unpacks a packed coordinate pair into this+0x74/+0x78 through
// the same 0x00E176D0 global, tying both members to one object; it is declared
// here and not defined, so this TU reproduces the call only.

class BfmeAptValue006DCD20
{
public:
	int isString() const;
	bool isUndefined() const;
	void *rva006E04A0() const;
	int isScriptFunction() const;
	BfmeAptValue006DCD20 *rva006DCEE0();
	void setGCRootCount(unsigned int);
	bool isCIH(bool) const;
	int rva006DCC60(bool) const;
	BfmeAptValue006DCD20 *rva006DCF60(bool);
	BfmeAptValue006DCD20 *checkedString();
	int rva006E02B0() const;
	virtual void vtableSlot0();
	virtual void vtableSlot1();
};

struct Rva006E3710Node;
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class Rva006E3710
{
public:
	bool rva006E3710(Rva006E3710Node*);
};
class AptCIH : public BfmeAptValue006DCD20
{
public:
	bool rva006CFCD0()const;
	void *rva006E1170()const;
	int rva006E1F90(int);
	bool queueClipEvents(int,int,int);
	void factorySetProperty(int,float,bool);
	void *rva006E1090() const; // rowed, 0x006E1090
	void rva006E1F00(int value); // address-derived, 0x006E1F00
};
extern AptCIH *__cdecl rva006F99D0(int eventCode, AptCIH *first,
                                   AptCIH *second);

// Partial pool view for input dispatch, button state and hit testing.
struct ButtonHitTestRecord;
class Rva006E1E30;
struct BfmeMesh1290;
struct BfmeTransform2_1290;
struct BfmePickNode1284;

class AptAnimationPoolData {
public:
	char pad[0x10];
	int mBILCount;
	ButtonHitTestRecord *aButtonInstanceList;
	unsigned short m18, m1a;
	BfmeAptValue006DCD20 **m1c;
	unsigned short m20, m22;
	BfmeAptValue006DCD20 **m24;
	char pad28[0x3C - 0x28];
	int mListCount;
	int *aList;
	BfmeAptValue006DCD20 *mValue;
	float m48, m4C, m50, m54, m58, m5C;
	BfmeAptValue006DCD20 *m60, *m64, *m68;
	AptCIH *current;
	unsigned char m70;
	char pad71[3];
	int m74, m78;
	bool validateBIL();
	void Rva006F9EF0();
	void rva006FA7E0(bool first, bool enabled, int value);
	bool rva006F9FC0(Rva006E1E30 *object, int unused);
	void rva006E6540();
	bool HandleFocusButton(int, int, void **);
	void AddListenerToQueue(BfmeAptValue006DCD20 *, int, int);
	void rva006FA100(AptCIH *, int);
	bool bfmeMeshHitTest1290(BfmeMesh1290 *mesh, const BfmeTransform2_1290 *transform,
		int pointX, int pointY);
	BfmePickNode1284 *bfmePick1284(int pointX, int pointY);
	AptCIH *rva006FA420(int x, int y);
	void setValidFocusButton();
	void rva006FB860(int value, char isFirst);
	void rva006FB120(int x, int y, int packed, int field, char isFirst);
	void rva006FB5B0(int x, int y, int packed, int field);
	void rva006FB910();
	void ProcessButtonState();
	void HandleAutoNav(AptCIH *candidate, int eventCode, int transition);
};

// 0x006F9EF0 is an unnamed sibling of the same class, called thiscall on
// `this` (retail moves ecx from esi and leaves no stack cleanup). It reads
// this+0x44..0x5C and this+0x74/+0x78 against the -9999.0f sentinel 0xC61C3C00;
// its own body is banked blocked in reverse/re_attempts.log on the unrowed
// 0x006DCF60 and 0x006E0930. Declared above as a member, not defined here.

void AptAnimationPoolData::rva006FB910()
{
    if (!mValue->isUndefined())
        Rva006F9EF0();
    for (int i = 0; i < mListCount; ++i)
        rva006FB860(aList[i], i == 0);
    mListCount = 0;
}

// Retail 0x006FAA20 shares +0x74/+0x78 and this with 0x006FB860; its direct
// reads establish +0x6C as an AptCIH pointer and +0x70 as a byte selector.
// Calls to 0x006FA420, 0x006E1F00 and 0x006FA100 remain address-based because
// their target bodies are unlanded; their addresses and ABIs come from these
// retail call sites. The owning class name remains address-derived.
void AptAnimationPoolData::ProcessButtonState()
{
    AptCIH *value = rva006FA420(m74, m78);
    Rva006E3710 *pool = (Rva006E3710 *)g_bfmeAptPtrAtE176D0;
    if (pool->rva006E3710((Rva006E3710Node *)value))
        value = 0;
    else if (value)
        value->vtableSlot0();

    if (m70) {
        if (current && !current->isUndefined()) {
            if (value != current) {
                if (*(int *)((char *)current->rva006E1090() + 0x18) == 4) {
                    current->rva006E1F00(2);
                    rva006FA100(current, 0x10);
                }
            } else if (*(int *)((char *)current->rva006E1090() + 0x18) == 2) {
                current->rva006E1F00(4);
                rva006FA100(current, 0x20);
            }
        } else if (value && !value->isUndefined()) {
            rva006FA100(value, 0x20);
        }
    } else if (value != current) {
        if (current && !current->isUndefined()) {
            current->rva006E1F00(1);
            rva006FA100(current, 2);
        }
        if (current)
            current->vtableSlot1();
        current = value;
        if (value) {
            value->vtableSlot0();
            if (!value->isUndefined()) {
                current->rva006E1F00(2);
                rva006FA100(value, 1);
            }
        }
    }

    if (value)
        value->vtableSlot1();
}

// ?rva006FAF80@AptAnimationPoolData@@QAEXPAVAptCIH@@HH@Z @0x006FAF80 386B.
// Retail bytes establish ECX=this, three 32-bit stack arguments (ret 0xC),
// a 0..15 state dispatch, and reads/writes of this+0x6C/+0x70. The candidate
// argument is tested by the rowed AptCIH predicate at 0x006CFCD0. The fields and
// direct sibling calls tie it to AptAnimationPoolData; WorldBuilder's twin names
// it HandleAutoNav (see the declaration above).
void AptAnimationPoolData::HandleAutoNav(AptCIH *candidate, int eventCode,
                              int transition)
{
    switch (eventCode) {
    case 1:
    case 2:
    case 14:
    case 15:
        if (m70 || transition)
            return;
        setValidFocusButton();
        if (!current)
            return;
        if (!candidate) {
            candidate = rva006F99D0(
                eventCode, *(AptCIH **)((char *)current + 0x48), current);
        } else if (candidate->rva006CFCD0()) {
            candidate = rva006F99D0(eventCode, candidate, 0);
        }
        if (!candidate)
            return;

        current->rva006E1F00(1);
        candidate->rva006E1F00(2);
        rva006FA100(current, 2);
        rva006FA100(candidate, 1);
        if (current)
            current->vtableSlot1();
        current = candidate;
        candidate->vtableSlot0();
        return;

    case 0:
        if (!current) {
            m70 = transition != 1;
            return;
        }

        if (!m70 && !transition) {
            m70 = 1;
            current->rva006E1F00(4);
            rva006FA100(current, 4);
        }
        if (!m70 || transition != 1)
            return;

        m70 = 0;
        if (*(int *)((char *)current->rva006E1090() + 0x18) == 2) {
            current->rva006E1F00(1);
            rva006FA100(current, 0x40);
            if (!current)
                return;
            current->rva006E1F00(2);
            if ((void *)mValue == *(void **)((char *)current + 0x48))
                rva006FA100(current, 8);
            else
                rva006FA100(current, 1);
            return;
        }
        current->rva006E1F00(2);
        rva006FA100(current, 8);
        return;
    }
}

// ?rva006FB860@AptAnimationPoolData@@QAEXHD@Z @0x006FB860 173B.
// The target uses thiscall with two stack arguments (ret 8). When the packed
// value is four-aligned it updates the global Apt coordinates at +0x74/+0x78;
// otherwise it extracts three bit fields. Both paths feed two direct helper
// calls, then a local AptCIH output slot passed to 0x006FACA0; a false result
// forwards that value and the extracted coordinates to 0x006FAF80.
void AptAnimationPoolData::rva006FB860(int value, char isFirst)
{
    void *candidate = 0;
    unsigned int packed = (unsigned int)value;
    int x;
    int y;
    int field;
    if ((packed & 3) == 0) {
        *(int *)((char *)g_bfmeAptPtrAtE176D0 + 0x74) = packed >> 17;
        unsigned int yValue = (packed >> 2) & 0x7FFF;
        x = 0xC8;
        y = 5;
        field = 1;
        *(int *)((char *)g_bfmeAptPtrAtE176D0 + 0x78) = yValue;
    } else {
        x = packed >> 17;
        y = (packed >> 10) & 0x7F;
        field = (packed >> 2) & 0xFF;
    }

    rva006FB120(x, y, value, field, isFirst);
    rva006FB5B0(x, y, value, field);
    if (!HandleFocusButton(x, y, &candidate))
        HandleAutoNav((AptCIH *)candidate, x, y);
}

typedef char PoolCountOffset[(sizeof(AptAnimationPoolData) >= 0x44 + sizeof(BfmeAptValue006DCD20)) ? 1 : -1];

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class EAStringC
{
public:
	EAStringC();
	~EAStringC();
	const char *rva00620090() const;
	unsigned int rva006D3750() const;
	EAStringC(const char *);
	void *data; // +0x00
};
class AptValue;
class AptInteger { public: static AptValue *Create(int); };
bool rva006EE6C0(AptValue *target, const EAStringC *name, AptValue *value);
#define APTINPUT_CHECK(c,s,l) if (!(c)) { g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",l); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }
// Retail FB5B0..FB840 ends in RET16 at FB83D (the queue omitted its three bytes).
// The 20-byte table at FB840 is also emitted and checked against retail. WB
// 17993B0/AptInput.cpp lines1032..1084 supplies the listener-dispatch guide;
// fields18/1A/1C and20/22/24, masks and ABIs are independently read in retail.
// The original member name is unproven, so retain the address-derived identity.
void AptAnimationPoolData::rva006FB5B0(int x, int y, int packed, int field)
{
    APTINPUT_CHECK(y==0 || y==1 || y==3 || y==4 || y==5,"eState == AptInputState_Pressed || eState == AptInputState_Released || eState == AptInputState_WheelUp || eState == AptInputState_WheelDown || eState == AptInputState_MouseMove",0x408);
    BfmeAptValue006DCD20 *value=0;
    int count=0;
    if (field==1 && ((x==0 && (y==0 || y==1)) || y==4 || y==3)) {
        count=0;
        for (int i=0; i<m22; ++i) {
            if (count==m20) break;
            if (!m24[i]) continue;
            value=m24[i];
            switch(y) {
            case 0:
                APTINPUT_CHECK(x==0,"eType == AptInputType_MouseButton0",0x41f);
                AddListenerToQueue(value,0x10,packed); break;
            case 1:
                APTINPUT_CHECK(x==0,"eType == AptInputType_MouseButton0",0x423);
                AddListenerToQueue(value,0x20,packed); break;
            case 3: case 4:
                if (static_cast<unsigned char>(value->isCIH(false)) && static_cast<unsigned char>(value->rva006DCF60(false)->rva006E02B0())) {
                    if (m68==value) {
                        int delta=x;
                        if (y==4) delta=-delta;
                        AptValue *aptValue=AptInteger::Create(delta);
                        EAStringC name("scroll");
                        value->rva006DCF60(false);
                        rva006EE6C0((AptValue *)value,&name,aptValue);
                    }
                } else AddListenerToQueue(value,0x80000,packed);
                break;
            default: APTINPUT_CHECK(false,"NOT_REACHED",0x43c); break;
            }
            ++count;
        }
    } else if (y==0 || y==1) {
        for (int i=0; i<m1a; ++i) {
            if (count==m18) break;
            if (!m1c[i]) continue;
            value=m1c[i];
            switch(y) {
            case 0: AddListenerToQueue(value,0x40,packed); break;
            case 1: AddListenerToQueue(value,0x80,packed); break;
            }
            ++count;
        }
    }
}

