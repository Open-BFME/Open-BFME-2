// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BF1 GlobalLanguageInitBfme.cpp@575ba2b04 supplies font-install semantics.
// Native1EA55A..1EA77F and GlobalLanguage vtable7DEFC8 slot1 establish init.
// Native replaces donor locale probing with language.ini and uses INI87C,
// local-font list138 and a directory GUID shared with onGameEngineExit.
#include <list>
#include <string.h>
#include "ascii_string.h"
typedef void *HANDLE;typedef void *HMODULE;typedef unsigned long DWORD;typedef int BOOL;
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char*);
extern "C" __declspec(dllimport) void * __stdcall GetProcAddress(HMODULE,const char*);
extern "C" __declspec(dllimport) BOOL __stdcall FreeLibrary(HMODULE);
extern "C" __declspec(dllimport) DWORD __stdcall GetTempPathA(DWORD,char*);
extern "C" __declspec(dllimport) BOOL __stdcall CreateDirectoryA(const char*,void*);
extern "C" __declspec(dllimport) DWORD __stdcall GetTempFileNameA(const char*,const char*,DWORD,char*);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(const char*,DWORD,DWORD,void*,DWORD,DWORD,HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall WriteFile(HANDLE,const void*,DWORD,DWORD*,void*);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall DeleteFileA(const char*);
extern const char BfmeFontExtractionDirectoryName[]="{70FF7DF1-E69E-47df-9AA6-F062FADD6146}";
const char *BfmeFontExtractionDirectory=BfmeFontExtractionDirectoryName;
class Xfer;
enum INILoadType{INI_LOAD_INVALID,INI_LOAD_OVERWRITE};
class INI{public:INI();~INI();unsigned char loadFile(AsciiString,INILoadType,Xfer*);private:char bytes[0x87C];};
class File{public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();
 virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual int size();virtual void v12();virtual char *readEntireAndClose();
 char unknown04[9];bool deleteWhenClosed;
 void deleteOnClose(){deleteWhenClosed=true;}
};
class FileSystem{public:File *openFile(const char*,int,int=0);};
extern FileSystem *TheFileSystem;
struct Rva001EA443{AsciiString m_text0,m_text1;};
namespace _STL{template<class T,class Traits>static inline bool operator!=(const _List_iterator<T,Traits>&a,const _List_iterator<T,Traits>&b){return a._M_node!=b._M_node;}}
class GlobalLanguage{public:virtual void init();private:char unknown04[0x138-4];_STL::list<Rva001EA443> localFonts;};
void GlobalLanguage::init(){
 INI ini;ini.loadFile("language.ini",INI_LOAD_OVERWRITE,0);
 if(localFonts.size()){
  HMODULE library=LoadLibraryA("GDI32.DLL");
  if(library){
   typedef int(__stdcall *AddFontProc)(const char*,DWORD,void*);
   AddFontProc addFont=(AddFontProc)GetProcAddress(library,"AddFontResourceExA");
   char tempPath[260];
   if(GetTempPathA(260,tempPath)){
    strcat(tempPath,"\\");strcat(tempPath,BfmeFontExtractionDirectory);CreateDirectoryA(tempPath,0);
    if(addFont){
     for(_STL::list<Rva001EA443>::iterator it=localFonts.begin();it!=localFonts.end();++it){
      File *file=TheFileSystem->openFile(it->m_text0.str(),1);
      if(file){
       file->deleteOnClose();int size=file->size();char*data=file->readEntireAndClose();
       if(data){
        char tempFile[260];bool written=false;
        if(GetTempFileNameA(tempPath,"lrf",0,tempFile)){
         HANDLE handle=CreateFileA(tempFile,0x40000000,0,0,2,0x80,0);
         if(handle!=(HANDLE)-1){
          DWORD bytesWritten;
          if(WriteFile(handle,data,size,&bytesWritten,0)){written=true;CloseHandle(handle);}
          else{CloseHandle(handle);DeleteFileA(tempFile);}
         }
        }
        delete[]data;
        if(written){if(addFont(tempFile,0x30,0))it->m_text1=tempFile;else DeleteFileA(tempFile);}
       }
      }
     }
    }
   }
   FreeLibrary(library);
  }
 }
}
