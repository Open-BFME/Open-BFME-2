// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// WB BDDCA0 StandingWaterArea::getDepthColoringTexturePixels and native
// 308799..3089CF RET8 prove identity and ABI. Target name8C and dimensions
// 90/94 plus owned pixel cache98/reload9C are witnessed by this body.
// Existing exact TerrainLogic ambient loader supplies File and diagnostic
// interfaces; target adds cached reload and Art\\Terrain\\ fallback path.
// Explicit array new/delete declarations preserve native 2FDE0/2FD80.
#include "ascii_string.h"
void * __cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *);

class File
{
public:
 virtual void unused0(); virtual void unused1();
 virtual void close();
 virtual int read(void *buffer, int count);
};
class FileSystem { public: File *openFile(const char *, int, int); };
extern FileSystem *TheFileSystem;
class Debug
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
 virtual void slot30(); virtual void slot34(); virtual Debug &slot38(const char *);
 virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual void slot4c(int); virtual void slot50(); virtual void slot54(); virtual void slot58();
 virtual void slot5c(); virtual void slot60(); virtual void slot64(); virtual void slot68();
 virtual Debug &slot6c(int,int,int);
};
extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int);
#define REPORT(message) if (bfmeRva000387C0()) { _bfme_debugRecordCallsite(1); theDebug->slot60(); (theDebug->slot6c(0,0,0) << *(const StringBase<char> *)&name).slot38(message).slot4c(2); }
#pragma pack(push,1)
struct DepthTgaHeader { unsigned char idLength,colorMapType,imageType,unused[9]; unsigned short width,height; unsigned char bitsPerPixel,descriptor; };
#pragma pack(pop)
class StandingWaterArea {
 char prefix[0x8c]; AsciiString name; int width,height; unsigned char *pixels; bool reload;
public: unsigned char *getDepthColoringTexturePixels(int*,int*);
};
unsigned char *StandingWaterArea::getDepthColoringTexturePixels(int *outWidth,int*outHeight) {
 if(reload) {
  reload=false;
  if(pixels){delete[] pixels;pixels=0;width=0;height=0;}
  AsciiString path("Art\\Terrain\\");path.concat(name);
  File *file=TheFileSystem->openFile(path.str(),0x41,0);
  if(!file)file=TheFileSystem->openFile(name.str(),0x41,0);
  if(!file)return pixels;
  DepthTgaHeader header;
  if(file->read(&header,18)!=18){REPORT(" is damaged");file->close();return pixels;}
  if(!header.idLength&&!header.colorMapType&&header.imageType==2&&header.bitsPerPixel==24){
   width=header.width;height=header.height;
   pixels=new unsigned char[width*height*3];
   file->read(pixels,width*height*3);file->close();
  }else{file->close();REPORT(" is no valid 24 bit RGB TGA");return pixels;}
 }
 *outWidth=width;*outHeight=height;return pixels;
}
