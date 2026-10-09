// ?rva006D47F0@EAStringC@@QAEHPBD0@Z
// partial score=0.9404652742 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc
// 006D47F0..006D4A9C, complete retail extent including ret8 omitted by Ghidra.
// WB1775230 guides non-overlapping substring replacement; native proves
// StringDataC header and assertions. Address-derived member name preserved.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char *test,const char *file,int line){g_bfmeAptAssertAtE17734(test,file,line);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
#define STRING_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp"
#define STRING_INL ".\\string\\EAString.inl"
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" char *__cdecl strstr(const char*,const char*);
extern "C" void *__cdecl memcpy(void*,const void*,unsigned int);
#pragma intrinsic(strlen,memcpy)
class EAStringC {
public:
 class StringDataC {public:unsigned short refs,size,maxSize,hash;};
 StringDataC *data;
 EAStringC(unsigned int);
 static void FreeData(StringDataC*);
 ~EAStringC(){FreeData(data);}
 int rva006D47F0(const char*,const char*);
 char *buffer()const{return (char*)data+8;}
 void setSize(unsigned int n){StringDataC *p=data;if(n>p->maxSize)aptAssert("uSize <= GetInternalMaxSize()",STRING_INL,0x5C);p->size=(unsigned short)n;p->hash=0;}
 EAStringC &operator=(const EAStringC&);
};
extern EAStringC::StringDataC g_eaEmptyStringData;
EAStringC &EAStringC::operator=(const EAStringC &s){
 if(s.data!=&g_eaEmptyStringData && s.data->refs>0xFFFE)aptAssert("m_pData->m_uRefCount <= 0xfffe",STRING_INL,0xE1);
 ++s.data->refs;FreeData(data);data=s.data;return *this;
}
int EAStringC::rva006D47F0(const char *oldString,const char *newString){
 if(!oldString)aptAssert("pStrOld != NULL",STRING_FILE,0x3B4);
 if(!newString)aptAssert("pStrNew != NULL",STRING_FILE,0x3B5);
 unsigned int oldLength=strlen(oldString);
 if(!oldLength)return 0;
 unsigned int newLength=strlen(newString);
 int count=0;
 const char *src=buffer();
 const char *occurrence;
 while((occurrence=strstr(src,oldString))!=0){++count;src=occurrence+oldLength;}
 if(!count)return 0;
 int resultSize=data->size+(newLength-oldLength)*count;
 EAStringC result(resultSize);
 src=buffer();
 char *start=result.buffer();char *dest=start;
 for(int i=0;i<count;++i){
  occurrence=strstr(src,oldString);
  if(!occurrence)aptAssert("pStrOccurence != NULL",STRING_FILE,0x3E7);
  unsigned int prefix=occurrence-src;
  if(prefix){memcpy(dest,src,prefix);dest+=prefix;}
  src=occurrence+oldLength;
  memcpy(dest,newString,newLength);dest+=newLength;
 }
 unsigned int remaining=resultSize-(dest-start);
 if(remaining){memcpy(dest,src,remaining);dest+=remaining;}
 *dest=0;result.setSize(resultSize);
 *this=result;
 return count;
}
