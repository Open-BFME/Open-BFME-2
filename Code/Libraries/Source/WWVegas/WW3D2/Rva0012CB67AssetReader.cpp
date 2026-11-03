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
// Suppress this TU's non-retail copy of ??0?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_Rb_tree(const less<Rva001408C0Target *> &, const allocator<Rva001408C0Target *> &); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::_Rb_tree_base(const allocator<Rva001408C0Target *> &); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_erase(_Rb_tree_node<Rva001408C0Target *> *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *, size_t) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEPAU?$_Rb_tre:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@U12@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t); }
// The row calls the set constructor out of line; bind it to retail's copy at 0x000D3A71.
namespace _STL { template <> set<Rva001408C0Target *, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::set(); }
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
class FXShaderAsset
{
public:
	static void Register(const char *);
};
void Rva001806D8Create(const char *,int,int);
void Rva001804CBCreate(const char *,int,int);
void Rva001800B2Create(const char *,int,int);
void Rva0017FD2F_RegisterPrototype(const char *,int,int);
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"
void RegisterDependencies(void *,void *);
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
    case 'ANIM': Register_Aggregate_Prototype(assetName,asset.firstOffset,nameLen);break;
    case 'AGGR': Rva00180C6FCreate(assetName,asset.firstOffset,nameLen);break;
    case 'FXSH': FXShaderAsset::Register(assetName);break;
    case 'TEX': if(skipTextures)break;TextureAsset::Register(assetName);break;
    case 'BOX': Rva001809EACreate(assetName,asset.firstOffset,nameLen);break;
    case 'PART': Rva001806D8Create(assetName,asset.firstOffset,nameLen);break;
    case 'MESH': Rva001804CBCreate(assetName,asset.firstOffset,nameLen);break;
    case 'HLOD': Rva001800B2Create(assetName,asset.firstOffset,nameLen);break;
    case 'HIER': Rva0017FD2F_RegisterPrototype(assetName,asset.firstOffset,nameLen);break;
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
  if(!dependencies.assets.empty())RegisterDependencies(parentName,&dependencies);
  }
  --counts.parentCount;
 }
 return counts.groupCount==0 && counts.parentCount==0;
}

