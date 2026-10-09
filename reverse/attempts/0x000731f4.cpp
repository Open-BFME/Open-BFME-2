// ?setShroudLevel@W3DShroud@@QAEXHHE_N@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
class GlobalData { public: char pad[0xBEA]; unsigned char alpha; };
extern GlobalData *TheGlobalData;
class Rva000729CC { public: void rva00073CC0(int,int,int,int); };
class BaseHeightMapRenderObjClass { public: char pad[0x387C]; Rva000729CC *taint; };
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class BfmeTaintManager { public: int rva006C0840(int,int); };
extern BfmeTaintManager *TheTaintManager;
unsigned short __cdecl Rva00072D5DShroudPixel(unsigned char);
class W3DShroud { public: void setShroudLevel(int,int,unsigned char,bool);
 int width,height; char pad08[0x10]; unsigned short *data; char pad1c[0x1c];
 unsigned char *levels; char pad3c[12]; bool track; char pad49[3]; _STL::set<int> dirty;
};
void W3DShroud::setShroudLevel(int x,int y,unsigned char level,bool textureOnly) {
 if(!data) return;
 if(x>=width) return;
 if(y>=height) return;
 if(level<TheGlobalData->alpha) level=TheGlobalData->alpha;
 if(!textureOnly) {
  int cell=x+y*width; levels[cell]=level;
  if(track) dirty.insert(cell);
 }
 data[x+y*width]=Rva00072D5DShroudPixel(level);
 Rva000729CC *taint=TheTerrainRenderObject->taint;
 if(taint && TheTaintManager) taint->rva00073CC0(x,y,TheTaintManager->rva006C0840(x,y),true);
}
