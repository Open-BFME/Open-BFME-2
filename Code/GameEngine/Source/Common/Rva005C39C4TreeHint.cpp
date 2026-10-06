// cl: /MD
// ?rva005C39C4@Rva005C39C4@@QAE?AUTreeHintRef00217D4C@@H@Z @0x005C39C4 26B: TreeHintRef forwarder to virtual slot 2.
// Retail: push ebp / mov ebp esp / push ecx / push [ebp+0xC] / mov eax,[ecx] / push [ebp+8] / and [ebp-4],0 / call [eax+8] / mov eax,[ebp+8] / leave / ret 8.
// Target facts: hidden-pointer struct return (TreeHintRef 4B with user copy/dtor forces hidden plus RVO guard and [ebp-4],0); virtual at +8 is slot 2.
// Callers pass TreeHintRef temp as hidden plus int and assign via rowed ??4TreeHintRef00217D4C at 0x002174A4 then Release at 0x0007DEEF:
// 0x005C3BB9 (lea [ebp-0x14] plus edx) 0x005D2A87 (lea [ebp-0x18] plus [esi]) 0x005F84BF (lea [ebp+8] plus [ebp+0xC]).
// Unblocks 0x005C3B3E 0x005D2A53 0x005F8484. Precedent Rva000F5D1BGet.cpp (/O1 /MD hidden plus guard plus leave plus ret).
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C();
};
class Rva005C39C4
{
public:
	virtual void m_unknown01();
	virtual void m_unknown02();
	virtual TreeHintRef00217D4C m_unknown03(int x);
	TreeHintRef00217D4C rva005C39C4(int x);
};
TreeHintRef00217D4C Rva005C39C4::rva005C39C4(int x)
{
	return m_unknown03(x);
}
