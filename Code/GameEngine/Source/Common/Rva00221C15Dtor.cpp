// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??1Rva00221C15@@QAE@XZ @0x00221C78 54B
// Dtor of Rva00221C15: second base Rva00221B42 at +8 via rowed 0x00221B0D plus
// base vtable restore to g_00BC6F20. Layout from rowed ctor 0x00221C15.
// Evidence: retail bytes and caller 0x00221C5C deleting shape.
#include "ascii_string.h"

class Rva0022185A
{
public:
	Rva0022185A(const Rva0022185A &other);
private:
	AsciiString m_str;
	int m_04;
	unsigned char m_08;
};

class Rva00221A58
{
public:
	Rva00221A58(const Rva00221A58 &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	Rva0022185A m_0C;
	int m_18;
};

class Rva00221B42
{
public:
	~Rva00221B42();
private:
	Rva00221A58 m_00;
	AsciiString m_1C;
};

extern const void *const g_00BC6F20[];

class Rva00221C15Empty
{
public:
	Rva00221C15Empty() {}
	~Rva00221C15Empty() {}
};

class Rva00221C15Base : public Rva00221C15Empty
{
public:
	~Rva00221C15Base() { *(const void **)&m_vtable = g_00BC6F20; }
protected:
	const void *m_vtable;
	int m_04;
};

class Rva00221C15 : public Rva00221C15Base, public Rva00221B42
{
public:
	~Rva00221C15();
};

Rva00221C15::~Rva00221C15()
{
}

// Native 005EB095..005EB0CB is the complete EH destructor. Its deleting
// wrapper 005EB079 and adjustor 005EB071 establish the opaque owner; the
// subobject at +8 directly calls the rowed 005FBBEE virtual destructor.
// Its cleanup view models only that call and the observed adjustment; the
// source inheritance and complete payload layout remain unproven.
class Rva005FBBEE
{
public:
    virtual ~Rva005FBBEE();
};

class Rva005EB095Payload
{
public:
    ~Rva005EB095Payload()
    {
        reinterpret_cast<Rva005FBBEE *>(this)->Rva005FBBEE::~Rva005FBBEE();
    }
private:
    const void *m_vtable;
};

class Rva005EB095 : public Rva00221C15Base, public Rva005EB095Payload
{
public:
    ~Rva005EB095();
};

Rva005EB095::~Rva005EB095()
{
}
