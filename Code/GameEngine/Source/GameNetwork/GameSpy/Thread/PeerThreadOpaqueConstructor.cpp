// cl: /O1 /G7 /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// BF1 PeerThreadConstructor clean f98983a7d donor; target38AAEB662,
// startThread allocation4B0 and vtableC1989C support opaque worker identity.
// Native field addresses plus owned aggregate destructor38ADE2 define layout.
// Donor member purposes are leads rather than independently proved target names;
// target-only additions remain unknown words. Existing integer-tree provider
// is reused for its proved three-pointer ABI, with no key/value identity claim.
#include <string>
#include <map>
#include <string.h>
class MutexClass;
class __declspec(novtable) ThreadClass{public:ThreadClass(const char*);virtual ~ThreadClass();virtual void Execute();protected:virtual void Thread_Function()=0;private:char pad[0x4c];};
struct BfmeOpaqueOwnedRecord492{BfmeOpaqueOwnedRecord492();~BfmeOpaqueOwnedRecord492();char bytes[492];};
struct Rva0037BF60Less{bool operator()(int,int)const;};
typedef _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,Rva0037BF60Less,_STL::allocator<_STL::pair<const int,int> > > WorkerTree;
namespace _STL {template<> WorkerTree::_Rb_tree();template<> map<string,int>::map();}
class Rva00388EAE:public WorkerTree{public:~Rva00388EAE();void rva00389129();};
class Rva0038AAEBThreadObject:public ThreadClass{public:Rva0038AAEBThreadObject(MutexClass*);virtual ~Rva0038AAEBThreadObject();virtual void Execute();virtual void Thread_Function();
 bool isConnecting,isConnected;char pad52[2];std::string loginName,originalName,password,email;
 int profileID,groupRoomID;bool sawComplete;char pad8d[3];int unknown90;bool unknown94;char pad95[3];
 std::map<std::string,int> groupStats,stagingStats;
 bool isHosting,hasPassword;char padb2[2];std::string mapName;int unknownC0;std::string openStaging,names[8];
 int crcWords[4],unknown140,unknown144,otherWords[4],unknown158;bool useStats;char pad15d[3];std::string ping,ladderIP;unsigned short ladderPort;char pad17a[2];
 int wins[8],profiles[8],unknownPlayers[8],colors[8],factions[8],losses[8];int numPlayers,maxPlayers,numObservers,unknown248[10],unknown270,nextServer;
 Rva00388EAE servers;std::wstring serverName;int roomID,qmStatus;BfmeOpaqueOwnedRecord492 record;
 bool roomJoined;char pad485[3];void*peer;bool sawEnd,sawBot;char pad48e[2];std::string botName;
 bool unknown49c;char pad49d[3];int unknown4a0,unknown4a4;bool unknown4a8;char pad4a9[3];MutexClass*lock;
};
typedef char WorkerExtent[sizeof(Rva0038AAEBThreadObject)==0x4b0?1:-1];
Rva0038AAEBThreadObject::Rva0038AAEBThreadObject(MutexClass*p):ThreadClass(0),lock(p){
 hasPassword=false;useStats=false;roomJoined=false;
 memset(crcWords,0,sizeof crcWords);unknown144=0;unknown140=0;memset(otherWords,0,sizeof otherWords);
 unknown158=0;ladderPort=0;roomID=0;numObservers=0;numPlayers=1;maxPlayers=8;peer=0;
 sawEnd=sawBot=false;sawComplete=false;qmStatus=0;isConnecting=isConnected=false;unknown90=0;groupRoomID=profileID=0;
 nextServer=1;servers.rva00389129();ping="";mapName="";ladderIP="";isHosting=false;unknownC0=0;openStaging="openstaging";
 for(int i=0;i<8;++i){names[i]="";colors[i]=0;factions[i]=0;losses[i]=0;profiles[i]=0;unknownPlayers[i]=0;wins[i]=0;}
 unknown49c=false;unknown4a0=0;unknown4a4=0;unknown4a8=false;memset(unknown248,0,sizeof unknown248);unknown270=0;unknown94=false;
}
