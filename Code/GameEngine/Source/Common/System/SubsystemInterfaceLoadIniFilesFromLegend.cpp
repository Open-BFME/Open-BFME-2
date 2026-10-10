// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/ini_bfme2 /Ireference/shims/subsystem_bfme2 /Ireference/open-bfme-1/game/GameEngine/Include /Ireference/open-bfme-1/game/GameEngine/Include/Precompiled /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/GameEngine/Source/Common/System
// stlport
// Semantic guide: BF1 575ba2b04 Libraries/Source/subsystem/SubsystemInterface.cpp.
// Native1B5384..1B552E426B and base vtable7D77A0 slot2 establish identity.
// Target adds mithril verification, exclusion and conditional cinematic paths,
// byte load results and type1/5 selection. Record offsets are independently
// established by the target LoadSubsystem schema and72B ctor/copy/dtor owners.
#include <vector>
#include "PreRTS.h"
#include "subsystem_interface.h"
#include "Common/INI/INI.h"
#include "ascii_string.h"
struct IniLoadFileList;
class SubsystemLegend {public:IniLoadFileList *rva001B49C4(AsciiString);};
extern SubsystemLegend *TheSubsystemLegend;
struct BfmeLegendLoadRecord {
 AsciiString name;_STL::vector<AsciiString> files,paths,extensions,cinematicPaths,excludePaths;
 unsigned loader;AsciiString debugFile;
};
struct BfmeSubsystemLoadXfer {char prefix[0x24];Xfer *xfer;};
class FileSystem {public:bool doesFileExist(const char*)const;};
extern FileSystem *TheFileSystem;
class CopyProtect {public:static void setVerified(bool);};
struct Rva0002C5E6Range {const StringBase<char> *begin,*end;};
bool Rva0002C5E6(const StringBase<char>&,const Rva0002C5E6Range*);
// Target global byte atDFD944 controls adding Cinematics paths to the exclusion filter.
// Its original name is unknown; this descriptive name claims only that use.
bool skipCinematicSubsystemExclusions;
Bool SubsystemInterface::loadIniFilesFromLegend(){
 CopyProtect::setVerified(TheFileSystem && TheFileSystem->doesFileExist("mithriledition.txt"));
 if(!TheSubsystemLegend)return false;
 Bool loaded=false;
 AsciiString name=m_name;
 BfmeLegendLoadRecord *entry=reinterpret_cast<BfmeLegendLoadRecord*>(TheSubsystemLegend->rva001B49C4(name));
 if(!entry)return false;
 _STL::vector<AsciiString> excluded;
 for(AsciiString *p=entry->excludePaths.begin();p!=entry->excludePaths.end();++p)excluded.push_back(*p);
 if(!skipCinematicSubsystemExclusions)
  for(AsciiString *p=entry->cinematicPaths.begin();p!=entry->cinematicPaths.end();++p)excluded.push_back(*p);
 INI ini;
 Bool flag=m_flag; INILoadType type=(INILoadType)(flag?5:1);
 for(AsciiString *p=entry->files.begin();p!=entry->files.end();++p){
  if(!Rva0002C5E6(reinterpret_cast<const StringBase<char>&>(*p),reinterpret_cast<const Rva0002C5E6Range*>(&excluded)))
   if(ini.loadFile(*p,type,reinterpret_cast<BfmeSubsystemLoadXfer*>(TheSubsystemList)->xfer))loaded=true;
 }
 for(AsciiString *p=entry->paths.begin();p!=entry->paths.end();++p)
  if(ini.loadDirectory(*p,true,type,reinterpret_cast<BfmeSubsystemLoadXfer*>(TheSubsystemList)->xfer,reinterpret_cast<int>(&excluded)))loaded=true;
 return loaded;
}
