// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?InitializeAssetManager@@YA_NVAsciiString@@0_N@Z @0x0012CFA0 757B
// Evidence: WB 009D6590 InitializeAssetManager (assetinit.cpp:318..327);
// retail confirms two by-value AsciiString inputs (char releaseBuffer calls at
// 0x12D273/0x12D27F, cross-charset UnicodeString ctor 0x6CB6D0) and a bool
// skipTextures. BIGF/BIG4 archive magic pointers (0xDB61EC/F0 -> BD22F0/E8)
// and the three builder flags (DB61E8..EA) are named from their use here;
// the original names are not proven. filename is a 260 byte buffer (retail
// frame 0x124). Cleanup provider 0x12CA49 is a free cdecl function (its only
// caller makes the call with no ECX setup).
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#undef _strcmpi
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern AsciiString g_00DEE93C;
extern bool AssetInitRunTextureBuilder; // native VA DB61E8
extern bool AssetInitRunModelBuilder;   // native VA DB61E9
extern bool AssetInitRunShaderBuilder;  // native VA DB61EA
extern const char *AssetInitArchiveMagicF; // native DB61EC points BD22F0 BIGF
extern const char *AssetInitArchiveMagic4; // native DB61F0 points BD22E8 BIG4
void Create_Rva00972880_Prototype();
bool Rva0012CAC3Run(); bool Rva0012C99DRun(); bool Rva0012CB15Run();
bool Rva0012CB67(FILE *,bool);
void forwardRegistrySettingRva0061F1A0(unsigned,int);
void Rva0012CA49Run();
bool InitializeAssetManager(AsciiString directory,AsciiString archive,bool skipTextures)
{
 g_00DEE93C=directory;
 Create_Rva00972880_Prototype();
 if(!skipTextures) {
  if(AssetInitRunModelBuilder) Rva0012CAC3Run();
  if(AssetInitRunShaderBuilder) Rva0012C99DRun();
 }
 if(AssetInitRunTextureBuilder) Rva0012CB15Run();
 if(!archive.isEmpty()) {
  UnicodeString name(archive);
  FILE *f=_wfopen(reinterpret_cast<const wchar_t *>(name.str()),L"rb");
  if(f) {
   char filename[260];
   fread(filename,4,1,f);filename[4]=0;
   if(strcmp(filename,AssetInitArchiveMagicF)==0 || strcmp(filename,AssetInitArchiveMagic4)==0) {
    unsigned fileSize=0; int entryCount=0;
    fread(&fileSize,4,1,f);fread(&entryCount,4,1,f);
    entryCount=htonl(entryCount);
    fseek(f,16,SEEK_SET);
    int entry=0;
    for(;entry<entryCount;++entry) {
     unsigned entrySize=0,entryOffset=0;
     fread(&entryOffset,4,1,f);fread(&entrySize,4,1,f);
     entrySize=htonl(entrySize);entryOffset=htonl(entryOffset);
     int last=-1;
     do {++last;fread(&filename[last],1,1,f);} while(filename[last]);
     int begin=last;
     while(begin>=0 && filename[begin]!='\\' && filename[begin]!='/') --begin;
     if(_strcmpi(filename+begin+1,"asset.dat")==0) {
      fseek(f,entryOffset,SEEK_SET);break;
     }
    }
    if(entry<entryCount) Rva0012CB67(f,skipTextures);
   }
   fclose(f);
  }
 }
 if(!directory.isEmpty()) {
  UnicodeString name(directory);name+=reinterpret_cast<const unsigned short *>(L"\\asset.dat");
  FILE *f=_wfopen(reinterpret_cast<const wchar_t *>(name.str()),L"rb");
  if(f) {Rva0012CB67(f,skipTextures);fclose(f);}
 }
 FILE *f=fopen("asset.dat","rb");
 if(!f) return false;
 bool ok=Rva0012CB67(f,skipTextures);fclose(f);
 if(!ok) return false;
 forwardRegistrySettingRva0061F1A0(0,0);
 Rva0012CA49Run();
 return true;
}

