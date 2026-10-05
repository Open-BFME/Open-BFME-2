// cl: /O1 /MD /EHsc /D_CRTIMP= /Ireference/shims/bfme2_ascii
//
// ??1Rva005C4230@@UAE@XZ @0x005C4230 (80B)

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

class Rva005C4230 : public Rva005C4B1B
{
public:
	virtual ~Rva005C4230();
};

Rva005C4230::~Rva005C4230()
{
	g_00DFEF18->rva002C004F(m_str.str());
}
