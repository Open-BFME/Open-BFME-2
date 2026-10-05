// cl: /O1 /MD
// Three tiny range-27 forwarders (24-30B).
// ?rva0052A22C@Holder0052A22C@@QAEXPAVObj0052A22C@@@Z @0x0052A22C 24B
// Thiscall through-call: forwards o->m_74 (or 0) to the pinned 0x529DA9
// on the same this.
// ?Rva0052B225@@YAHPAVObj0052B225@@@Z @0x0052B225 24B
// Cdecl getter: helper 0x52B1EF maps the arg to a record; answers its
// +0xBC int or 0.
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

struct Rec0052B225
{
	char m_pad[0xBC];
	int m_BC;
};

struct Obj0052B225
{
	char m_pad[4];
};

Rec0052B225 *Rva0052B1EF(Obj0052B225 *obj);

int Rva0052B225(Obj0052B225 *obj)
{
	Rec0052B225 *rec = Rva0052B1EF(obj);
	return rec ? rec->m_BC : 0;
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

void __stdcall Rva005258F8(int a, int b)
{
	Pair005258F8 pair;
	pair.m_0 = a;
	pair.m_4 = b;
	Rva00525407(&pair);
}
