// ?writeINI@Rva0055C263@@UAEXPAVFile@@I@Z
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// Native full body 55C263..55C414, RET8. WB1417BE0 is unnamed; retain a
// neutral owner. Literal Color and ColorScale plus eight 16-byte records at
// +0xC establish this serializer's measured view, not an original template name.
// Primary C++ guides: matched Rva00563D3FWrite.cpp stream serialization and
// Rva0055C18BWrite.cpp stream/header setup. Target helpers supply the key RGB,
// float-pair, indentation, File write, and trailing-record operations.
// The independent key cursor keeps ESI at RGB's first member as retail does;
// an indexed reference anchors it at the frame and grows this body by two bytes.
#include <stl/_algobase.h>
namespace _STL {template<> const unsigned int& max<unsigned int>(const unsigned int&,const unsigned int&);}
#include <sstream>
class File {public: virtual ~File(); virtual bool open(const char*,int=0); virtual void close(); virtual int read(void*,int); virtual int write(const void*,int);};
struct RGBColor {float red,green,blue;};
struct ColorKey {RGBColor color;unsigned long frame;};
struct S001F87D5 {unsigned int first;float x,y;};
struct Rva001F458BText {const char* start;const char* finish;};
typedef _STL::basic_ostream<char,_STL::char_traits<char> > OutputStream;
OutputStream& Rva001F6951Pad(OutputStream&,unsigned int);
OutputStream& Rva0055C0E1Write(OutputStream&,const RGBColor&);
OutputStream& Rva001F87D5Put(OutputStream&,const S001F87D5&);
void Rva0055C18BWriteHeader(const void*,File*,unsigned int*);
void Rva003AFC6BWrite(File*,unsigned int*);
File& Rva001F458BWrite(File&,const Rva001F458BText&);
class Rva0055C263 {public: virtual void v0();virtual void v1();virtual void v2();virtual void writeINI(File*,unsigned int); private:char pad[8];ColorKey keys[8];S001F87D5 scale;};
void Rva0055C263::writeINI(File* file,unsigned int flags) {
 Rva0055C18BWriteHeader(this,file,&flags);
 _STL::basic_ostringstream<char,_STL::char_traits<char>,_STL::allocator<char> > oss(16);
 const ColorKey* cursor=keys;
 for(unsigned int i=0;i<8;i++,cursor++) {
  const ColorKey& key=*cursor;
  if(key.color.red!=0.0f || key.color.green!=0.0f || key.color.blue!=0.0f || key.frame!=0) {
   Rva001F6951Pad(oss,flags)<<"Color"<<(unsigned long)(i+1)<<" = ";
   Rva0055C0E1Write(oss,key.color)<<' '<<key.frame<<'\n';
  }
 }
 if(scale.x!=0.0f || scale.y!=0.0f) {
  Rva001F6951Pad(oss,flags)<<"ColorScale = ";
  Rva001F87D5Put(oss,scale)<<'\n';
 }
 Rva001F458BWrite(*file,(const Rva001F458BText&)oss.str());
 Rva003AFC6BWrite(file,&flags);
}
