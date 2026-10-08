// cl: /O1 /MD /arch:SSE
// ?Update@InGameHelpBoxMovieClip@@QAEXXZ @ 0x005279DD (270B): thiscall state switch calling Hide Show SampleContentWidth via rowed AptCall wrappers plus float Fire 0x00527925. Evidence: calls just-landed 0x00527925 plus rowed 0x005278DD 0x00524EF4 plus int-return twin 0x005CB260 row says void but retail uses int return pinned QAEHH; strings Show Hide SampleContentWidth; globals TheRva00222A8BTarget g_Rva0107301CEmptyString; neighbours Rva0052798FConcat Rva00527AEBWrapper.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class Rva00527890
{
public:
	void rva005278DD();
};

class Rva005CB260
{
public:
	int rva005CB260(int);
};

// Retail 0x005CB260 is rowed under the void spelling in
// Rva005CB260Forwarder.cpp (5B slot-1 forwarder: mov eax,[ecx]; jmp
// [eax+4], so the int result flows through the tail jump). Bind this
// TU's int-view spelling to that single definition.
#pragma comment(linker, "/alternatename:?rva005CB260@Rva005CB260@@QAEHH@Z=?rva005CB260@Rva005CB260@@QAEXXZ")

struct Rva005279DDInner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva00222A8BSlot40Ret
{
public:
	int m_00;
	float m_04;
};

class Rva00222A8BSlot40
{
public:
	virtual void _s00(); virtual void _s01(); virtual void _s02(); virtual void _s03();
	virtual void _s04(); virtual void _s05(); virtual void _s06(); virtual void _s07();
	virtual void _s08(); virtual void _s09(); virtual void _s10(); virtual void _s11();
	virtual void _s12(); virtual void _s13(); virtual void _s14(); virtual void _s15();
	virtual Rva00222A8BSlot40Ret *slot16();
};

class InGameHelpBoxMovieClip
{
public:
	void Update();
private:
	char m_pad00[4];
	void *m_level04;
	Rva005279DDInner *m_inner08;
	int m_state0C;
	int m_1010;
	int m_count14;
	int m_arg18;
	Rva005CB260 *m_obj1C;
};

void InGameHelpBoxMovieClip::Update()
{
	switch (m_state0C)
	{
	case 4:
		if (--m_count14 > 0)
			return;
		((Rva00527890 *)this)->rva005278DD();
		return;
	case 2:
	{
		if (m_obj1C == 0)
			return;
		int v = m_obj1C->rva005CB260(m_arg18);
		Rva00222A8BSlot40Ret *p = ((Rva00222A8BSlot40 *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->slot16();
		float f = (float)v * p->m_04;
		const char *s = m_inner08 ? m_inner08->m_name : "";
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, s, "Show", &f);
		m_state0C = 3;
		return;
	}
	case 1:
	{
		if (m_arg18 <= 0)
			return;
		const char *s = m_inner08 ? m_inner08->m_name : "";
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, s, "Hide");
		m_state0C = 2;
		return;
	}
	case 0:
	{
		const char *s = m_inner08 ? m_inner08->m_name : "";
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, s, "SampleContentWidth");
		m_arg18 = -1;
		m_state0C = 1;
		return;
	}
	default:
		return;
	}
}
