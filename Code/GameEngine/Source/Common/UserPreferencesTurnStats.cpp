// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva005378E9@UserPreferences@@QAEXVAsciiString@@H@Z @0x005378E9 355B
// UserPreferences turn-stats path: append TurnsPlayed to faction copy, bump it,
// track Longest/ShortestGameTurns, recompute AverageGameTurns.
// Evidence: concat TurnsPlayed 0x00868FE8 slot 0x2C calls 0x00536815 0x005368A6
// 0x0053685F 0x00536937 0x005368F0 0x0053734E 0x005369CC 0x00536981 float
// 1.0f 0x007BB8D8 ret 8 chain same TU unlock.
// The running-average denominator adds the 1.0f literal (pooled at
// 0x00BBB8D8), not a float global standing in for it.
// Native callers preserve the one-pointer string ABI. Use the shared
// view and its independently verified workers instead of private wrappers.
#include "ascii_string.h"

class UserPreferences
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual float v5(const AsciiString &s, float x);
	virtual int v6(const AsciiString &s, int x);
	virtual void v7();
	virtual AsciiString v8(const AsciiString &key, const AsciiString &def);
	virtual void v9();
	virtual void v10(const AsciiString &s, float x);
	virtual void v11(const AsciiString &s, int x);
	virtual void v12(const AsciiString &a, const AsciiString &b);
	int rva00536815(AsciiString arg);
	int rva005368A6(AsciiString arg);
	void rva0053685F(AsciiString arg, int x);
	int rva00536937(AsciiString arg);
	void rva005368F0(AsciiString arg, int x);
	int rva0053734E(AsciiString arg);
	float rva005369CC(AsciiString arg);
	void rva00536981(AsciiString arg, float x);
	void rva005378E9(AsciiString faction, int turns);
};

void UserPreferences::rva005378E9(AsciiString faction, int turns)
{
	AsciiString key(faction);
	((StringBase<char> *)&key)->concat("TurnsPlayed");
	int oldTurns = rva00536815(key);
	v11(key, oldTurns + turns);
	int longest = rva005368A6(faction);
	if (turns > longest)
		rva0053685F(faction, turns);
	int shortest = rva00536937(faction);
	if (shortest == 0 || turns < shortest)
		rva005368F0(faction, turns);
	float avg;
	int total = rva0053734E(faction);
	float totalF;
	totalF = (float)total;
	avg = rva005369CC(faction);
	float newAvg = (totalF * avg + (float)turns) / (totalF + 1.0f);
	rva00536981(faction, newAvg);
}
