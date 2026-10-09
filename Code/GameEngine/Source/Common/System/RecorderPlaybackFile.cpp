// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BFME1 9cbfb551 System/RecorderPlaybackFile.cpp semantic lead.
// Native37D1E6..37D3C9,483B; Unicode by-value filename is witnessed at
// GameEngine::init and the existing playbackFile pin. BFME1 supplies purpose
// and sequence; retail supplies fields24/C/E70/E74, seed74, MessageStream48,
// TheGameInfo assignment and saved GlobalData1100/1104 values. Unknown
// callee identities retain their existing address-derived ABI views.
// Header5C has the six inline null string slots and existing out-of-line dtor.
// CRC state constructor37D076 consumes12B; only local-player field08 is used.
// Saved values are TU statics, independently inferred from the native stores.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../GameLogicObjectLookupView.h"
struct FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *,unsigned int,unsigned int,FILE *);
class Rva0037B5DF {public:
 ~Rva0037B5DF();
 int startTime,endTime;unsigned int duration;int interval,mode;bool quitEarly,discons[8];char gap1D[3];
 AsciiString options20;int player24;UnicodeString filename28;bool forPlayback2C;char gap2D[3];
 UnicodeString name30;char time34[16];UnicodeString version44,versionTime48;unsigned int iniCRC4C;
 bool desync50;char gap51[3];unsigned int tail54;UnicodeString string58;
};
class Rva0037BBED {public:bool rva0037CBB6(Rva0037B5DF &);};
class Rva0037B7C7 {public:void rva0037B7C7();};
class Rva0037D076 {public:
 Rva0037D076();unsigned char mismatch,skipped;char gap02[2];void *list04;int localPlayer08;
};
class GameInfo {public:
 AsciiString getMap()const;
 char unknown00[0xc];int crcInterval;char unknown10[0x50-0x10];
 unsigned int seed;char unknown54[0xe3c-0x54];
};
class GlobalData {public:
 char unknown00[0xac0];AsciiString pendingFile;
 char unknownAC4[0x1100-0xac4];unsigned char flag1100;char unknown1101[3];int value1104;
};
class GameMessage {public:
 enum Type {NEW_GAME=0x1e};void appendIntegerArgument(int);
};
class MessageStream {public:
#define V(n) virtual void v##n();
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
 V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
#undef V
 virtual GameMessage *appendMessage(GameMessage::Type);
};
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
extern GameInfo *TheGameInfo;
extern MessageStream *TheMessageStream;
int REPLAY_CRC_INTERVAL;
static int recorderSavedGlobalValue;
static unsigned char recorderSavedGlobalFlag;
void InitRandom(unsigned int);
class RecorderClass {public:
 bool playbackFile(UnicodeString filename);
 char unknown00[0xc];Rva0037D076 *crcInfo;FILE *file;
 UnicodeString path14;char unknown18[4];int mode;UnicodeString currentReplayFilename;
 GameInfo gameInfo;int interval,originalMode,playerCount,localPlayer;
 bool doingAnalysis;char unknownE71[3];int recordedMode;
};
bool RecorderClass::playbackFile(UnicodeString filename)
{
 if(!doingAnalysis)TheGameLogic->rva00376E92(false,false);
 mode=1;
 Rva0037B5DF header;
 header.forPlayback2C=true;header.filename28=filename;
 bool success=reinterpret_cast<Rva0037BBED *>(this)->rva0037CBB6(header);
 if(!success)return false;
 recorderSavedGlobalFlag=TheWritableGlobalData->flag1100;
 recorderSavedGlobalValue=TheWritableGlobalData->value1104;
 TheWritableGlobalData->flag1100=header.desync50;
 TheWritableGlobalData->value1104=header.tail54;
 TheWritableGlobalData->pendingFile=gameInfo.getMap();
 crcInfo=new Rva0037D076;
 crcInfo->localPlayer08=header.player24;
 REPLAY_CRC_INTERVAL=gameInfo.crcInterval;
 int difficulty=0;fread(&difficulty,4,1,file);
 fread(&recordedMode,4,1,file);
 int rankPoints=0;fread(&rankPoints,4,1,file);
 int maxFPS=0;fread(&maxFPS,4,1,file);
 reinterpret_cast<Rva0037B7C7 *>(this)->rva0037B7C7();
 if(!doingAnalysis){
  TheGameInfo=&gameInfo;
  GameMessage *message=TheMessageStream->appendMessage(GameMessage::NEW_GAME);
  message->appendIntegerArgument(3);
  message->appendIntegerArgument(difficulty);
  message->appendIntegerArgument(rankPoints);
  if(maxFPS!=0)message->appendIntegerArgument(maxFPS);
  InitRandom(gameInfo.seed);
 }
 currentReplayFilename=filename;
 return true;
}
