// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ??0Rva005C44A3@@QAE@ABV?$StringBase@D@@@Z @0x005C44A3 32B.
// The body first delegates to Rva004FA830's matched string constructor,
// clears two dwords, then installs retail table 0x00C745D4: slot 0 the
// deleting destructor (0x005C4537, ICF-shared with Rva004FA830's), then
// 0x005C44DF (makes the bonus's Rva005C436E record), getName 0x005C44C3
// ("IncreaseCommandPoints") and the field-parse builder 0x005C4352 (Type at
// +0x08, Amount at +0x0C). The compiler stores the class's own table.
#include "ascii_string.h"

class Rva005C436E;
class MultiIniFieldParse;

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
	virtual Rva005C436E *rva005C44DF(unsigned int a);
	virtual AsciiString getName() const;
	virtual void rva005C4352(MultiIniFieldParse &p);

private:
	int m_08;
	int m_0c;
};

Rva005C44A3::Rva005C44A3(const StringBase<char> &value)
	: Rva004FA830(value), m_08(0), m_0c(0)
{
}
