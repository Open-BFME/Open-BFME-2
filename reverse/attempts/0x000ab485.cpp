// ?createRenderData@AptAnimData@@AAEXABVAsciiString@@@Z
// partial score=0.983 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// BANK: clean BFME1 donor 575ba2b04743f190f069805fbdc59936123c45da
// game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Rva00788A30GeometryParser.cpp
// WB 8A9470 proves AptAnimData::createRenderData identity; native AB485..AB7F9 RET4.
// Target measured frame458 and shape layouts/callees; donor supplies control-flow semantics.
// Remaining 15 stack-offset bytes: wrap native +B versus -1; blue native -4 versus -8; alpha native -8 versus +8.
// Container ctor AA83B still needs native vector<void*> base call at211E58 instead of rowed15B wrapper142E20; do not substitute unrelated E16 vector.
// Tested scope and channel permutations plus volatile and imports; best all309 instructions aligned.
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "ascii_string.h"
class File {public:
 virtual ~File();virtual void s04();virtual void close();virtual void s0C();
 virtual void s10();virtual void s14();virtual void nextLine(char*,int);
 bool eof();
};
class FileSystem {public:File *openFile(const char*,int,int);};
extern FileSystem *TheFileSystem;
static File *openFile(const AsciiString *fname)throw()
{
 char *t=*(char *const*)fname;
 const char *s=t?t+8:"";
 for(;;){File *f=TheFileSystem->openFile(s,1,0);if(f)return f;
 s=strchr(s,'\\');if(!s)return 0;++s;}
}
static inline const char *getNameAndIndex(const AsciiString &path,int *index,bool fullPath)
{
 const char *fname=path.reverseFind('\\');if(!fname)return 0;
 const char *digits=path.reverseFind('.');if(!digits)return 0;
 while(isdigit(digits[-1]))--digits;
 sscanf(digits,"%d.",index);
 return fullPath?path.str():fname+1;
}
struct Rva000AB3E2Element;
struct Rva000AB419Element;
namespace _STL {
 template<> class vector<Rva000AB3E2Element> {public:void *first,*last,*capacity;void push_back(const Rva000AB3E2Element&);};
 template<> class vector<Rva000AB419Element> {public:void *first,*last,*capacity;void push_back(const Rva000AB419Element&);};
}
class Rva000AADC1 {public:Rva000AADC1()throw();void *vptr;_STL::vector<void*> records;float matrix[6];};
class Rva000AAD06 {public:Rva000AAD06()throw();char unknown[0x14];};
class Rva000AAE3D {public:Rva000AAE3D()throw();char unknown[0x18];};
class Rva000AAD5C {public:Rva000AAD5C()throw();char unknown[0x34];};
struct SolidRecordView {void *vptr;unsigned color;_STL::vector<Rva000AB3E2Element> triangles;};
struct LineRecordView {void *vptr;float width;unsigned color;_STL::vector<Rva000AB419Element> segments;};
struct TexturedRecordView {void *vptr;unsigned color;char unknown08[12];bool wrap,normalized;unsigned texture;float uv[6];};
class Rva000A953B {public:Rva000A953B()throw();float data[6];};
class Rva000A9551 {public:Rva000A9551()throw();float data[4];};
struct Rva007882F0Value;
class Rva007882F0PointerMap {public:Rva007882F0Value *lookup(unsigned);};
class GeometryRecord00788A30 {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual unsigned slot10();
};
class Object;
class ObjectLookupMap {public:Object **findSlot(int*);};
class AptAnimData {char unknown[8];ObjectLookupMap map;void createRenderData(const AsciiString&);};
void AptAnimData::createRenderData(const AsciiString &filename)
{
 int number=0;
 const char *path=getNameAndIndex(filename,&number,true);
 if(!path)return;
 File *file;{AsciiString name(path);file=openFile(&name);}
 if(!file)return;
 char line[1024];line[1023]=0;
 file->nextLine(line,1023);
 if(line[0]!='c'){file->close();return;}
 GeometryRecord00788A30 *current=0;
 _STL::vector<Rva000AB3E2Element> *triangles=0;
 Rva000AADC1 *geometry=new Rva000AADC1;
 *(Rva000AADC1**)map.findSlot(&number)=geometry;
 char wrap;
 while(!file->eof()) {
  file->nextLine(line,1023);
  switch(line[0]) {
  case 'c':current=0;triangles=0;break;
  case 's': {
   unsigned red,green,blue,alpha;
   switch(line[2]) {
   case 't': {
    wrap=0;
    TexturedRecordView *record=(TexturedRecordView*)new Rva000AAD5C;
    current=(GeometryRecord00788A30*)record;
    unsigned texture;
    sscanf(line,"s t%c:%d:%d:%d:%d:%d:%f:%f:%f:%f:%f:%f",&wrap,&red,&green,&blue,&alpha,&texture,
     &record->uv[0],&record->uv[1],&record->uv[2],&record->uv[3],&record->uv[4],&record->uv[5]);
    record->color=(((alpha<<8)|red)<<8|green)<<8|blue;
    record->wrap=wrap=='w';
    record->texture=(unsigned)((Rva007882F0PointerMap*)this)->lookup(texture);
    triangles=(_STL::vector<Rva000AB3E2Element>*)((char*)record+8);
    break;
   }
   case 's': {
    SolidRecordView *record=(SolidRecordView*)new Rva000AAD06;
    current=(GeometryRecord00788A30*)record;
    sscanf(line,"s s:%d:%d:%d:%d",&red,&green,&blue,&alpha);
    record->color=(((alpha<<8)|red)<<8|green)<<8|blue;
    triangles=&record->triangles;break;
   }
   case 'l': {
    LineRecordView *record=(LineRecordView*)new Rva000AAE3D;
    current=(GeometryRecord00788A30*)record;
    sscanf(line,"s l:%f:%d:%d:%d:%d",&record->width,&red,&green,&blue,&alpha);
    record->color=(((alpha<<8)|red)<<8|green)<<8|blue;break;
   }
   default:file->close();return;
   }
   geometry->records.push_back(*(void **)&current);break;
  }
  case 't': {
   if(!current||!triangles){file->close();return;}
   Rva000A953B triangle;
   sscanf(line,"t %f:%f:%f:%f:%f:%f",&triangle.data[0],&triangle.data[1],&triangle.data[2],&triangle.data[3],&triangle.data[4],&triangle.data[5]);
   triangles->push_back(*(Rva000AB3E2Element*)&triangle);break;
  }
  case 'l': {
   if(!current||!current->slot10()){file->close();return;}
   Rva000A9551 segment;
   sscanf(line,"l %f:%f:%f:%f",&segment.data[0],&segment.data[1],&segment.data[2],&segment.data[3]);
   ((_STL::vector<Rva000AB419Element>*)((char*)current+12))->push_back(*(Rva000AB419Element*)&segment);break;
  }
  default:file->close();return;
  }
 }
 file->close();
}
