// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/sweep /O1 /G7 /MD /EHsc
// BFME1 donor9cbfb551fe20dae985f91f2319d8997287b6a705:
// game/GameEngine/Source/Common/System/RecorderStartRecording.cpp and
// RecorderLogGameStart.cpp. ZH Recorder.cpp supplies their purpose; WB
// F57070/F54AE0 independently names startRecording/logGameStart.
// Native37C57E..37CBB6 is1592B including the catch funclet37CAD7 and
// continuation37CB16; the inventory1369B stops at that embedded handler.
// RET10 proves four argument slots. Target accesses prove the wide path,
// mode1C, FILE10, embeddedGameInfo24 and CRC fieldsE60/E64. Hero serialization
// (slot60 flag/64 object; CreateAHeroData virtual slot3; XferSave40B) is a
// BFME2 addition reconstructed from target calls, offsets and catch data.
// Address names retain uncertainty for unnamed providers and fields.
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>
void __cdecl operator delete[](void*);
void* __cdecl operator new[](unsigned int);

class FileSystem {public:bool rva0037BD2B(const UnicodeString &);};extern FileSystem*TheFileSystem;
UnicodeString Rva0037B9D4Get(); UnicodeString GetLastReplayDisplayName(); UnicodeString Rva0037BA48Get();

class GameTextInterface {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12();virtual void slot13();virtual void slot14();
    virtual UnicodeString fetch(const char *, bool *exists=0);
};
extern GameTextInterface *TheGameText;
class Version { public: UnicodeString getFullUnicodeVersion(); UnicodeString getUnicodeBuildTime(); };
extern Version *TheVersion;
class GlobalData {public:char p0[0xb04];unsigned int field0b04;char pB08[0x1100-0xb08];bool field1100;char p1101[3];int field1104;};
extern GlobalData *TheWritableGlobalData;
struct BfmeNetAddress { unsigned int address,port;bool Rva00248CBF(const BfmeNetAddress*) const;};
// Target compares the complete address through rowed248CBF; donor IP-only
// comparison would omit the port. Native GameSlot/GameInfo address is38.
class CreateAHeroData;
class GameSlot { public: char pad000[0x38]; BfmeNetAddress address;char pad40[0x60-0x40];bool heroPresent;char pad61[3];void rva0037AD8D(const CreateAHeroData&); };;
class GameInfo {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9(); virtual void reset();virtual void startGame(int);virtual void slot12();virtual int getLocalSlotNum();
    int field0004;int field0008; int m_crcInterval;
    char pad010[0x38-0x10]; BfmeNetAddress address;
    GameSlot *getSlot(int);const GameSlot *getConstSlot(int) const;void enterGame();void endGame();
    void setCRCInterval(int n) { m_crcInterval = n < 100 ? n : 100; }
};
class GameSpyStagingRoom : public GameInfo {};
class LANAPI {public:
virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual void slot16();virtual void slot17();virtual void slot18();virtual void slot19();virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();virtual void slot24();virtual void slot25();virtual void slot26();virtual void slot27();virtual void slot28();virtual void slot29();virtual void slot30();virtual void slot31();virtual void slot32();virtual void slot33();virtual void slot34();virtual void slot35();virtual void slot36();virtual void slot37();virtual void slot38();virtual void slot39();virtual void slot40();virtual void slot41();virtual void slot42();virtual void slot43();virtual void slot44();virtual void slot45();virtual void slot46();virtual void slot47();virtual void slot48();virtual void slot49();virtual void slot50();virtual void slot51();virtual void slot52();virtual void slot53();virtual void slot54();virtual void slot55();virtual GameInfo *GetMyGame();};
class NetworkInterface;
extern NetworkInterface *TheNetwork;
extern LANAPI *TheLAN;
extern GameSpyStagingRoom *TheGameSpyGame;
class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;
extern int NET_CRC_INTERVAL;
AsciiString GameInfoToAsciiString(const GameInfo *, bool=true);

class Xfer { public: virtual ~Xfer();};
class XferSave { public:XferSave();virtual ~XferSave(); unsigned char Open(Xfer*,int,bool);void close();char tail[0x3c];};
class CreateAHeroData {public:virtual void s0();virtual void s1();virtual void s2();virtual void xfer(Xfer*);CreateAHeroData&operator=(const CreateAHeroData&);};
class Rva00219251 {public:CreateAHeroData *rva00219251(int,int,int,const UnicodeString&,int,int,int);void rva0021929D(CreateAHeroData**);};
extern Rva00219251 *TheCreateAHeroManager;
class BfmeMade_009CB5F0;
BfmeMade_009CB5F0*bfmeMake_009CB5F0(void*);
class BfmeThingEC {public:int bfmeTakeEC(int*);};
extern GameInfo *TheGameInfo;
class Debug {public:
virtual void p0();virtual void p1();virtual void p2();virtual void p3();virtual void p4();virtual void p5();virtual void p6();virtual void p7();virtual void p8();virtual void p9();virtual void p10();virtual void p11();virtual void p12();virtual void p13();virtual Debug&operator<<(const char*);virtual void p15();virtual void p16();virtual void p17();virtual void p18();virtual bool CrashDone(int);virtual void p20();virtual void p21();virtual void p22();virtual void p23();virtual void SkipNext();virtual void p25();virtual void p26();virtual Debug&CrashBegin(const char*,int,int);};
extern Debug *theDebug;void _bfme_debugRecordCallsite(int);
class RecorderClass {
public:
virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void reset();
 char pad004[0x10-4];FILE*m_file;UnicodeString m_fileName;int field0018;int m_mode;int field0020;
 GameInfo m_gameInfo;char padGameInfo[0xe60-0x24-sizeof(GameInfo)];int field0e60,field0e64;
protected:
 void logGameStart(AsciiString);
 void startRecording(int difficulty,int gameMode,int rankPoints,int maxFPS);
};

void RecorderClass::startRecording(int difficulty, int gameMode, int rankPoints, int maxFPS)
{
    reset();
    m_mode = 0;
    UnicodeString filepath = Rva0037B9D4Get();
    TheFileSystem->rva0037BD2B(filepath);
    m_fileName = GetLastReplayDisplayName();
    m_fileName += Rva0037BA48Get();
    filepath += m_fileName;
    m_file = _wfopen((const wchar_t*)filepath.str(), L"w+b");
    if (!m_file) return;
    fprintf(m_file, "BFME2RPL");
    unsigned int t=0;
    fwrite(&t,4,1,m_file); fwrite(&t,4,1,m_file);
    unsigned int frames=0;
    fwrite(&frames,4,1,m_file);
    fwrite(&field0e60,4,1,m_file); fwrite(&field0e64,4,1,m_file);
    bool b=false;
    fwrite(&b,1,1,m_file);
    for (int i=0;i<8;++i) fwrite(&b,1,1,m_file);
    UnicodeString replayName;
    replayName = TheGameText->fetch("GUI:LastReplay");
    fwprintf(m_file,L"%ws",replayName.str()); fputwc(0,m_file);
    SYSTEMTIME systemTime;
    GetLocalTime(&systemTime); fwrite(&systemTime,sizeof(systemTime),1,m_file);
    UnicodeString versionString=TheVersion->getFullUnicodeVersion();
    UnicodeString versionTimeString=TheVersion->getUnicodeBuildTime();
    fwprintf(m_file,L"%ws",versionString.str()); fputwc(0,m_file);
    fwprintf(m_file,L"%ws",versionTimeString.str()); fputwc(0,m_file);
    fwrite(&TheWritableGlobalData->field0b04,4,1,m_file);
    fwrite(&TheWritableGlobalData->field1100,1,1,m_file);
    fwrite(&TheWritableGlobalData->field1104,4,1,m_file);
    fpos_t position;
    fgetpos(m_file,&position);
    AsciiString theSlotList;
    int localIndex=-1;
    if (TheNetwork) {
        if (TheLAN) {
            GameInfo *game=TheLAN->GetMyGame();
            theSlotList=GameInfoToAsciiString(game);
            for (int i=0;i<8;++i) {
                GameSlot *slot=game->getSlot(i);
                if (game->address.Rva00248CBF(&slot->address)) { localIndex=i; break; }
            }
        } else {
            theSlotList=GameInfoToAsciiString(TheGameSpyGame);
            localIndex=TheGameSpyGame->getLocalSlotNum();
        }
    } else {
        if (TheSkirmishGameInfo) {
            reinterpret_cast<GameInfo *>(TheSkirmishGameInfo)->setCRCInterval(NET_CRC_INTERVAL);
            theSlotList=GameInfoToAsciiString(reinterpret_cast<GameInfo *>(TheSkirmishGameInfo));
            localIndex=0;
        } else {
            m_gameInfo.setCRCInterval(NET_CRC_INTERVAL);
            theSlotList=GameInfoToAsciiString(&m_gameInfo);
        }
    }
    logGameStart(theSlotList);
    fwrite(theSlotList.str(),theSlotList.getLength()+1,1,m_file);
    fprintf(m_file,"%d",localIndex); fputc(0,m_file);
    if(TheGameInfo) {
     CreateAHeroData*hero=TheCreateAHeroManager->rva00219251(0,0,0,UnicodeString::TheEmptyString,-1,0xff707070,-1);
     for(unsigned i=0;i<8;++i) {
      GameSlot*slot=TheGameInfo->getSlot(i);
      bool hasHero=(slot->heroPresent?(CreateAHeroData*)((char*)slot+0x64):0)!=0;fwrite(&hasHero,1,1,m_file);
      if(hasHero) {
       *hero=*(slot->heroPresent?(CreateAHeroData*)((char*)slot+0x64):0);
       BfmeMade_009CB5F0*memory=bfmeMake_009CB5F0((void*)"heroString");
       XferSave writer;
       try {writer.Open((Xfer*)memory,1,false);}catch(...) {
        _bfme_debugRecordCallsite(1);theDebug->SkipNext();(theDebug->CrashBegin(0,0,0)<<"ERROR: Could not open Hero Memory file, in Replay!!!").CrashDone(1);return;
       }
       hero->xfer((Xfer*)&writer);writer.close();int length;int data=((BfmeThingEC*)memory)->bfmeTakeEC(&length);
       fwrite(&length,4,1,m_file);fwrite((void*)data,length,1,m_file);
       // The released buffer uses the game's array deallocator2FD80.
       // MSVC's delete[] expression on char* selected scalar delete2FD60.
       operator delete[] ((void*)data);
      }
     }
     TheCreateAHeroManager->rva0021929D(&hero);
    }
    fwrite(&difficulty,4,1,m_file); fwrite(&gameMode,4,1,m_file);
    fwrite(&rankPoints,4,1,m_file); fwrite(&maxFPS,4,1,m_file);
}

// Target time() and fwrite() use the same persistent timestamp at VA E0228C.
// Donor source calls it startTime; the target does not independently name it.
static time_t startTime;

void RecorderClass::logGameStart(AsciiString options)
{
	if (!m_file)
		return;

	time(&startTime);
	unsigned int fileSize = ftell(m_file);
	if (!fseek(m_file, 8, 0))
		fwrite(&startTime, sizeof(time_t), 1, m_file);
	fseek(m_file, fileSize, 0);
}

// Replay-header reader: clean BFME1 RecorderReadReplayHeader.cpp donor at
//9cbfb551 gives the IO and game-info sequence; WB F58540 names this target.
// Native37CBB6..37D076 is1216B, including the catch cleanup37CF51 and
// continuation37CF85. Target calls and reads prove the wide path and
// header fields; header dtor37B5DF independently proves all six strings.
// Original names of the late header fields remain unknown. The Rva receiver
// and method spellings preserve the existing caller37D0EF's typed binding.
// BFME2 hero deserialization is target reconstruction; no donor claim for it.
class Rva0037B5DF {
public:
 int start,end,frame,crcInterval,mode;
 bool quitEarly,disconnected[8];char pad1D[3];
 AsciiString options;int localIndex;UnicodeString filename;bool forPlayback;char pad2D[3];
 UnicodeString name;SYSTEMTIME time;UnicodeString version,versionTime;
 unsigned int crc4C;bool flag50;char pad51[3];int word54;UnicodeString str58;
};
class Rva0037BBED {
public:
 char head[0x10];FILE*m_file;char gap14[0x10];GameInfo m_gameInfo;
 char gap64[0xe60-0x24-sizeof(GameInfo)];int m_crcInterval,m_mode,m_numPlayers,m_localIndex;
 UnicodeString rva0037BCA8();AsciiString rva0037B70A();bool rva0037CBB6(Rva0037B5DF&);
};
class File {public:virtual void p0();virtual void p1();virtual void close();};
File*createMemoryReadFile(char*,int);
struct Rva0060C3C3Stream;
struct XferLoad {bool Open(Rva0060C3C3Stream*,int*);};
class Rva0060C5FA : public Xfer {public:Rva0060C5FA(void*,void*,void*);char tail[28];};
class Rva0060C45E {public:void clear();};
bool ParseAsciiStringToGameInfo(GameInfo*,AsciiString,bool) throw();

bool Rva0037BBED::rva0037CBB6(Rva0037B5DF&header) {
 UnicodeString filepath;
 if(header.filename.find('\\'))filepath=header.filename;
 else {filepath=Rva0037B9D4Get();filepath+=header.filename;}
 m_file=_wfopen((const wchar_t*)filepath.str(),L"rb");
 if(!m_file)return false;
 char genrep[9];fread(genrep,1,8,m_file);genrep[8]=0;
 if(strncmp(genrep,"BFME2RPL",8)!=0){fclose(m_file);m_file=0;return false;}
 fread(&header.start,4,1,m_file);fread(&header.end,4,1,m_file);fread(&header.frame,4,1,m_file);
 fread(&header.crcInterval,4,1,m_file);m_crcInterval=header.crcInterval;
 fread(&header.mode,4,1,m_file);m_mode=header.mode;
 fread(&header.quitEarly,1,1,m_file);
 for(int i=0;i<8;++i)fread(&header.disconnected[i],1,1,m_file);
 header.name=rva0037BCA8();fread(&header.time,16,1,m_file);
 header.version=rva0037BCA8();header.versionTime=rva0037BCA8();
 fread(&header.crc4C,4,1,m_file);fread(&header.flag50,1,1,m_file);fread(&header.word54,4,1,m_file);
 fpos_t pos;fgetpos(m_file,&pos);
 header.options=rva0037B70A();
 GameInfo*gameInfo=&m_gameInfo;gameInfo->reset();gameInfo->enterGame();
 if(!ParseAsciiStringToGameInfo(gameInfo,header.options,true)){fclose(m_file);m_file=0;return false;}
 gameInfo->startGame(0);
 AsciiString playerIndex=rva0037B70A();header.localIndex=atoi(playerIndex.str());
 CreateAHeroData*hero=TheCreateAHeroManager->rva00219251(0,0,0,UnicodeString::TheEmptyString,-1,0xff707070,-1);
 for(unsigned i=0;i<8;++i) {
  bool hasHero=false;fread(&hasHero,1,1,m_file);
  if(hasHero) {
   int length;fread(&length,4,1,m_file);char*data=(char*)operator new[](length);fread(data,length,1,m_file);
   File*memory=createMemoryReadFile(data,length);
   Rva0060C5FA reader(0,0,0);
   GameSlot*slot=gameInfo->getSlot(i);
   try {
    int unused;
    if(((XferLoad*)&reader)->Open((Rva0060C3C3Stream*)memory,&unused)){hero->xfer((Xfer*)&reader);slot->rva0037AD8D(*hero);}
   }catch(...) {
    if(hero)TheCreateAHeroManager->rva0021929D(&hero);
    operator delete[](data);((Rva0060C45E*)&reader)->clear();memory->close();return false;
   }
   operator delete[](data);((Rva0060C45E*)&reader)->clear();memory->close();
  }
 }
 TheCreateAHeroManager->rva0021929D(&hero);
 if(header.localIndex< -1 || header.localIndex>=8){gameInfo->endGame();gameInfo->reset();fclose(m_file);m_file=0;return false;}
 if(header.localIndex>=0){GameSlot*slot=m_gameInfo.getSlot(header.localIndex);m_gameInfo.address=slot->address;}
 if(!header.forPlayback){gameInfo->endGame();gameInfo->reset();fclose(m_file);m_file=0;}
 // Reload the embedded view after the address-copy and playback branches.
 // This preserves the native pointer/counter allocation for the final scan.
 gameInfo=&m_gameInfo;
 m_numPlayers=0;
 for(int i=0;i<8;++i)if(*(const int*)((const char*)gameInfo->getConstSlot(i)+4)==6)++m_numPlayers;
 m_localIndex=header.localIndex;return true;
}
