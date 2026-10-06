// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000C38F8@@QAE@XZ @0x000C47F4 231B
// Retail ctor: base Rva0042526Member 0x42526 then 10x Vector_base PlayerAITypeEntry 0x211E58,
// List_base BfmePod32 0xB92D2 at 0xB4, AsciiString inlines at 0x58 0x5C 0x60 0x70 0x74,
// then helper rva000C38F8 0xC38F8. Evidence: packet callees all rowed, caller 0xC8914,
// layout matches INIRva000C38F8 offsets; vector T uses rowed PlayerAITypeEntry twin
// at 0x211E58 (same bytes as BfmeE16 twin) though retail element semantics may differ.
#include <vector>
#include <list>
#include "ascii_string.h"

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

struct PlayerAITypeEntry
{
	AsciiString name;
	char unknown[12];
};

struct BfmePod32
{
	char data[32];
};

class Rva000C38F8 : public Rva0042526Member
{
public:
	Rva000C38F8();
	void rva000C38F8();
private:
	_STL::vector<PlayerAITypeEntry> m_4c;
	AsciiString m_58;
	AsciiString m_5c;
	AsciiString m_60;
	_STL::vector<PlayerAITypeEntry> m_64;
	AsciiString m_70;
	AsciiString m_74;
	_STL::vector<PlayerAITypeEntry> m_78;
	_STL::vector<PlayerAITypeEntry> m_84;
	_STL::vector<PlayerAITypeEntry> m_90;
	_STL::vector<PlayerAITypeEntry> m_9c;
	_STL::vector<PlayerAITypeEntry> m_a8;
	_STL::list<BfmePod32> m_b4;
	_STL::vector<PlayerAITypeEntry> m_b8;
	_STL::vector<PlayerAITypeEntry> m_c4;
	_STL::vector<PlayerAITypeEntry> m_d0;
};

Rva000C38F8::Rva000C38F8()
{
	rva000C38F8();
}
