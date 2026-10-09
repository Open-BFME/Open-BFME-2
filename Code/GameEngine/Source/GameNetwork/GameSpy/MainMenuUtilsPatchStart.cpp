// cl: /O1 /G7 /arch:SSE /MD /EHsc
// BFME1 reallyStartPatchCheck, donor9cbfb551fe20, supplies the four URLs,
// proxy lookup and HTTP categories. Native5BD6A7..5BD82E supplies blocking
// calls, run/check ownership and BFME2 type10/type12 PS requests.
// String storage follows the independently rowed WWDownload string ABI.
// The one-byte allocator view represents only its addressable stack object;
// the constructor consumes no allocator state here.
#include "../../Common/MainMenuOnlineState.h"
#include <new>
void Rva00030830GameFree(void*);
namespace _STL {
template<class C>class char_traits;
template<class C>class allocator {char opaque;public:allocator(){}};
template<class C,class T,class A>class basic_string {public:
 basic_string();basic_string(const basic_string&);basic_string(const C*,const A&);
 ~basic_string(){if(start)Rva00030830GameFree(start);}
 const C*c_str()const{return start;}bool empty()const{return start==finish;}
private:C*start;C*finish;C*storageEnd;
};
}
typedef _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > PatchString;
enum GHTTPBool {GHTTPFalse,GHTTPTrue};enum GHTTPResult {GHTTPSuccess};
typedef GHTTPBool (*PatchHttpComplete)(int,GHTTPResult,char*,__int64,void*);
extern "C" int ghttpGetA(const char*,int,PatchHttpComplete,void*);
extern "C" int ghttpHeadA(const char*,int,PatchHttpComplete,void*);
extern "C" int ghttpSetProxy(const char*);
void FormatURLFromRegistry(PatchString&,PatchString&,PatchString&,PatchString&);
bool GetStringFromRegistry(PatchString,PatchString,PatchString&);
GHTTPBool gamePatchCheckCallback(int,GHTTPResult,char*,__int64,void*);
GHTTPBool configHeadCallback(int,GHTTPResult,char*,__int64,void*);
GHTTPBool motdCallback(int,GHTTPResult,char*,__int64,void*);
void rva005BD64D();void Rva005BD5F3Add();
void rva005BD6A7(){
 g_mainMenuOnlineState.checks=4;
 unsigned char allocatorStorage[sizeof(_STL::allocator<char>)];
 const _STL::allocator<char>&allocator=*new(allocatorStorage)_STL::allocator<char>();
 PatchString gameURL,mapURL,configURL,motdURL;
 FormatURLFromRegistry(gameURL,mapURL,configURL,motdURL);
 PatchString proxy;
 if(GetStringFromRegistry(PatchString("",allocator),PatchString("Proxy",allocator),proxy)&&!proxy.empty())ghttpSetProxy(proxy.c_str());
 ghttpGetA(gameURL.c_str(),1,gamePatchCheckCallback,(void*)g_mainMenuOnlineState.run);
 ghttpGetA(mapURL.c_str(),1,gamePatchCheckCallback,(void*)g_mainMenuOnlineState.run);
 ghttpHeadA(configURL.c_str(),1,configHeadCallback,(void*)g_mainMenuOnlineState.run);
 ghttpGetA(motdURL.c_str(),1,motdCallback,(void*)g_mainMenuOnlineState.run);
 rva005BD64D();Rva005BD5F3Add();
}
