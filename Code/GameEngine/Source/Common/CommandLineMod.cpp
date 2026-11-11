// EA BFME1 CommandLine.cpp parseMod, adapted to BFME2 Unicode paths.
// Live -mod table81FB60 identifies3BA348..3BA4DA, complete403B.
// BFME2WideConcatPair and BFME2FileSystemFacade are descriptive ABI types,
// not claims about original source spelling. Pair materializer21C3F7 (98B)
// sums two referenced lengths then copies UTF-16 payloads into a new string.
// Facade60068A (11B) forwards via E06E5C vslot10; ctor604A5F establishes
// vtable C7A9A8 whose slot4 target604873 tests _waccess(path,0)==0.
// UnicodeString narrow ctor6CB6D0 has an explicit retail export. The PE
// import table independently names _wstat at BBA4AC and _waccess at BBA400.
// cl: /DNDEBUG /MD /EHs
#include <sys/stat.h>
typedef unsigned short Wide;
class AsciiString;
class UnicodeString;
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct BFME2WideConcatPair {
    const UnicodeString *a,*b;
    BFME2WideConcatPair(const UnicodeString& unicodeString,const UnicodeString& y){b=&y;a=&unicodeString;}
    operator UnicodeString();
};
inline BFME2WideConcatPair operator+(const UnicodeString& a,const UnicodeString& b) {
    return BFME2WideConcatPair(a,b);
}
#include "../../Include/Common/GlobalData.h"
#include "../../Include/Common/BFME2FileSystemFacade.h"
extern GlobalData *TheWritableGlobalData;
class FileSystem;
extern FileSystem *TheFileSystem;
extern bool BFME2PreferLocalFiles;
int parseMod(char *args[],int num) {
    BFME2PreferLocalFiles=true;
    if(TheWritableGlobalData && num>1) {
        UnicodeString modPath((AsciiString(args[1])));
        if(modPath.find(':') || modPath.startsWith((const Wide*)L"/") || modPath.startsWith((const Wide*)L"\\")) {
        } else {
            modPath = TheWritableGlobalData->rva002360FC()+modPath;
        }
        if(!((BFME2FileSystemFacade *)TheFileSystem)->doesWideFileExist(modPath.str())) return 2;
        struct _stat statBuf;
        if(_wstat(modPath.str(),&statBuf)!=0) return 2;
        if(statBuf.st_mode & _S_IFDIR) {
            if(!modPath.endsWith((const Wide*)L"\\") && !modPath.endsWith((const Wide*)L"/")) { Wide sep = '\\'; modPath.concat(&sep, 1); }
            TheWritableGlobalData->m_modDir=modPath;
        } else {
            TheWritableGlobalData->m_modBIG=modPath;
        }
        return 2;
    }
    return 1;
}
