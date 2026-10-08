// cl: /MD /Ireference/shims/bfme2_ascii

#include "ascii_string.h"

class Rva005C46D9
{
public:
	Rva005C46D9(const Rva005C46D9 &source);
	virtual ~Rva005C46D9();

private:
	char m_fields[24];
};

// ?rva0052B5C6@@YGPAXPBX@Z @0x0052B5C6 55B
// Target evidence: allocates 0x1C bytes, skips construction on null, calls 0x005C46D9 with
// the stack argument, and returns the constructor result under an EH frame.
// Structural inference: model this as a stdcall address-derived factory for a 28B polymorphic
// copy-source type. The source object's full identity and layout remain unknown.
void *__stdcall rva0052B5C6(const void *source)
{
	return new Rva005C46D9(*(const Rva005C46D9 *)source);
}

class Rva004FA830
{
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &);

private:
	StringBase<char> m_s;
};

class Rva005C44A3 : public Rva004FA830
{
public:
	Rva005C44A3(const StringBase<char> &);

private:
	int m_08;
	int m_0c;
};

// ?rva0052B58F@@YGPAXPBX@Z @0x0052B58F 55B
// Target evidence: allocates 0x10 bytes, skips construction on null, calls
// 0x005C44A3 with the stack argument, returns constructor result under EH.
// Same 55B stdcall factory pattern as rva0052B5C6 above; VTABLE slot 1 at
// 0x008745A0 names no proven owner so honest address-derived stdcall is used.
void *__stdcall rva0052B58F(const void *source)
{
	return new Rva005C44A3(*(const StringBase<char> *)source);
}
