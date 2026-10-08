// cl: /O1 /arch:SSE /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// WB0x15D4C90 names GameStats::RealTimeEndGame and GameStats.cpp:97.
// Native5DE9F5..5DEBF8 allocates 24 rows and initializes these exact labels.
// The same receiver's C76DD4 table owns scalar delete5DF160 and inherited
// destructor thunk5DCFC9 -> the existing table destructor5DE9E3. The table
// constructor5DE9C4 and destructor5DE9E3 share C76AFC and a 20-byte layout;
// their former split class spellings are reconciled at the existing owner.
// Row stride24 is proved by every native Init receiver and the rowed copy,
// destructor and setValue providers; only its UnicodeString first word is
// accessed here. Its remaining fields stay opaque in this consuming view.
// No applicable clean BFME1 GameStats source exists at donor9cbfb551fe20.
// RealTimeEndGame and StrategicEndGame store the SAME native C76DD4 table.
// Their complete implicit destructors and scalar wrappers are byte/relocation
// twins. The existing named StrategicEndGame owners stay the sole owners of
// 5DCFC9 and5DF160: no second non-template pin or duplicate row is added.
#include "unicode_string.h"
class GameStats {
public:
 class Row {
 public: void Init(const char *,int);
 private: UnicodeString label; char remaining[20];
 };
 class RealTimeEndGame;
};
// Constructor31 and destructor18 own the same C76AFC table and 20B
// object: vptr0, three-pointer vector4, trailing word10.
class Rva005DE9E3 {
public:
 Rva005DE9E3(unsigned int);
 virtual ~Rva005DE9E3();
protected:
 GameStats::Row *rows;
 GameStats::Row *finish;
 GameStats::Row *capacity;
 int extra;
};
class GameStats::RealTimeEndGame : public Rva005DE9E3 {
public:
 RealTimeEndGame(int numCells);
};
GameStats::RealTimeEndGame::RealTimeEndGame(int numCells) : Rva005DE9E3(24) {
 rows[0].Init("STAT:RTS_SESSION_LENGTH",numCells);
 rows[1].Init("STAT:RTS_STRUCTURES_CREATED",numCells);
 rows[2].Init("STAT:RTS_STRUCTURES_LOST",numCells);
 rows[3].Init("STAT:RTS_STRUCTURES_DESTROYED",numCells);
 rows[4].Init("STAT:RTS_FORTRESSES_BUILT",numCells);
 rows[5].Init("STAT:RTS_UNITS_CREATED",numCells);
 rows[6].Init("STAT:RTS_UNITS_LOST",numCells);
 rows[7].Init("STAT:RTS_UNIT_KILL_DEATH_RATIO",numCells);
 rows[8].Init("STAT:RTS_UNITS_KILLED",numCells);
 rows[9].Init("STAT:RTS_FAVORITE_UNIT",numCells);
 rows[10].Init("STAT:RTS_MAXIMUM_INCOME_RATE_PER_MINUTE",numCells);
 rows[11].Init("STAT:RTS_TOTAL_RESOURCES_GATHERED",numCells);
 rows[12].Init("STAT:RTS_MONEY_GIVEN_TO_ALLIES",numCells);
 rows[13].Init("STAT:RTS_MONEY_RECEIVED_FROM_ALLIES",numCells);
 rows[14].Init("STAT:RTS_RESOUCES_SPENT_ON_STRUCTURES",numCells);
 rows[15].Init("STAT:RTS_RESOUCES_SPENT_ON_UNITS",numCells);
 rows[16].Init("STAT:RTS_RESOUCES_SPENT_ON_HEROES",numCells);
 rows[17].Init("STAT:RTS_TIME_SPENT_TO_REACH_LAST_SPELL_LEVEL",numCells);
 rows[18].Init("STAT:RTS_STRATEGIC_SKILL",numCells);
 rows[19].Init("STAT:RTS_TACTICAL_SKILL",numCells);
 rows[20].Init("STAT:RTS_TIME_SPENT_TO_BUILD_FIRST_HERO",numCells);
 rows[21].Init("STAT:RTS_TIMES_EACH_HERO_WAS_PURCHASED",numCells);
 rows[22].Init("STAT:RTS_HEROES_BUILT",numCells);
 rows[23].Init("STAT:RTS_HEROES_LOST",numCells);
}
