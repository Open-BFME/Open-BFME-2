// ?InitializeAssetManager@@YA_NVAsciiString@@0_N@Z
// partial score=0.0 date=2026-10-09
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native0012CFA0..0012D295/757B; WB009D6590 InitializeAssetManager
// assetinit.cpp318..327; semantic/control-flow lead corroborated by retail.
// Both by-value inputs are AsciiString, not a UnicodeString second argument:
// two char releaseBuffer calls at12D273/27F and exported cross-charset ctor6CB6D0.
// No clean BF1/ZH assetinit.cpp exists. This draft has NOT been compiled:
// current master pins0bef414b but binding read-only checkout9cbfb551.
// The three builder flags and two archive magic pointers below are unpinned
// semantic names; original names/owners unknown, addresses separately evidenced.
// Cleanup provider12CA49 is declared cdecl for native no-ECX-setup call at12D265;
// current matched owner's unused-this view needs ABI/name reconciliation first.
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
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
void Rva0012CA49Run(); // unresolved until existing provider declaration reconciled
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
   char filename[256];
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
     if(_stricmp(filename+begin+1,"asset.dat")==0) {
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
