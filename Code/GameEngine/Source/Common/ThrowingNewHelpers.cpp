// cl: /MD /EHsc /DNDEBUG
//
// Wave-3 F78 shape family: throwing-new plus final. Each body allocates its
// POD helper with operator new, constructs it in place with (member, arg)
// (the null-checked call some shapes mistake for a cond call), then passes
// the helper (or null when allocation failed) to a thiscall final on the
// member's +0x1C subobject. The throwing new plus the in-place ctor is what
// requires the EH prologue and its 0/-1 state transitions. Callees pinned
// under their addresses; identities unproven.
//

struct Rva005CF22CBig;

class Rva00575674Sub
{
public:
	void rva00575674(void *h);
};

struct Rva005CF22CBig
{
	char m_pad[0x10];
	void *m_view10;
	char m_pad14[8];
	Rva00575674Sub m_sub;
};

class Rva005CF07EHelper
{
public:
	Rva005CF07EHelper(Rva005CF22CBig *b, int x);
	unsigned char m_data[0x14];
};

class Rva005CF22COwner
{
public:
	void rva005CF22C(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF22COwner::rva005CF22C(int x)
{
	Rva005CF07EHelper *h = new Rva005CF07EHelper(m_a, x);
	m_a->m_sub.rva00575674(h);
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva005773DB {
public:
    Rva005773DB(const int *);
    ~Rva005773DB() { if (m_impl) ReleaseTreeHintRef00217D4C(m_impl); }
private:
    TargetRef00217D4C *m_impl;
};
class Rva005CEA74 {
public:
    struct Payload { int v[2]; };
};
template <class T> class RvaCloneResult {
    TargetRef00217D4C *pointer;
public:
    ~RvaCloneResult() { if (pointer) ReleaseTreeHintRef00217D4C(pointer); }
};
RvaCloneResult<Rva005CEA74> Rva005CEC5DCreate(const Rva005CEA74::Payload *);
class Image;
struct Rva005D2355In;
const Image *Rva005D2355Get(Rva005D2355In *);
int GetMaxCommandPoints(void *);
class Rva00318FBE { public: int rva00318FBE(); };
class Rva00319B0AOwner { public: void rva00319B0A(); };
class Rva0042D703PtrChaseField { public: int get() const; };
class Rva0042D69DPtrChaseField { public: int get() const; };
class Rva0042D6B4PtrChaseField { public: int get() const; };
struct Rva005CF37DPortrait {
    virtual void slot0();
    virtual void setImage(const Image *);
    virtual void slot2();
    virtual void setCounts(int current, int maximum);
    virtual void slot4();
    virtual void slot5();
    virtual void setArmy(const Rva005773DB &);
    virtual void slot7();
    virtual void refresh();
};
struct Rva005CF37DCommandUI {
    virtual void slot0();
    virtual void createButton(int slot, const RvaCloneResult<Rva005CEA74> &);
};
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
class Rva005CF37DBase0 {
public:
    Rva005CF37DBase0(Rva005CF22CBig *b) : m_owner(b) {}
    virtual ~Rva005CF37DBase0() {}
    Rva005CF22CBig *m_owner;
};
// Existing one-vptr observer-base view: its emitted vtable is retail C3702C.
class Rva00575E4EBase2 {
public:
    Rva00575E4EBase2() {}
    virtual ~Rva00575E4EBase2() {}
};
class Rva005CF37DHelper : public Rva005CF37DBase0, public Rva00575E4EBase2
{
public:
    Rva005CF37DHelper(Rva005CF22CBig *b, int x);
    virtual ~Rva005CF37DHelper();
private:
    int m_army;
};

// Native boundary 5CF37D..5CF4A8, RET8. Existing allocating caller5CF6B5
// proves this constructor and its16B allocation. Primary/secondary vptrs at
// +0/+8; owner+4 and army+0C; WB is an unnamed StrategicInGameUI lead.
Rva005CF37DHelper::Rva005CF37DHelper(Rva005CF22CBig *b, int x)
    : Rva005CF37DBase0(b), m_army(x)
{
    ((Rva00319B0AOwner *)m_army)->rva00319B0A();
    void *view = m_owner->m_view10;
    Rva005CF37DPortrait *portrait = (Rva005CF37DPortrait *)
        ((Rva0042D703PtrChaseField *)view)->get();
    if (portrait) {
        portrait->setImage(Rva005D2355Get((Rva005D2355In *)m_army));
        { int army = m_army; Rva005773DB ref(&army); portrait->setArmy(ref); }
        portrait->setCounts(((Rva00318FBE *)m_army)->rva00318FBE(),
                            GetMaxCommandPoints((void *)m_army));
        portrait->refresh();
    }
    Rva005CF37DCommandUI *commands = (Rva005CF37DCommandUI *)
        ((Rva0042D69DPtrChaseField *)view)->get();
    if (commands) {
        int button = ((Rva0042D6B4PtrChaseField *)view)->get();
        if (button) {
            int army = m_army;
            Rva005CEA74::Payload payload = { button, army };
            commands->createButton(1, Rva005CEC5DCreate(&payload));
        }
    }
    ((Rva005A0B4CList *)((char *)m_army + 8))->append(
        (Rva002BA8F1Listener *)static_cast<Rva00575E4EBase2 *>(this));
}

class Rva005CF6B5Owner
{
public:
	void rva005CF6B5(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF6B5Owner::rva005CF6B5(int x)
{
	Rva005CF37DHelper *h = new Rva005CF37DHelper(m_a, x);
	m_a->m_sub.rva00575674(h);
}

class Rva005CF4A8Helper
{
public:
	Rva005CF4A8Helper(Rva005CF22CBig *b, int x);
	unsigned char m_data[0x14];
};

class Rva005CF703Owner
{
public:
	void rva005CF703(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF703Owner::rva005CF703(int x)
{
	Rva005CF4A8Helper *h = new Rva005CF4A8Helper(m_a, x);
	m_a->m_sub.rva00575674(h);
}
