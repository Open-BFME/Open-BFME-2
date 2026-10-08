// cl: /O1 /arch:SSE /G7 /Oy- /MD
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
	__forceinline Rva002BED91(const Rva002BED91 &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr) ++m_ptr->references;
	}
	~Rva002BED91()
	{
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva004E06FBPtrChase32Field { public: int get() const; };
class Rva002E071E { public: int rva002E0BC0(int id); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

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

// Target 0x0052B09A..0x0052B106, 108B RET4: conditional refresh and retained
// copy of +0x40. Same receiver as the adjacent verified refresh method.
// The returned one-pointer reference owns cleanup at 0x0007DEEF. Its
// nontrivial destructor and inline retain-copy reproduce the hidden result
// construction bookkeeping; no dummy stack object is needed.
// WorldBuilder 0x010DB5B0 supports the reference return and field layout;
// retail additionally rejects a missing id when parent+0x20 is -1.
Rva002BED91 Rva005392C2::rva0052B09A()
{

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
