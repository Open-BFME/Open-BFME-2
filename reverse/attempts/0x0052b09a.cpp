// ?rva0052B09A@Rva005392C2@@QAE?AURva002BED91@@XZ
// partial score=0.94 date=2026-10-07
// cl: /O1
// ?rva0052B045@Rva005392C2@@QAEXXZ, RVA 0x0052B045 size 85.
// Leaf lane: called by 3 matched rows showing the call shape.
// Evidence: pin Rva005392C2; Helper pin 0x0056BB8C returning RvaF6Ret;
// TreeHint op= row 0x002174A4; Release row 0x0007DEEF; clear row 0x002BED91;
// callers at 0x004E06EA 0x0052B0ED 0x0052B39A; neighbours share /O1.
// The helper's by-value result is a temporary whose inline destructor
// releases a non-null reference (0x0007DEEF), which is the retail tail
// after the assignment (EH state -1, test ecx, call).
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
class Rva002E0BC0Helper
{
public:
	unsigned char rva002E0BC0(int id);
};
struct Rva0059E647World;
extern Rva0059E647World *g_rva0059E647World;
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
void Rva005392C2::rva0052B045()
{
	if (m_38 != 0)
		*(TreeHintRef00217D4C *)&m_40 = Helper0056BB8C(m_38);
	else
		m_40.clear();
}

// Target facts: 0x0052B09A is a 108-byte thiscall body with one hidden
// return-storage pointer. It reads +0x38, conditionally calls 0x004E06FB,
// 0x002E0BC0 and 0x0052B045, then copies +0x40 into that return storage.
// Structural inference: the returned 4-byte holder shares the +0x40 layout;
// copying it retains the referenced object. Field meaning remains unknown.
// ?rva0052B09A@Rva005392C2@@QAE?AURva002BED91@@XZ present-unmatched
Rva002BED91 Rva005392C2::rva0052B09A()
{
	Rva0052B09AStackState rva0052B09AStackSlot;
	if (m_38 != 0) {
		int value = ((Rva004E06FBPtrChase32Field *)m_38)->get();
		Rva002E0BC0Helper *lookup = *(Rva002E0BC0Helper **)((char *)g_rva0059E647World + 0x98);
		unsigned char found = lookup->rva002E0BC0(value);
		if (!found && *(int *)((char *)m_38 + 0x20) == -1)
			return Rva002BED91();
		if (*(int *)((char *)g_rva0059E647World + 0xF4) != 0 || found)
			rva0052B045();
	}
	return m_40;
}
