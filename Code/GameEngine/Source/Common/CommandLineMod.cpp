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
template<class T> class StringBase {
    friend class AsciiString;
    friend class UnicodeString;
    struct Header { int refs; unsigned short length,capacity; T data[1]; };
    Header *data;
    StringBase(const T*);
    StringBase(const StringBase&);
    void releaseBuffer();
public:
    StringBase():data(0){}
    ~StringBase(){ releaseBuffer(); }
    const T* find(T) const;
    bool startsWith(const T*) const;
    bool endsWith(const T*) const;
    const T* str() const { static const T TheNullChr = 0; return data ? data->data : &TheNullChr; }
    void set(const StringBase&);
    void concat(const T*,int);
    void concat(T c) { concat(&c,1); }
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class AsciiString:public StringBase<char> {
public:
    AsciiString(const char *s):StringBase<char>(s){}
    AsciiString& operator=(const UnicodeString&);
};
class UnicodeString:public StringBase<Wide> {
public:
    UnicodeString(const AsciiString&);
    UnicodeString(const UnicodeString& s):StringBase<Wide>(s){}
    UnicodeString& operator=(const UnicodeString& s){set(s);return *this;}
};
struct BFME2WideConcatPair {
    const UnicodeString *a,*b;
    BFME2WideConcatPair(const UnicodeString& x,const UnicodeString& y){b=&y;a=&x;}
    operator StringBase<Wide>();
};
inline BFME2WideConcatPair operator+(const UnicodeString& a,const UnicodeString& b) {
    return BFME2WideConcatPair(a,b);
}
class GlobalData {
public:
    char prefix[0xd38];
    AsciiString m_modDir,m_modBIG;
    UnicodeString rva002360FC() const;
};
class BFME2FileSystemFacade { public: bool doesWideFileExist(const Wide*); };
extern GlobalData *TheWritableGlobalData;
// ?BFME2FileFacade@@3PAVBFME2FileSystemFacade@@A: the global at this VA is ?TheFileSystem@@3PAVFileSystem@@A; this name is an alias for it.
extern BFME2FileSystemFacade * BFME2FileFacade;
#pragma comment(linker, "/alternatename:?BFME2FileFacade@@3PAVBFME2FileSystemFacade@@A=?TheFileSystem@@3PAVFileSystem@@A")
extern bool BFME2PreferLocalFiles;
int parseMod(char *args[],int num) {
    BFME2PreferLocalFiles=true;
    if(TheWritableGlobalData && num>1) {
        UnicodeString modPath((AsciiString(args[1])));
        if(modPath.find(':') || modPath.startsWith((const Wide*)L"/") || modPath.startsWith((const Wide*)L"\\")) {
        } else {
            modPath.set(TheWritableGlobalData->rva002360FC()+modPath);
        }
        if(!BFME2FileFacade->doesWideFileExist(modPath.str())) return 2;
        struct _stat statBuf;
        if(_wstat(modPath.str(),&statBuf)!=0) return 2;
        if(statBuf.st_mode & _S_IFDIR) {
            if(!modPath.endsWith((const Wide*)L"\\") && !modPath.endsWith((const Wide*)L"/")) modPath.concat('\\');
            TheWritableGlobalData->m_modDir=modPath;
        } else {
            TheWritableGlobalData->m_modBIG=modPath;
        }
        return 2;
    }
    return 1;
}
