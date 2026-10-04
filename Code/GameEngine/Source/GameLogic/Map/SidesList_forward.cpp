// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD
#include "ascii_string.h"
//
// ?forward@Rva0019C520Owner@@QAEHVAsciiString@@H@Z @0x0032D7DB 64B
// Evidence: donor game/GameEngine/Source/GameLogic/Map/Rva0019C520Forward.cpp
// (Rva0019C520Owner::forward via m_member.lookup); callers 0x002AD46D,
// ?verifyValidTeam@MapObject@@QAEXXZ +0x4F (casts TheSidesList to
// Rva0019C520Owner and forwards teamName); callees rowed (lookup 0x0032D0B5,
// releaseBuffer 0x00036410). Offset 0xF44 from retail add ecx.
//

class Rva0019C520Member
{
public:
	int lookup(AsciiString *name, int extra);
};

class Rva0019C520Owner
{
public:
	int forward(AsciiString name, int extra);

private:
	char m_head[0xF44];
	Rva0019C520Member m_member;
};

int Rva0019C520Owner::forward(AsciiString name, int extra)
{
	return m_member.lookup(&name, extra);
}
