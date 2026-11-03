// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x00387109 constructs the object at ebp-0x2C through 0x0054F52F with mode -1; 0x0038711C and 0x00387138 call its named getDisallowAsianText and getDisallowNonAsianText bodies on that same object. The special members are rowed as Rva0054F508.
// 0x0054F543 calls GameModePreferences' constructor 0x0044D54B on this with the incoming int mode; 0x0054F550 then installs 0x00C6AA60. 0x0054F508 restores that same table and tail-calls ~GameModePreferences at 0x0044D56A. Both special members are out of line.
// GameModePreferences' constructor calls UserPreferences at 0x0044D54E, stores mode at +0x14 (0x0044D557), installs its own 0x00C3EF60 (0x0044D55A), and zeros its four-byte AsciiString at +0x18 (0x0044D560). UserPreferences constructs its map at +4 (0x003B1FF4) and zeros its four-byte UnicodeString at +0x10 (0x003B2002). These members belong to the registered bases.
// The extent is 0x1C with no added fields: 0x005A5C32 addresses the embedded preferences at +0x46C, 0x005A5C3C calls 0x0054F52F, and 0x005A5C57 initializes the next member at +0x488. The inherited member at +0x18 occupies the last four bytes.
// 0x00C6AA60 has 13 virtual slots, followed by "%s\\CustomPref%d.ini" at 0x00C6AA94. Slots 0..12 target 0x0054F513, 0x003B2026, 0x003B1A09, 0x0044D50D, 0x0044D6C7, 0x0044D6F6, 0x0044D729, 0x003B1CEE, 0x003B1FA1, 0x0044D636, 0x0044D665, 0x0044D698, 0x003B21A6. Slots 1..12 equal GameModePreferences' table; only deleting-destructor slot 0 is overridden. 0x0054F513 calls 0x0054F508 at 0x0054F516.
// The named nonvirtual rows declare getLastLadderAddr 0x005DF4B9, getLastLadderPort 0x005DF50A, setLastLadder 0x0054F696, setUsesLongGameList 0x0054F745, getDisallowAsianText 0x0054F5DE, getDisallowNonAsianText 0x0054F63A, setDisallowAsianText 0x0054F825 and setDisallowNonAsianText 0x0054F8A0. Their retail map accesses adjust this by +4; no added data member or virtual slot is required.
// Donor facts (Zero Hour CustomMatchPreferences.h): class and accessor names, public preference inheritance, and a virtual destructor. Retail inserts GameModePreferences and passes an int to the constructor.

#pragma once

#ifndef __BFME2_CUSTOMMATCHPREFERENCESCLASS_H_
#define __BFME2_CUSTOMMATCHPREFERENCESCLASS_H_

#include "GameModePreferences.h"

class CustomMatchPreferences : public GameModePreferences
{
public:
	CustomMatchPreferences(int mode);
	virtual ~CustomMatchPreferences();

	void setLastLadder(const AsciiString &addr, unsigned short port);
	AsciiString getLastLadderAddr(void);
	unsigned short getLastLadderPort(void);
	void setUsesLongGameList(bool val);
	bool getDisallowAsianText(void);
	void setDisallowAsianText(bool val);
	bool getDisallowNonAsianText(void);
	void setDisallowNonAsianText(bool val);
};

#endif
