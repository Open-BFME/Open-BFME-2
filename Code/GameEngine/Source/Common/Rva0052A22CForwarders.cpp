// cl: /MD
// Three tiny range-27 forwarders (24-30B).
// ?rva0052A22C@Holder0052A22C@@QAEXPAVObj0052A22C@@@Z @0x0052A22C 24B
// Thiscall through-call: forwards o->m_74 (or 0) to the pinned 0x529DA9
// on the same this.
struct Obj0052A22C
{
	char m_pad[0x74];
	int m_74;
};

struct Holder0052A22C
{
	void rva00529DA9(int value);
	void rva0052A22C(Obj0052A22C *obj);
};

void Holder0052A22C::rva0052A22C(Obj0052A22C *obj)
{
	rva00529DA9(obj ? obj->m_74 : 0);
}

// ?Rva005258F8@@YGXHH@Z @0x005258F8 30B
// Stack-pair forwarder: packs two ints into an 8-byte struct and passes
// it to pinned 0x00525407.
struct Pair005258F8
{
	int m_0;
	int m_4;
};

void __stdcall Rva00525407(Pair005258F8 *pair);


// ?Rva005243FA@@YAXHHH@Z @0x005243FA 27B
// Cdecl forwarder: passes three ints plus a temp byte to pinned 0x52408B.
void Rva0052408B(int a, int b, int c, char *tmp);

void Rva005243FA(int a, int b, int c)
{
	char tmp;
	Rva0052408B(a, b, c, &tmp);
}

// ?rva0052A287@Rva0052A287@@QAEXPAUObj0052A22C@@@Z @0x0052A287 7B
// Tail-forwarding wrapper holding Holder0052A22C* at +0: loads it and jmps
// to rowed 0x0052A22C with the incoming Obj* arg preserved on the stack.
// Evidence: unlock lane all callees rowed; caller at 0x002D3651 in 0x002D363E
// passes its incoming 4B arg through; neighbours share /O1 /MD.
struct Rva0052A287
{
	Holder0052A22C *m_holder;
	void rva0052A287(Obj0052A22C *obj);
};

void Rva0052A287::rva0052A287(Obj0052A22C *obj)
{
	m_holder->rva0052A22C(obj);
}
