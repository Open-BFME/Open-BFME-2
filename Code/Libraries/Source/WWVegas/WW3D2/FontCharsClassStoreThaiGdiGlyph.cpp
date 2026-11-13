// cl: /D_WIN32_WINNT=0x0500 /O2 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// stlport
// platformsdk
// FontCharsClass::Store_Thai_GDI_Glyph: rasterizes one Thai glyph index through the shared GDI DIB in
// 64x64 tiles and box-filters it by Scale into 4-bit alpha (ZH Store_GDI_Char semantics, WB 0x9F1BD0
// Thai twin shape, sibling loadCharBitmap 0x00156A60 statement shape). Tile, origin and cell
// coordinates are POINT/SIZE pairs; the ABC widths widen the cell and give the left origin, and the
// glyph map caches every record, including the empty 0xffff one.
// Keep the opaque handle ABI shared with loadCharBitmap.
#define NO_STRICT
#include <windows.h>
#include <map>
#include <string.h>

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
#include "FontCharsBuffer.h"
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
// The glyph map's subscript is the shared out-of-line instantiation (0x00157DD0).
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
 SIZE tile_size={Scale*tileX,Scale*tileY};
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
 SIZE cell_size;
 cell_size.cx=(Scale+charSize.cx-1)/Scale;
 cell_size.cy=(Scale+charSize.cy-1)/Scale;
 // Get a pointer to the surface that this character should use
 Update_Current_Buffer(cell_size.cx);
 unsigned short *pixels=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 int top=ExtraHeight/2;
 int bottom=ExtraHeight-top;
 unsigned short *start=pixels;
 pixels+=top*cell_size.cx;
 memset(start,0,top*cell_size.cx*2);
 memset(pixels+cell_size.cx*cell_size.cy,0,bottom*cell_size.cx*2);
 SIZE tile_count;
 tile_count.cx=(cell_size.cx+tileX-1)/tileX;
 tile_count.cy=(cell_size.cy+tileY-1)/tileY;
 // Copy the BMP contents to the buffer
 POINT tile_pos;
 for(tile_pos.y=0;tile_pos.y<tile_count.cy;++tile_pos.y) {
  for(tile_pos.x=0;tile_pos.x<tile_count.cx;++tile_pos.x) {
   // Draw the character into the memory DC
   RECT rect={0,0,tile_size.cx,tile_size.cy};
   POINT tile_origin;
   tile_origin.x=tile_size.cx*tile_pos.x;
   tile_origin.y=tile_size.cy*tile_pos.y;
   ::ExtTextOutW(g_fontCharsGdiState->dc,origin-tile_origin.x,-tile_origin.y,0x12,&rect,&glyph,1,0);
   POINT cell_start;
   cell_start.x=tileX*tile_pos.x;
   cell_start.y=tileY*tile_pos.y;
   POINT cell_end;
   cell_end.x=cell_start.x+tileX;
   if(cell_end.x>cell_size.cx) cell_end.x=cell_size.cx;
   cell_end.y=cell_start.y+tileY;
   if(cell_end.y>cell_size.cy) cell_end.y=cell_size.cy;
   for(int y=cell_start.y;y<cell_end.y;++y) {
    unsigned short *dest=pixels+y*cell_size.cx+cell_start.x;
    int srcTop=Scale*y;
    int srcBottom=srcTop+Scale;
    if(srcBottom>charSize.cy) srcBottom=charSize.cy;
    for(int x=cell_start.x;x<cell_end.x;++x) {
     unsigned int intensity=0;
     int srcLeft=Scale*x;
     int srcRight=srcLeft+Scale;
     if(srcRight>charSize.cx) srcRight=charSize.cx;
     for(int row=srcTop;row<srcBottom;++row) {
      // Compute the indices into the BMP and surface
      int index=(row-tile_origin.y)*192+(srcLeft-tile_origin.x)*3;
      // Loop over each column
      for(int col=srcLeft;col<srcRight;++col) {
       // Get the pixel color at this location
       unsigned char sample=g_fontCharsGdiState->bits[index];
       index+=3;
       intensity+=(sample>>4)&15;
      }
     }
     // Convert the pixel intensity from 8bit to 4bit and store it in our buffer
     unsigned short alpha=(intensity+halfArea)/area;
     *dest++=0xfff|(alpha<<12);
    }
   }
  }
 }
 // Save information about this character in our list
 FontCharsClassCharDataStruct *data=new FontCharsClassCharDataStruct;
 data->Value=glyph;
 data->Width=cell_size.cx;
 data->Bearing=(1-Scale-origin)/Scale;
 data->Buffer=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 glyphs[glyph]=reinterpret_cast<int>(data);
 // Advance the character position
 CurrPixelOffset+=CharHeight*cell_size.cx;
 return data;
}
