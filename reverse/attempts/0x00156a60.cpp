// ?loadCharBitmap@FontCharsClass@@AAEPBUFontCharsClassCharDataStruct@@G@Z
// partial score=0.7604897040120062 date=2026-10-10
// cl: /Ireference/shims/sweep /O2 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// stlport
// ZH Store_GDI_Char is the semantic guide; BFME1 reference575ba2b04.
// BFME2 Thai glyph sibling supplies the proven tiled downsampling extension.
// Native156A60..156F73 is1299B, not the queued truncated1292B extent.
// Target glyph-index validation/cache at4C/44C/45C, scale40, font48,
// buffer list14/count20, pixel28/height2C/ascent30/overlap38 measured.
// Text-output flag2 and direct character cache replace Thai flag12/map.
// This is a nonmatching bank:1303B/frameA4 vsnative1299/frameAC,
// all calls resolve; compiler loop/local allocation remains different.
#include <windows.h>
extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(HDC,LPCWSTR,int,LPWORD,DWORD);
#include <map>
#include <string.h>
struct ABC { int abcA; unsigned int abcB; int abcC; };
extern "C" __declspec(dllimport) int __stdcall GetTextExtentPointI(HDC,const unsigned short*,int,SIZE*);
extern "C" __declspec(dllimport) int __stdcall GetCharABCWidthsI(HDC,unsigned int,unsigned int,const unsigned short*,ABC*);

struct FontCharsClassCharDataStruct
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
 int unknown34,overlap,unknown3c;
 int Scale;
 int unknown44;
 HFONT font;
 const FontCharsClassCharDataStruct *directChars[256];
 const FontCharsClassCharDataStruct **pages;
 _STL::map<unsigned short,int> glyphs;
 unsigned short first,last;
 void Update_Current_Buffer(int width);
private:
 const FontCharsClassCharDataStruct *loadCharBitmap(unsigned short ch);
};
const FontCharsClassCharDataStruct *FontCharsClass::loadCharBitmap(unsigned short ch)
{
 FontGlyphDCSelection selection(g_fontCharsGdiState->dc,font);
 unsigned int glyphIndex=0xffff;
 ::GetGlyphIndicesW(g_fontCharsGdiState->dc,&ch,1,reinterpret_cast<WORD*>(&glyphIndex),1);
 if(static_cast<unsigned short>(glyphIndex)==0xffff) {
  if(ch<256) directChars[ch]=reinterpret_cast<const FontCharsClassCharDataStruct*>(-1);
  else pages[ch-first]=reinterpret_cast<const FontCharsClassCharDataStruct*>(-1);
  return reinterpret_cast<const FontCharsClassCharDataStruct*>(-1);
 }

 int area=Scale*Scale;
 int halfArea=area>>1;
 int tileX=64/Scale;
 int tileY=64/Scale;
 int tileWidth=Scale*tileX;
 int tileHeight=Scale*tileY;
 SIZE charSize={tileWidth,tileHeight};
 if(!::GetTextExtentPoint32W(g_fontCharsGdiState->dc,&ch,1,&charSize))
  charSize.cx=charSize.cy=1;
 int width=(Scale+charSize.cx-1)/Scale+overlap;
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
 RECT rect={0,0,tileWidth,tileHeight};
 for(int ty=0;ty<tilesY;++ty) {
  for(int tx=0;tx<tilesX;++tx) {

   int sx=tx*tileWidth,sy=ty*tileHeight;
   ::ExtTextOutW(g_fontCharsGdiState->dc,-sx,-sy,2,&rect,&ch,1,0);
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
 data->Value=ch;
 data->Width=width;
 data->Bearing=0;
 data->Buffer=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 if(ch<256) directChars[ch]=data; else pages[ch-first]=data;
 CurrPixelOffset+=CharHeight*(width+overlap);
 return data;
}
