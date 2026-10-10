// ?loadUserMaps@MapCache@@QAE_NXZ
// partial score=1.0 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// BFME1 575ba2b04 MapCacheLoadUserMaps semantic guide. Target30529C..305749
// includes the native invalid-map reporting branch and full INI catch continuation.
#include <map>
#include <set>
#include <string.h>
#include "ascii_string.h"
namespace _STL {template<class T,class L,class R>static inline bool operator!=(const _Rb_tree_iterator<T,L>&a,const _Rb_tree_iterator<T,R>&b){return a._M_node!=b._M_node;}}
struct BfmeStringNoCaseLess{bool operator()(const AsciiString&,const AsciiString&)const;};
typedef _STL::set<AsciiString,BfmeStringNoCaseLess> FilenameList;
struct TreeHintPayload00207343{unsigned char value;TreeHintPayload00207343():value(0){}};
typedef _STL::map<AsciiString,TreeHintPayload00207343> SeenMap;
namespace _STL{template<>TreeHintPayload00207343&SeenMap::operator[](const AsciiString&);}
class Rva00206667{public:void rva00206F6B();};
class MapMetaData{char storage[256];};
struct FileInfo{unsigned sizeHigh,sizeLow,timestampHigh,timestampLow;};
class File{public:virtual void slot0();virtual void slot1();virtual void close();};
class FileSystem{public:File*openFile(const char*,int,int);void getFileListInDirectory(const AsciiString&,const AsciiString&,FilenameList&,bool)const;bool getFileInfo(const AsciiString&,FileInfo*)const;};extern FileSystem*TheFileSystem;
class GlobalData{public:char pad[0xAB5];bool buildMapCache;};extern GlobalData*TheWritableGlobalData;
class Xfer;enum INILoadType{INI_LOAD_INVALID,INI_LOAD_OVERWRITE,INI_LOAD_CREATE_OVERRIDES,INI_LOAD_MULTIFILE};
class INI{public:INI();~INI();void load(AsciiString,INILoadType,Xfer*,void(*)(INI*));static void parseMapCacheDefinition(INI*);private:char storage[0x87C];};
class Rva00300489{public:virtual AsciiString rva00300489()const;};
class Rva00300D7A{public:AsciiString rva00300D7A();};
class Rva003004A5{public:virtual AsciiString rva003004A5()const;};
class Debug{public:class Format{public:Format(const char*,...);private:char text[0x200];};};
class RvaLoadUserReport{public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual RvaLoadUserReport*setText(const char*);virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void show(int);
 RvaLoadUserReport&operator<<(const Debug::Format&v){setText((const char*)&v);return *this;}
};
class RvaLoadUserDebug{public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void beginReport();virtual void s25();virtual void s26();virtual RvaLoadUserReport*getReport(int,int,int);
};extern Debug*theDebug;
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
class MapCache:public _STL::map<AsciiString,MapMetaData>{public:bool loadUserMaps();bool addMap(AsciiString,AsciiString,FileInfo*,bool);private:bool clearUnseenMaps(AsciiString);SeenMap m_seen;_STL::set<AsciiString>m_allowedMaps;};
bool MapCache::loadUserMaps(){
 AsciiString mapDir;
 if(TheWritableGlobalData->buildMapCache)mapDir=((const Rva00300489*)this)->Rva00300489::rva00300489();
 else{
  mapDir=((Rva00300D7A*)this)->rva00300D7A();
  INI ini;AsciiString fname;fname.format("%s\\%s",mapDir.str(),"MapCache.ini");
  File*fp=TheFileSystem->openFile(fname.str(),1,0);
  if(fp){fp->close();try{ini.load(fname,INI_LOAD_OVERWRITE,0,INI::parseMapCacheDefinition);}catch(...) {}}
 }
 ((Rva00206667*)&m_seen)->rva00206F6B();
 iterator it=begin();while(it!=end()){m_seen[it->first].value=0;++it;}
 FilenameList::iterator iter;FilenameList filenameList;AsciiString toplevelPattern;
 toplevelPattern.format("%s\\",mapDir.str());bool parsedAMap=false;AsciiString filenamepattern;
 filenamepattern.format("*.%s",((const Rva003004A5*)this)->Rva003004A5::rva003004A5().str());
 TheFileSystem->getFileListInDirectory(toplevelPattern,filenamepattern,filenameList,true);
 iter=filenameList.begin();while(iter!=filenameList.end()){
  FileInfo fileInfo;AsciiString tempfilename;tempfilename=*iter;tempfilename.toLower();
  const char*s=tempfilename.reverseFind('\\');
  if(s){
   AsciiString endingStr;AsciiString fname=s+1;
   for(unsigned i=0;i<strlen(".map");++i)fname.removeLastChar();
   endingStr.format("%s\\%s%s",fname.str(),fname.str(),".map");
   bool skipMap=false;
   if(TheWritableGlobalData->buildMapCache){_STL::set<AsciiString>::const_iterator sit=m_allowedMaps.find(fname);if(m_allowedMaps.size()!=0&&sit==m_allowedMaps.end())skipMap=true;}
   if(!skipMap){
    if(!tempfilename.endsWithNoCase(endingStr.str())){
     if(bfmeRva000387C0()){
      _bfme_debugRecordCallsite(1);((RvaLoadUserDebug*)theDebug)->beginReport();
      const char*badname=tempfilename.str();const char*expected=fname.str();
      RvaLoadUserReport*out=((RvaLoadUserDebug*)theDebug)->getReport(0,0,0);
      (*out<<Debug::Format("Found map '%s' in wrong spot (%s)",expected,badname)).show(2);
     }
    }else if(TheFileSystem->getFileInfo(tempfilename,&fileInfo)){
     char funk[260];strcpy(funk,tempfilename.str());char*filenameptr=funk;char*tempchar=funk;
     while(*tempchar!=0){if(*tempchar=='\\'||*tempchar=='/')filenameptr=tempchar+1;++tempchar;}
     if(strlen(filenameptr)<0x50){m_seen[tempfilename].value=1;parsedAMap|=addMap(mapDir,*iter,&fileInfo,TheWritableGlobalData->buildMapCache);}
    }
   }
  }
  ++iter;
 }
 if(clearUnseenMaps(mapDir))return true;return parsedAMap;
}
