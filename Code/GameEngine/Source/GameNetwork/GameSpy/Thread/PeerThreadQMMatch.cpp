// cl: /D_CRTIMP= /Ireference/shims/bfmealloc /O1 /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Donor6583b3c1 PeerHandleQMMatch supplies purpose and six-array ABI.
// Native38B6C1/502, independently called by playerMessage38C05E, witnesses
// thread status294, login54 and response payload10C, including port13C and
// unnamed sixth numeric array1AC. Names for the sixth field remain unknown.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include "PreRTS.h"
#include "PeerThreadRetail.h"
namespace AtoiIAT { extern "C" __declspec(dllimport) int __cdecl atoi(const char *); }
extern "C" void peerLeaveRoomA(PEER, int, const char *);
extern "C" void peerMessagePlayerA(PEER, const char *, const char *, MessageType);
#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=??0BfmeOpaqueOwnedRecord840@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=??1BfmeOpaqueOwnedRecord840@@QAE@XZ")
struct BfmeLoginThread { unsigned char unknown[0x54]; std::string name; };
struct BfmeQMThread { unsigned char unknown[0x294]; QMStatus status; };
class PeerThreadClass { public:
 void handleQMMatch(PEER,Int,Int,char *[MAX_SLOTS],char *[MAX_SLOTS],
 char *[MAX_SLOTS],char *[MAX_SLOTS],char *[MAX_SLOTS],char *[MAX_SLOTS]);
};
void PeerThreadClass::handleQMMatch(PEER peer,Int mapIndex,Int seed,
 char *playerName[MAX_SLOTS],char *playerIP[MAX_SLOTS],char *playerSide[MAX_SLOTS],
 char *playerColor[MAX_SLOTS],char *playerNAT[MAX_SLOTS],char *playerExtra[MAX_SLOTS])
{
 if(reinterpret_cast<BfmeQMThread *>(this)->status==QM_WORKING) {
  reinterpret_cast<BfmeQMThread *>(this)->status=QM_MATCHED;
  peerLeaveRoomA(peer,1,"");
  Int i;
  for(i=0;i<MAX_SLOTS;++i) {
   if(playerName[i] && _strcmpi(playerName[i],reinterpret_cast<BfmeLoginThread *>(this)->name.c_str()))
    peerMessagePlayerA(peer,playerName[i],"We're matched!",NormalMessage);
  }
  PeerResponse resp;
  resp.peerResponseType=PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
  resp.qmStatus.status=QM_MATCHED;
  for(i=0;i<MAX_SLOTS;++i) {
   if(playerName[i]) {
    resp.stagingRoomPlayerNames[i]=playerName[i];
    resp.qmStatus.IP[i]=AtoiIAT::atoi(playerIP[i]);
    resp.qmStatus.port[i]=8088+i;
    resp.qmStatus.side[i]=AtoiIAT::atoi(playerSide[i]);
    resp.qmStatus.color[i]=AtoiIAT::atoi(playerColor[i]);
    resp.qmStatus.nat[i]=AtoiIAT::atoi(playerNAT[i]);
    resp.qmStatus.extra[i]=AtoiIAT::atoi(playerExtra[i]);
   } else {
    resp.stagingRoomPlayerNames[i]="";
    resp.qmStatus.IP[i]=0;
    resp.qmStatus.side[i]=0;
    resp.qmStatus.color[i]=0;
    resp.qmStatus.nat[i]=0;
    resp.qmStatus.extra[i]=-1;
   }
  }
  resp.qmStatus.seed=seed;
  resp.qmStatus.mapIdx=mapIndex;
  TheGameSpyPeerMessageQueue->addResponse(resp);
 }
}
