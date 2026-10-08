// cl: /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
// ??1Rva0039AD56@@UAE@XZ @0x0039AD56 89B
// Target evidence: vtable 0x0081AD20 at +0 then base Snapshot 0x007BB554; EH frame
//  with states 1 then 0; member at +0x2C deleted via virtual slot0 with 0
//  return-fed to rowed operator delete 0x0002FD60 then nulled; AsciiString at
//  +8 via rowed releaseBuffer 0x00036410 (AsciiStringMember pin); callers are
//  the deleting dtor 0x0039AF5A plus derived dtors 0x0039ADF3 and 0x005DB100.
// Shape follows PlayerList dtor (ternary deleteInstance plus null plus EH).

#include "Common/Snapshot.h"

void __cdecl operator delete(void *p);

class AsciiStringMember
{
public:
	~AsciiStringMember();

private:
	char m_data[4];
};

class Rva0039AD56Target
{
public:
	virtual void *deleteInstance(unsigned int flags);
};

struct Rva0039AD56Holder
{
	Rva0039AD56Target *m_p;

	__forceinline ~Rva0039AD56Holder()
	{
		::operator delete(m_p ? m_p->deleteInstance(0) : 0);
		m_p = 0;
	}
};

class Rva0039AD56 : public Snapshot
{
public:
	virtual ~Rva0039AD56();

private:
	int m_pad04; // +4
	AsciiStringMember m_str08; // +8
	char m_pad0C[0x20]; // +0x0C..+0x2B
	Rva0039AD56Holder m_holder2C; // +0x2C
};

Rva0039AD56::~Rva0039AD56()
{
}

// ??1Rva0039ADF3@@UAE@XZ @0x0039ADF3 11B
// Derived dtor: stores vtable 0x0081AD34 then tail-jmps to rowed base
// ??1Rva0039AD56@@UAE@XZ at 0x0039AD56; caller is 0x0039B0F1.
class Rva0039ADF3 : public Rva0039AD56
{
public:
	virtual ~Rva0039ADF3();
};

Rva0039ADF3::~Rva0039ADF3()
{
}
