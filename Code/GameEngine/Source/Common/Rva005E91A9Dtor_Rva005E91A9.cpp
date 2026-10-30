// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ob2 /EHsc /MD
// Split from Rva005E91A9Dtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
#include "ascii_string.h"
class Image;
class Rva005E12D1
{
public:
    Rva005E12D1(void *, const AsciiString &, void *);
    virtual ~Rva005E12D1();
private:
    char holderStorage[0x10];
};
class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
	virtual ~Rva005E1158();
private:
	int m_04; // +0x04
	void *m_08; // +0x08
};
class Rva005E16B9
{
public:
	const Image *GetImage();
	char m_pad00[0x8];
private:
	AsciiString m_8; // +0x08
};
class Rva005E16DA;
extern Rva005E16DA g_cancelArmyMoveButton;
class Rva005E91A9Base
{
public:
    __declspec(dllimport) __forceinline Rva005E91A9Base() : m_04(0) {}
    virtual ~Rva005E91A9Base() {}
protected:
    int m_04;
};
class Rva005F5C77Base0 : public Rva005E91A9Base
{
public:
    virtual ~Rva005F5C77Base0() {}
};
class Rva005E91A9 : public Rva005F5C77Base0, public Rva005E12D1
{
public:
    Rva005E91A9(unsigned int owner, void *record);
    virtual ~Rva005E91A9();
private:
    unsigned int m_state;
};
Rva005E91A9::Rva005E91A9(unsigned int owner, void *record)
    : Rva005E12D1((void *)owner, AsciiString("button"), *(void **)record)
{
    m_state = ((unsigned int *)record)[1];
    reinterpret_cast<Rva005E1158 *>(static_cast<Rva005E12D1 *>(this))->rva005E1158(((Rva005E16B9 *)&g_cancelArmyMoveButton)->GetImage());
}

