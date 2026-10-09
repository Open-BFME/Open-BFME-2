// cl: /O1 /G7 /MD /EHsc /Oy-
// BF1 PeerThread room statistics is the semantic guide. Native38AF29..38B1BB
// WB F665D0 names pushStatsToRoom and shows BF2 strategic/open-play selection.
// Target vslot30 returns the owned548B aggregate; vslot7C returns the profile
// id; vslot168 returns one byte. Their original method names are uncertain.
// Static room key/value/buffer names and singleton names retain existing owners.
// ABI record views match independently owned PersistentStorageThread.cpp
// 154B core,190B open-play,208B strategic,548B aggregate; payload stays opaque.
extern "C" __declspec(dllimport) int _snprintf(char*,unsigned,const char*,...);
class Rva00553E47StatsCore{public:virtual void reset();virtual void xfer0(void*);virtual void xfer1(void*);virtual void merge(const Rva00553E47StatsCore*);private:char payload[0x150];};
class Rva003844D7:public Rva00553E47StatsCore{public:Rva003844D7(int);Rva003844D7(const Rva003844D7&);~Rva003844D7();Rva003844D7&operator=(const Rva003844D7&);private:char tail[0x3c];};
class Rva0038454E:public Rva00553E47StatsCore{public:Rva0038454E(int);Rva0038454E(const Rva0038454E&);~Rva0038454E();Rva0038454E&operator=(const Rva0038454E&);private:char tail[0xb4];};
class PSPlayerAllStats{public:~PSPlayerAllStats();Rva003844D7 rva00389DF1()const;Rva0038454E rva00389E0F()const;private:char fields[0x548];};
class Rva005537BA{public:unsigned short rva005537BA();};class Rva005537EB{public:unsigned short rva005537EB();};class Rva00553D26{public:unsigned char rva00553D26();};
class Rva00559D0CRankWeights{public:int rva00559E48(const Rva00553E47StatsCore*)const;int rva00559DA0(const Rva00553E47StatsCore*,unsigned char)const;private:char table[0x34];};
extern Rva00559D0CRankWeights g_00E05FCC,g_00E06000;
class GameSpyMiscPreferences{public:GameSpyMiscPreferences();virtual ~GameSpyMiscPreferences();int rva00559782();private:char fields[0x10];};
#define S(n) virtual void slot##n();
class GameSpyPSMessageQueueInterface{public:S(0)S(1)S(2)S(3)S(4)S(5)S(6)S(7)S(8)S(9)S(10)S(11)virtual PSPlayerAllStats get(int);};
class GameSpyInfoInterface{public:
S(0)S(1)S(2)S(3)S(4)S(5)S(6)S(7)S(8)S(9)S(10)S(11)S(12)S(13)S(14)S(15)S(16)S(17)S(18)S(19)S(20)S(21)S(22)S(23)S(24)S(25)S(26)S(27)S(28)S(29)S(30)virtual int getLocalProfileID();
S(32)S(33)S(34)S(35)S(36)S(37)S(38)S(39)S(40)S(41)S(42)S(43)S(44)S(45)S(46)S(47)S(48)S(49)S(50)S(51)S(52)S(53)S(54)S(55)S(56)S(57)S(58)S(59)S(60)S(61)S(62)S(63)S(64)S(65)S(66)S(67)S(68)S(69)S(70)S(71)S(72)S(73)S(74)S(75)S(76)S(77)S(78)S(79)S(80)S(81)S(82)S(83)S(84)S(85)S(86)S(87)S(88)S(89)virtual bool premium(int);};
#undef S
class GameSpyStagingRoom{public:char gap[0x5c];int type;};
extern GameSpyPSMessageQueueInterface*TheGameSpyPSMessageQueue;extern GameSpyInfoInterface*TheGameSpyInfo;extern GameSpyStagingRoom*TheGameSpyGame;

void dispatchIndexedValue(void*,int,void*,int,int*,int*);
struct PeerLogin{char*data,*finish,*end;const char*c_str()const{return data;}};
class PeerThreadClass{private:static const char*s_keys[9],*s_values[9];static char s_valueBuffers[9][20];public:void pushStatsToRoom(void*);char gap[0x54];PeerLogin login;char gap60[0x34];bool publishing;};
void PeerThreadClass::pushStatsToRoom(void*peer){
 if(!TheGameSpyPSMessageQueue||!TheGameSpyInfo)return;
 PSPlayerAllStats all=TheGameSpyPSMessageQueue->get(TheGameSpyInfo->getLocalProfileID());
 Rva0038454E strategic(0);Rva003844D7 open(0);
 strategic=all.rva00389E0F();open=all.rva00389DF1();publishing=true;
 if(!TheGameSpyGame)return;
 Rva00553E47StatsCore*stats=0;
 switch(TheGameSpyGame->type){case 1:stats=&strategic;break;case 0:stats=&open;break;default:return;}
 GameSpyMiscPreferences preferences;
 bool premium=TheGameSpyInfo->premium(TheGameSpyInfo->getLocalProfileID());
 _snprintf(s_valueBuffers[0],20,"%d",preferences.rva00559782());
 _snprintf(s_valueBuffers[1],20,"%d",reinterpret_cast<Rva005537BA*>(stats)->rva005537BA());
 _snprintf(s_valueBuffers[2],20,"%d",reinterpret_cast<Rva005537EB*>(stats)->rva005537EB());
 if(TheGameSpyGame->type==1){int key=g_00E05FCC.rva00559E48(stats);_snprintf(s_valueBuffers[6],20,"%d",key);_snprintf(s_valueBuffers[3],20,"%d",g_00E05FCC.rva00559DA0(stats,key));}
 else if(TheGameSpyGame->type==0){int key=g_00E06000.rva00559E48(stats);_snprintf(s_valueBuffers[6],20,"%d",key);_snprintf(s_valueBuffers[3],20,"%d",g_00E06000.rva00559DA0(stats,key));}
 _snprintf(s_valueBuffers[4],20,"%d",reinterpret_cast<Rva00553D26*>(stats)->rva00553D26());
 _snprintf(s_valueBuffers[5],20,"%d",premium);
 dispatchIndexedValue(peer,1,(void*)login.c_str(),7,reinterpret_cast<int*>(s_keys),reinterpret_cast<int*>(s_values));dispatchIndexedValue(peer,2,(void*)login.c_str(),7,reinterpret_cast<int*>(s_keys),reinterpret_cast<int*>(s_values));publishing=false;
}
