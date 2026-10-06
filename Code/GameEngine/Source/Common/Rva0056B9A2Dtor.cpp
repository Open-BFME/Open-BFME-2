// cl: /O1 /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
//
// ??1Rva0056B9A2@@UAE@XZ @0x0056B9A2 (80B)

#include "ascii_string.h"

class Rva002D3627Host
{
public:
	void rva002C004F(const char *name);
};

extern Rva002D3627Host *g_00DFEF18;

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
	g_00DFEF18->rva002C004F(m_str.str());
}
