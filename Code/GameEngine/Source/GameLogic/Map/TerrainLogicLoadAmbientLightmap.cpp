// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail2817F2..2819AD443B RET4. WB TerrainLogic::LoadAmbientLightmap
// at C4DF60..C4E2C6, TerrainLogic.cpp4763, independently corroborates
// the ambient-map clear, FileSystem open mode41, packed18-byte TGA header,
// two diagnostics,24-bit uncompressed RGB allocation and descriptor20 row flip.
// Native offsets: pixels24,width28,height2C; File close slot8/read slotC;
// theDebug stream slots60/6C/38/4C and StringBase<char> insertion28E8.
// Preserve the existing address-derived member spelling used by the verified
// GameLogic loader. Full original declaration is not claimed from a WB title.
// The explicit array-new declaration keeps the native2FDE0 call; MSVC's
// undeclared primitive-array allocation otherwise collapses to scalar2FDA0.
#include "ascii_string.h"
void * __cdecl operator new[](unsigned int size);

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
class Rva0062AF7 { public: void Rva0027DA58(); };
#pragma pack(push,1)
struct AmbientTgaHeader
{
 unsigned char idLength, colorMapType, imageType;
 unsigned char unused[9];
 unsigned short width, height;
 unsigned char bitsPerPixel, descriptor;
};
#pragma pack(pop)
class TerrainLogic
{
public:
 void rva002817F2(const AsciiString &name);
 char pad[0x24];
 unsigned char *pixels;
 unsigned width,height;
};
void TerrainLogic::rva002817F2(const AsciiString &name)
{
 ((Rva0062AF7 *)this)->Rva0027DA58();
 File *file=TheFileSystem->openFile(name.str(),0x41,0);
 if (!file) return;
 AmbientTgaHeader header;
 if (file->read(&header,18)!=18)
 {
  REPORT(" is damaged");
  file->close();
  return;
 }
 if (!header.idLength && !header.colorMapType && header.imageType==2 && header.bitsPerPixel==24)
 {
  width=header.width;
  height=header.height;
  pixels=new unsigned char[width*height*3];
  file->read(pixels,width*height*3);
  file->close();
  if (header.descriptor&0x20)
  {
   for (unsigned i=0;i<height/2;++i)
   {
    unsigned char *a=pixels+i*width*3;
    unsigned char *b=pixels+(height-i-1)*width*3;
    unsigned count=width*3;
    while (count)
    {
     unsigned char temp=*a;
     *a++=*b;
     *b++=temp;
     --count;
    }
   }
  }
 }
 else
 {
  file->close();
  REPORT(" is no valid 24 bit RGB TGA");
 }
}


