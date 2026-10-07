// ?rva0052B09A@Rva005392C2@@QAE?AURva002BED91@@XZ
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy-
// ?rva0052B09A@Rva005392C2@@QAE?AURva002BED91@@XZ, retail 0x0052B09A (108B).
// Finish from reverse/attempts/0x0052b09a.cpp (score 0.94). Same-this call to
// rowed 0x0052B045 supports Rva005392C2; slot 12 of 0x008685E0. Row 0x002E0BC0
// types wrong per use (row H int return used as byte via test al): declare row
// name Rva002E071E QAEHH and keep uchar local without unrelated cast.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
struct RvaF6Ret
{
	~RvaF6Ret()
	{
		if (m_ptr != 0)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	operator const TreeHintRef00217D4C &() const { return *(const TreeHintRef00217D4C *)this; }
	TargetRef00217D4C *m_ptr;
};
struct RvaF6Ret __cdecl Helper0056BB8C(int value);
struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	void clear();
	Rva002BED91() : m_ptr(0) {}
	Rva002BED91(const Rva002BED91 &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr != 0)
			++m_ptr->references;
	}
};
class Rva004E06FBPtrChase32Field
{
public:
	int get() const;
};
class Rva002E071E
{
public:
	int rva002E0BC0(int id);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva0052B09AStackState
{
	int value;
	Rva0052B09AStackState() : value(0) {}
	~Rva0052B09AStackState() {}
};
class Rva005392C2
{
public:
	void rva0052B045();
	Rva002BED91 rva0052B09A();
private:
	char m_pad[0x38];
	int m_38;
	char m_pad3C[0x40 - 0x3C];
	Rva002BED91 m_40;
};

Rva002BED91 Rva005392C2::rva0052B09A()
{
	Rva0052B09AStackState rva0052B09AStackSlot;
	if (m_38 != 0) {
		int value = ((Rva004E06FBPtrChase32Field *)m_38)->get();
		Rva002E071E *lookup = *(Rva002E071E **)((char *)TheLivingWorldLogic + 0x98);
		unsigned char found = lookup->rva002E0BC0(value);
		if (!found && *(int *)((char *)m_38 + 0x20) == -1)
			return Rva002BED91();
		if (*(int *)((char *)TheLivingWorldLogic + 0xF4) != 0 || found)
			rva0052B045();
	}
	return m_40;
}
