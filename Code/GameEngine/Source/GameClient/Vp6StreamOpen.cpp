// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// platformsdk
// 0x000918BC..0x00091A25 (361B): stream vslot 19, independently identified
// by VideoPlayerRva009111BOpen.cpp's call with path/video/alpha arguments.
// The existing stream constructor proves parser +1C and frame pointers +14/+18.
// Native header reads prove the temporary header offsets and destination fields;
// these labels describe the wrapper's accesses, not proprietary codec internals.
// All direct callees already have verified ledger bodies. This only performs
// container-header scanning, frame allocation/configuration, and stream timing.
// The empty AsciiString path resolves to retail's existing empty literal.
#include <windows.h>
#include "ascii_string.h"
class Rva00090FE0 {public:int rva00090FE0(unsigned int);};
class Rva007E4AD0Vp6Stream {public:void update();};
class At2cObj {public:virtual void v0();};
extern unsigned char g_00DE4498;
struct Video;
struct CodecState;
extern "C" int __cdecl VP6_StartDecoder(CodecState **,int,int);
extern "C" void __cdecl VP6_SetPbParam(void*,unsigned,int);
void freeBlock(void**);
void *Rva0009072BAlloc(int,int);
class Rva00106AC9 {public:bool rva00106AC9(const char*,int,bool);};
class BfmeB996Range {public:bool rva001068D1(int,unsigned*,char*);void rva0010690D();bool rva0010694B(void**,int*,unsigned*);private:char data[16];};
struct MovieHeader {int id;unsigned size;int unused;short width,height;int a,maxFrameSize,b;short c;};
class Rva007E3C20Vp6Stream {
public:
 virtual ~Rva007E3C20Vp6Stream();
 virtual void s01();virtual void s02();virtual void s03();virtual void s04();virtual bool s05(int);virtual int rva000911F6(int);virtual void s07();virtual void s08();virtual void s09();virtual void s10();virtual void s11();virtual void s12();virtual bool s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();
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
 freeBlock(&raw);
 buffer=Rva0009072BAlloc(0,length);
 VP6_StartDecoder(&frame,width,height);VP6_SetPbParam(frame,0,0);
 hasAlpha=foundAlpha&&alpha;
 if(hasAlpha){VP6_StartDecoder(&alphaFrame,width,height);VP6_SetPbParam(alphaFrame,0,0);}
 s02();start=-s20(video);start+=timeGetTime();last=-1;lastAlpha=-1;
 return true;
}

// Native 000911F6..00091323 is the 301-byte stream vslot6 dispatcher.
// Vtable BC7F20 slot6 at BC7F38 points here; slot19 points to the
// independently rowed open method at 000918BC.
// It selects a target frame from the owned elapsed-time helper; advances
// through stream virtuals; updates the existing clock; and returns status
// bits 2 (already done) / 4 (advanced) / 1 (output dispatched).
// The body describes native scheduling and virtual dispatch only. No codec
// implementation source was read or used. The original method name is unknown.
int Rva007E3C20Vp6Stream::rva000911F6( int flags )
{
	bool initiallyDone = s13();
	int resultFlags = initiallyDone ? 2 : 0;
	if ( last < 0 )
		s02();
	int nonBlocking = flags & 4;
	if ( nonBlocking == 0 && ( resultFlags & 2 ) )
		return resultFlags;
	if ( !s05( flags ) )
		return resultFlags;
	int targetFrame = ((Rva00090FE0 *)this)->rva00090FE0((unsigned int)flags);
	if ( g_00DE4498 != 0 || nonBlocking != 0 || ( flags & 0x40 ) != 0 ) {
		int scale = c; int rate = this->b;
		DWORD now = timeGetTime();
		// Equal-valued divisor alternatives retain this compiler
		// home for the saved flag; both use the same measured rate.
		int diff = (int)now - (int)( ( (__int64)( scale * 1000 ) * targetFrame ) / (nonBlocking ? rate : rate) );
		int framesPerSecond = rate / scale;
		int msPerFrame = 1000 / framesPerSecond;
		if ( diff - start > msPerFrame )
			start = diff;
	}
	int limit = targetFrame;
	while ( last < limit ) {
		if ( s13() )
			break;
		if ( nonBlocking != 0 )
			break;
		s02();
		resultFlags |= 4;
	}
	if ( flags & 1 )
		return resultFlags;
	if ( (lastAlpha) == last )
		return resultFlags;
	s03();
	((At2cObj *)at2c)->v0();
	resultFlags |= 1;
	s02();
	if ( *(volatile int*)&nonBlocking == 0 )
		return resultFlags;
	if ( !s13() )
		return resultFlags;
	((Rva007E4AD0Vp6Stream *)this)->update();
	return resultFlags;
}
