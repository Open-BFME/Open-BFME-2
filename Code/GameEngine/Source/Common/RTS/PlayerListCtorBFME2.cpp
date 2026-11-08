// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ZH PlayerList.cpp and BF1 f98983a7d PlayerList.cpp77-85 semantic donor.
// Native2A7F80..2A8008 complete136B constructor: twenty758-byte Players.
// Existing BFME2 destructor and loop providers establish local10 count14
// array18 and Snapshot baseC; the shared BFME2 subsystem header supplies
// the native12-byte base and fourteen-slot vtable ABI.
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "Common/Snapshot.h"
#include "../../../Include/Common/Player.h"
class PlayerList : public SubsystemInterface, public Snapshot {
public:
 PlayerList();virtual ~PlayerList();virtual void init();virtual void reset();virtual void update();
 virtual void newGame();virtual void newMap();virtual void rva002A7ACE();
 virtual void DoXfer(Xfer*);
protected:virtual void LoadPostProcess();virtual const char*GetSnapshotName()const;
private:Player*local;int count;Player*players[20];
};
PlayerList::PlayerList():local(0),count(0) {for(int i=0;i<20;++i)players[i]=new Player(i);init();}
