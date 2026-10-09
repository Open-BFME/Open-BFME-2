// ?Rva004E697DInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABMAB_NABQBD@Z
// partial score=0.9516999520100409 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
#include "ascii_string.h"
class Rva00222A8BTarget {public:int invoke(void*,const char*,int,const char*,void*,void*,void*,void*);};
AsciiString Rva002228E8Get(float);
char** Rva004E678BGet(char**,bool);
static __forceinline const char*noticeStr(const AsciiString&s){return ((const StringBase<char>*)&s)->str();}
static __forceinline const char*noticeFlag(const bool&v){char*p;return *Rva004E678BGet(&p,v);}
static __forceinline const char*noticePass(const char*s){return s;}
int Rva004E697DInvoke(Rva00222A8BTarget*target,void*owner,const char*name,const float&a,const bool&b,const char*const&c){return target->invoke(owner,name,3,noticeStr(Rva002228E8Get(a)),(void*)noticeFlag(b),(void*)noticePass(c),0,0);}
