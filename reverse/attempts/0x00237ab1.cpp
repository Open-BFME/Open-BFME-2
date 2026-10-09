// ?rva00237AB1@GlobalData@@SAXPAVINI@@@Z
// partial score=0.9 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// BF1 f989 GlobalDataParseDefinition.cpp semantic donor; native237AB1..237CFC RET establishes588B parser ABI,1254B object and fieldsC/98/1240..1250. Mode5 is observed, original enum/name unknown. The static table spelling is carried from donor, not a target name fact.
#include "ascii_string.h"
#include "unicode_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#include <wchar.h>
extern "C" __declspec(dllimport) int __stdcall SHGetSpecialFolderPathW(void *,unsigned short *,int,int);
extern "C" __declspec(dllimport) int __stdcall CreateDirectoryW(const unsigned short *,void *);
struct FieldParse;
class INI {public: int getLoadType() const {return *(const int*)((const char*)this+8);} void initFromINI(void*,const FieldParse*);};
class GlobalData:public SubsystemInterface {public:
 GlobalData();virtual ~GlobalData();virtual void init();virtual void reset();virtual void update();virtual bool vslot04(int);virtual int vslot06();
 static GlobalData *newOverride();void applyOptionPreferences();static void rva00237AB1(INI*);
 static const FieldParse s_GlobalDataFieldParseTable[];
 AsciiString fieldC;char unknown10[0x98-0x10];float flag98;char unknown9C[0x1240-0x9C];
 AsciiString userDataDir;UnicodeString userDataDirUnicode;AsciiString picturePath;AsciiString userDataLeafName;GlobalData *next;
};
extern GlobalData *TheWritableGlobalData;
UnicodeString getUserDataLeafName();
void GlobalData::rva00237AB1(INI *ini) {
 bool flag=false;
 if(TheWritableGlobalData) {
  if(ini->getLoadType()==5) {
   AsciiString saved=TheWritableGlobalData->fieldC;
   if(TheWritableGlobalData->flag98!=0.0f)flag=true;
   ini->initFromINI(TheWritableGlobalData,s_GlobalDataFieldParseTable);
   TheWritableGlobalData->fieldC=saved;
   TheWritableGlobalData->flag98=(float)flag;
   TheWritableGlobalData->applyOptionPreferences();
   return;
  }
  if(ini->getLoadType()!=3 && ini->getLoadType()==2)TheWritableGlobalData->newOverride();
 } else TheWritableGlobalData=new GlobalData;
 ini->initFromINI(TheWritableGlobalData,s_GlobalDataFieldParseTable);
 TheWritableGlobalData->userDataDir.clear();TheWritableGlobalData->userDataDirUnicode.clear();TheWritableGlobalData->picturePath.clear();
 UnicodeString leaf=getUserDataLeafName();
 if(leaf.isEmpty())leaf.translate(TheWritableGlobalData->userDataLeafName);
 else TheWritableGlobalData->userDataLeafName.translate(leaf);
 unsigned short path[260];
 if(SHGetSpecialFolderPathW(0,path,0x1A,1)) {
  if(path[wcslen(path)-1]!=L'\\')wcscat(path,L"\\");
  wcscat(path,leaf.str());wcscat(path,L"\\");CreateDirectoryW(path,0);
  TheWritableGlobalData->userDataDirUnicode=path;
  TheWritableGlobalData->userDataDir.translate(path);
 }
 TheWritableGlobalData->applyOptionPreferences();
}
