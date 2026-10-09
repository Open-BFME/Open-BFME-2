// cl: /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1ScoreKeeper@@UAE@XZ retail 0x0039C2B5..0x0039C3A6 (241 bytes).
// Evidence: stores vtable 0x00C1AD98 (slot 0 is the matched scalar deleting
// destructor ??_GScoreKeeper@@UAEPAXI@Z 0x0039C5E1 which calls this body)
// then calls the pinned ScoreKeeper::unhookAllScoredKillTrackers 0x0039C09C
// and tears the members down in reverse order: vector 0x328 (inline free)
// frame-stats vector 0x31C (0x0039C151) UnicodeString 0x310 (releaseBuffer
// 0x00036E70) vector 0x304 (inline free) maps 0x2F8 0x2EC the twenty-map
// array 0x1FC (eh vector destructor iterator with map dtor 0x00357CD9) and
// maps 0x1F0 0x1E4 0x1D4 0x1C8 (tree dtor 0x00357C6A) then the Snapshot base
// vptr 0x00BBB554. Layout follows the matched ScoreKeeper::reset 0x0039C5FD
// (ScoreKeeperReset.cpp). Zero Hour's ~ScoreKeeper is empty; BFME 2 unhooks
// the scored kill trackers first. Both vectors are viewed as vector<int>:
// their unwind actions reach the rowed folded vector dtor 0x0007FAB3.
#include <map>
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT 1
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS 1
#include "Common/Snapshot.h"
#undef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#undef BFME_SNAPSHOT_NAME_SLOT
#include "unicode_string.h"

typedef _STL::map<unsigned, void *> ScoreCountMap;

class Rva0039C151
{
public:
	~Rva0039C151();
	void *begin, *end, *capacity;
};

class ScoreKeeper : public Snapshot
{
public:
	virtual ~ScoreKeeper();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *);
	void unhookAllScoredKillTrackers();

private:
	char opaque004[0x1C4];
	ScoreCountMap map1C8, map1D4;
	int field1E0;
	ScoreCountMap map1E4, objectsBuilt, objectsDestroyed[20], objectsLost, objectsCaptured;
	_STL::vector<int> trackedKills;
	UnicodeString field310;
	int field314, field318;
	Rva0039C151 frameStats;
	_STL::vector<int> field328;
};

ScoreKeeper::~ScoreKeeper()
{
	unhookAllScoredKillTrackers();
}
