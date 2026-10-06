// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs
// ??1Rva005F2F80Elem@@QAE@XZ retail 0x005F2F80 111B
// Non-virtual dtor of a polymorphic element: own vptr C79290, empty body,
// member dtors in reverse order under EH states 4..0 -- UnicodeString +0x48
// (releaseBuffer 0x00036E70), the vector +0x24 (inline CRT free of its block),
// the holder +0x1C whose inline dtor runs the rowed
// ?clear@Rva000AD6F4@@QAEXXZ 0x000AD6F4, the vector wrapper +0x10 (rowed
// 0x0052413E) and AsciiString +0xC (releaseBuffer 0x00036410); then the
// base's inline dtor restores C6EE20. Names address-derived.
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" void __cdecl free(void *block);

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4()
	{
		clear();
	}
	void clear();
private:
	void *m_ptr;
};

class Rva005F2F80Vector
{
public:
	~Rva005F2F80Vector()
	{
		if (m_begin)
			free(m_begin);
	}

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class Rva005F2F80ElemBase
{
public:
	~Rva005F2F80ElemBase() {}
	virtual void Rva005F2F80ElemSlot0();
private:
	char m_pad04[8];
};

class Rva005F2F80Elem : public Rva005F2F80ElemBase
{
public:
	~Rva005F2F80Elem();

private:
	AsciiString m_0C;
	Rva0052413E m_10;
	Rva000AD6F4 m_1C;
	int m_20;
	Rva005F2F80Vector m_24;
	char m_pad30[0x48 - 0x30];
	UnicodeString m_48;
};

Rva005F2F80Elem::~Rva005F2F80Elem()
{
}
