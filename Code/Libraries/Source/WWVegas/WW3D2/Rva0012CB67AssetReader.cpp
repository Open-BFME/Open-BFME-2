// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva0012CB67@@YA_NPAU_iobuf@@_N@Z @0x0012CB67 1081B
// Codegen: the FXSH case must precede the TEXT case in source; MSVC 7.1 then
// merges the shared pop-ecx tails into the earlier (texture) copy as retail does.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdio.h>
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <set>
// Native12CB67..12CFA0/1081B. WB9D5C30 assetinit.cpp lines54..145 is
// an independent debug semantic lead (larger assertions), with matching
// FILE reads, EALA/102 header, asset registration and dependency collection.
// No source counterpart exists in the readonly BFME1 or ZH source trees.
// Existing named or address-derived providers establish their own identity;
// this parser's original name is unknown. Opaque records remain opaque.
bool Render_Obj_Exists(const char *);
void Register_Aggregate_Prototype(const char *,int,int);
void Rva00180C6FCreate(const char *,int,int);
void Rva001809EACreate(const char *,int,int);
void Rva001516C1RegisterPrototype(const char *);
void Rva001806D8Create(const char *,int,int);
void Rva001804CBCreate(const char *,int,int);
void Rva001800B2Create(const char *,int,int);
void Rva0017FD2F_RegisterPrototype(const char *,int,int);
class TextureAsset { public: static void Register(const char *); };
void bfmeInvokeResourceEnumeration(void *,void *);
struct Rva001408C0Target;
class Rva0006C995 {public:Rva0006C995 *rva0006C995(Rva001408C0Target *);};
struct Q1ReceiverLocalSet {
 _STL::set<Rva001408C0Target *,_STL::less<Rva001408C0Target *>,_STL::allocator<Rva001408C0Target *> > assets;
 int unknown0c;bool changed;
 // ?Q1ReceiverLocalSet::Q1ReceiverLocalSet present-unmatched
 Q1ReceiverLocalSet():unknown0c(0),changed(true){}
 // ?Q1ReceiverLocalSet::~Q1ReceiverLocalSet present-unmatched
 ~Q1ReceiverLocalSet(){}
};
bool Rva0012CB67(_iobuf *file,bool skipTextures)
{
 struct HeaderValues {unsigned assetKind,magic,version;} header;
 struct Counts {unsigned parentCount,groupCount,dependencyCount;} counts;
 char groupName[264],assetName[256],parentName[256],dependencyName[256];
 unsigned nameLen;
 struct AssetCounts {unsigned assetCount,firstOffset;} asset;
 unsigned parentNameLen,dependencyLen;
 setvbuf(file,0,0,0x200000);
 if(fread(&header.magic,4,1,file)!=1 || header.magic!=0x45414C41 ||
    fread(&header.version,4,1,file)!=1 || header.version!=0x102 ||
    fread(&counts.groupCount,4,1,file)!=1 || fread(&counts.parentCount,4,1,file)!=1){
  fclose(file);return false;
 }
 while(counts.groupCount){
  asset.assetCount=0;
  if(fread(&asset.assetCount,1,1,file)!=1)break;
  fread(groupName,asset.assetCount+8,1,file);
  if(fread(&asset.assetCount,2,1,file)!=1)break;
  while(asset.assetCount){
   nameLen=0;
   if(fread(&nameLen,1,1,file)!=1)break;
   if(fread(assetName,nameLen,1,file)!=1)break;
   assetName[nameLen]=0;
   if(fread(&header.assetKind,4,1,file)!=1)break;
   if(fread(&asset.firstOffset,4,1,file)!=1)break;
   if(fread(&nameLen,4,1,file)!=1)break;
   _strlwr(assetName);
   if(!Render_Obj_Exists(assetName)){
    switch(header.assetKind){
    case 0x414E494D: Register_Aggregate_Prototype(assetName,asset.firstOffset,nameLen);break;
    case 0x41474752: Rva00180C6FCreate(assetName,asset.firstOffset,nameLen);break;
    case 0x46585348: Rva001516C1RegisterPrototype(assetName);break;
    case 0x544558: if(skipTextures)break;TextureAsset::Register(assetName);break;
    case 0x424F58: Rva001809EACreate(assetName,asset.firstOffset,nameLen);break;
    case 0x50415254: Rva001806D8Create(assetName,asset.firstOffset,nameLen);break;
    case 0x4D455348: Rva001804CBCreate(assetName,asset.firstOffset,nameLen);break;
    case 0x484C4F44: Rva001800B2Create(assetName,asset.firstOffset,nameLen);break;
    case 0x48494552: Rva0017FD2F_RegisterPrototype(assetName,asset.firstOffset,nameLen);break;
    }
   }
   --asset.assetCount;
  }
  if(asset.assetCount)break;
  --counts.groupCount;
 }
 while(counts.parentCount){
  parentNameLen=0;
  if(fread(&parentNameLen,1,1,file)!=1)break;
  if(fread(parentName,parentNameLen,1,file)!=1)break;
  if(fread(&parentNameLen,1,1,file)!=1)break;
  if(fread(parentName,parentNameLen,1,file)!=1)break;
  parentName[parentNameLen]=0;
  if(!Render_Obj_Exists(parentName))break;
  {
  Q1ReceiverLocalSet dependencies;
  counts.dependencyCount=0;
  if(fread(&counts.dependencyCount,2,1,file)!=1)break;
  while(counts.dependencyCount){
   dependencyLen=0;
   if(fread(&dependencyLen,1,1,file)!=1)break;
   if(fread(dependencyName,dependencyLen,1,file)!=1)break;
   dependencyName[dependencyLen]=0;
   if(Render_Obj_Exists(parentName))
    reinterpret_cast<Rva0006C995 *>(&dependencies)->rva0006C995(reinterpret_cast<Rva001408C0Target *>(dependencyName));
   --counts.dependencyCount;
  }
  if(counts.dependencyCount)break;
  if(!dependencies.assets.empty())bfmeInvokeResourceEnumeration(parentName,&dependencies);
  }
  --counts.parentCount;
 }
 return counts.groupCount==0 && counts.parentCount==0;
}

