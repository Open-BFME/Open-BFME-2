// cl: /O1 /arch:SSE /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// WB0x15D5180 names GameStats::StrategicEndGame and GameStats.cpp:161.
// Native5DEBF8..5DEE37 allocates 27 rows and initializes these exact labels.
// The same receiver's C76DD4 table owns scalar delete5DF160 and inherited
// destructor thunk5DCFC9 -> the existing table destructor5DE9E3. The table
// constructor5DE9C4 and destructor5DE9E3 share C76AFC and a 20-byte layout;
// their former split class spellings are reconciled at the existing owner.
// Row stride24 is proved by every native Init receiver and the rowed copy,
// destructor and setValue providers; only its UnicodeString first word is
// accessed here. Its remaining fields stay opaque in this consuming view.
// No applicable clean BFME1 GameStats source exists at donor9cbfb551fe20.
// Implicit derived destruction forwards to the existing table destructor.
#include "unicode_string.h"
class GameStats {
public:
 class Row {
 public: void Init(const char *,int);
 private: UnicodeString label; char remaining[20];
 };
 class StrategicEndGame;
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
class GameStats::StrategicEndGame : public Rva005DE9E3 {
public:
 StrategicEndGame(int numCells);
};
GameStats::StrategicEndGame::StrategicEndGame(int numCells) : Rva005DE9E3(27) {
 rows[0].Init("STAT:STRATEGIC_RTS_TIME",numCells);
 rows[1].Init("STAT:STRATEGIC_NON_RTS_TIME",numCells);
 rows[2].Init("STAT:STRATEGIC_TURNS_PLAYED",numCells);
 rows[3].Init("STAT:STRATEGIC_STRUCTURES_CREATED_RTS",numCells);
 rows[4].Init("STAT:STRATEGIC_STRUCTURES_LOST_RTS",numCells);
 rows[5].Init("STAT:STRATEGIC_STRUCTURES_LOST_AUTORESOLVE",numCells);
 rows[6].Init("STAT:STRATEGIC_STRUCTURES_DESTROYED_RTS",numCells);
 rows[7].Init("STAT:STRATEGIC_STRUCTURES_DESTROYED_AUTORESOLVE",numCells);
 rows[8].Init("STAT:STRATEGIC_FORTRESSES_BUILT",numCells);
 rows[9].Init("STAT:STRATEGIC_FARMS_BUILT",numCells);
 rows[10].Init("STAT:STRATEGIC_ARMORIES_BUILT",numCells);
 rows[11].Init("STAT:STRATEGIC_BARRACKS_BUILT",numCells);
 rows[12].Init("STAT:STRATEGIC_UNITS_CREATED",numCells);
 rows[13].Init("STAT:STRATEGIC_UNITS_LOST",numCells);
 rows[14].Init("STAT:STRATEGIC_UNIT_KILL_DEATH_RATIO",numCells);
 rows[15].Init("STAT:STRATEGIC_UNITS_LOST_AUTORESOLVE",numCells);
 rows[16].Init("STAT:STRATEGIC_UNITS_KILLED_RTS",numCells);
 rows[17].Init("STAT:STRATEGIC_UNITS_KILLED_AUTORESOLVE",numCells);
 rows[18].Init("STAT:STRATEGIC_RTS_BATTLES_WON",numCells);
 rows[19].Init("STAT:STRATEGIC_RTS_BATTLES_LOST",numCells);
 rows[20].Init("STAT:STRATEGIC_RTS_BATTLES_WIN_LOSS_RATIO",numCells);
 rows[21].Init("STAT:STRATEGIC_AUTORESOLVED_BATTLES_WON",numCells);
 rows[22].Init("STAT:STRATEGIC_AUTORESOLVED_BATTLES_LOST",numCells);
 rows[23].Init("STAT:STRATEGIC_TERRITORIES_CONQUERED",numCells);
 rows[24].Init("STAT:STRATEGIC_TERRITORIES_LOST",numCells);
 rows[25].Init("STAT:STRATEGIC_REGIONS_CONQUERED",numCells);
 rows[26].Init("STAT:STRATEGIC_REGIONS_LOST",numCells);
}
