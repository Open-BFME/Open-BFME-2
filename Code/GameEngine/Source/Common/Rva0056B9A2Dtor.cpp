// cl: /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
//
// ??1Rva0056B9A2@@UAE@XZ @0x0056B9A2 (80B)

#include "ascii_string.h"

// LINK: rva002C004F's rowed home is Rva002BFF5A (Rva002C004FErase.cpp, 0x2C004F);
// the old Rva002D3627Host spelling named an unresolved symbol. The global keeps
// its pointer type, the call binds the rowed member through a cast.
class Rva002D3627Host;
struct Rva002BFFD4Template;
class Rva002BFF5A
{
public:
	void rva002BFFD4(Rva002BFFD4Template *, int, unsigned int);
	void rva002C004F(const char *name);
};

class LivingWorld; extern LivingWorld *TheLivingWorld;

class Rva003FCE38
{
public:
	virtual ~Rva003FCE38();
protected:
	AsciiString m_str;
};

class Rva005C4B1B : public Rva003FCE38
{
public:
	virtual ~Rva005C4B1B();
};

class Rva0056B9A2 : public Rva005C4B1B
{
public:
	virtual ~Rva0056B9A2();
};

Rva0056B9A2::~Rva0056B9A2()
{
	((Rva002BFF5A *)((Rva002D3627Host *)TheLivingWorld))->rva002C004F(m_str.str());
}
