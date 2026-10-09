// ?rva0005522C@MilesAudioManager@@QAEXABVAsciiString@@@Z
// partial score=0.6714901960784314 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD
#include "ascii_string.h"
struct ReverbRoom {const char *name;int type;};
static const ReverbRoom s_reverbRooms[26]={
{"None",0},
{"Padded Cell",1},
{"Room",2},
{"Bathroom",3},
{"Living Room",4},
{"Stone Room",5},
{"Auditorium",6},
{"Concert Hall",7},
{"Cave",8},
{"Arena",9},
{"Hangar",10},
{"Carpeted Hallway",11},
{"Hallway",12},
{"Stone Corridor",13},
{"Alley",14},
{"Forest",15},
{"City",16},
{"Mountains",17},
{"Quarry",18},
{"Plain",19},
{"Parking Lot",20},
{"Sewer Pipe",21},
{"Underwater",22},
{"Drugged",23},
{"Dizzy",24},
{"Psychotic",25},
};
class MilesMutexGuard {public:MilesMutexGuard(void *,int);~MilesMutexGuard();void *mutex;bool held;};
class MilesAudioManager {
public:
 virtual ~MilesAudioManager();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual void slot090();
 virtual void slot91();
 void rva0005522C(const AsciiString &name);
 void internalSetReverbRoomType(int);
 char at04[0x9D4-4];void *m_mutex;
 char at9D8[0xBE4-0x9D8];int m_atBE4;
};
void MilesAudioManager::rva0005522C(const AsciiString &name)
{
 MilesMutexGuard guard(&m_mutex,0);
 if(name.compareNoCase("Hanger")==0) {
  m_atBE4=10;internalSetReverbRoomType(10);
 } else {
  int type=-1;
  for(unsigned int i=0;i<26;++i) {
   if(name.compareNoCase(s_reverbRooms[i].name)==0) {type=s_reverbRooms[i].type;break;}
  }
  if(type!=-1) {m_atBE4=type;internalSetReverbRoomType(type);}
  else slot91();
 }
}
