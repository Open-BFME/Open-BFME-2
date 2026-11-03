// Target facts (game.dat 1.06; code addresses are RVAs, tables are VAs):
// 0x005CB1B3 calls UserPreferences 0x003B1FF1 on this, stores 0x00C74C48
// at +0, and calls map constructor 0x0033C432 at +0x14/+0x20/+0x2C/+0x38.
// UserPreferences occupies 0x14 bytes; four 12-byte maps make sizeof 0x44.
// 0x005728B0 constructs this class at owner+0x60; the next field is +0xA4.
// 0x0057F330 destroys it at owner+0x58, below the next field at +0x9C.
// 0x005CAB59 restores 0x00C74C48 and destroys +0x38/+0x2C via 0x005CA918,
// +0x20/+0x14 via 0x003B1E83, then calls UserPreferences 0x003B1F65.
// The parent's constructor/destructor store 0x00C1EF0C, its own 13-slot table.
// The derived table has 14 slots and ends at the date_ string at 0x00C74C80.
// Slots 0-3: 0x005CABDD (deleting destructor), 0x003B2026 (load UnicodeString),
// 0x003B1A09 (load const AsciiString&), 0x005CA2B3 (write).
// Slots 4-8: 0x003B1DBE, 0x003B1A67, 0x003B1AC7, 0x003B1CEE, 0x003B1FA1;
// slots 9-12: 0x003B1B20, 0x003B1B65, 0x003B1BAE, 0x003B21A6.
// These accessor slots retain the registered parent's names and signatures.
// Slot 13 is 0x005CAF5F, load(AsciiString) by value, not a base-slot override.
// That load decodes pass_/date_ into +0x14/+0x20 and nick_/clan_ into +0x2C/+0x38;
// 0x005CA70E reads the password map, and 0x005CA58E reads the date map.
// 0x005CA201/0x005CA211 pass +0x2C/+0x38 to borrowed-list helper 0x005CA1A0.
// 0x005CADD3/0x005CAE72 delete from those respective list-valued maps;
// 0x005CAE04 adds a clan entry, 0x005CACDE sets a login, 0x005CABF9 erases one.
// Ledger rows also prove rva005C9FC4 (0x005C9FC4), rva005CA07D (0x005CA07D),
// rva005CA53E (0x005CA53E), Write_Rva005C9DA8 (0x005C9DA8), and
// ReadEmailList_Rva005CAEA3 (0x005CAEA3), with the declarations below.
// Original field names are unknown; field14/20/2C/38 name their retail offsets.

#pragma once

#ifndef __BFME2_GAMESPYLOGINPREFERENCES_H_
#define __BFME2_GAMESPYLOGINPREFERENCES_H_

#include "../Common/UserPreferences.h"
#include <list>

struct _iobuf;

class GameSpyLoginPreferences : public UserPreferences
{
public:
	GameSpyLoginPreferences();
	virtual ~GameSpyLoginPreferences();
	virtual bool write();
	virtual bool load(AsciiString fname);

	AsciiString rva005C9FC4();
	_STL::list<AsciiString> rva005CA07D();
	const _STL::list<AsciiString> &rva005CA1A0(const AsciiString &email, _STL::map<AsciiString, _STL::list<AsciiString> > &emails);
	const _STL::list<AsciiString> &rva005CA201(const AsciiString &email);
	const _STL::list<AsciiString> &rva005CA211(const AsciiString &email);
	void rva005CA53E(const AsciiString &email);
	AsciiString rva005CA58E(AsciiString email, AsciiString &month, AsciiString &day, AsciiString &year);
	AsciiString getPasswordForEmail(AsciiString email);
	void rva005CABF9(AsciiString email);
	void rva005CACDE(AsciiString email, AsciiString nick, AsciiString password, AsciiString date);
	void deleteNick(const AsciiString &email, const AsciiString &nick);
	bool rva005CAE04(const AsciiString &email, const AsciiString &nick);
	void deleteClan(const AsciiString &email, const AsciiString &nick);
	void Write_Rva005C9DA8(_STL::map<AsciiString, _STL::list<AsciiString> > &emails, const char *prefix, _iobuf *fp);
	void ReadEmailList_Rva005CAEA3(_STL::map<AsciiString, _STL::list<AsciiString> > &emails, const char *prefix, UserPreferences::iterator &upIt);

private:
	_STL::map<AsciiString, AsciiString> field14;
	_STL::map<AsciiString, AsciiString> field20;
	_STL::map<AsciiString, _STL::list<AsciiString> > field2C;
	_STL::map<AsciiString, _STL::list<AsciiString> > field38;
};

#endif
