// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// LivingWorldBattle::BattlePlayer::DoXfer: WB1049300 names the body and
// native3F5CA9..3F5DBD supplies all276 bytes including RET4. The native
// virtual Xfer slots are loading+4/version+28/unsigned-count+78. The two-byte
// version and branch-local player IDs follow the retail/WB lifetime evidence.
// Player layout is48 bytes: player+0 armies+4 summaries+10 results+1C.
// ArmySummary is104 bytes (owned ctor40E3EE/dtor40E499; vtableC394F0);
// its snapshot transfer is virtual+0C. Legacy version3 uses owned3F5729.
// ArmyRecords is a storage view whose visible clear uses the existing folded
// range-erase owner3B908A; resize retains its existing provider3F5C4F.
// Keeping clear visible and the indexed summary local reproduces the target
// register allocation without barriers; separate player-ID scopes allow the
// loop offset to reuse the incoming argument slot. No native EH states.
#include <vector>
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
struct XferVersion {UnsignedByte m_version,m_currentVersion;};
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"


#include "../../../../Include/Common/Rva003F4E07Player.h"
class Rva002E2903Player;
class ModuleData;
// LivingWorldBattle.h needs the capitalized Snapshot slots with the reference transfer.
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
struct LivingWorldArmy;
class ArmySummary {public:ArmySummary();virtual ~ArmySummary();virtual void v1();virtual void v2();virtual void v3(Xfer*);char data[100];};
typedef ArmySummary BattleArmyRecord;
struct BfmeAssignRecord104 {int data[26];};
namespace _STL {template<> BfmeAssignRecord104 *vector<BfmeAssignRecord104>::erase(BfmeAssignRecord104*,BfmeAssignRecord104*);}
class Rva003F5A06 {public:void rva003F5C4F(int);};
class Rva003F3FFE {public:void rva003F3FFE(Xfer&);};
void XferLivingWorldPlayerID(Xfer*,int*);
Xfer *Rva003F5729Xfer(Xfer*,std::vector<ArmySummary>*);
class ArmyRecords: public std::vector<ArmySummary> {public:
void clear(){((_STL::vector<BfmeAssignRecord104> *)this)->erase((BfmeAssignRecord104 *)begin(),(BfmeAssignRecord104 *)end());}
};
#include "../../../../Include/GameLogic/LivingWorldBattle.h"
class LivingWorldBattle::BattlePlayer {public:
 void DoXfer(Xfer*);
 Rva003F4E07Player *m_player;
 std::vector<LivingWorldArmy*>m_armies;
 ArmyRecords m_records;
 int counters[5];
};
void LivingWorldBattle::BattlePlayer::DoXfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 4;
	(*xfer == reinterpret_cast<Xfer::Version &>(version));
	if (xfer->IsLoading()) {
		int playerID;
		XferLivingWorldPlayerID(xfer, &playerID);
		m_player = (Rva003F4E07Player *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerID, 0);
	} else {
		int playerID = m_player->id;
		XferLivingWorldPlayerID(xfer, &playerID);
	}
	((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B8D06(xfer, (_STL::vector<const ModuleData *> *)&m_armies);
	if (version.m_currentVersion >= 2)
		((Rva003F3FFE *)counters)->rva003F3FFE(*xfer);
	if (version.m_currentVersion == 3)
		Rva003F5729Xfer(xfer, (std::vector<ArmySummary> *)&m_records);
	else if (version.m_currentVersion >= 4) {
		UnsignedInt count = (UnsignedInt)m_records.size();
		(*xfer == count);
		if (xfer->IsLoading()) {
			m_records.clear();
			((Rva003F5A06 *)&m_records)->rva003F5C4F(count);
		}
		for(int i=0;i<m_records.size();++i) {
			ArmySummary *summary=&m_records[i];
			summary->v3(xfer);
		}
	}
}
