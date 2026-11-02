// cl: /MD
// Three tiny range-27 forwarders (24-30B).
// ?rva0052A22C@Holder0052A22C@@QAEXPAVObj0052A22C@@@Z @0x0052A22C 24B
// Thiscall through-call: forwards o->m_74 (or 0) to rowed 0x529DA9 on the
// same this. 0x529DA9 is Holder00529E19::Rva00529DA9 (Rva00529E19Reset.cpp,
// called on the same holder by reset 0x529E19), so the call goes through
// that class's view of this.
struct Obj0052A22C
{
	char m_pad[0x74];
	int m_id;
};

struct Holder00529E19
{
	void Rva00529DA9(int value);
	void Rva00529E19();
};

struct Holder0052A22C
{
	void rva0052A22C(Obj0052A22C *obj);
};

void Holder0052A22C::rva0052A22C(Obj0052A22C *obj)
{
	((Holder00529E19 *)this)->Rva00529DA9(obj ? obj->m_id : 0);
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


// ?find@@YAHHHH@Z @0x005243FA 27B
// Cdecl forwarder: passes three pointers plus the address of a temp tag byte
// to rowed find 0x52408B (Rva0052408BFind, stlport_hero_integer_vector_tree.cpp)
// and returns its EAX result, which range dispatch 0x524477 reads
// (Rva00524477Dispatch.cpp declares this int-returning spelling).
struct Rva00523DB7;
const Rva00523DB7 *Rva0052408BFind(const Rva00523DB7 *first, const Rva00523DB7 *last, const Rva00523DB7 *val, int tag);

int find(int first, int last, int searchValue)
{
	char tag;
	return (int)Rva0052408BFind((const Rva00523DB7 *)first, (const Rva00523DB7 *)last, (const Rva00523DB7 *)searchValue, (int)&tag);
}

// ?setObject@Rva0052A287@@QAEXPAUObj0052A22C@@@Z @0x0052A287 7B
// Tail-forwarding wrapper holding Holder0052A22C* at +0: loads it and jmps
// to rowed 0x0052A22C with the incoming Obj* arg preserved on the stack.
// Evidence: unlock lane all callees rowed; caller at 0x002D3651 in 0x002D363E
// passes its incoming 4B arg through; neighbours share /O1 /MD.
struct Rva0052A287
{
	Holder0052A22C *m_holder;
	void setObject(Obj0052A22C *obj);
};

void Rva0052A287::setObject(Obj0052A22C *obj)
{
	m_holder->rva0052A22C(obj);
}

// ?rva00529FB7@Rva00529FB7@@QAEXXZ @0x00529FB7 7B
// Tail-forwarding wrapper holding Holder00529E19* at +0: loads it and jmps
// to rowed 0x00529E19 with no args.
// Evidence: unlock lane all callees rowed; caller at 0x002D66B1 in 0x002D65F6;
// neighbours share /MD; same 7B pattern as rva0052A287 above.
struct Rva00529FB7
{
	Holder00529E19 *m_holder;
	void rva00529FB7();
};

void Rva00529FB7::rva00529FB7()
{
	m_holder->Rva00529E19();
}
