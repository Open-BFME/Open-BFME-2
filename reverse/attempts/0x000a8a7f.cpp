// ?rva000A8A7F@Rva000A8A7F@@QAEPAXPAX@Z
// partial score=0.9 date=2026-10-05
// BANKED 0xA8A7F attempt v2 (closest yet): BOOL dummy + explicit return p +
// __assume + /Oy- reproduces everything EXCEPT `push ecx; and [ebp-4],0`
// (dead dummy dropped without SEH pinning; volatile gives mov not and).
// Refuted: <new>+EHsc (SEH pollution), inline op-new (nullcheck), __assume
// variants, /Oy- (restores frame+call+mov-eax). Next: find clean-C++ dead
// store that survives DCE without SEH, or split-return insight.
// cl: /O1 /MD /DNDEBUG /Oy-
typedef int BOOL;
#define FALSE 0
inline void *__cdecl operator new(unsigned int, void *p) { return p; }
class Gen0002857E;
class Rva00690FF0Handle {
public:
	Rva00690FF0Handle(Gen0002857E *target);
};
class Rva000A8A7F {
public:
	void *rva000A8A7F(void *p);
private:
	Gen0002857E *m_0;
};
void *Rva000A8A7F::rva000A8A7F(void *p)
{
	BOOL unused = FALSE;
	(void)unused;
	__assume(p != 0);
	new (p) Rva00690FF0Handle(m_0);
	return p;
}
