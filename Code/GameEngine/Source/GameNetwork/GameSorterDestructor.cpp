// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// GameSorter constructor580842 and WB1562BC0 bind its five named sort
// callbacks; target stores primary4/previous8 at0C/10, flags14/15 and cycle18.
// 580B40 appends the LAN/online GameInfo pointers, 58113D indexes and sorts
// them, and 580182 changes the sort fields. Vector storage is12B, object28B.
// The automatic destructor has the full14-byte free-first-pointer shape at
// 7FAB3 called by AptLanLobby::~AptLanLobby44455C and its EH cleanup.
// Keep this provider separate: whole-TU exception analysis otherwise removes
// the caller's state2 transition. No public exception guarantee is inferred.
#include <vector>
class GameInfo;
class Rva005248D0;
class GameSorter {
public:
 GameSorter(Rva005248D0 *registry);
 ~GameSorter();
 void OnSortName(const char*);
 void OnSortMap(const char*);
 void OnSortPlayers(const char*);
 void OnSortPing(const char*);
 void OnSortStatus(const char*);

private:
 _STL::vector<GameInfo*> m_games;
 int m_primarySort;
 int m_previousSort;
 bool m_changed;
 bool m_sorted;
 int m_cycle;
};
GameSorter::~GameSorter() {}

// The existing state-change provider has the same receiver and field layout.
class Rva00580172 { public: void rva00580182(int); };

// Constructor580842 binds native5801C0 to GameSorter::OnSortName.
// Its complete10B body forwards selector1 to580182 and returns RET4.
void GameSorter::OnSortName(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(1);
}

// Constructor580842 binds native5801CA to GameSorter::OnSortMap.
// Its complete10B body forwards selector2 to580182 and returns RET4.
void GameSorter::OnSortMap(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(2);
}

// Constructor580842 binds native5801D4 to GameSorter::OnSortPlayers.
// Its complete10B body forwards selector4 to580182 and returns RET4.
void GameSorter::OnSortPlayers(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(4);
}

// Constructor580842 binds native5801DE to GameSorter::OnSortPing.
// Its complete10B body forwards selector8 to580182 and returns RET4.
void GameSorter::OnSortPing(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(8);
}

// Constructor580842 binds native5801E8 to GameSorter::OnSortStatus.
// Its complete10B body forwards selector16 to580182 and returns RET4.
void GameSorter::OnSortStatus(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(16);
}
