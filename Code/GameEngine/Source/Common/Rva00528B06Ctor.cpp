// cl: /Ireference/shims/bfme2_ascii /MD
// ??0Rva00528B06@@QAE@HABVAsciiString@@@Z retail 0x00528B06 28B
// Evidence: stores vtable 0x008681C4 at [this]; calls base 0x005C31D5 ??0Rva005C31FB@@QAE@HABVAsciiString@@@Z; ret 8; callers 0x00577A2A 0x005C3975 0x005D2462
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

Rva00528B06::Rva00528B06(int level, const AsciiString &name) : Rva005C31FB(level, name)
{
}

Rva00528B06::~Rva00528B06()
{
}
