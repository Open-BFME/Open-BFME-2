// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??1Rva005FE7FA@@UAE@XZ @0x005FE7FA 59B via derived vtable plus wide string plus base Rva005FE750
// Evidence: chain from just-landed base 0x005FE750; prev same flags; callee rowed releaseBuffer wide 0x00036E70 plus base dtor; vtable 0x0087A408.

#include "unicode_string.h"

class Rva005FE750
{
public:
	virtual ~Rva005FE750();
private:
	char m_pad[0x30];
};

class Rva005FE7FA : public Rva005FE750
{
public:
	virtual ~Rva005FE7FA();
private:
	int m_34;
	UnicodeString m_38;
};

Rva005FE7FA::~Rva005FE7FA()
{
}
