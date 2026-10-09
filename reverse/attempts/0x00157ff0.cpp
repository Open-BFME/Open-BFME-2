// ?Store_Thai_GDI_Glyph@FontCharsClass@@AAEPBVFontCharsClassCharDataStruct@@G@Z
// partial score=0.924901 date=2026-10-09
// cl: /O2 /G7 /DNDEBUG /MD /EHsc
// stlport
// FontCharsClass::Store_Thai_GDI_Glyph, target 00157FF0..0015851B (1323B).
// WB 009F1BD0 supplies the named glyph-index rasterization and averaging loop.
// ZH Store_GDI_Char supplies the parent buffer/copy/CharData semantics only;
// target bytes establish the Thai path, scale, map, DC and 12-byte record.
#include <windows.h>
#include <map>
#include <string.h>
struct ABC { int abcA; unsigned int abcB; int abcC; };
extern "C" __declspec(dllimport) int __stdcall GetTextExtentPointI(HDC,const unsigned short*,int,SIZE*);
extern "C" __declspec(dllimport) int __stdcall GetCharABCWidthsI(HDC,unsigned int,unsigned int,const unsigned short*,ABC*);

class FontCharsClassCharDataStruct
{
public:
 unsigned short Value,Width;
 short Bearing;
 unsigned short unused;
 unsigned short *Buffer;
};
class FontCharsClassGdiState
{
public:
 int refs;
 HBITMAP oldBitmap,bitmap;
 unsigned char *bits;
 HDC dc;
};
extern FontCharsClassGdiState *g_fontCharsGdiState;
class FontGlyphDCSelection
{
 HDC dc;
 HGDIOBJ old;
public:
 FontGlyphDCSelection(HDC dc_,HFONT font):dc(dc_),old(::SelectObject(dc_,font)) {}
 ~FontGlyphDCSelection() { ::SelectObject(dc,old); }
};
class FontCharsBuffer { public: unsigned short *Buffer; };
template<class T> class DynamicVectorClass
{
public:
 int vptr;
 T *items;
 int capacity;
 bool valid,allocated;
 unsigned short padding;
 int activeCount;
 int growth;
 T &operator[](int i) { return items[i]; }
 int Count() const { return activeCount; }
};
namespace _STL {
template<> map<unsigned short,int,less<unsigned short>,allocator<pair<const unsigned short,int> > >::mapped_type &map<unsigned short,int,less<unsigned short>,allocator<pair<const unsigned short,int> > >::operator[](const key_type &);
}
class FontCharsClass
{
 void *unused00,*unused04;
 FontCharsClass *alternate;
 int unused0c;
 DynamicVectorClass<FontCharsBuffer*> BufferList;
 int CurrPixelOffset,CharHeight,ExtraHeight;
 int unknown34,unknown38,unknown3c;
 int Scale;
 int unknown44;
 HFONT font;
 const FontCharsClassCharDataStruct *directChars[256];
 const FontCharsClassCharDataStruct **pages;
 _STL::map<unsigned short,int> glyphs;
 void Update_Current_Buffer(int width);
private:
 const FontCharsClassCharDataStruct *Store_Thai_GDI_Glyph(unsigned short glyph);
};
const FontCharsClassCharDataStruct *FontCharsClass::Store_Thai_GDI_Glyph(unsigned short glyph)
{
 if(glyph==0xffff) {
  FontCharsClassCharDataStruct *data=new FontCharsClassCharDataStruct;
  data->Value=glyph;data->Width=0;data->Bearing=0;data->Buffer=0;
  glyphs[glyph]=reinterpret_cast<int>(data);
  return data;
 }
 FontGlyphDCSelection selection(g_fontCharsGdiState->dc,font);
 int area=Scale*Scale;
 int halfArea=area>>1;
 int tileX=64/Scale;
 int tileY=64/Scale;
 int tileWidth=Scale*tileX;
 int tileHeight=Scale*tileY;
 SIZE charSize;
 if(!::GetTextExtentPointI(g_fontCharsGdiState->dc,&glyph,1,&charSize))
  charSize.cx=charSize.cy=1;
 ABC abc;
 int origin=0;
 if(!::GetCharABCWidthsI(g_fontCharsGdiState->dc,glyph,1,0,&abc)) {
  abc.abcA=0;abc.abcB=1;abc.abcC=0;
 } else {
  unsigned int width=abc.abcB;
  if(abc.abcC>0) width+=abc.abcC;
  if(abc.abcA>0) width+=abc.abcA;
  else origin=-abc.abcA;
  charSize.cx=width;
 }
 int width=(Scale+charSize.cx-1)/Scale;
 int height=(Scale+charSize.cy-1)/Scale;
 Update_Current_Buffer(width);
 unsigned short *start=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 int top=ExtraHeight/2;
 int bottom=ExtraHeight-top;
 unsigned short *pixels=start+top*width;
 memset(start,0,top*width*2);
 memset(pixels+width*height,0,bottom*width*2);
 int tilesX=(width+tileX-1)/tileX;
 int tilesY=(height+tileY-1)/tileY;
 for(int ty=0;ty<tilesY;++ty) {
  for(int tx=0;tx<tilesX;++tx) {
   RECT rect={0,0,tileWidth,tileHeight};
   int sx=tx*tileWidth,sy=ty*tileHeight;
   ::ExtTextOutW(g_fontCharsGdiState->dc,origin-sx,-sy,0x12,&rect,&glyph,1,0);
   int maxX=tx*tileX+tileX;
   if(maxX>width) maxX=width;
   int maxY=ty*tileY+tileY;
   if(maxY>height) maxY=height;
   for(int y=ty*tileY;y<maxY;++y) {
    unsigned short *dest=pixels+y*width+tx*tileX;
    int y0=Scale*y;
    int y1=y0+Scale;
    if(y1>charSize.cy) y1=charSize.cy;
    for(int x=tx*tileX;x<maxX;++x) {
     unsigned int intensity=0;
     int x0=Scale*x;
     int x1=x0+Scale;
     if(x1>charSize.cx) x1=charSize.cx;
     for(int row=y0;row<y1;++row) {
      int index=(row-sy)*192+(x0-sx)*3;
      for(int col=x0;col<x1;++col) {
       unsigned char sample=g_fontCharsGdiState->bits[index];
       index+=3;
       intensity+=(sample>>4)&15;
      }
     }
     unsigned short alpha=(intensity+halfArea)/area;
     *dest++=0xfff|(alpha<<12);
    }
   }
  }
 }
 FontCharsClassCharDataStruct *data=new FontCharsClassCharDataStruct;
 data->Value=glyph;
 data->Width=width;
 data->Bearing=(1-Scale-origin)/Scale;
 data->Buffer=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 glyphs[glyph]=reinterpret_cast<int>(data);
 CurrPixelOffset+=CharHeight*width;
 return data;
}
