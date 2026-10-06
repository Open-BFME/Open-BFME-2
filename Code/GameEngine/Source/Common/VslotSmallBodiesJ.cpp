// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch J. As in VslotSmallBodiesA-I, each class and method
// is address-derived unless the ledger already names it, and models only what
// its body touches; the comment above each gives the .rdata slot address(es)
// that reference it. Meanings are not recovered.

typedef int Int;
typedef bool Bool;

// slot at VA 0x00BCEEA8: raises five flag bytes deep inside the object.
class Rva000EAF80
{
public:
	void rva000EAF80();
private:
	char m_pad00[0x44544];
	Bool m_44544;
	Bool m_44545;
	char m_pad44546[0x44556 - 0x44546];
	Bool m_44556;
	char m_pad44557[0x45C5C - 0x44557];
	Bool m_45C5C;
	char m_pad45C5D[0x45C64 - 0x45C5D];
	Bool m_45C64;
};
void Rva000EAF80::rva000EAF80()
{
	m_44556 = true;
	m_45C5C = true;
	m_44544 = true;
	m_45C64 = true;
	m_44545 = true;
}

// slots 3 and 5 of the vtable at VA 0x00BCF7FC (slot 0 is the rowed
// ??_GRva00104DB0Base): the first adds the extents of the rectangle given by
// its four arguments to +0xC8/+0xCC, the second sets the embedded +0x04
// sentence's font from the argument's +0x14 (rowed
// Render2DSentenceClass::Set_Font); both raise the +0xD5/+0xD4 dirty bytes.
class FontCharsClass;
class Render2DSentenceClass
{
public:
	void Set_Font(FontCharsClass *font);
};
struct Rva00104DE6Font
{
	char m_pad00[0x14];
	FontCharsClass *m_14;
};
class Rva00104DE6
{
public:
	void rva00104E68(Int left, Int top, Int right, Int bottom);
	void rva00104DE6(const Rva00104DE6Font *font);
private:
	char m_pad00[0x04];
	Render2DSentenceClass m_04;
	char m_pad05[0xC8 - 0x05];
	Int m_C8;
	Int m_CC;
	char m_padD0[0xD4 - 0xD0];
	Bool m_D4;
	Bool m_D5;
};
void Rva00104DE6::rva00104E68(Int left, Int top, Int right, Int bottom)
{
	m_D5 = true;
	m_C8 += right - left;
	m_CC += bottom - top;
}
void Rva00104DE6::rva00104DE6(const Rva00104DE6Font *font)
{
	m_04.Set_Font(font->m_14);
	m_D4 = true;
}

// slots at VA 0x00BC70FC and 0x00BC70EC: erase from the pointer vector at
// +0x40 (resp. +0x4C) the first element whose object has +0x40 equal to the
// second argument, through the rowed vector erase 0x004F70D1; the first
// argument is unused.
struct Rva00080637Object
{
	char m_pad00[0x40];
	Int m_40;
};
struct TreeHintRef00217D4C
{
	Rva00080637Object *m_object;
};
class Rva004F70D1
{
public:
	TreeHintRef00217D4C *rva004F70D1(TreeHintRef00217D4C *position);
	TreeHintRef00217D4C *m_begin;
	TreeHintRef00217D4C *m_end;
};
class Rva00080637
{
public:
	void rva00080637(Int unused, Int id);
	void rva00080664(Int unused, Int id);
private:
	char m_pad00[0x40];
	Rva004F70D1 m_40;
	char m_pad48[0x4C - 0x48];
	Rva004F70D1 m_4C;
};
void Rva00080637::rva00080637(Int unused, Int id)
{
	for (TreeHintRef00217D4C *it = m_40.m_begin; it != m_40.m_end; ++it)
	{
		if (it->m_object->m_40 == id)
		{
			m_40.rva004F70D1(it);
			return;
		}
	}
}
void Rva00080637::rva00080664(Int unused, Int id)
{
	for (TreeHintRef00217D4C *it = m_4C.m_begin; it != m_4C.m_end; ++it)
	{
		if (it->m_object->m_40 == id)
		{
			m_4C.rva004F70D1(it);
			return;
		}
	}
}
