// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x00559723 calls UserPreferences's constructor 0x003B1FF1 with unchanged this;
// 0x00559730 installs 0x00C6B3AC at +0. 0x005596EA restores the same table
// and tail-calls ~UserPreferences (0x003B1F65) without adjusting this.
// The parent's constructor constructs its map at +4 (0x003B1FF4) and clears
// its four-byte UnicodeString at +0x10 (0x003B2002). Its destructor releases
// the string at 0x003B1F83 and destroys the map at 0x003B1F8F.
// 0x00517234 constructs GameSpyMiscPreferences at ebp-0x20, below the saved
// EH link at ebp-0x0C (read at 0x005172FF): sizeof is 0x14, the parent's
// full extent, with no added data members.
// 0x00C6B3AC has 13 slots, ending at the filename format string 0x00C6B3E0.
// Slot 0 is 0x005596F5, which calls ~GameSpyMiscPreferences at 0x005596F8.
// Slots 1-12 equal UserPreferences's 0x00C1EF0C slots 1-12, in order:
// 0x003B2026, 0x003B1A09, 0x003B1BF3, 0x003B1DBE, 0x003B1A67, 0x003B1AC7,
// 0x003B1CEE, 0x003B1FA1, 0x003B1B20, 0x003B1B65, 0x003B1BAE, 0x003B21A6.
// The class overrides the virtual destructor and introduces no virtual slots.
// Nonvirtual ledger rows declare rva00559782/rva005597CB (Locale get/set),
// rva00559813/rva0055986F (ToolTipCachedStats get/set), rva005598C8/rva00559924
// (AllOtherCachedStats get/set), rva0055997D (QMResLock) and rva005599C8
// (MaxMessagesPerUpdate); each suffix is its retail RVA. Their retail calls
// use inherited slots 6/11, 8/12, 8/12, 4 and 6 respectively.
// Donor facts (Zero Hour GameSpyMiscPreferences.h): public UserPreferences
// inheritance and a virtual destructor. BFME2 methods retain their ledger names.

#pragma once

#ifndef __BFME2_GAMESPYMISCPREFERENCESCLASS_H_
#define __BFME2_GAMESPYMISCPREFERENCESCLASS_H_

#include "UserPreferences.h"

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();

	int rva00559782();
	void rva005597CB(int value);
	void rva0055986F(AsciiString value);
	void rva00559924(AsciiString value);
	AsciiString rva00559813();
	AsciiString rva005598C8();
	bool rva0055997D();
	int rva005599C8();
};

#endif
