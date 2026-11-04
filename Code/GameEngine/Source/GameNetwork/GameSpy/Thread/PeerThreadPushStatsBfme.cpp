// cl: /O1 /G7 /MD /EHsc /Oy-
// stlport
// BF1 PeerThread room statistics is the semantic guide. Native38AF29..38B1BB
// WB F665D0 names pushStatsToRoom and shows BF2 strategic/open-play selection.
// Target vslot30 returns the owned548B aggregate; vslot7C returns the profile
// id; vslot168 is didPlayerPreorder. Their original method names are uncertain.
// Static room key/value/buffer names and singleton names retain existing owners.
// ABI record views match independently owned PersistentStorageThread.cpp
// 154B core,190B open-play,208B strategic,548B aggregate; payload stays opaque.
// stlport
#include <stdio.h>

#include "../../../../Include/GameNetwork/Rva00553E47StatsCore.h"
#include "../../../../Include/GameNetwork/Rva003844D7.h"
#include "../../../../Include/GameNetwork/Rva0038454E.h"
class PSPlayerAllStats{public:~PSPlayerAllStats();Rva003844D7 rva00389DF1()const;Rva0038454E rva00389E0F()const;private:char fields[0x548];};
class Rva005537BA{public:unsigned short rva005537BA();};class Rva005537EB{public:unsigned short rva005537EB();};class Rva00553D26{public:unsigned char rva00553D26();};
class Rva00559D0CRankWeights{public:int rva00559E48(const Rva00553E47StatsCore*)const;int rva00559DA0(const Rva00553E47StatsCore*,int)const;private:char table[0x34];};
extern Rva00559D0CRankWeights g_00E05FCC,g_00E06000;
class GameSpyMiscPreferences{public:GameSpyMiscPreferences();virtual ~GameSpyMiscPreferences();int rva00559782();private:char fields[0x10];};
#define S(n) virtual void slot##n();
class GameSpyPSMessageQueueInterface{public:S(0)S(1)S(2)S(3)S(4)S(5)S(6)S(7)S(8)S(9)S(10)S(11)virtual PSPlayerAllStats get(int);};
#undef S
#include "../../../../Include/GameNetwork/GameSpyStagingRoom.h"
#include "../../../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyPSMessageQueueInterface*TheGameSpyPSMessageQueue;extern GameSpyInfoInterface*TheGameSpyInfo;extern GameSpyStagingRoom*TheGameSpyGame;

void dispatchIndexedValue(void*,int,void*,int,int*,int*);
struct PeerLogin{char*data,*finish,*end;const char*c_str()const{return data;}};
// Login string at +0x54 and the publishing flag at +0x94 (the canonical m_054/m_094).
struct BfmePeerPushState{unsigned char unknown[0x54];PeerLogin login;unsigned char gap60[0x34];bool publishing;};
#include "../../../../Include/GameNetwork/GameSpy/PeerThreadClass.h"
void PeerThreadClass::pushStatsToRoom(void*peer){
 BfmePeerPushState*state=reinterpret_cast<BfmePeerPushState*>(this);
 if(!TheGameSpyPSMessageQueue||!TheGameSpyInfo)return;
 PSPlayerAllStats all=TheGameSpyPSMessageQueue->get(TheGameSpyInfo->getLocalProfileID());
 Rva0038454E strategic(0);Rva003844D7 open(0);
 strategic=all.rva00389E0F();open=all.rva00389DF1();state->publishing=true;
 if(!TheGameSpyGame)return;
 Rva00553E47StatsCore*stats=0;
 switch(TheGameSpyGame->m_field5C){case 1:stats=&strategic;break;case 0:stats=&open;break;default:return;}
 GameSpyMiscPreferences preferences;
 bool premium=TheGameSpyInfo->didPlayerPreorder(TheGameSpyInfo->getLocalProfileID());
 _snprintf(s_valueBuffers[0],20,"%d",preferences.rva00559782());
 _snprintf(s_valueBuffers[1],20,"%d",reinterpret_cast<Rva005537BA*>(stats)->rva005537BA());
 _snprintf(s_valueBuffers[2],20,"%d",reinterpret_cast<Rva005537EB*>(stats)->rva005537EB());
 if(TheGameSpyGame->m_field5C==1){int key=g_00E05FCC.rva00559E48(stats);_snprintf(s_valueBuffers[6],20,"%d",key);_snprintf(s_valueBuffers[3],20,"%d",g_00E05FCC.rva00559DA0(stats,key));}
 else if(TheGameSpyGame->m_field5C==0){int key=g_00E06000.rva00559E48(stats);_snprintf(s_valueBuffers[6],20,"%d",key);_snprintf(s_valueBuffers[3],20,"%d",g_00E06000.rva00559DA0(stats,key));}
 _snprintf(s_valueBuffers[4],20,"%d",reinterpret_cast<Rva00553D26*>(stats)->rva00553D26());
 _snprintf(s_valueBuffers[5],20,"%d",premium);
 dispatchIndexedValue(peer,1,(void*)state->login.c_str(),7,reinterpret_cast<int*>(s_keys),reinterpret_cast<int*>(s_values));dispatchIndexedValue(peer,2,(void*)state->login.c_str(),7,reinterpret_cast<int*>(s_keys),reinterpret_cast<int*>(s_values));state->publishing=false;
}
