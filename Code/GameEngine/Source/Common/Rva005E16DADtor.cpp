// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva005E16DA@@UAE@XZ @0x005E16FD 86B ctor at 0x005E16DA three AsciiStrings base dtor pin at 0x0022167C callers incl 0x005E184E
#include "ascii_string.h"
class Rva0022167C
{
public:
	~Rva0022167C();
	virtual void _pure() = 0;
	int m_4;
};
class Rva005E16DA : public Rva0022167C
{
	AsciiString m_8;
	AsciiString m_c;
	AsciiString m_10;
public:
	virtual ~Rva005E16DA();
};
Rva005E16DA::~Rva005E16DA()
{
}
