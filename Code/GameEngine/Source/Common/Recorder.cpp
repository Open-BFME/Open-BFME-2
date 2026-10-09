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
class GameSlot { public: char pad000[0x38]; BfmeNetAddress address;char pad40[0x60-0x40];bool heroPresent;char pad61[3]; };
class GameInfo {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9(); virtual void slot10();virtual void slot11();virtual void slot12();virtual int getLocalSlotNum();
    int field0004;int field0008; int m_crcInterval;
    char pad010[0x38-0x10]; BfmeNetAddress address;
    GameSlot *getSlot(int);
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
