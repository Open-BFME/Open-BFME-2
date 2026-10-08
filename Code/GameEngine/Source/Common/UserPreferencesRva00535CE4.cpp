// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00535CE4@UserPreferences@@QAEHVAsciiString@@@Z @0x00535CE4 74B
// UserPreferences Losses path: append Losses to by-value AsciiString, slot6 virtual
// with (arg, 0), return its int, EH dtor via releaseBuffer.
// Evidence: concat 0x00005629, slot6 0x18, releaseBuffer 0x00036410, ret 4,
// unblocks 5, callers 10, sibling UserPreferencesWinsLossesVs.
// ?rva0053587C@UserPreferences@@QAEXVAsciiString@@H@Z @0x0053587C 71B
// UserPreferences Points path: append Points, slot 0x2C virtual with (arg, x), void ret 8.
// Evidence: concat Points 0x00868E24, slot 0x2C, releaseBuffer, unblocks 2, callers 2,
// sibling 0x00535CE4 same TU(flags pins).
// ?rva00535BAF@UserPreferences@@QAEXVAsciiString@@H@Z @0x00535BAF 71B
// UserPreferences Wins path: append Wins, slot 0x2C with (arg, x), void ret 8.
// Evidence: concat Wins 0x00868E7C, slot 0x2C, releaseBuffer, gap between 0x0053587C
// and 0x00535CE4 same TU, unblocks 2 callers 2.
// ?rva00535C9D@UserPreferences@@QAEXVAsciiString@@H@Z @0x00535C9D 71B
// UserPreferences Losses-void path: append Losses slot 0x2C with (arg, x) void ret 8.
// Evidence: concat Losses 0x00868E84 slot 0x2C releaseBuffer gap Wins-Losses same TU.
// ?rva00535D2E@UserPreferences@@QAEXVAsciiString@@H@Z @0x00535D2E 71B
// UserPreferences WinStreak-void path: append WinStreak slot 0x2C with (arg, x) void ret 8.
// Evidence: concat WinStreak 0x00868E8C slot 0x2C releaseBuffer gap same TU unlock.
// ?rva00535DBF@UserPreferences@@QAEXVAsciiString@@H@Z @0x00535DBF 71B
// UserPreferences LossStreak-void path: append LossStreak slot 0x2C with (arg, x) void ret 8.
// Evidence: concat LossStreak 0x00868E98 slot 0x2C releaseBuffer gap same TU unlock.
// ?rva00535E50@UserPreferences@@QAEXVAsciiString@@H@Z @0x00535E50 71B
// UserPreferences BestWinStreak-void path: append BestWinStreak slot 0x2C with (arg, x) void ret 8.
// Evidence: concat BestWinStreak 0x00868EA4 slot 0x2C releaseBuffer gap same TU unlock.
// ?rva00535EE1@UserPreferences@@QAEXVAsciiString@@H@Z @0x00535EE1 71B
// UserPreferences WorstLossStreak-void path: append WorstLossStreak slot 0x2C with (arg, x) void ret 8.
// Evidence: concat WorstLossStreak 0x00868EB4 slot 0x2C releaseBuffer gap same TU unlock.
// ?rva00535F72@UserPreferences@@QAEXH@Z @0x00535F72 72B
// UserPreferences OverallWinStreak-void path: local AsciiString OverallWinStreak slot 0x2C with (tmp, x) void ret 4.
// Evidence: StringBase PBD ctor 0x00037BA0 slot 0x2C releaseBuffer gap same TU unlock.
// ?rva00535FBA@UserPreferences@@QAEHXZ @0x00535FBA 73B
// UserPreferences OverallWinStreak-getter path: local AsciiString OverallWinStreak slot 0x18 with (tmp, 0) int ret 0.
// Evidence: StringBase PBD ctor 0x00037BA0 slot 0x18 releaseBuffer gap same TU unlock.
// ?rva005358C3@UserPreferences@@QAEHVAsciiString@@@Z @0x005358C3 74B
// UserPreferences Points-getter path: append Points to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat Points 0x00868E24 slot 0x18 releaseBuffer gap same TU unlock.
// ?rva00535BF6@UserPreferences@@QAEHVAsciiString@@@Z @0x00535BF6 74B
// UserPreferences Wins-getter path: append Wins to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat Wins 0x00868E7C slot 0x18 releaseBuffer gap same TU unlock.
// ?rva00535C40@UserPreferences@@QAEHXZ @0x00535C40 93B
// UserPreferences total-wins path: sum Wins-getter over 6 faction table slot 0x18 chain.
// Evidence: faction table 0x009BE9B0 calls 0x00535BF6 chain same TU.
// ?rva005373AF@UserPreferences@@QAEHXZ @0x005373AF 93B
// UserPreferences total-losses path: sum Losses-getter over 6 faction table slot 0x18 chain.
// Evidence: faction table 0x009BE9B0 calls 0x00535CE4 chain same TU.
// ?rva0053734E@UserPreferences@@QAEHVAsciiString@@@Z @0x0053734E 97B
// UserPreferences total-games path: Wins-getter plus Losses-getter over same by-value faction arg chain.
// Evidence: copy 0x000365F0 calls 0x00535BF6 0x00535CE4 releaseBuffer ret 4 chain same TU.
// ?rva00537C28@UserPreferences@@QAEHXZ @0x00537C28 23B
// UserPreferences grand-total path: total-losses plus total-wins chain.
// Evidence: calls 0x005373AF 0x00535C40 ret 0 chain same TU.
// ?rva00536C61@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536C61 71B
// UserPreferences BattlesLostRTS-void path: append BattlesLostRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat BattlesLostRTS 0x00869084 slot 0x2C releaseBuffer gap same TU.
// ?rva00536CA8@UserPreferences@@QAEHVAsciiString@@@Z @0x00536CA8 74B
// UserPreferences BattlesLostRTS-getter path: append BattlesLostRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat BattlesLostRTS 0x00869084 slot 0x18 releaseBuffer gap same TU.
// ?rva00536CF2@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536CF2 71B
// UserPreferences BattlesWonRTS-void path: append BattlesWonRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat BattlesWonRTS 0x00869094 slot 0x2C releaseBuffer gap same TU.
// ?rva00536D39@UserPreferences@@QAEHVAsciiString@@@Z @0x00536D39 74B
// UserPreferences BattlesWonRTS-getter path: append BattlesWonRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat BattlesWonRTS 0x00869094 slot 0x18 releaseBuffer gap same TU.
// ?rva00536D83@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536D83 71B
// UserPreferences BattlesLostAutoResolve-void path: append BattlesLostAutoResolve slot 0x2C with (arg, x) void ret 8.
// Evidence: concat BattlesLostAutoResolve 0x008690A4 slot 0x2C releaseBuffer gap same TU.
// ?rva00536DCA@UserPreferences@@QAEHVAsciiString@@@Z @0x00536DCA 74B
// UserPreferences BattlesLostAutoResolve-getter path: append BattlesLostAutoResolve to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat BattlesLostAutoResolve 0x008690A4 slot 0x18 releaseBuffer gap same TU.
// ?rva00536E14@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536E14 71B
// UserPreferences BattlesWonAutoResolve-void path: append BattlesWonAutoResolve slot 0x2C with (arg, x) void ret 8.
// Evidence: concat BattlesWonAutoResolve 0x008690BC slot 0x2C releaseBuffer gap same TU.
// ?rva00536E5B@UserPreferences@@QAEHVAsciiString@@@Z @0x00536E5B 74B
// UserPreferences BattlesWonAutoResolve-getter path: append BattlesWonAutoResolve to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat BattlesWonAutoResolve 0x008690BC slot 0x18 releaseBuffer gap same TU.
// ?rva00536EA5@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536EA5 71B
// UserPreferences RegionsConquered-void path: append RegionsConquered slot 0x2C with (arg, x) void ret 8.
// Evidence: concat RegionsConquered 0x008690D4 slot 0x2C releaseBuffer gap same TU.
// ?rva00536EEC@UserPreferences@@QAEHVAsciiString@@@Z @0x00536EEC 74B
// UserPreferences RegionsConquered-getter path: append RegionsConquered to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat RegionsConquered 0x008690D4 slot 0x18 releaseBuffer gap same TU.
// ?rva00536F36@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536F36 71B
// UserPreferences RegionsLost-void path: append RegionsLost slot 0x2C with (arg, x) void ret 8.
// Evidence: concat RegionsLost 0x008690E8 slot 0x2C releaseBuffer gap same TU.
// ?rva00536F7D@UserPreferences@@QAEHVAsciiString@@@Z @0x00536F7D 74B
// UserPreferences RegionsLost-getter path: append RegionsLost to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat RegionsLost 0x008690E8 slot 0x18 releaseBuffer gap same TU.
// ?rva00536FC7@UserPreferences@@QAEXH@Z @0x00536FC7 72B
// UserPreferences Challenge-void path: local AsciiString Challenge slot 0x2C with (tmp, x) void ret 4.
// Evidence: StringBase PBD 0x00037BA0 slot 0x2C releaseBuffer gap same TU.
// ?rva00535D75@UserPreferences@@QAEHVAsciiString@@@Z @0x00535D75 74B
// UserPreferences WinStreak-getter path: append WinStreak to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat WinStreak 0x00868E8C slot 0x18 releaseBuffer gap same TU unlock.
// ?rva00535E06@UserPreferences@@QAEHVAsciiString@@@Z @0x00535E06 74B
// UserPreferences LossStreak-getter path: append LossStreak to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat LossStreak 0x00868E98 slot 0x18 releaseBuffer gap same TU unlock.
// ?rva00535E97@UserPreferences@@QAEHVAsciiString@@@Z @0x00535E97 74B
// UserPreferences BestWinStreak-getter path: append BestWinStreak to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat BestWinStreak 0x00868EA4 slot 0x18 releaseBuffer gap same TU unlock.
// ?rva00535F28@UserPreferences@@QAEHVAsciiString@@@Z @0x00535F28 74B
// UserPreferences WorstLossStreak-getter path: append WorstLossStreak to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat WorstLossStreak 0x00868EB4 slot 0x18 releaseBuffer gap same TU unlock.
// ?rva0053595E@UserPreferences@@QAEXVAsciiString@@M@Z @0x0053595E 75B
// UserPreferences LongestGameTime-setter path: append LongestGameTime to by-value AsciiString slot 0x28 with (arg, float) void ret 8.
// Evidence: concat LongestGameTime 0x00868E38 slot 0x28 releaseBuffer gap same TU unlock.
// ?rva0053590D@UserPreferences@@QAEMVAsciiString@@@Z @0x0053590D 81B
// UserPreferences TimePlayed-getter path: append TimePlayed to by-value AsciiString slot 0x14 with (arg, 0.0f) float ret 4.
// Evidence: concat TimePlayed 0x00868E2C slot 0x14 releaseBuffer fldz fstp gap same TU unlock.
// ?rva005359A9@UserPreferences@@QAEMVAsciiString@@@Z @0x005359A9 81B
// UserPreferences LongestGameTime-getter path: append LongestGameTime to by-value AsciiString slot 0x14 with (arg, 0.0f) float ret 4.
// Evidence: concat LongestGameTime 0x00868E38 slot 0x14 releaseBuffer fldz fstp gap same TU unlock.
// ?rva00535A45@UserPreferences@@QAEMVAsciiString@@@Z @0x00535A45 81B
// UserPreferences ShortestGameTime-getter path: append ShortestGameTime to by-value AsciiString slot 0x14 with (arg, 0.0f) float ret 4.
// Evidence: concat ShortestGameTime 0x00868E48 slot 0x14 releaseBuffer fldz fstp gap same TU unlock.
// ?rva00535AE1@UserPreferences@@QAEMVAsciiString@@@Z @0x00535AE1 81B
// UserPreferences AverageGameTime-getter path: append AverageGameTime to by-value AsciiString slot 0x14 with (arg, 0.0f) float ret 4.
// Evidence: concat AverageGameTime 0x00868E5C slot 0x14 releaseBuffer fldz fstp gap same TU unlock.
// ?rva005359FA@UserPreferences@@QAEXVAsciiString@@M@Z @0x005359FA 75B
// UserPreferences ShortestGameTime-setter path: append ShortestGameTime to by-value AsciiString slot 0x28 with (arg, float) void ret 8.
// Evidence: concat ShortestGameTime 0x00868E48 slot 0x28 releaseBuffer gap same TU unlock.
// ?rva00535A96@UserPreferences@@QAEXVAsciiString@@M@Z @0x00535A96 75B
// UserPreferences AverageGameTime-setter path: append AverageGameTime to by-value AsciiString slot 0x28 with (arg, float) void ret 8.
// Evidence: concat AverageGameTime 0x00868E5C slot 0x28 releaseBuffer gap same TU unlock.
// Native callers preserve the one-pointer string ABI. Use the shared
// view and its independently verified workers instead of private wrappers.
#include "ascii_string.h"
#include "unicode_string.h"
typedef unsigned short WideChar;

struct SYSTEMTIME
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
};

extern "C" __declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME *st);

UnicodeString Rva002DBFAD(SYSTEMTIME st);

// TheGameText (VA 0xdff0bc). Slot 0x44 follows the by-value fetch overloads at
// 0x3C/0x40 and returns the label's string by pointer; its name is not proven.
class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual UnicodeString slot38(const AsciiString &label, bool *exists);
	virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

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
	int rva00535CE4(AsciiString arg);
	AsciiString rva00535820();
	void rva00536B3F(AsciiString arg, int x);
	int rva00536B86(AsciiString arg);
	void rva00536BD0(AsciiString arg, int x);
	int rva00536C17(AsciiString arg);
	int rva0053700F();
	int rva005370D2();
	AsciiString rva00537261();
	void rva00537058(int bits);
	void rva0053711B(AsciiString arg, int x, int value);
	UnicodeString rva00535B32(float seconds);
	void rva0053587C(AsciiString arg, int x);
	void rva00535BAF(AsciiString arg, int x);
	void rva00535C9D(AsciiString arg, int x);
	void rva00535D2E(AsciiString arg, int x);
	void rva00535DBF(AsciiString arg, int x);
	void rva00535E50(AsciiString arg, int x);
	void rva00535EE1(AsciiString arg, int x);
	void rva00535F72(int x);
	void rva00536003(int x);
	void rva00536094(int x);
	void rva00536125(int x);
	int rva0053604B();
	int rva005360DC();
	int rva0053616D();
	void rva005361B6(AsciiString arg);
	AsciiString rva0053620F();
	int rva00535FBA();
	int rva005358C3(AsciiString arg);
	int rva00535BF6(AsciiString arg);
	int rva00535C40();
	int rva005373AF();
	int rva0053734E(AsciiString arg);
	int rva00537C28();
	UnicodeString rva00537C3F();
	void rva00536C61(AsciiString arg, int x);
	int rva00536CA8(AsciiString arg);
	void rva00536CF2(AsciiString arg, int x);
	int rva00536D39(AsciiString arg);
	void rva00536D83(AsciiString arg, int x);
	int rva00536DCA(AsciiString arg);
	void rva00536E14(AsciiString arg, int x);
	int rva00536E5B(AsciiString arg);
	void rva00536EA5(AsciiString arg, int x);
	int rva00536EEC(AsciiString arg);
	void rva00536F36(AsciiString arg, int x);
	int rva00536F7D(AsciiString arg);
	void rva00536FC7(int x);
	int rva00535D75(AsciiString arg);
	int rva00535E06(AsciiString arg);
	int rva00535E97(AsciiString arg);
	int rva00535F28(AsciiString arg);
	void rva0053595E(AsciiString arg, float x);
	float rva0053590D(AsciiString arg);
	float rva005359A9(AsciiString arg);
	float rva00535A45(AsciiString arg);
	float rva00535AE1(AsciiString arg);
	void rva005359FA(AsciiString arg, float x);
	void rva00535A96(AsciiString arg, float x);
	void rva00535781();
	int rva00537190(AsciiString arg, int x);
	void rva005372BD(int x);
	int rva00537305();
	void rva00537208(AsciiString arg);
	void rva0053626B(AsciiString arg, int x);
	int rva005362B2(AsciiString arg);
	void rva005362FC(AsciiString arg, int x);
	int rva00536343(AsciiString arg);
	void rva0053638D(AsciiString arg, int x);
	int rva005363D4(AsciiString arg);
	void rva0053641E(AsciiString arg, int x);
	int rva00536465(AsciiString arg);
	void rva005364AF(AsciiString arg, int x);
	int rva005364F6(AsciiString arg);
	void rva00536540(AsciiString arg, int x);
	int rva00536587(AsciiString arg);
	void rva005365D1(AsciiString arg, int x);
	int rva00536618(AsciiString arg);
	void rva00536662(AsciiString arg, int x);
	int rva005366A9(AsciiString arg);
	void rva005366F3(AsciiString arg, int x);
	int rva0053673A(AsciiString arg);
	void rva00536784(AsciiString arg, int x);
	int rva005367CB(AsciiString arg);
	int rva00536815(AsciiString arg);
	void rva0053685F(AsciiString arg, int x);
	int rva005368A6(AsciiString arg);
	void rva005368F0(AsciiString arg, int x);
	int rva00536937(AsciiString arg);
	void rva00536981(AsciiString arg, float x);
	float rva005369CC(AsciiString arg);
	void rva00536A1D(AsciiString arg, int x);
	int rva00536A64(AsciiString arg);
	void rva00536AAE(AsciiString arg, int x);
	int rva00536AF5(AsciiString arg);
};

static const char *kFactions[] = { "Men", "Elves", "Dwarves", "Isengard", "Mordor", "Wild" };

int UserPreferences::rva00535CE4(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("Losses");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva0053587C(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("Points");
	v11(arg, x);
}

void UserPreferences::rva00535BAF(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("Wins");
	v11(arg, x);
}

void UserPreferences::rva00535C9D(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("Losses");
	v11(arg, x);
}

void UserPreferences::rva00535D2E(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("WinStreak");
	v11(arg, x);
}

void UserPreferences::rva00535DBF(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("LossStreak");
	v11(arg, x);
}

void UserPreferences::rva00535E50(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("BestWinStreak");
	v11(arg, x);
}

void UserPreferences::rva00535EE1(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("WorstLossStreak");
	v11(arg, x);
}

void UserPreferences::rva00535F72(int x)
{
	AsciiString tmp("OverallWinStreak");
	v11(tmp, x);
}

void UserPreferences::rva00536003(int x)
{
	AsciiString tmp("OverallBestWinStreak");
	v11(tmp, x);
}

void UserPreferences::rva00536094(int x)
{
	AsciiString tmp("OverallLossStreak");
	v11(tmp, x);
}

void UserPreferences::rva00536125(int x)
{
	AsciiString tmp("OverallWorstLossStreak");
	v11(tmp, x);
}

int UserPreferences::rva0053604B()
{
	AsciiString tmp("OverallBestWinStreak");
	int ret = v6(tmp, 0);
	return ret;
}

int UserPreferences::rva005360DC()
{
	AsciiString tmp("OverallLossStreak");
	int ret = v6(tmp, 0);
	return ret;
}

int UserPreferences::rva0053616D()
{
	AsciiString tmp("OverallWorstLossStreak");
	int ret = v6(tmp, 0);
	return ret;
}

// ?rva005361B6@UserPreferences@@QAEXVAsciiString@@@Z @0x005361B6 89B
// UserPreferences FavoriteSide path: local AsciiString FavoriteSide with (tmp, arg) v12 void ret 4.
// Evidence: StringBase PBD ctor 0x00037BA0 slot 0x30 releaseBuffer gap same TU unlock.
void UserPreferences::rva005361B6(AsciiString arg)
{
	AsciiString tmp("FavoriteSide");
	v12(tmp, arg);
}

// ?rva0053620F@UserPreferences@@QAE?AVAsciiString@@XZ @0x0053620F 92B
// UserPreferences FavoriteSide path: local AsciiString FavoriteSide getAsciiString with (tmp, Empty) hidden-ptr ret 4.
// Evidence: StringBase PBD ctor 0x00037BA0 slot 0x20 releaseBuffer gap same TU unlock.
AsciiString UserPreferences::rva0053620F()
{
	AsciiString tmp("FavoriteSide");
	return v8(tmp, AsciiString::TheEmptyString);
}

int UserPreferences::rva00535FBA()
{
	AsciiString tmp("OverallWinStreak");
	int ret = v6(tmp, 0);
	return ret;
}

int UserPreferences::rva005358C3(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("Points");
	int ret = v6(arg, 0);
	return ret;
}

int UserPreferences::rva00535BF6(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("Wins");
	int ret = v6(arg, 0);
	return ret;
}

int UserPreferences::rva00535C40()
{
	AsciiString dummy;
	int sum = 0;
	for (int i = 0; i < 6; ++i)
		sum += rva00535BF6(AsciiString(kFactions[i]));
	return sum;
}

int UserPreferences::rva005373AF()
{
	AsciiString dummy;
	int sum = 0;
	for (int i = 0; i < 6; ++i)
		sum += rva00535CE4(AsciiString(kFactions[i]));
	return sum;
}

int UserPreferences::rva0053734E(AsciiString arg)
{
	int wins = rva00535BF6(arg);
	int losses = rva00535CE4(arg);
	return wins + losses;
}

int UserPreferences::rva00537C28()
{
	int losses = rva005373AF();
	int wins = rva00535C40();
	return losses + wins;
}

void UserPreferences::rva00536C61(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("BattlesLostRTS");
	v11(arg, x);
}

int UserPreferences::rva00536CA8(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("BattlesLostRTS");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva00536CF2(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("BattlesWonRTS");
	v11(arg, x);
}

int UserPreferences::rva00536D39(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("BattlesWonRTS");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva00536D83(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("BattlesLostAutoResolve");
	v11(arg, x);
}

int UserPreferences::rva00536DCA(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("BattlesLostAutoResolve");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva00536E14(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("BattlesWonAutoResolve");
	v11(arg, x);
}

int UserPreferences::rva00536E5B(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("BattlesWonAutoResolve");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva00536EA5(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("RegionsConquered");
	v11(arg, x);
}

int UserPreferences::rva00536EEC(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("RegionsConquered");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva00536F36(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("RegionsLost");
	v11(arg, x);
}

int UserPreferences::rva00536F7D(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("RegionsLost");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva00536FC7(int x)
{
	AsciiString tmp("Challenge");
	v11(tmp, x);
}

int UserPreferences::rva00535D75(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("WinStreak");
	int ret = v6(arg, 0);
	return ret;
}

int UserPreferences::rva00535E06(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("LossStreak");
	int ret = v6(arg, 0);
	return ret;
}

int UserPreferences::rva00535E97(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("BestWinStreak");
	int ret = v6(arg, 0);
	return ret;
}

int UserPreferences::rva00535F28(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("WorstLossStreak");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva0053595E(AsciiString arg, float x)
{
	((StringBase<char> *)&arg)->concat("LongestGameTime");
	v10(arg, x);
}

float UserPreferences::rva0053590D(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("TimePlayed");
	float ret = v5(arg, 0.0f);
	return ret;
}

float UserPreferences::rva005359A9(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("LongestGameTime");
	float ret = v5(arg, 0.0f);
	return ret;
}

float UserPreferences::rva00535A45(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("ShortestGameTime");
	float ret = v5(arg, 0.0f);
	return ret;
}

float UserPreferences::rva00535AE1(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("AverageGameTime");
	float ret = v5(arg, 0.0f);
	return ret;
}

void UserPreferences::rva005359FA(AsciiString arg, float x)
{
	((StringBase<char> *)&arg)->concat("ShortestGameTime");
	v10(arg, x);
}

void UserPreferences::rva00535A96(AsciiString arg, float x)
{
	((StringBase<char> *)&arg)->concat("AverageGameTime");
	v10(arg, x);
}

void UserPreferences::rva00535781()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	UnicodeString tmp = Rva002DBFAD(st);
	AsciiString val;
	val.translate(tmp);
	AsciiString key("ProfileCreatedDate");
	v12(key, val);
}

int UserPreferences::rva00537190(AsciiString arg, int x)
{
	AsciiString tmp;
	const char *base = *(const char **)&arg;
	const char *s = base ? base + 8 : "";
	tmp.format("%s_%d", s, x);
	int ret = v6(tmp, 0);
	return ret;
}

void UserPreferences::rva005372BD(int x)
{
	AsciiString tmp("LoyalGames");
	v11(tmp, x);
}

int UserPreferences::rva00537305()
{
	AsciiString tmp("LoyalGames");
	int ret = v6(tmp, 0);
	return ret;
}

void UserPreferences::rva00537208(AsciiString arg)
{
	AsciiString tmp("LastHouse");
	v12(tmp, arg);
}

// ?rva0053626B@UserPreferences@@QAEXVAsciiString@@H@Z @0x0053626B 71B
// UserPreferences StructuresCreatedRTS-void path: append StructuresCreatedRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat StructuresCreatedRTS 0x00868F2C slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva0053626B(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("StructuresCreatedRTS");
	v11(arg, x);
}

int UserPreferences::rva005362B2(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("StructuresCreatedRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva005362FC@UserPreferences@@QAEXVAsciiString@@H@Z @0x005362FC 71B
// UserPreferences StructuresLostRTS-void path: append StructuresLostRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat StructuresLostRTS 0x00868F44 slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva005362FC(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("StructuresLostRTS");
	v11(arg, x);
}

// ?rva00536343@UserPreferences@@QAEHVAsciiString@@@Z @0x00536343 74B
// UserPreferences StructuresLostRTS-getter path: append StructuresLostRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat StructuresLostRTS 0x00868F44 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536343(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("StructuresLostRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva0053638D@UserPreferences@@QAEXVAsciiString@@H@Z @0x0053638D 71B
// UserPreferences StructuresKilledRTS-void path: append StructuresKilledRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat StructuresKilledRTS 0x00868F58 slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva0053638D(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("StructuresKilledRTS");
	v11(arg, x);
}

// ?rva005363D4@UserPreferences@@QAEHVAsciiString@@@Z @0x005363D4 74B
// UserPreferences StructuresKilledRTS-getter path: append StructuresKilledRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat StructuresKilledRTS 0x00868F58 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva005363D4(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("StructuresKilledRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva0053641E@UserPreferences@@QAEXVAsciiString@@H@Z @0x0053641E 71B
// UserPreferences UnitsCreatedRTS-void path: append UnitsCreatedRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat UnitsCreatedRTS 0x00868F6C slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva0053641E(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("UnitsCreatedRTS");
	v11(arg, x);
}

// ?rva00536465@UserPreferences@@QAEHVAsciiString@@@Z @0x00536465 74B
// UserPreferences UnitsCreatedRTS-getter path: append UnitsCreatedRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat UnitsCreatedRTS 0x00868F6C slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536465(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("UnitsCreatedRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva005364AF@UserPreferences@@QAEXVAsciiString@@H@Z @0x005364AF 71B
// UserPreferences UnitsLostRTS-void path: append UnitsLostRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat UnitsLostRTS 0x00868F7C slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva005364AF(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("UnitsLostRTS");
	v11(arg, x);
}

// ?rva005364F6@UserPreferences@@QAEHVAsciiString@@@Z @0x005364F6 74B
// UserPreferences UnitsLostRTS-getter path: append UnitsLostRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat UnitsLostRTS 0x00868F7C slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva005364F6(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("UnitsLostRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva00536540@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536540 71B
// UserPreferences UnitsKilledRTS-void path: append UnitsKilledRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat UnitsKilledRTS 0x00868F8C slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva00536540(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("UnitsKilledRTS");
	v11(arg, x);
}

// ?rva00536587@UserPreferences@@QAEHVAsciiString@@@Z @0x00536587 74B
// UserPreferences UnitsKilledRTS-getter path: append UnitsKilledRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat UnitsKilledRTS 0x00868F8C slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536587(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("UnitsKilledRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva005365D1@UserPreferences@@QAEXVAsciiString@@H@Z @0x005365D1 71B
// UserPreferences ResourcesGatheredRTS-void path: append ResourcesGatheredRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat ResourcesGatheredRTS 0x00868F9C slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva005365D1(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("ResourcesGatheredRTS");
	v11(arg, x);
}

// ?rva00536618@UserPreferences@@QAEHVAsciiString@@@Z @0x00536618 74B
// UserPreferences ResourcesGatheredRTS-getter path: append ResourcesGatheredRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat ResourcesGatheredRTS 0x00868F9C slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536618(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("ResourcesGatheredRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva00536662@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536662 71B
// UserPreferences ResourcesSpentRTS-void path: append ResourcesSpentRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat ResourcesSpentRTS 0x00868FB4 slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva00536662(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("ResourcesSpentRTS");
	v11(arg, x);
}

// ?rva005366A9@UserPreferences@@QAEHVAsciiString@@@Z @0x005366A9 74B
// UserPreferences ResourcesSpentRTS-getter path: append ResourcesSpentRTS to by-value AsciiString slot 0x18 with (arg, -1) int ret 4.
// Evidence: concat ResourcesSpentRTS 0x00868FB4 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva005366A9(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("ResourcesSpentRTS");
	int ret = v6(arg, -1);
	return ret;
}

// ?rva005366F3@UserPreferences@@QAEXVAsciiString@@H@Z @0x005366F3 71B
// UserPreferences HeroesBuiltRTS-void path: append HeroesBuiltRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat HeroesBuiltRTS 0x00868FC8 slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva005366F3(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("HeroesBuiltRTS");
	v11(arg, x);
}

// ?rva0053673A@UserPreferences@@QAEHVAsciiString@@@Z @0x0053673A 74B
// UserPreferences HeroesBuiltRTS-getter path: append HeroesBuiltRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat HeroesBuiltRTS 0x00868FC8 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva0053673A(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("HeroesBuiltRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva00536784@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536784 71B
// UserPreferences HeroesLostRTS-void path: append HeroesLostRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat HeroesLostRTS 0x00868FD8 slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva00536784(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("HeroesLostRTS");
	v11(arg, x);
}

// ?rva005367CB@UserPreferences@@QAEHVAsciiString@@@Z @0x005367CB 74B
// UserPreferences HeroesLostRTS-getter path: append HeroesLostRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat HeroesLostRTS 0x00868FD8 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva005367CB(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("HeroesLostRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva00536815@UserPreferences@@QAEHVAsciiString@@@Z @0x00536815 74B
// UserPreferences TurnsPlayed-getter path: append TurnsPlayed to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat TurnsPlayed 0x00868FE8 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536815(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("TurnsPlayed");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva0053685F@UserPreferences@@QAEXVAsciiString@@H@Z @0x0053685F 71B
// UserPreferences LongestGameTurns-void path: append LongestGameTurns slot 0x2C with (arg, x) void ret 8.
// Evidence: concat LongestGameTurns 0x00868FF4 slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva0053685F(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("LongestGameTurns");
	v11(arg, x);
}

// ?rva005368A6@UserPreferences@@QAEHVAsciiString@@@Z @0x005368A6 74B
// UserPreferences LongestGameTurns-getter path: append LongestGameTurns to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat LongestGameTurns 0x00868FF4 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva005368A6(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("LongestGameTurns");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva005368F0@UserPreferences@@QAEXVAsciiString@@H@Z @0x005368F0 71B
// UserPreferences ShortestGameTurns-void path: append ShortestGameTurns slot 0x2C with (arg, x) void ret 8.
// Evidence: concat ShortestGameTurns 0x00869008 slot 0x2C releaseBuffer gap same TU unlock.
void UserPreferences::rva005368F0(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("ShortestGameTurns");
	v11(arg, x);
}

// ?rva00536937@UserPreferences@@QAEHVAsciiString@@@Z @0x00536937 74B
// UserPreferences ShortestGameTurns-getter path: append ShortestGameTurns to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat ShortestGameTurns 0x00869008 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536937(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("ShortestGameTurns");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva00536981@UserPreferences@@QAEXVAsciiString@@M@Z @0x00536981 75B
// UserPreferences AverageGameTurns-setter path: append AverageGameTurns to by-value AsciiString slot 0x28 with (arg, float) void ret 8.
// Evidence: concat AverageGameTurns 0x0086901C slot 0x28 releaseBuffer gap same TU unlock.
void UserPreferences::rva00536981(AsciiString arg, float x)
{
	((StringBase<char> *)&arg)->concat("AverageGameTurns");
	v10(arg, x);
}

// ?rva005369CC@UserPreferences@@QAEMVAsciiString@@@Z @0x005369CC 72B
// UserPreferences AverageGameTurns getter: same string 0x00C6901C as the
// setter above, slot 0x14 float read with 0.0f default (fldz), caller
// 0x005378E9 (turn stats). Same shape as the TimePlayed getter 0x0053590D.
float UserPreferences::rva005369CC(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("AverageGameTurns");
	float ret = v5(arg, 0.0f);
	return ret;
}

void UserPreferences::rva00536A1D(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("StructuresLostNonRTS");
	v11(arg, x);
}

// ?rva00536A64@UserPreferences@@QAEHVAsciiString@@@Z @0x00536A64 74B
// UserPreferences StructuresLostNonRTS-getter path: append StructuresLostNonRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat StructuresLostNonRTS 0x00869030 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536A64(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("StructuresLostNonRTS");
	int ret = v6(arg, 0);
	return ret;
}

void UserPreferences::rva00536AAE(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("StructuresKilledNonRTS");
	v11(arg, x);
}

// ?rva00536AF5@UserPreferences@@QAEHVAsciiString@@@Z @0x00536AF5 74B
// UserPreferences StructuresKilledNonRTS-getter path: append StructuresKilledNonRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat StructuresKilledNonRTS 0x00869048 slot 0x18 releaseBuffer gap same TU unlock.
int UserPreferences::rva00536AF5(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("StructuresKilledNonRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva00535820@UserPreferences@@QAE?AVAsciiString@@XZ @0x00535820 92B
// UserPreferences ProfileCreatedDate path: local AsciiString ProfileCreatedDate getAsciiString with (tmp, Empty) hidden-ptr ret 4.
// Evidence: StringBase PBD ctor 0x00037BA0 slot 0x20 releaseBuffer, the FavoriteSide body's shape.
AsciiString UserPreferences::rva00535820()
{
	AsciiString tmp("ProfileCreatedDate");
	return v8(tmp, AsciiString::TheEmptyString);
}

// ?rva00536B3F@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536B3F 71B
// UserPreferences UnitsLostNonRTS-void path: append UnitsLostNonRTS slot 0x2C with (arg, x) void ret 8.
// Evidence: concat UnitsLostNonRTS 0x00869060 slot 0x2C releaseBuffer gap same TU.
void UserPreferences::rva00536B3F(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("UnitsLostNonRTS");
	v11(arg, x);
}

// ?rva00536B86@UserPreferences@@QAEHVAsciiString@@@Z @0x00536B86 74B
// UserPreferences UnitsLostNonRTS-getter path: append UnitsLostNonRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
// Evidence: concat UnitsLostNonRTS 0x00869060 slot 0x18 releaseBuffer gap same TU.
int UserPreferences::rva00536B86(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("UnitsLostNonRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva00536BD0@UserPreferences@@QAEXVAsciiString@@H@Z @0x00536BD0 71B
// UserPreferences UnitsKilledNonRTS-void path: append UnitsKilledNonRTS slot 0x2C with (arg, x) void ret 8.
void UserPreferences::rva00536BD0(AsciiString arg, int x)
{
	((StringBase<char> *)&arg)->concat("UnitsKilledNonRTS");
	v11(arg, x);
}

// ?rva00536C17@UserPreferences@@QAEHVAsciiString@@@Z @0x00536C17 74B
// UserPreferences UnitsKilledNonRTS-getter path: append UnitsKilledNonRTS to by-value AsciiString slot 0x18 with (arg, 0) int ret 4.
int UserPreferences::rva00536C17(AsciiString arg)
{
	((StringBase<char> *)&arg)->concat("UnitsKilledNonRTS");
	int ret = v6(arg, 0);
	return ret;
}

// ?rva0053700F@UserPreferences@@QAEHXZ @0x0053700F 73B
// UserPreferences Challenge-getter path: local AsciiString Challenge slot 0x18 with (tmp, 0) int ret 0.
// Evidence: StringBase PBD ctor 0x00037BA0 slot 0x18 releaseBuffer, the OverallWinStreak getter's shape.
int UserPreferences::rva0053700F()
{
	AsciiString tmp("Challenge");
	int ret = v6(tmp, 0);
	return ret;
}

// ?rva005370D2@UserPreferences@@QAEHXZ @0x005370D2 73B
// UserPreferences Honors-getter path: local AsciiString Honors slot 0x18 with (tmp, 0) int ret 0.
int UserPreferences::rva005370D2()
{
	AsciiString tmp("Honors");
	int ret = v6(tmp, 0);
	return ret;
}

// ?rva00537261@UserPreferences@@QAE?AVAsciiString@@XZ @0x00537261 92B
// UserPreferences LastHouse path: local AsciiString LastHouse getAsciiString with (tmp, Empty) hidden-ptr ret 4.
AsciiString UserPreferences::rva00537261()
{
	AsciiString tmp("LastHouse");
	return v8(tmp, AsciiString::TheEmptyString);
}

// ?rva00537058@UserPreferences@@QAEXH@Z @0x00537058 122B
// UserPreferences Honors-or path: read Honors (slot 0x18, default 0), OR the argument
// in and write it back (slot 0x2C); both keys are the one pooled literal, held in ebx.
void UserPreferences::rva00537058(int bits)
{
	int honors;
	{
		AsciiString tmp("Honors");
		honors = v6(tmp, 0);
	}
	AsciiString tmp("Honors");
	v11(tmp, honors | bits);
}

// ?rva0053711B@UserPreferences@@QAEXVAsciiString@@HH@Z @0x0053711B 117B
// UserPreferences indexed setter: format "%s_%d" from the by-value key and index and
// store the value (slot 0x2C); the setter twin of the getter at 0x00537190, ret 0xC.
void UserPreferences::rva0053711B(AsciiString arg, int x, int value)
{
	AsciiString tmp;
	const char *base = *(const char **)&arg;
	const char *s = base ? base + 8 : "";
	tmp.format("%s_%d", s, x);
	v11(tmp, value);
}

// ?rva00535B32@UserPreferences@@QAE?AVUnicodeString@@M@Z @0x00535B32 125B
// UserPreferences time-played text: whole hours of the float seconds, formatted as
// days and hours through the "Apt:TimePlayed" string. Evidence: cvttss2si, idiv by
// 60, 60 and 24, TheGameText slot 0x44, UnicodeString::format(const UnicodeString *)
// 0x006CB660, wide copy 0x00037050 into the hidden return, ret 8. `this` is unused.
UnicodeString UserPreferences::rva00535B32(float seconds)
{
	UnicodeString text;
	int hours = (int)seconds / 60 / 60;
	text.format(TheGameText->slot44("Apt:TimePlayed", 0), hours / 24, hours % 24);
	return text;
}

// ?rva00537C3F@UserPreferences@@QAE?AVUnicodeString@@XZ @0x00537C3F 244B
// Retail boundary: complete EH prologue at 0x00537C3F after the preceding
// rva00537C28 return; all branches converge before ret 4 at 0x00537D30.
// Target reads FavoriteSide through the same slot 0x20 as sibling preference
// getters, compares the narrow empty string, formats Side:%s, then fetches
// its wide label through TheGameText slot 0x38. Return and temporary cleanup
// use the rowed wide copy constructor and releaseBuffer. The method name
// remains address-derived; these bytes do not establish a public spelling.
UnicodeString UserPreferences::rva00537C3F()
{
    AsciiString side = v8(AsciiString("FavoriteSide"), AsciiString::TheEmptyString);
    if (side == AsciiString::TheEmptyString)
        return UnicodeString::TheEmptyString;
    AsciiString label;
    label.format("Side:%s", side.str());
    const UnicodeString &text = TheGameText->slot38(label, 0);
    return text;
}
