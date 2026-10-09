// cl: /O1 /G7 /arch:SSE /MD /EHsc
// stlport
// Native AEAA6..AEBC7 RET20,289B. Tile draw11580A calls this five times.
// Target four-byte owning texture return (hidden stack result), copy424BB,
// assign424D0 and cleanup61ED10 establish lifetime. Fourth input is a full
// 32-bit selector: native loads/indexes the entire word. First three inputs
// are unused. BFME1 f98983a7 WorldHeightMapGetTerrainTexture.cpp supplies the
// lazy-cache/terrain-construction semantic lead; this grid lookup differs.
// Native record span80BC has stride36; signed word at first+46 is shifted2;
// count80C8 and40-byte records80CC contain start/count/width at4/8/C.
// Two caller selectors0/1 address cache120D8; original type names and the
// purpose of the shifted index remain unknown. ConstructorEF902 makes an
// owning one-word holder; native local cleanup proves the inherited ABI view.
// updateCliff is independently recovered atEF63F in TerrainTex.cpp.
#include <vector>
class TextureClass {public:void Release_Ref();};
template<class T>class RefCountPtr {public:
 RefCountPtr(T*p=0):m_ptr(p){}
 RefCountPtr(const RefCountPtr&);
 const RefCountPtr &operator=(const RefCountPtr&);
 ~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();}
 bool isValid()const{return m_ptr!=0;}
private:T*m_ptr;
};
class Rva000EF902 : public RefCountPtr<TextureClass> {public:Rva000EF902(int,int,int);};
class TileData;
class TerrainTextureClass {public:int updateCliff(TileData**,int,int,int,int);};
class GlobalData {public:char unknown00[0x49];bool m_flag49;};extern GlobalData *TheWritableGlobalData;
struct IndexRecord36 {char unknown00[0x22];short indexWord;};
struct TerrainTextureGridView {int unknown00,start,count,width;char unknown10[0x18];};
class WorldHeightMap {public:
 RefCountPtr<TextureClass> rva000AEAA6(int,int,int,int selector);
private:
 char unknown00[0xB0];TileData *tileData[0x2003];
 _STL::vector<IndexRecord36> m_records;
 int m_numGrids;TerrainTextureGridView m_grids[1024];char unknown120CC[12];
 RefCountPtr<TextureClass> m_cached[2];
};
RefCountPtr<TextureClass> WorldHeightMap::rva000AEAA6(int,int,int,int selector) {
 RefCountPtr<TextureClass> &cached=m_cached[selector];
 if(cached.isValid())return cached;
 if(selector==1 && !TheWritableGlobalData->m_flag49)return RefCountPtr<TextureClass>(0);
 if(m_records.size()<2)return RefCountPtr<TextureClass>(0);
 int index=m_records[1].indexWord>>2;
 for(int i=0;i<m_numGrids;++i) {
  if(index>=m_grids[i].start && index<m_grids[i].start+m_grids[i].count) {
   Rva000EF902 texture(m_grids[i].width*64,m_grids[i].width*64,25);
   ((TerrainTextureClass*)&texture)->updateCliff(tileData,m_grids[i].start,m_grids[i].count,m_grids[i].width,selector);
   cached=texture;
   return cached;
  }
 }
 return RefCountPtr<TextureClass>(0);
}
