// cl: /O2 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// stlport
// platformsdk
// FontCharsClass::loadCharBitmap: rasterizes one glyph through the shared GDI DIB in 64x64 tiles and
// box-filters it by Scale into 4-bit alpha (ZH Store_GDI_Char semantics, Thai sibling 0x00157FF0 shape).
// Tile, origin and cell coordinates are POINT/SIZE pairs; a missing glyph caches the -1 sentinel.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// Preserve the existing opaque-handle ABI of FontGlyphDCSelection.
#define NO_STRICT
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <map>
#include <string.h>

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
 SIZE tile_size={Scale*tileX,Scale*tileY};
 SIZE charSize;
 if(!::GetTextExtentPoint32W(g_fontCharsGdiState->dc,&ch,1,&charSize))
  charSize.cx=charSize.cy=1;
 SIZE cell_size;
 cell_size.cx=(Scale+charSize.cx-1)/Scale+overlap;
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
   ::ExtTextOutW(g_fontCharsGdiState->dc,-tile_origin.x,-tile_origin.y,2,&rect,&ch,1,0);
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
    int y0=Scale*y;
    int y1=y0+Scale;
    if(y1>charSize.cy) y1=charSize.cy;
    for(int x=cell_start.x;x<cell_end.x;++x) {
     unsigned int intensity=0;
     int x0=Scale*x;
     int x1=x0+Scale;
     if(x1>charSize.cx) x1=charSize.cx;
     for(int row=y0;row<y1;++row) {
      // Compute the indices into the BMP and surface
      int index=(row-tile_origin.y)*192+(x0-tile_origin.x)*3;
      // Loop over each column
      for(int col=x0;col<x1;++col) {
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
 data->Value=ch;
 data->Width=cell_size.cx;
 data->Bearing=0;
 data->Buffer=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 // Insert this character into our array
 if(ch<256) directChars[ch]=data; else pages[ch-first]=data;
 // Advance the character position
 CurrPixelOffset+=CharHeight*(cell_size.cx+overlap);
 // Return the index of the entry we just added
 return data;
}
