// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ??1Rva004F1B56@@UAE@XZ @ 0x004F1B56 54B evidence: dtor stores vtable 0x00C62E40 then destroys AsciiString at plus0x20 via releaseBuffer then restores base vtable 0x007BB554; EH prolog 0xB92CB5; caller 0x004F1D1F; same vtable as ctor 0x004F10E6 size 0x30
#include "ascii_string.h"

extern const void *const g_00BBB554[];

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = g_00BBB554;
}

class Rva004F1B56 : public Snapshot
{
public:
	virtual ~Rva004F1B56();

private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	unsigned char m_18;
	unsigned char m_19;
	unsigned char m_pad1A[2];
	int m_1C;
	AsciiString m_20;
	int m_24;
	unsigned char m_28;
	unsigned char m_29;
	unsigned char m_pad2A[2];
	int m_2C;
};

Rva004F1B56::~Rva004F1B56()
{
}
