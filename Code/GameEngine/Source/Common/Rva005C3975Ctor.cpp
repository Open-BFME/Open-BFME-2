// cl: /Ireference/shims/bfme2_ascii /MD
// ??0Rva005C3975@@QAE@HHABVAsciiString@@@Z retail 0x005C3975 35B
// Evidence: calls base 0x00528B06 (int AsciiString); stores +0x10; vtable 0x00874490; ret 0xC; caller 0x005C3D0E
#include "ascii_string.h"

class Rva005C31FB
{
public:
	virtual ~Rva005C31FB();
	Rva005C31FB(int level, const AsciiString &name);
private:
	int m_level;
	AsciiString m_name;
	bool m_flag0C;
};

class Rva00528B06 : public Rva005C31FB
{
public:
	Rva00528B06(int level, const AsciiString &name);
	virtual ~Rva00528B06();
};

class Rva005C3975 : public Rva00528B06
{
public:
	Rva005C3975(int a, int level, const AsciiString &name);
private:
	int m_10;
};

Rva005C3975::Rva005C3975(int a, int level, const AsciiString &name) : Rva00528B06(level, name), m_10(a)
{
}
