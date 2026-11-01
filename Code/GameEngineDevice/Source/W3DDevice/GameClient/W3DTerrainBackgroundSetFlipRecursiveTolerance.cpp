// ?setFlipRecursive@W3DTerrainBackground@@QAEXHHHM@Z
// retail 0x00112AD1, 749 bytes; tolerance overload of 0x00112898, called by 0x00113151.
// Shape follows ZH W3DTerrainBackground::setFlipRecursive (declaration order limitX/limitY,
// match, minX/minY); maxX/maxY as full origin+offset+width expressions leave EBX to map.
// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG
class BoundedShortGrid {public:short load(int,int);};
class Rva0006AB49BitPlane {public:bool test(int,int) const;};
class Rva000ABD19 {public:bool rva000ABD19(int,int);};
class Rva000AD9AB {public:void rva000AD9AB(int,int,bool);};
class WorldHeightMap {public:
 __declspec(dllimport) __forceinline int getXExtent() { return m_width; }
 __declspec(dllimport) __forceinline int getYExtent() { return m_height; }
char pad00[8];int m_width,m_height;
 __declspec(dllimport) __forceinline unsigned short getHeight(int x,int y){return (unsigned short)((BoundedShortGrid*)this)->load(x,y);}
 __forceinline bool getFlag(int x,int y){return ((Rva0006AB49BitPlane*)this)->test(x,y);}
 __forceinline bool hasDetail(int x,int y){return ((Rva000ABD19*)this)->rva000ABD19(x,y);}
};
class W3DTerrainBackground {public:
 void setFlipRecursive(int,int,int);
 void setFlipRecursive(int,int,int,float);

 bool isEdgeAligned(int,int,int);
 char pad00[0x50];int m_xOrigin,m_yOrigin,m_width;WorldHeightMap*m_map;char pad60[0x28];int m_baseDivisor;
};

void W3DTerrainBackground::setFlipRecursive(int xOffset,int yOffset,int width,float tolerance) {
 int limitX=m_map->getXExtent()-1,limitY=m_map->getYExtent()-1;
 bool match=true;
 int minX=m_xOrigin+xOffset,minY=m_yOrigin+yOffset;
 int maxX=m_xOrigin+xOffset+width;maxX=maxX<limitX?maxX:limitX;
 int maxY=m_yOrigin+yOffset+width;maxY=maxY<limitY?maxY:limitY;
 WorldHeightMap *map=m_map;
 int h00=map->getHeight(minX,minY),h10=map->getHeight(maxX,minY),h11=map->getHeight(maxX,maxY),h01=map->getHeight(minX,maxY);
 bool flag=map->getFlag(minX,minY);
 for(int i=0;i<=width && match;++i) {
  for(int j=0;j<=width;++j) {
   int k=minX+i;k=k<limitX?k:limitX;
   int l=minY+j;l=l<limitY?l:limitY;
   if(map->hasDetail(k,l)||(i<width&&j<width&&map->getFlag(k,l)!=flag)) {match=false;break;}
   float x=(float)i/(float)width,y=(float)j/(float)width,height;
   if(y>1.0f-x)height=((float)(h10-h11)*(1.0f-y)+(float)(h01-h11)*(1.0f-x)+(float)h11)*0.0390625f;
   else height=((float)(h01-h00)*y+(float)(h10-h00)*x+(float)h00)*0.0390625f;
   float delta=height-(float)map->getHeight(k,l)*0.0390625f;
   if(delta<0.0f)delta=-delta;
   if(delta>tolerance){match=false;break;}
  }
 }
 if(width==1)match=true;
 if(match) {
  int right=minX+width;right=right<limitX?right:limitX;
  int bottom=minY+width;bottom=bottom<limitY?bottom:limitY;
  ((Rva000AD9AB *)m_map)->rva000AD9AB(minX,minY,true);
  ((Rva000AD9AB *)m_map)->rva000AD9AB(right,minY,true);
  ((Rva000AD9AB *)m_map)->rva000AD9AB(right,bottom,true);
  ((Rva000AD9AB *)m_map)->rva000AD9AB(minX,bottom,true);
  return;
 }
 int halfWidth=width/2;
 setFlipRecursive(xOffset,yOffset,halfWidth,tolerance);
 setFlipRecursive(xOffset,yOffset+halfWidth,halfWidth,tolerance);
 setFlipRecursive(xOffset+halfWidth,yOffset,halfWidth,tolerance);
 setFlipRecursive(xOffset+halfWidth,yOffset+halfWidth,halfWidth,tolerance);
}
