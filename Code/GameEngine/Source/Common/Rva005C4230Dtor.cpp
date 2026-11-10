// cl: /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
//
// ??1Rva005C4230@@UAE@XZ @0x005C4230 (80B)

#include "ascii_string.h"

// LINK: rva002C004F's rowed home is Rva002BFF5A (Rva002C004FErase.cpp, 0x2C004F);
// the old Rva002D3627Host spelling named an unresolved symbol. The global keeps
// its pointer type, the call binds the rowed member through a cast.
class Rva002D3627Host;
#include "../../Include/Common/Rva002BFF5A.h"

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

class Rva005C4230 : public Rva005C4B1B
{
public:
	virtual ~Rva005C4230();
};

Rva005C4230::~Rva005C4230()
{
	((Rva002BFF5A *)((Rva002D3627Host *)TheLivingWorld))->rva002C004F(m_str.str());
}
