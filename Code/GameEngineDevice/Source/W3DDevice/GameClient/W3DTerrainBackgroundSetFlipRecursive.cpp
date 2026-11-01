// ?setFlipRecursive@W3DTerrainBackground@@QAEXHHH@Z
// retail 0x00112898, 569 bytes (WB setInMeshRecursive family).
// Lever (W7-MP3 r8): explicit volatile reads of m_yOrigin keep the
// two origin subtractions in memory homes and closes the spill/subtract wall.
// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG
class BoundedShortGrid 
{
 public:short load(int,int);
 
};
class Rva0006AB49BitPlane 
{
 public:bool test(int,int) const;
 
};
class Rva000ABD19 
{
 public:bool rva000ABD19(int,int);
 
};
class Rva000AD9AB 
{
 public:void rva000AD9AB(int,int,bool);
 
};
class WorldHeightMap 
{
 public:
 __declspec(dllimport) __forceinline int getXExtent() { return m_width; }
 __declspec(dllimport) __forceinline int getYExtent() { return m_height; }
char pad00[8];
 int m_width;
 int m_height;
 // Keep these wrappers inlined without emitting alternative external bodies.
 // The caller has no relocations to either wrapper; see terrain-inline-link-20261015.
 __declspec(dllimport) __forceinline unsigned short getHeight(int x,int y)
 {
  return (unsigned short)((BoundedShortGrid*)this)->load(x,y);
  
 }
 __forceinline bool getFlag(int x,int y)
 {
  return ((Rva0006AB49BitPlane*)this)->test(x,y);
  
 }
 __forceinline bool hasDetail(int x,int y)
 {
  return ((Rva000ABD19*)this)->rva000ABD19(x,y);
  
 }
 
};
class W3DTerrainBackground 
{
 public:
 void setFlipRecursive(int,int,int);
 void setFlipRecursive(int,int,int,float);
 bool isEdgeAligned(int,int,int);
 char pad00[0x50];
 int m_xOrigin;
 int m_yOrigin;
 int m_width;
 WorldHeightMap*m_map;
 char pad60[0x28];
 int m_baseDivisor;
 
};
void W3DTerrainBackground::setFlipRecursive(int xOffset,int yOffset,int width) 
{
 int limitX=m_map->getXExtent()-1,limitY=m_map->getYExtent()-1;
 bool match=true;
 int minX=m_xOrigin+xOffset,minY=(*(volatile int *)&m_yOrigin)+yOffset;
 int cornerHeight=m_map->getHeight(minX,minY);
 bool flag=m_map->getFlag(minX,minY);
 for(int i=0;i<=width && match;i+=m_baseDivisor) 
 {
  for(int j=0;j<=width;j+=m_baseDivisor) 
  {
   int k=minX+i;
   k=k<limitX?k:limitX;
   int l=minY+j;
   l=l<limitY?l:limitY;
   if(cornerHeight!=m_map->getHeight(k,l)||m_map->hasDetail(k,l)||(i<width&&j<width&&m_map->getFlag(k,l)!=flag)) 
   {
    match=false;
    break;
    
   }
   
  }
  
 }
 if(width==m_baseDivisor)match=true;
 if(match) 
 {
  int maxX=minX+width;
  maxX=maxX<limitX?maxX:limitX;
  int maxY=minY+width;
  maxY=maxY<limitY?maxY:limitY;
  int x0=minX;
  int y1=maxY-(*(volatile int *)&m_yOrigin);
  *(volatile int*)&x0-=(m_map ? m_xOrigin : m_xOrigin);
  bool c0=isEdgeAligned(x0,y1,width);
  int x1=maxX-m_xOrigin;
  bool c1=isEdgeAligned(x1,y1,width);
  int y0=minY;
  *(volatile int*)&y0-=(*(volatile int *)&m_yOrigin);
  bool c2=isEdgeAligned(x1,y0,width);
  bool c3=isEdgeAligned(x0,y0,width);
  if(c3)((Rva000AD9AB *)m_map)->rva000AD9AB(minX,minY,true);
  if(c2)((Rva000AD9AB *)m_map)->rva000AD9AB(maxX,minY,true);
  if(c1)((Rva000AD9AB *)m_map)->rva000AD9AB(maxX,maxY,true);
  if(c0)((Rva000AD9AB *)m_map)->rva000AD9AB(minX,maxY,true);
  return;
  
 }
 int halfWidth=width/2;
 setFlipRecursive(xOffset,yOffset,halfWidth);
 setFlipRecursive(xOffset,yOffset+halfWidth,halfWidth);
 setFlipRecursive(xOffset+halfWidth,yOffset,halfWidth);
 setFlipRecursive(xOffset+halfWidth,yOffset+halfWidth,halfWidth);
 
}
