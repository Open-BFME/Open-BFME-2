// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x003B1FF1 calls the map constructor 0x0033C432 on this+4, stores
// 0x00C1EF0C at +0 and zeros the four-byte string at +0x10. The 0x14-byte
// layout has a 12-byte nonvirtual map base at +4 and UnicodeString at +0x10.
// 0x005547A8 constructs it at ebp-0x20, below the saved EH link at ebp-0x0C.
// 0x003B1F65 restores the same table, calls StringBase<unsigned short>'s
// releaseBuffer (0x00036E70) on +0x10, then the AsciiString-pair tree
// destructor 0x003B1E83 on +4. 0x003B2026 uses +0x10 as a wide filename;
// 0x003B1BF3 traverses the +4 map's nodes, with AsciiString key/value at +0x10/+0x14.
// The table has 13 slots; 0x00C1EF40 starts IgnorePreferences' table, stored
// by 0x003B21C0 after calling 0x003B1FF1. Slots 0-12 target, in order:
// 0x003B200A (deleting destructor), 0x003B2026 (load UnicodeString),
// 0x003B1A09 (load AsciiString), 0x003B1BF3 (write), 0x003B1DBE (getBool),
// 0x003B1A67 (getReal), 0x003B1AC7 (getInt), 0x003B1CEE (getEnumIndex),
// 0x003B1FA1 (getAsciiString), 0x003B1B20 (setBool), 0x003B1B65 (setReal),
// 0x003B1BAE (setInt), 0x003B21A6 (setAsciiString). The load overloads are
// declared in reverse slot order for MSVC 7.1. All signatures follow ledger rows.
// Nonvirtual rva003B2322 and rva00535781 through rva00537C3F retain their
// ledger names and out-of-line declarations; no semantic names are inferred.
// Donor facts (Zero Hour UserPreferences.h): public PreferenceMap inheritance,
// m_filename's name and the shared accessor names. Retail changes its filename
// type to UnicodeString and supplies the additional virtual accessor slots.

#pragma once

#ifndef __BFME2_USERPREFERENCES_H_
#define __BFME2_USERPREFERENCES_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include <map>

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();

	virtual bool load(const AsciiString &fname);
	virtual bool load(const UnicodeString &fname);
	virtual bool write(void);

	virtual bool getBool(const AsciiString &key, bool defaultValue) const;
	virtual float getReal(const AsciiString &key, float defaultValue) const;
	virtual int getInt(const AsciiString &key, int defaultValue) const;
	virtual int getEnumIndex(const char *key, const char **names, int count, int defaultValue) const;
	virtual AsciiString getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const;

	virtual void setBool(const AsciiString &key, bool val);
	virtual void setReal(const AsciiString &key, float val);
	virtual void setInt(const AsciiString &key, int val);
	virtual void setAsciiString(const AsciiString &key, const AsciiString &val);

	void rva003B2322(const AsciiString &val, int num, bool flag);

	int rva00535CE4(AsciiString factionPrefix);
	AsciiString rva00535820();
	void rva00536B3F(AsciiString factionPrefix, int amount);
	int rva00536B86(AsciiString factionPrefix);
	void rva00536BD0(AsciiString factionPrefix, int amount);
	int rva00536C17(AsciiString factionPrefix);
	int rva0053700F();
	int rva005370D2();
	AsciiString rva00537261();
	void rva00537058(int bits);
	void rva0053711B(AsciiString factionPrefix, int amount, int value);
	UnicodeString rva00535B32(float seconds);
	void rva0053587C(AsciiString factionPrefix, int amount);
	void rva00535BAF(AsciiString factionPrefix, int amount);
	void rva00535C9D(AsciiString factionPrefix, int amount);
	void rva00535D2E(AsciiString factionPrefix, int amount);
	void rva00535DBF(AsciiString factionPrefix, int amount);
	void rva00535E50(AsciiString factionPrefix, int amount);
	void rva00535EE1(AsciiString factionPrefix, int amount);
	void rva00535F72(int amount);
	void rva00536003(int amount);
	void rva00536094(int amount);
	void rva00536125(int amount);
	int rva0053604B();
	int rva005360DC();
	int rva0053616D();
	void rva005361B6(AsciiString factionPrefix);
	AsciiString rva0053620F();
	int rva00535FBA();
	int rva005358C3(AsciiString factionPrefix);
	int rva00535BF6(AsciiString factionPrefix);
	int rva00535C40();
	int rva005373AF();
	int rva0053734E(AsciiString factionPrefix);
	int rva00537C28();
	UnicodeString rva00537C3F();
	void rva00536C61(AsciiString factionPrefix, int amount);
	int rva00536CA8(AsciiString factionPrefix);
	void rva00536CF2(AsciiString factionPrefix, int amount);
	int rva00536D39(AsciiString factionPrefix);
	void rva00536D83(AsciiString factionPrefix, int amount);
	int rva00536DCA(AsciiString factionPrefix);
	void rva00536E14(AsciiString factionPrefix, int amount);
	int rva00536E5B(AsciiString factionPrefix);
	void rva00536EA5(AsciiString factionPrefix, int amount);
	int rva00536EEC(AsciiString factionPrefix);
	void rva00536F36(AsciiString factionPrefix, int amount);
	int rva00536F7D(AsciiString factionPrefix);
	void rva00536FC7(int amount);
	int rva00535D75(AsciiString factionPrefix);
	int rva00535E06(AsciiString factionPrefix);
	int rva00535E97(AsciiString factionPrefix);
	int rva00535F28(AsciiString factionPrefix);
	void rva0053595E(AsciiString factionPrefix, float amount);
	float rva0053590D(AsciiString factionPrefix);
	float rva005359A9(AsciiString factionPrefix);
	float rva00535A45(AsciiString factionPrefix);
	float rva00535AE1(AsciiString factionPrefix);
	void rva005359FA(AsciiString factionPrefix, float amount);
	void rva00535A96(AsciiString factionPrefix, float amount);
	void rva00535781();
	int rva00537190(AsciiString factionPrefix, int amount);
	void rva005372BD(int amount);
	int rva00537305();
	void rva00537208(AsciiString factionPrefix);
	void rva0053626B(AsciiString factionPrefix, int amount);
	int rva005362B2(AsciiString factionPrefix);
	void rva005362FC(AsciiString factionPrefix, int amount);
	int rva00536343(AsciiString factionPrefix);
	void rva0053638D(AsciiString factionPrefix, int amount);
	int rva005363D4(AsciiString factionPrefix);
	void rva0053641E(AsciiString factionPrefix, int amount);
	int rva00536465(AsciiString factionPrefix);
	void rva005364AF(AsciiString factionPrefix, int amount);
	int rva005364F6(AsciiString factionPrefix);
	void rva00536540(AsciiString factionPrefix, int amount);
	int rva00536587(AsciiString factionPrefix);
	void rva005365D1(AsciiString factionPrefix, int amount);
	int rva00536618(AsciiString factionPrefix);
	void rva00536662(AsciiString factionPrefix, int amount);
	int rva005366A9(AsciiString factionPrefix);
	void rva005366F3(AsciiString factionPrefix, int amount);
	int rva0053673A(AsciiString factionPrefix);
	void rva00536784(AsciiString factionPrefix, int amount);
	int rva005367CB(AsciiString factionPrefix);
	int rva00536815(AsciiString factionPrefix);
	void rva0053685F(AsciiString factionPrefix, int amount);
	int rva005368A6(AsciiString factionPrefix);
	void rva005368F0(AsciiString factionPrefix, int amount);
	int rva00536937(AsciiString factionPrefix);
	void rva00536981(AsciiString factionPrefix, float amount);
	float rva005369CC(AsciiString factionPrefix);
	void rva00536A1D(AsciiString factionPrefix, int amount);
	int rva00536A64(AsciiString factionPrefix);
	void rva00536AAE(AsciiString factionPrefix, int amount);
	int rva00536AF5(AsciiString factionPrefix);
	int rva00537505(AsciiString a, const AsciiString &b);
	void rva005374B3(AsciiString a, const AsciiString &b, int v);
	int rva0053745E(AsciiString a, const AsciiString &b);
	void rva0053740C(AsciiString a, const AsciiString &b, int v);
	AsciiString rva0053755A(AsciiString a);
	AsciiString rva00537616(AsciiString a);
	AsciiString rva005376D2();
	AsciiString rva005377B6();
	void rva00537A9B(AsciiString arg, float gameTime);
	void rva005378E9(AsciiString faction, int turns);

protected:
	UnicodeString m_filename;
};

#endif
