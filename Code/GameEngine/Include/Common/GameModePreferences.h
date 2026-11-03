// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x0044D54B calls UserPreferences' constructor 0x003B1FF1 on this, stores its int argument at +0x14 (0x0044D557), installs 0x00C3EF60 (0x0044D55A), and zeros four bytes at +0x18 (0x0044D560).
// 0x0044D512 reads the int at +0x14 and formats the AsciiString at +0x18 through 0x00038150 with "%s:%s" (0x00C3E4D0), "Rts" (0x00C3EF54) or "Strat" (0x00C3EF58); it returns this+0x18.
// 0x0044D56A restores 0x00C3EF60 at 0x0044D57B, releases the AsciiString at +0x18 through 0x00036410 (0x0044D588), then calls ~UserPreferences at 0x003B1F65 (0x0044D593). Both special members are out of line.
// The extent is 0x1C: the last four-byte member starts at +0x18; AptLanLobby's constructor calls the LAN-derived constructor on this+0x684 at 0x00445F5A and initializes the next string at +0x6A0. UserPreferences occupies +0..+0x13; no extra base or virtual base is constructed.
// 0x00C3EF60 has 13 virtual slots, followed by "StrategicScenario" at 0x00C3EF94. Slots 0..12 target 0x0044D758, 0x003B2026, 0x003B1A09, 0x0044D50D, 0x0044D6C7, 0x0044D6F6, 0x0044D729, 0x003B1CEE, 0x003B1FA1, 0x0044D636, 0x0044D665, 0x0044D698, 0x003B21A6. The ledger names every slot; unoverridden slots come from UserPreferences.h.
// LANPreferences' constructor 0x0044D2F5 calls this constructor at 0x0044D309, then installs 0x00C3EF04. The custom-match constructor 0x0054F52F calls it at 0x0054F543, then installs 0x00C6AA60. These tables differ from 0x00C3EF60 only in deleting-destructor slot 0; their destructors 0x0044D285 and 0x0054F508 tail-call 0x0044D56A.
// Nonvirtual signatures and access follow ledger rows: makeKey 0x0044D512, getStrategicScenario 0x0044D5A5, setStrategicScenario 0x0044D5EE, and the rva-prefixed methods at their named RVAs. Field spellings are neutral because retail does not preserve their names.

#pragma once

#ifndef __BFME2_GAMEMODEPREFERENCES_H_
#define __BFME2_GAMEMODEPREFERENCES_H_

#include "UserPreferences.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class GameSlot;

class GameModePreferences : public UserPreferences
{
public:
	GameModePreferences(int mode);
	virtual ~GameModePreferences();

	virtual bool write(void);
	virtual bool getBool(const AsciiString &key, bool defaultValue) const;
	virtual float getReal(const AsciiString &key, float defaultValue) const;
	virtual int getInt(const AsciiString &key, int defaultValue) const;
	virtual void setBool(const AsciiString &key, bool val);
	virtual void setReal(const AsciiString &key, float val);
	virtual void setInt(const AsciiString &key, int val);

	int getStrategicScenario(void);
	void setStrategicScenario(int scenario);
	UnicodeString rva0044D330(void);
	bool rva0044D774(GameSlot *slot);
	int rva0044D836(void);
	int rva0044D88C(void);
	bool rva0044D940(void);
	AsciiString rva0044D986(void);
	AsciiString rva0044DAA8(const AsciiString &defaultValue);
	bool rva0044DB54(int *values);
	AsciiString rva0044DBA5(void);
	void rva0044DC54(int val);
	void rva0044DCB9(int val);
	void rva0044DD1E(int val);
	void rva0044DD83(AsciiString val);
	void rva0044DDFB(int *values);
	void rva0044DE5A(const AsciiString &val);
	void rva0044DEC1(const AsciiString &val);
	int rva0054F5A4(void);
	void rva0054F7C0(int val);

private:
	const AsciiString &makeKey(const char *key) const;

	int field14;
	mutable AsciiString field18;
};

#endif
