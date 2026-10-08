// ?rva005BD6A7@@YAXXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /EHsc /MD /G6 /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Source lead: BF1 9cbfb551 MainMenuUtils.cpp reallyStartPatchCheck.
// Target replaces nonblocking false with true, and calls the two PS helpers.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <string>
typedef int (*HttpComplete)(int,int,char *,int,void *);
extern "C" int ghttpGetA(const char *,int,HttpComplete,void *);
extern "C" int ghttpHeadA(const char *,int,HttpComplete,void *);
extern "C" int ghttpSetProxy(const char *);
void FormatURLFromRegistry(_STL::string &,_STL::string &,_STL::string &,_STL::string &);
bool GetStringFromRegistry(_STL::string,_STL::string,_STL::string &);
int rva005BD425(int,int,char *,int,void *);
int rva005BCC77(int,int,char *,int,void *);
int rva005BCA60(int,int,char *,int,void *);
void rva005BD64D();
void Rva005BD5F3Add();
int checksLeftBeforeOnline=0;
int timeThroughOnline=0;
void rva005BD6A7()
{
 checksLeftBeforeOnline=4;
 _STL::allocator<char> allocator;
 _STL::string gameURL,mapURL,configURL,motdURL;
 FormatURLFromRegistry(gameURL,mapURL,configURL,motdURL);
 _STL::string proxy;
 if(GetStringFromRegistry(_STL::string("",allocator),_STL::string("Proxy",allocator),proxy) && !proxy.empty())
  ghttpSetProxy(proxy.c_str());
 ghttpGetA(gameURL.c_str(),1,rva005BD425,(void *)timeThroughOnline);
 ghttpGetA(mapURL.c_str(),1,rva005BD425,(void *)timeThroughOnline);
 ghttpHeadA(configURL.c_str(),1,rva005BCC77,(void *)timeThroughOnline);
 ghttpGetA(motdURL.c_str(),1,rva005BCA60,(void *)timeThroughOnline);
 rva005BD64D();
 Rva005BD5F3Add();
}

