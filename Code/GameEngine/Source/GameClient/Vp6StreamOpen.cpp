// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// 0x000918BC..0x00091A25 (361B): stream vslot 19, independently identified
// by VideoPlayerRva009111BOpen.cpp's call with path/video/alpha arguments.
// The existing stream constructor proves parser +1C and frame pointers +14/+18.
// Native header reads prove the temporary header offsets and destination fields;
// these labels describe the wrapper's accesses, not proprietary codec internals.
// All direct callees already have verified ledger bodies. This only performs
// container-header scanning, frame allocation/configuration, and stream timing.
// The empty AsciiString path resolves to retail's existing empty literal.
#include "ascii_string.h"
struct Video;
struct CodecState;
int bfmeInitCodecJX(CodecState **,int,int);
void Rva009A4E50Configure(void*,unsigned,int);
void Rva00090714Free(void**);
void *Rva0009072BAlloc(int,int);
extern "C" __declspec(dllimport) unsigned __stdcall timeGetTime();
class Rva00106AC9 {public:bool rva00106AC9(const char*,int,bool);};
class BfmeB996Range {public:bool rva001068D1(int,unsigned*,char*);void rva0010690D();bool rva0010694B(void**,int*,unsigned*);private:char data[16];};
struct MovieHeader {int id;unsigned size;int unused;short width,height;int a,maxFrameSize,b;short c;};
class Rva007E3C20Vp6Stream {
public:
 virtual ~Rva007E3C20Vp6Stream();
 virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();
 virtual bool open(const AsciiString&,const Video*,bool);
 virtual int s20(const Video*);
private:
 char pad04[0x10];CodecState *frame,*alphaFrame;BfmeB996Range parser;void *at2c;int width,height;bool hasAlpha;int a,b,c,last,lastAlpha,start;void *buffer;int length;
};
bool Rva007E3C20Vp6Stream::open(const AsciiString &path,const Video *video,bool alpha) {
 if(!((Rva00106AC9*)&parser)->rva00106AC9(path.str(),1,false))return false;
 void *raw=0;int id;unsigned size;char flag;bool foundAlpha=false;
 while(parser.rva001068D1((int)&id,&size,&flag)) {
  if(id==0x36505641)foundAlpha=true;
  else if(id==0x6468564d) {parser.rva0010694B(&raw,&id,&size);break;}
  parser.rva0010690D();
 }
 MovieHeader *header=(MovieHeader*)raw;
 if(!header||header->size-8!=24)return false;
 width=header->width;height=header->height;a=header->a;b=header->b;c=header->c;
 length=((header->maxFrameSize+3)&~3)+8;
 Rva00090714Free(&raw);
 buffer=Rva0009072BAlloc(0,length);
 bfmeInitCodecJX(&frame,width,height);Rva009A4E50Configure(frame,0,0);
 hasAlpha=foundAlpha&&alpha;
 if(hasAlpha){bfmeInitCodecJX(&alphaFrame,width,height);Rva009A4E50Configure(alphaFrame,0,0);}
 s02();start=-s20(video);start+=timeGetTime();last=-1;lastAlpha=-1;
 return true;
}
