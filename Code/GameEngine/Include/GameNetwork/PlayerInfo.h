// Target facts (BFME2 retail RVAs): PlayerInfo has no virtual functions or base.
// The constructors at 0x003822C4 and 0x001EF485 and destructor at 0x001EF50E
// store no vtable pointer; +0 is the first string, not a virtual dispatch table.
// 0x003822C4 initializes three strings at +0, +4 and +8 through StringBase<char>
// assignment 0x000366F0, sets dwords +0x20/+0x24 to -1 and the other eight
// dwords at +0x0C..+0x30 to zero. 0x001EF485 copies the three strings through
// 0x000365F0 and separately copies every dword at +0x0C..+0x30.
// 0x001EF50E releases strings at +8, +4 and +0 through 0x00036410.
// sizeof is 0x34: 0x00383D4F allocates a 0x48-byte node with its pair at +0x10;
// pair copy 0x00382BF0 places PlayerInfo at +4 after its AsciiString key.
// 0x00386EF8 independently takes PlayerInfo at [ebp+8], its following string
// at [ebp+0x3C], and returns with RET 0x38. It calls assignment 0x00381E9B
// at 0x00386F40 and destruction 0x001EF50E at 0x00386F5F.
// 0x00382BF0 calls copy construction 0x001EF485; 0x00385F29 calls default
// construction 0x003822C4. These methods are declared out of line.
// isIgnored (0x00382841) reads profile ID at +0x14, or passes the +0 string
// to GameSpyInfo's name-based query. Other field names remain offset placeholders.

#pragma once

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class PlayerInfo
{
public:
	PlayerInfo();
	PlayerInfo(const PlayerInfo &other);
	~PlayerInfo();
	PlayerInfo &operator=(const PlayerInfo &other);
	bool isIgnored();

	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	int m_at24;
	int m_at28;
	int m_at2c;
	int m_at30;
};
