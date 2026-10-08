// cl: /O1 /Oa /G7 /arch:SSE /MD /EHs /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common
// stlport
// MainMenuUtils companion unit: keep the independently verified settings
// of the 900-byte callback without changing sibling list/callback bodies.
#include "ascii_string.h"
#include "MainMenuOnlineState.h"
#include <string>
#define online g_mainMenuOnlineState
enum GHTTPBool {GHTTPFalse,GHTTPTrue};
enum GHTTPResult {GHTTPSuccess};
GHTTPBool configCallback(int,GHTTPResult,char *,__int64,void *);
void b_00042a50();void startOnline();
void *__cdecl operator new[](unsigned);void __cdecl operator delete[](void *);
class GlobalData {public:AsciiString rva002360DE() const;};
extern GlobalData *TheWritableGlobalData;
class File {public:
 virtual ~File();virtual bool open(const char *,int);virtual void close();
 virtual int read(void *,int);virtual int write(const void *,int);
 virtual void seek();virtual void nextLine();virtual void scanInt();virtual void scanReal();
 virtual void scanString();virtual void print();virtual int size();
};
class FileSystem {public:File *openFile(const char *,int,int);};
extern FileSystem *TheFileSystem;
// BFME1 34f59164 configHeadCallback; native 5BCC77..5BCFFB (900B). A
// cached Config.txt of the advertised Content-Length is reloaded through
// TheFileSystem (its size from File::size) instead of fopen; otherwise the
// config is fetched blocking, as BFME2 passes GHTTPTrue to ghttpGet. The
// second open reuses the first fname (native 5BCE39 reads it, not the new
// one). /EHs: retail keeps EH states around the url strings' C free calls
// (5BCF20..5BCF62). /Oa: the donor's state is file-static, so retail loads
// File's vftable before storing the config pointer (5BCF83..5BCF8A).
extern "C" const char *__cdecl ghttpGetHeaders(int request);
typedef GHTTPBool (*ghttpCompletedCallback)(int,GHTTPResult,char *,__int64,void *);
extern "C" int __cdecl ghttpGetA(const char *URL,GHTTPBool blocking,ghttpCompletedCallback completedCallback,void *param);
namespace MainMenuCRT { extern "C" __declspec(dllimport) int __cdecl atoi(const char *); }
void FormatURLFromRegistry(_STL::string &gameURL,_STL::string &mapURL,_STL::string &configURL,_STL::string &motdURL);
GHTTPBool configHeadCallback(int request,GHTTPResult result,char *buffer,__int64 bufferLen,void *param)
{
 if((int)param!=online.run)return GHTTPTrue;
 if(result==GHTTPSuccess){
  AsciiString headers(ghttpGetHeaders(request));
  AsciiString line;
  while(headers.nextToken(&line,"\n\r")){
   AsciiString key,val;
   line.nextToken(&key,": ");
   line.nextToken(&val,": \r\n");
   if(key.compare("Content-Length")==0 && !val.isEmpty()){
    int serverLen=MainMenuCRT::atoi(val.str());
    int fileLen=0;
    AsciiString fname;
    fname.format("%s%s\\Config.txt",TheWritableGlobalData->rva002360DE().str(),"Online Files");
    File *fp=TheFileSystem->openFile(fname.str(),0x41,0);
    if(fp){fileLen=fp->size();fp->close();}
    if(serverLen==fileLen){
     --online.checks;
     if(online.cancel && online.checks==0){b_00042a50();online.cancel=false;}
     if(online.config){delete[] online.config;online.config=0;}
     AsciiString fname2;
     fname2.format("%s%s\\Config.txt",TheWritableGlobalData->rva002360DE().str(),"Online Files");
     fp=TheFileSystem->openFile(fname.str(),0x41,0);
     if(fp){
      fp->read(online.config=new char[fileLen],fileLen);
      online.config[fileLen-1]=0;
      fp->close();
      if(online.checks==0)startOnline();
      return GHTTPTrue;
     }
    }
   }
  }
 }
 _STL::string gameURL,mapURL;
 _STL::string configURL,motdURL;
 FormatURLFromRegistry(gameURL,mapURL,configURL,motdURL);
 ghttpGetA(configURL.c_str(),GHTTPTrue,configCallback,param);
 return GHTTPTrue;
}

