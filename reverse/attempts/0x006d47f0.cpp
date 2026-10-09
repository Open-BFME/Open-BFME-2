// ?Rva006D47F0Replace@EAStringC@@QAEHPBD0@Z
// partial score=0.7109144543 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc
extern "C" char *__cdecl strstr(const char*,const char*);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void *__cdecl memcpy(void*,const void*,unsigned int);
#pragma intrinsic(strlen,memcpy)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class EAStringC {
public:
 struct StringDataC {unsigned short m_uRefCount,m_uSize,m_uMaxSize,m_uHash;};
 StringDataC *m_pData;
 static void FreeData(StringDataC*);
 EAStringC(unsigned int);
 ~EAStringC(){FreeData(m_pData);}
 char *buffer()const{return (char*)m_pData+8;}
 void SetSize(int size){
  if((unsigned)size>m_pData->m_uMaxSize){
   g_bfmeAptAssertAtE17734("uSize <= GetInternalMaxSize()",".\\string\\EAString.inl",0x5c);
   if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
  }
  m_pData->m_uSize=(unsigned short)size;
 }
 EAStringC &operator=(const EAStringC&other);
 int Rva006D47F0Replace(const char*,const char*);
};
extern EAStringC::StringDataC g_eaEmptyStringData;
inline EAStringC& EAStringC::operator=(const EAStringC&other){
 if(other.m_pData!=&g_eaEmptyStringData && other.m_pData->m_uRefCount>0xfffe){
  g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe",".\\string\\EAString.inl",0xe1);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 ++other.m_pData->m_uRefCount;
 FreeData(m_pData);
 m_pData=other.m_pData;
 return *this;
}
int EAStringC::Rva006D47F0Replace(const char *find,const char *replacement){
 if(!find){g_bfmeAptAssertAtE17734("pStrOld != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",0x3b4);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
 if(!replacement){g_bfmeAptAssertAtE17734("pStrNew != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",0x3b5);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
 int findLength=strlen(find);
 if(!findLength)return 0;
 int replacementLength=strlen(replacement);
 int count=0;
 const char*match=strstr(buffer(),find);
 if(match){do{++count;match=strstr(match+findLength,find);}while(match);}
 if(!count)return 0;
 int newLength=m_pData->m_uSize+(replacementLength-findLength)*count;
 EAStringC result(newLength);
 const char*source=buffer();
 char*destination=result.buffer();
 char*destinationStart=destination;
 for(int remaining=count;remaining>0;--remaining){
  match=strstr(source,find);
  if(!match){g_bfmeAptAssertAtE17734("pStrOccurence != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",0x3e7);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
  int prefixLength=(int)(match-source);
  if(prefixLength){memcpy(destination,source,prefixLength);destination+=prefixLength;}
  source=match+findLength;
  memcpy(destination,replacement,replacementLength);
  destination+=replacementLength;
 }
 int tailLength=newLength-(int)(destination-destinationStart);
 if(tailLength){memcpy(destination,source,tailLength);destination+=tailLength;}
 *destination=0;
 result.SetSize(newLength);
 result.m_pData->m_uHash=0;
 *this=result;
 return count;
}
