// ?iniParseFXListVec@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.98355 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include "ascii_string.h"
#include <vector>
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
class INI {public:const char*getNextToken(const char *seps=0);const char*getNextTokenOrNull(const char *seps=0);int getLineNum()const;AsciiString getFilename()const;};
class FXList;
class FXListStore {public:const FXList*findFXList(const char*)const;};
extern FXListStore *TheFXListStore;
namespace _STL {template<> void vector<const FXList*>::push_back(const FXList*const&);}
class Debug
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual Debug &operator<<(const char *value);
    virtual Debug &operator<<(int value);
    virtual Debug &operator<<(unsigned int value);
    virtual Debug &operator<<(unsigned char value);
    virtual Debug &operator<<(short value);
    virtual Debug &operator<<(unsigned short value);
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual bool CrashDone(int);
    virtual Debug &operator<<(float value);
 virtual void s50();virtual void s54();virtual void s58();virtual void s5C();
 virtual void SkipNext();virtual void s64();virtual void s68();
 virtual Debug& CrashBegin(int,int,int);
};


extern Debug *theDebug;
template<class T> Debug& operator<<(Debug&,const StringBase<T>&);
inline const StringBase<char>& FilenameBase(const AsciiString& s){return *reinterpret_cast<const StringBase<char>*>(&s);}
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
void iniParseFXListVec(INI *ini,void*,void*store,const void*) {
 _STL::vector<const FXList*>*v=static_cast<_STL::vector<const FXList*>*>(store);
 for(const char *token=ini->getNextToken();token;token=ini->getNextTokenOrNull()) {
  const FXList *fx=TheFXListStore->findFXList(token);
  v->push_back(fx);
  if(!fx && _strcmpi(token,"None"))
   !bfmeRva000387C0() || (_bfme_debugRecordCallsite(1),theDebug->SkipNext(),(theDebug->CrashBegin(0,0,0)<<"Unknown FX list "<<token<<" requested near line "<<static_cast<unsigned int>(ini->getLineNum())<<" of "<<reinterpret_cast<const StringBase<char>&>(ini->getFilename())).CrashDone(2));
 }
}
