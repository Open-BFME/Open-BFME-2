// ?rva005B89A1@Rva005B8EBB@@QAEXXZ
// partial score=0.942 date=2026-10-09
// cl: /O1 /GR- /EHsc- /G6 /arch:SSE
// ?Run@Rva005B8EBB@@QAEXXZ @0x005B8EBB 73B: dispatch + tail.
// Calls the +0x60 sub-object helper (rowed 0x5DE96B) and the +0x58 object
// helper (pinned 0x517F31), switches m_8C 0/1/2 to the pinned trio
// (0x5B8D1C/0x5B89A1/0x5B8A40), then tailcalls the pinned 0x5DD48C on the
// +0x60 sub-object. Targets from retail REL32; names unknown.
class Rva005DE96B
{
public:
	void rva005DE96B();
};

struct Rva005B8EBB
{
	char pad[0x58];
	void *m_58;
	char pad2[0x60 - 0x58 - 4];
	char m_60[0x8C - 0x60];
	int m_8C;

	void rva00517F31();
	void rva005B8D1C();
	void rva005B89A1();
	void rva005B8A40();
	void rva005DD48C();

	void rva005B87ED(void *, unsigned *);
	void Run();
};

void Rva005B8EBB::Run()
{
	((Rva005DE96B *)((char *)this + 0x60))->rva005DE96B();
	((Rva005B8EBB *)m_58)->rva00517F31();
	switch (m_8C) {
	case 0:
		rva005B8D1C();
		break;
	case 1:
		rva005B89A1();
		break;
	case 2:
		rva005B8A40();
		break;
	}
	((Rva005B8EBB *)((char *)this + 0x60))->rva005DD48C();
}

// ABI-only returned-record views. Sizes independently proved in the
// PersistentStorageThread provider; names retained from its owned types.
class Rva003844D7 { unsigned storage[0x190/4]; public: Rva003844D7(const Rva003844D7 &); ~Rva003844D7(); };
class Rva00385333 { unsigned storage[0x1A8/4]; public: Rva00385333(const Rva00385333 &); ~Rva00385333(); };
class PSPlayerAllStats { unsigned storage[0x548/4]; public:
    PSPlayerAllStats(const PSPlayerAllStats &);
    ~PSPlayerAllStats();
    Rva003844D7 rva00389DF1() const;
    Rva00385333 rva00556508() const;
};
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
struct Rva005B89A1InfoView {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();

    virtual PSPlayerAllStats stats();
};
namespace GameStats { class Persistent { public: void CalculateTotalColumn(float); }; }
void Rva005B8EBB::rva005B89A1() {
    PSPlayerAllStats all=((Rva005B89A1InfoView *)TheGameSpyInfo)->stats();
    Rva003844D7 stats=all.rva00389DF1();
    unsigned total=0;
    rva005B87ED(&stats,&total);
    ((GameStats::Persistent *)m_60)->CalculateTotalColumn((float)total);
}
void Rva005B8EBB::rva005B8D1C() {
    PSPlayerAllStats all=((Rva005B89A1InfoView *)TheGameSpyInfo)->stats();
    Rva00385333 stats=all.rva00556508();
    unsigned total=0;
    rva005B87ED(&stats,&total);
    ((GameStats::Persistent *)m_60)->CalculateTotalColumn((float)total);
}
