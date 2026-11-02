// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x005DF1B5 calls UserPreferences's constructor 0x003B1FF1 with unchanged this;
// 0x005DF1C2 then installs 0x00C776DC at +0. 0x005DF17C restores that same
// table and tail-calls ~UserPreferences (0x003B1F65) without adjusting this.
// UserPreferences's constructor installs 0x00C1EF0C, constructs its map at +4
// and clears its four-byte UnicodeString at +0x10. Its destructor releases
// that string at 0x003B1F83 and destroys the map at 0x003B1F8F.
// 0x005BABAC constructs QuickMatchPreferences at screen+0x64; 0x005BABBC
// writes the next member at +0x78. With the parent's 0x14-byte extent this
// bounds sizeof(QuickMatchPreferences) to 0x14, with no added data members.
// 0x00C776DC has 13 slots, ending at the filename format string 0x00C77710.
// Slot 0 is 0x005DF187, which calls ~QuickMatchPreferences at 0x005DF18A.
// Slots 1-12 equal UserPreferences's 0x00C1EF0C slots 1-12, in order:
// 0x003B2026, 0x003B1A09, 0x003B1BF3, 0x003B1DBE, 0x003B1A67, 0x003B1AC7,
// 0x003B1CEE, 0x003B1FA1, 0x003B1B20, 0x003B1B65, 0x003B1BAE, 0x003B21A6.
// The class overrides only the virtual destructor and introduces no slots.
// Nonvirtual ledger rows prove these out-of-line method names and signatures:
// setMapSelected 0x005DF73F, isMapSelected 0x005DF458, setLastLadder 0x005DF7A7;
// set/getMaxDisconnects 0x005DF856/0x005DF55B, MaxPoints 0x005DF8CF/0x005DF5AB,
// MinPoints 0x005DF948/0x005DF5FE, WaitTime 0x005DF9C1/0x005DF64E,
// NumPlayers 0x005DFA3A/0x005DF69E, MaxPing 0x005DFAB3/0x005DF6EE,
// Color 0x005DF214/0x005DF25C, Side 0x005DF2A5/0x005DF2ED,
// Highest1vs1Rank 0x005DF336/0x005DF37E, Highest2vs2Rank 0x005DF3C7/0x005DF40F.
// Donor facts (Zero Hour QuickmatchPreferences.h): public UserPreferences
// inheritance and the shared accessor names; the rank accessors are BFME2 rows.

#pragma once

#ifndef __BFME2_QUICKMATCHPREFERENCESCLASS_H_
#define __BFME2_QUICKMATCHPREFERENCESCLASS_H_

#include "UserPreferences.h"

class QuickMatchPreferences : public UserPreferences
{
public:
	QuickMatchPreferences();
	virtual ~QuickMatchPreferences();

	void setMapSelected(const AsciiString &mapName, bool selected);
	bool isMapSelected(const AsciiString &mapName);
	void setLastLadder(const AsciiString &address, unsigned short port);

	void setMaxDisconnects(int value);
	int getMaxDisconnects();
	void setMaxPoints(int value);
	int getMaxPoints();
	void setMinPoints(int value);
	int getMinPoints();
	void setWaitTime(int value);
	int getWaitTime();
	void setNumPlayers(int value);
	int getNumPlayers();
	void setMaxPing(int value);
	int getMaxPing();
	void setColor(int value);
	int getColor();
	void setSide(int value);
	int getSide();
	void setHighest1vs1Rank(int value);
	int getHighest1vs1Rank();
	void setHighest2vs2Rank(int value);
	int getHighest2vs2Rank();
};

#endif
