// ??0Rva005E87E0@@QAE@PAX0PAURva005CE172Context@@@Z
// partial score=0.85 date=2026-10-07
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// Native 5E87E0..5E8872: primary +0, vbptr +4, owned child +8,
// Rva0007DF07 virtual base +C and count +10. The final stack argument
// is MSVC's hidden most-derived flag, matching the recovered callers.
// Preserve the zeroing non-polymorphic base used by the existing exact
// Rva0007DF07 constructor at 7DF07, rather than a private member view.
struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};

class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
	Rva0007DF07() {}
	virtual ~Rva0007DF07() {}
};

class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
	Rva005CC5E5();
	virtual void slot0();
	virtual ~Rva005CC5E5();
};

struct Rva005CE172Context;
class Rva005E87E0;

// The allocation in this constructor proves size 34. Native 5E8350's
// constructor stores vptrs at +0/+8/+C, saves its owner argument at +10,
// consumes four pointer arguments with RET16, and returns this.
// Its unrecovered fields and interface names remain opaque here.
class Rva005E8350
{
public:
	Rva005E8350(Rva005E87E0 *, void *, void *, Rva005CE172Context *);
	virtual void slot0();
private:
	char unknown04[0x30];
};

class Rva005E87E0 : public Rva005CC5E5
{
public:
	Rva005E87E0(void *, void *, Rva005CE172Context *);
	virtual ~Rva005E87E0();
private:
	Rva005E8350 *payload;
};

Rva005E87E0::Rva005E87E0(void *a, void *b, Rva005CE172Context *c)
	: payload(new Rva005E8350(this, a, b, c))
{
}
