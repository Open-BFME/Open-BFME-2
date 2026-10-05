// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// ?rva00537A9B@UserPreferences@@QAEXVAsciiString@@M@Z @0x00537A9B 397B
// UserPreferences record-game-time path: TimePlayed add, Longest max, Shortest min-nonzero, Average recompute via total-games.
// Evidence: TimePlayed 0x00868E2C slot 0x28, Longest 0x00868E38 getter setter, Shortest 0x00868E48 getter setter,
// total-games 0x0053734E Average 0x00868E5C getter setter, TheGame float 1.0 0x007BB8D8, chain same class.
// Call sites 0x005BFA94 and 0x005BFE18. Structural inference: the average is
// recomputed in place in the getter's result (one float slot reused for the
// argument), as the turn-count sibling 0x005378E9 does with its own locals.
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
	virtual void v8();
	virtual void v9();
	virtual void v10(const AsciiString &s, float x);
	virtual void v11(const AsciiString &s, int x);
	float rva0053590D(AsciiString arg);
	float rva005359A9(AsciiString arg);
	void rva0053595E(AsciiString arg, float x);
	float rva00535A45(AsciiString arg);
	void rva005359FA(AsciiString arg, float x);
	int rva0053734E(AsciiString arg);
	float rva00535AE1(AsciiString arg);
	void rva00535A96(AsciiString arg, float x);
	void rva00537A9B(AsciiString arg, float gameTime);
};

void UserPreferences::rva00537A9B(AsciiString arg, float gameTime)
{
	AsciiString key(arg);
	((StringBase<char> *)&key)->concat("TimePlayed");
	float total = rva0053590D(arg) + gameTime;
	v10(key, total);
	float longest = rva005359A9(arg);
	if (gameTime > longest)
		rva0053595E(arg, gameTime);
	float shortest = rva00535A45(arg);
	if (shortest == 0.0f || gameTime < shortest)
		rva005359FA(arg, gameTime);
	int games = rva0053734E(arg);
	float fGames = (float)(games - 1);
	float avg = rva00535AE1(arg);
	avg = (fGames * avg + gameTime) / (fGames + 1.0f);
	rva00535A96(arg, avg);
}
