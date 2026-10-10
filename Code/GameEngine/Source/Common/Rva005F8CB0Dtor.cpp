// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /DNDEBUG
#include "ascii_string.h"
class Image;
class Rva005E1158 { public: void rva005E1158(const Image *); };
// ??1Rva005F8CB0@@UAE@XZ retail 0x005F8CB0 79 bytes.
// Virtual dtor with two polymorphic bases and a copied record base. Evidence: EH_prolog with two
// vptr stores at +0/+8 then record base at +0x1c via rowed 0x005E8908 then base
// at +8 via pinned 0x005E12D1 then base store; caller 0x005F8DEA deleting
// dtor; base size 8 puts second base at +8 size 0x14 puts member at +0x1c.
class Rva005E8908
{
public:
	Rva005E8908(const Rva005E8908 &);
	~Rva005E8908();
	void *m_owner;
	int m_04;
	const Image *m_image;
private:
	char m_tail[0x10];
};

class Rva005E12D1
{
public:
	Rva005E12D1(void *, const AsciiString &, void *);
	virtual ~Rva005E12D1();
private:
	char m_pad[0x10];
};

// The +0 base has a root of its own: the constructor's inline base ctor
// installs 0x00C7A630 (Rva005F8CB0Base0's vftable, the same one the
// Rva005F5C77 constructors install) while the destructor's inline base dtors
// end on 0x00BC6F20 (the widely shared root vftable). Each intermediate vptr
// store is dead and dropped by cl, so the two bodies name different classes.
class Rva005F8CB0Root
{
public:
	virtual ~Rva005F8CB0Root() {}
};

class Rva005F8CB0Base0 : public Rva005F8CB0Root
{
public:
	Rva005F8CB0Base0() : m_04(0) {}
	virtual ~Rva005F8CB0Base0() {}
	int m_04;
};

class Rva005F8CB0 : public Rva005F8CB0Base0, public Rva005E12D1, public Rva005E8908
{
public:
	Rva005F8CB0(void *, const Rva005E8908 &);
	virtual ~Rva005F8CB0();
};

Rva005F8CB0::~Rva005F8CB0()
{
}

// Retail 005F8D5C..005F8DE7 (139B) identifies this as a constructor,
// not the earlier proposed ScriptList parser. The record copy occurs
// before final vptr installation, supporting a third base rather than the
// member originally inferred from the destructor alone. The base choice is
// reconstruction evidence, not a recovered original declaration. Image +24 is
// the record's +8 field, independently forwarded to the rowed image setter.
Rva005F8CB0::Rva005F8CB0(void *frame, const Rva005E8908 &value)
	: Rva005F8CB0Base0(),
	  Rva005E12D1(frame, AsciiString("button"), value.m_owner),
	  Rva005E8908(value)
{
	((Rva005E1158 *)static_cast<Rva005E12D1 *>(this))->rva005E1158(m_image);
}
