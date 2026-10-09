// cl: /O1 /MD /Oy-
// Native50B5CEC8F..5CECC1: a counted callback handle returned by value.
// The caller5CF5DA supplies a hidden output and payload, then passes the
// returned address to its callback slot and releases the held pointer.
// The payload constructor5CEAE6 independently fixes the20B allocation,
// refcount4 and three-word payload8. Names and semantic roles remain
// address-derived. A nontrivial handle with a memberwise copy constructor
// gives MSVC NRV; its natural construction flag emits the native AND of
// the4B stack slot. This replaces the earlier explicit-out-pointer ABI and
// its inline asm state store; full50B match needs no asm.
class Rva005CEAE6
{
public:
	struct Payload { int v[3]; };
	Rva005CEAE6(const Payload *src) throw();
	virtual ~Rva005CEAE6() throw() {}
	int m_ref; // +4
	Payload m_data; // +8
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva005CEC8F
{
public:
 __forceinline Rva005CEC8F(Rva005CEAE6 *p):m_00(p){if(p)++p->m_ref;}
 __forceinline Rva005CEC8F(const Rva005CEC8F&x):m_00(x.m_00){if(m_00)++m_00->m_ref;}
 ~Rva005CEC8F() {if(m_00)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_00);}
	Rva005CEAE6 *m_00;
};

Rva005CEC8F __cdecl Rva005CEC8FCreate(const Rva005CEAE6::Payload *src){
 return Rva005CEC8F(new Rva005CEAE6(src));
}
