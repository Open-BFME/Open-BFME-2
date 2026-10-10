// ?rva00601C53@@YAXPAXH000@Z
// partial score=0.7662205239603235 date=2026-10-10
// cl: /O1 /G7 /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#define strcmp bfmeStatic_strcmp_unused
#define strncpy bfmeStatic_strncpy_unused
#include <vector>
#include "ascii_string.h"
#undef strcmp
#undef strncpy
extern int TextFileCharacterClasses[256];
extern "C" __declspec(dllimport) int __cdecl strcmp(const char*,const char*);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char*,const char*,unsigned);
extern "C" __declspec(dllimport) int __stdcall PathRemoveFileSpecA(char*);
extern "C" __declspec(dllimport) int __stdcall PathAppendA(char*,const char*);
extern "C" __declspec(dllimport) int __stdcall PathCanonicalizeA(char*,const char*);
void *operator new[](unsigned,unsigned);
class ModuleData;
class File {public:virtual void v0();virtual void v1();virtual void close();virtual int read(void*,int);virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual int size();AsciiString filename;};
class FileSystem {public:File *openFile(const char*,int,int);};
extern FileSystem *TheFileSystem;
class Debug {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void output(const char*);virtual void finish();virtual void v16();virtual void v17();virtual void v18();virtual void v19();virtual void v20();virtual void v21();virtual void v22();virtual void v23();virtual void skip();virtual void v25();virtual void v26();virtual Debug *start(int,int,int);class Format {public:Format(const char*,...);operator const char*()const{return data;}private:char data[512];};};
extern Debug *theDebug;
void _bfme_debugRecordCallsite(int);
class Rva00601B30 {public:void add(unsigned,unsigned,const char*);};
char *Rva006017DAParse(const char*,char*,int);
typedef _STL::vector<const char*> CStringVector;
__forceinline void appendCString(CStringVector &v,const char *const &s) {reinterpret_cast<_STL::vector<const ModuleData*>&>(v).push_back(reinterpret_cast<const ModuleData *const &>(s));}
void rva00601C53(void *outer,int lineFlag,void *vec1,void *vec2,void *member) {
 File *file=(File*)outer;CStringVector &stack=*(CStringVector*)vec1,&buffers=*(CStringVector*)vec2;
 int lineStart=1;int size=file->size();const char *token=0;int line=1;
 for(unsigned j=0;j<stack.size();++j)if(strcmp(file->filename.str(),stack[j])==0) {
  _bfme_debugRecordCallsite(1);theDebug->skip();const char *errorName=file->filename.str();const char **entries=stack.begin();Debug *d=theDebug->start(0,0,0);
  d->output(Debug::Format("ERROR: Circular include in %s line %d, Circular file %s, parent file %s",entries[stack.size()-1],lineFlag,errorName,entries[0]));d->finish();return;
 }
 const char *filename=file->filename.str();appendCString(stack,filename);
 char *data=new(0x737472) char[size+1];const char *owned=data;appendCString(buffers,owned);
 file->read(data,size);data[size]=0;
 int i=0;int cls=TextFileCharacterClasses[(unsigned char)data[0]];int tokenPosition=0;
 while(i<size) {
  switch(cls) {
  case 4:
   if(i<size-1 && data[i+1]=='/') {while(i<size && cls!=1) {data[i]=0;cls=TextFileCharacterClasses[(unsigned char)data[i+1]];++i;}lineStart=1;break;}
   cls=0;
  case 0:case 2:{
   bool meaningful=cls==0;
   if(lineStart==1){token=data+i;++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];tokenPosition=i;}
   lineStart=0;
   while(i<size && (cls==0 || cls==2)) {
    if(cls==2)data[i]=' ';else meaningful=true;
    ++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];
   }
   if(meaningful) {
    char includeName[264];int limit=size-tokenPosition;if(limit>260)limit=260;
    char *include=Rva006017DAParse(token,includeName,limit);
    if(include) {
     char path[260],canonical[260];strncpy(path,file->filename.str(),260);path[259]=0;
     PathRemoveFileSpecA(path);PathAppendA(path,include);
     for(char *p=path;*p;++p)if(*p=='/')*p='\\';
     char *name=path;if(PathCanonicalizeA(canonical,path))name=canonical;
     File *child=TheFileSystem->openFile(name,1,0);
     if(!child){_bfme_debugRecordCallsite(1);theDebug->skip();Debug *d=theDebug->start(0,0,0);d->output(Debug::Format("ERROR: Could not open include in %s line %d, file %s, parent file %s",stack.back(),lineFlag,name,stack.front()));d->finish();return;}
     rva00601C53(child,line,vec1,vec2,member);child->close();
    }else((Rva00601B30*)member)->add((unsigned)token,line,file->filename.str());
   }else token=0;
   break;}
  case 3:while(i<size && cls!=1){data[i]=0;++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];}lineStart=1;break;
  case 1:lineStart=1;while(i<size && cls==1){line+=data[i]=='\r';data[i]=0;++i;cls=TextFileCharacterClasses[(unsigned char)data[i]];}break;
  }
 }
 struct VectorWords {const char **begin,**end,**capacity;};--((VectorWords*)&stack)->end;
}
