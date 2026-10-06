// cl: /O1 /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
//
// ?rva0056AA54@@YG_NPAX0@Z @0x0056AA54 82B.
// Probe: construct a local Rva004E3184 with arg 0 via pinned 0x004E30D5,
// invoke the slot-0x10 virtual on the +0xC holder of the first argument
// with (second-arg, local), return (local.m_48 == 1), then tear down the
// local via rowed 0x004E3184. Sibling shape of other EH locals with
// explicit dtor calls. Honest address-derived name.
#include "ascii_string.h"

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	int m_x[3];
};

class Rva004E3184
{
public:
	Rva004E3184(void *arg);
	virtual ~Rva004E3184();

	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1c;
	char m_pad20[8];
	AsciiString m_28;
	AsciiString m_2c;
	AsciiString m_30;
	AsciiString m_34;
	RvaVecAscii m_vec38;
	char m_pad44[4];
public:
	int m_48;
	int m_4c;
private:
	AsciiString m_50;
	char m_54;
};

class Rva0056AA54Holder
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void rvaMethod(void *b, Rva004E3184 *local);
};

struct Rva0056AA54Arg
{
	char m_pad[0xC];
	Rva0056AA54Holder m_holder;
};

bool __stdcall rva0056AA54(void *a, void *b)
{
	Rva004E3184 local((void *)0);
	((Rva0056AA54Arg *)a)->m_holder.rvaMethod(b, &local);
	bool ok = (local.m_48 == 1);
	return ok;
}
