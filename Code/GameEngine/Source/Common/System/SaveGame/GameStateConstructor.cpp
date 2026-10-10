// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /O1 /G7 /MD /EHsc
// BFME1 GameState and ZH GameState.cpp provide subsystem and list semantics.
// Target constructor2DE4E6..2DE57F and complete destructor2DE58D prove the
// twelve-byte SubsystemInterface base and Snapshot at+C; canonical headers
// preserve those bases. Native array callbacks construct five four-byte
// SnapshotBlock lists at+10. The registration helper2DE34B independently
// proves each SnapshotBlock contains Snapshot* then AsciiString.
// DE8-byte save-info member at+24 uses existing neutral owner2DD173/2DD1E9.
// Post-process helpers2DC52B/2DC4B8 independently establish pointer-listE0C
// and sequence-record-listE10. Native stores prove scalarE14 and flagE18;
// their original names remain unknown. WB unnamed counterpartE697F0 confirms
// construction flow; it does not name the unresolved fields.
// Two list-base allocator ctors are full41-byte relocation twins with their
// existing owners. No claim is based on a masked placement alone.
// stlport
#include <list>
// The subsystem header expects the engine Bool typedef.
typedef bool Bool;
#include "subsystem_interface.h"
#include "Common/Snapshot.h"
struct BfmeSubobject0022CE19 { virtual ~BfmeSubobject0022CE19(); char opaque04[0xDE4]; BfmeSubobject0022CE19(); };
struct GameStatePostRecord { Snapshot *snapshot; unsigned sequence; };
class GameState : public SubsystemInterface,public Snapshot {
 struct SnapshotBlock {Snapshot *snapshot;AsciiString blockName;};
 std::list<SnapshotBlock> blocks[5];
 BfmeSubobject0022CE19 saveInfo;
 std::list<Snapshot*> pending;
 std::list<GameStatePostRecord> marks;
 unsigned wordE14;bool flagE18;
public:
 GameState();virtual ~GameState();virtual void init();virtual void reset();virtual void update();
protected:virtual void loadPostProcess();virtual void crc(Xfer*);virtual void xfer(Xfer*);
};
GameState::GameState():wordE14(0),flagE18(false) {}

typedef char GameStateExtent[sizeof(GameState)==0xE1C ? 1 : -1];
