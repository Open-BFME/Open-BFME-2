#ifndef BFME2_RVA004FA830_H
#define BFME2_RVA004FA830_H

#include "string_base.h"

class AsciiString;
class MultiIniFieldParse;

// Retail constructor 0x004FA815 installs table 0x008633A0 and copies
// the string at +4. The three derived parser builders call slot 3 directly.
class Rva004FA830
{
public:
	Rva004FA830(const StringBase<char> &name);
	virtual ~Rva004FA830();
	virtual void *slot1(unsigned int) = 0;
	virtual AsciiString slot2() const = 0;
	virtual void buildFieldParse(MultiIniFieldParse &parse);

private:
	StringBase<char> m_name;
};

#endif
