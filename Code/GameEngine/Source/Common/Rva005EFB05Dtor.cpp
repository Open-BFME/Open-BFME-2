// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /D_CRTIMP=
// ??1Rva005EFB05@@QAE@XZ @0x005EFB05 93B: dtor with AsciiString at +0x04 plus Rva0052413E at +0x0C plus Rva005241B0 at +0x18 plus range teardown at +0x24 plus wide release at +0x30.
// Evidence: calls rowed narrow 0x00036410 plus rowed dtors 0x0052413E and 0x005241B0 plus rowed 0x005EF8BB plus rowed wide 0x00036E70; callers 0x005EFB65 and 0x005EFD45.
#include "ascii_string.h"
#include "unicode_string.h"
class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};
class Rva005241B0
{
public:
	~Rva005241B0();
private:
	char m_pad[12];
};
class Rva005EF8BB
{
public:
	void rva005EF8BB();
	~Rva005EF8BB();
private:
	void *m_first;
	void *m_last;
};
// ??1Rva005EF8BB@@QAE@XZ present-unmatched
inline Rva005EF8BB::~Rva005EF8BB()
{
	rva005EF8BB();
}
class Rva005EFB05
{
public:
	~Rva005EFB05();
private:
	int m_00;
	AsciiString m_04;
	int m_08;
	Rva0052413E m_0C;
	Rva005241B0 m_18;
	Rva005EF8BB m_24;
	int m_2C;
	UnicodeString m_30;
};
Rva005EFB05::~Rva005EFB05()
{
}
