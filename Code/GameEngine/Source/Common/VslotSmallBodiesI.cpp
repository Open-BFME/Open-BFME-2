// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch I: bodies around one call to an already rowed
// function. As in VslotSmallBodiesA-H, each class and method is
// address-derived unless the ledger already names it, and models only what
// its body touches; the comment above each gives the .rdata slot address(es)
// that reference it. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class AsciiString;

// slot at VA 0x00C6F100: when the argument differs from +0x3C, runs the rowed
// cdecl 0x0057A51C with (+0x08, &+0x0C, argument) and stores it at +0x3C.
struct Rva0057A51CTeam;
void Rva0057A51CSet(Int count, Rva0057A51CTeam **teams, Int value);
class Rva0057A83C
{
public:
	void rva0057A83C(Int value);
private:
	char m_pad00[0x08];
	Int m_08;
	Rva0057A51CTeam *m_0C;
	char m_pad10[0x3C - 0x10];
	Int m_3C;
};
void Rva0057A83C::rva0057A83C(Int value)
{
	if (value != m_3C)
	{
		Rva0057A51CSet(m_08, &m_0C, value);
		m_3C = value;
	}
}

// slots at VA 0x00C6DAD0 and 0x00C74B7C: hands +0x14..+0x20 to the rowed
// 0x00524A2D on the embedded +0x218 object, then its vslot 12; answers 1.
class Rva00524A2D
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07(); virtual void vslot08();
	virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12();
	void rva00524A2D(Int a, Int b, Int c, Int d);
};
class Rva005C9604
{
public:
	Int rva005C9604(Int unused);
private:
	char m_pad00[0x14];
	Int m_14;
	Int m_18;
	Int m_1C;
	Int m_20;
	char m_pad24[0x218 - 0x24];
	Rva00524A2D m_218;
};
Int Rva005C9604::rva005C9604(Int unused)
{
	Rva00524A2D *inner = &m_218;
	inner->rva00524A2D(m_14, m_18, m_1C, m_20);
	inner->vslot12();
	return 1;
}

// slot at VA 0x00C75804 (next to 0x005D24E5's): assigns the argument to the
// +0x0C reference of 0x1C-byte entry i (entries after a 0x1C-byte header)
// through the rowed TreeHintRef00217D4C::operator=.
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	void *m_ptr;
};
struct Rva005D264DEntry
{
	char m_pad00[0x0C];
	TreeHintRef00217D4C m_0C;
	char m_pad10[0x1C - 0x10];
};
class Rva005D264D
{
public:
	void rva005D264D(Int index, const TreeHintRef00217D4C &value);
private:
	char m_header[0x1C];
	Rva005D264DEntry m_entries[1];
};
void Rva005D264D::rva005D264D(Int index, const TreeHintRef00217D4C &value)
{
	m_entries[index].m_0C = value;
}

// slot at VA 0x00C76224: true unless the object is of kind 0xD6 (rowed
// Object::isKindOf).
enum KindOfType
{
	KINDOF_BFME_D6 = 0xD6
};
class Object
{
public:
	Bool isKindOf(KindOfType t) const;
};
class Rva005D8BFC
{
public:
	Bool rva005D8BFC(const Object *obj);
};
Bool Rva005D8BFC::rva005D8BFC(const Object *obj)
{
	if (obj->isKindOf(KINDOF_BFME_D6))
		return false;
	return true;
}
