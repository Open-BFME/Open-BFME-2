// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x0043C13D calls UserPreferences' constructor 0x003B1FF1 on this+0.
// 0x0043C14E installs 0x00C3D658; 0x0043C154 stores the int argument at +0x14,
// 0x0043C157 constructs list<UnicodeString> at +0x18 through 0x0043C072,
// and 0x0043C15F zeros the four-byte AsciiString at +0x1C. The UserNames
// and CurrentUserName keys at 0x0043C193/0x0043C226 identify those members.
// 0x0043BAC7 passes +0x14 as the index in the ":%d:%s:%s" profile key.
// 0x0043BFFC/0x0043C059 replace and restore it while erasing a user's keys;
// 0x0043C308/0x0043C319 select indexes 0/1 before deleting each stats file.
// 0x00522B89 constructs the +0x698 subobject; 0x00522B9C writes the next
// member at +0x6B8, bounding sizeof at 0x20. The final +0x1C store reaches it.
// 0x0043C297 restores the same table, then destroys +0x1C via 0x00036410,
// +0x18 via 0x00433BD7, and UserPreferences via 0x003B1F65 at 0x0043C2BE.
// The base constructor/destructor install 0x00C1EF0C (0x003B1FFC/0x003B1F76),
// so that table belongs to the base. Its map is at +4 and wide filename at +0x10.
// SkirmishPreferences is polymorphic. Its table has 13 entries, ending before
// the non-code word 0x14 at 0x00C3D68C. Slots 0 and 3 are 0x0043C4B6
// (deleting destructor, calling 0x0043C286) and 0x0043C6C7 (write).
// Slots 1,2,4-12 retain the base's load(UnicodeString), load(AsciiString),
// getBool, getReal, getInt, getEnumIndex, getAsciiString, setBool, setReal,
// setInt and setAsciiString, at 0x003B2026, 0x003B1A09, 0x003B1DBE,
// 0x003B1A67, 0x003B1AC7, 0x003B1CEE, 0x003B1FA1, 0x003B1B20,
// 0x003B1B65, 0x003B1BAE and 0x003B21A6. No virtual slots are added.
// Nonvirtual declarations retain ledger names and signatures: 0x0043B9E8,
// 0x0043B9F5, 0x0043BA95, 0x0043BB08, 0x0043BB6A, 0x0043BB88,
// 0x0043BBB6, 0x0043BC0A, 0x0043BD36, 0x0043BE36, 0x0043BE7C,
// 0x0043BFDB, 0x0043C2D0, 0x0043C2EB, 0x0043C384, 0x0043C4D2,
// 0x0043C559 and 0x0043C612. 0x0043C2D8 passes this+0x18 to the list copy.

#pragma once

#ifndef __BFME2_SKIRMISHPREFERENCESCLASS_H_
#define __BFME2_SKIRMISHPREFERENCESCLASS_H_

#include "../Common/UserPreferences.h"
#include <list>

class SkirmishPreferences : public UserPreferences
{
public:
	SkirmishPreferences(int profileIndex);
	virtual ~SkirmishPreferences();
	virtual bool write();

	bool Rva0043B9E8();
	UnicodeString Rva0043B9F5();
	AsciiString formatProfileKey(const AsciiString *keySource, const char *name);
	AsciiString encodeUserKey(const UnicodeString &user, const char *name);
	AsciiString buildProfileKey(const char *name);
	UnicodeString Rva0043BB88();
	int Rva0043BBB6(UnicodeString user);
	bool getGameInfo();
	void rva0043BD36();
	void Rva0043BE36(const AsciiString &mapName);
	void rva0043BE7C();
	void Rva0043BFDB(const UnicodeString &user, int profileIndex);
	_STL::list<UnicodeString> getUserNames_Rva0043C2D0();
	void Rva0043C2EB(const UnicodeString &user);
	AsciiString getPreferredMap();
	void setCurrentUserName(const UnicodeString &newName);
	void rva0043C612(const UnicodeString &user);

private:
	void rebuildUserNamesEntry();

	int m_profileIndex;
	_STL::list<UnicodeString> m_userNames;
	AsciiString m_currentUserName;
};

#endif
