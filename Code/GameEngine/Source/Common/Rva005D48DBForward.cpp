// cl: /MD
// ?rva005D48DB@Rva005D48DB@@QAEXPAX@Z, RVA 0x005D48DB, 21B. Unlock lane forwarder:
// this holds member-fn ptr at +0 plus int at +4 and float at +8; invokes it with
// ecx = stack arg and the two members as stack args. Evidence: retail mov eax,ecx;
// fld [eax+8]; push ecx; mov ecx,[esp+8]; fstp [esp]; push [eax+4]; call [eax]; ret 4.
// Single-deref call [eax] so +0 is fn ptr not vtable. Follows Rva002B2FCBInvoke.cpp
// precedent (member-fn-ptr at +0 with ecx = elem). Caller 0x005D4A66 passes array
// element as stack arg which becomes new this.
class Rva005D48DBElem
{
public:
	void Method(int a, float b);
};
typedef void (Rva005D48DBElem::*Rva005D48DBFn)(int, float);
class Rva005D48DB
{
public:
	void rva005D48DB(void *elem);
private:
	Rva005D48DBFn m_fn;
	int m_4;
	float m_8;
};
void Rva005D48DB::rva005D48DB(void *elem)
{
	Rva005D48DBElem *e = (Rva005D48DBElem *)elem;
	(e->*m_fn)(m_4, m_8);
}
