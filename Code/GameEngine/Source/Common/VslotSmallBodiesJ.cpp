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

// slots 2 and 4 of Rva00104DB0's vtable at VA 0x00BCF800: the first adds the extents of the rectangle given by
// its four arguments to +0xC8/+0xCC, the second sets the embedded +0x04
// sentence's font from the argument's +0x14 (rowed
// Render2DSentenceClass::Set_Font); both raise the +0xD5/+0xD4 dirty bytes.
class FontCharsClass;
#include "../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"
struct Rva00104DE6Font
{
	char m_pad00[0x14];
	FontCharsClass *m_font;
};
class GameWindow;
struct Rva0010500FDrawData;
struct BfmeR1042;
// Retail table 0x00BCF7E8: five __purecall slots, then the deleting destructor.
class Rva00104DB0Base
{
public:
	Rva00104DB0Base() {}
	virtual void drawBorder(GameWindow *window) = 0;
	virtual void rva0010500F(GameWindow *window, Rva0010500FDrawData *data) = 0;
	virtual void addExtents(int left, int top, int right, int bottom) = 0;
	virtual void bfmeGo1042E(BfmeR1042 *rec) = 0;
	virtual void setFont(const Rva00104DE6Font *font) = 0;
	virtual ~Rva00104DB0Base() {}
};
// Retail table 0x00BCF800 (six slots); see Rva00104DB0Dtor.cpp.
class Rva00104DB0 : public Rva00104DB0Base
{
public:
	Rva00104DB0();
	virtual void drawBorder(GameWindow *window);
	virtual void rva0010500F(GameWindow *window, Rva0010500FDrawData *data);
	virtual void addExtents(int left, int top, int right, int bottom);
	virtual void bfmeGo1042E(BfmeR1042 *rec);
	virtual void setFont(const Rva00104DE6Font *font);
	virtual ~Rva00104DB0();
private:
	Render2DSentenceClass m_sentence;
	Int m_width;
	Int m_CC;
	char m_padD0[0xD4 - 0xD0];
	Bool m_fontDirty;
	Bool m_extentsDirty;
};
void Rva00104DB0::addExtents(Int left, Int top, Int right, Int bottom)
{
	m_extentsDirty = true;
	m_width += right - left;
	m_CC += bottom - top;
}
void Rva00104DB0::setFont(const Rva00104DE6Font *font)
{
	m_sentence.Set_Font(font->m_font);
	m_fontDirty = true;
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
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
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
		if (((Rva00080637Object *)it->m_ptr)->m_40 == id)
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
		if (((Rva00080637Object *)it->m_ptr)->m_40 == id)
		{
			m_4C.rva004F70D1(it);
			return;
		}
	}
}

// Installed-table buffer copies. Native x87 accesses establish the first
// float; other fields are opaque raw32-bit words. Original owner, field
// meanings and source-level return convention remain unknown. These views
// model the observed stack buffer, writes and EAX buffer pointer only.
struct Rva005C3513Buffer {float first; unsigned int second;};
class Rva005C3513 {public: void *rva005C3513(Rva005C3513Buffer *output); private: char prefix[0x14]; float first; unsigned int second;};
void *Rva005C3513::rva005C3513(Rva005C3513Buffer *output) {unsigned int word=second; output->first=first; output->second=word; return output;}
