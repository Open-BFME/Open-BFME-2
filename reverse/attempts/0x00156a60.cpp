// ?loadCharBitmap@FontCharsClass@@AAEPBUFontCharsClassCharDataStruct@@G@Z
// partial score=0.372 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /G7
// ZH render2dsentence.cpp Store_GDI_Char is the semantic donor. BFME2 adds
// glyph validation, the shared64x64 GDI bitmap, scaled tiled supersampling
// and ascent padding. Offsets, imports and each extension are target evidence.
// Existing opaque loadCharBitmap pin gives the ABI; no new function name.
#include <windows.h>
#include <string.h>
#define min(a,b) ((a)<(b)?(a):(b))

extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(HDC,LPCWSTR,int,LPWORD,DWORD);
class FontCharsClassGdiState {public: int refs;HBITMAP oldBitmap,bitmap;unsigned char *bits;HDC dc;};
extern FontCharsClassGdiState *g_fontCharsGdiState;

class BfmeSelectedGdiFont {
public:
 BfmeSelectedGdiFont(HDC dc,HGDIOBJ font):m_dc(dc),m_old(SelectObject(dc,font)){}
 ~BfmeSelectedGdiFont(){SelectObject(m_dc,m_old);}
private:HDC m_dc;HGDIOBJ m_old;
};
struct FontCharsClassCharDataStruct {unsigned short Value;short Width,ExtraSpacing;unsigned short *Buffer;};
struct FontCharsBitmapBuffer {unsigned short *Buffer;};
class FontCharsClass {
private:
 FontCharsClassCharDataStruct const *loadCharBitmap(unsigned short);
private:
 void Update_Current_Buffer(int);
 char fields00[0x14];
 FontCharsBitmapBuffer **buffers; // +14
 char fields18[8];int count;int growth; // +20
 int pixelOffset,height,ascent,overhang,overlap; // +28..38
 float pointSize;int sampleScale;int name;HFONT font; // +3C..48
 FontCharsClassCharDataStruct const *ascii[256];
 FontCharsClassCharDataStruct const **unicode;
 char tree[12];unsigned short first,last;
};
// ?loadCharBitmap@FontCharsClass@@AAEPBUFontCharsClassCharDataStruct@@G@Z present-unmatched
FontCharsClassCharDataStruct const *FontCharsClass::loadCharBitmap(unsigned short ch) {
 HFONT selectedFont=font;
 HDC dc=g_fontCharsGdiState->dc;
 BfmeSelectedGdiFont selection(dc,selectedFont);
 unsigned int glyph=0xFFFF;
 GetGlyphIndicesW(g_fontCharsGdiState->dc,&ch,1,(WORD *)&glyph,1);
 if ((unsigned short)glyph==0xFFFF) {
  if(ch<256) ascii[ch]=(const FontCharsClassCharDataStruct *)-1;
  else unicode[ch-first]=(const FontCharsClassCharDataStruct *)-1;
  return (const FontCharsClassCharDataStruct *)-1;
 }
 int sampleArea=sampleScale*sampleScale;
 int sampleRound=sampleArea>>1;
 int tileSize=64/sampleScale;
 int tileWidth=sampleScale*tileSize,tileHeight=sampleScale*tileSize;
 SIZE charSize={tileWidth,tileHeight};
 if(!GetTextExtentPoint32W(g_fontCharsGdiState->dc,&ch,1,&charSize)) charSize.cx=charSize.cy=1;
 int charWidth=(sampleScale+charSize.cx-1)/sampleScale+overlap;
 int charHeight=(sampleScale+charSize.cy-1)/sampleScale;
 Update_Current_Buffer(charWidth);
 unsigned short *buffer=buffers[count-1]->Buffer+pixelOffset;
 int top=ascent/2;
 int bottom=ascent-top;
 unsigned short *data=buffer+top*charWidth;
 memset(buffer,0,(char *)data-(char *)buffer);
 memset(data+charHeight*charWidth,0,bottom*charWidth*2);
 int tilesX=(charWidth+tileSize-1)/tileSize;
 int tilesY=(charHeight+tileSize-1)/tileSize;
 for(int tileY=0;tileY<tilesY;++tileY) {
  for(int tileX=0;tileX<tilesX;++tileX) {
   RECT rect={0,0,tileWidth,charSize.cy};
   ExtTextOutW(g_fontCharsGdiState->dc,-tileX*tileWidth,-tileY*tileHeight,ETO_OPAQUE,&rect,&ch,1,0);
   int firstX=tileX*tileSize,firstY=tileY*tileSize;
   int lastX=firstX+tileSize;
   if(lastX>charWidth)lastX=charWidth;
   int lastY=firstY+tileSize;
   if(lastY>charHeight)lastY=charHeight;
   for(int y=firstY;y<lastY;++y) {
    unsigned short *dest=data+y*charWidth+firstX;
    int sy=y*sampleScale;
    int lastSampleY=sy+sampleScale;
    if(lastSampleY>charSize.cy)lastSampleY=charSize.cy;
    for(int x=firstX;x<lastX;++x) {
     int sx=x*sampleScale,lastSampleX=min(sx+sampleScale,charSize.cx);
     unsigned int alpha=0;
     for(int sampleY=sy;sampleY<lastSampleY;++sampleY) {
      for(int sampleX=sx;sampleX<lastSampleX;++sampleX) {
       unsigned char pixel=g_fontCharsGdiState->bits[((sampleY-tileY*tileHeight)*64+sampleX-tileX*tileWidth)*3];
       alpha+=(pixel>>4);
      }
     }
     unsigned int value=(sampleRound+alpha)/(unsigned int)sampleArea;
     *dest++=(value<<12)|0xFFF;
    }
   }
  }
 }
 FontCharsClassCharDataStruct *record=new FontCharsClassCharDataStruct;
 record->Value=ch;record->Width=charWidth;record->ExtraSpacing=0;
 record->Buffer=buffers[count-1]->Buffer+pixelOffset;
 if(ch<256) ascii[ch]=record;
 else unicode[ch-first]=record;
 pixelOffset+=(charWidth+overlap)*height;
 return record;
}
