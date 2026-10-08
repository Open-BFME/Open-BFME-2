// ?setFlipRecursive@W3DTerrainBackground@@QAEXHHHM@Z
// partial score=0.808775 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG
class BoundedShortGrid {public:short rva00062A58(int,int);};
class Rva0006AB49BitPlane {public:bool test(int,int) const;};
class Rva000ABD19 {public:bool rva000ABD19(int,int);};
class Rva000AD9AB {public:void rva000AD9AB(int,int,bool);};
class WorldHeightMap {public:char pad00[8];int width,height;
 __forceinline unsigned short getHeight(int x,int y){return (unsigned short)((BoundedShortGrid*)this)->rva00062A58(x,y);}
 __forceinline bool getFlag(int x,int y){return ((Rva0006AB49BitPlane*)this)->test(x,y);}
 __forceinline bool hasDetail(int x,int y){return ((Rva000ABD19*)this)->rva000ABD19(x,y);}
 __forceinline void setFlipState(int x,int y,bool b){((Rva000AD9AB*)this)->rva000AD9AB(x,y,b);}
};
class W3DTerrainBackground {public:
 void setFlipRecursive(int,int,int);
 void setFlipRecursive(int,int,int,float);
 bool isEdgeAligned(int,int,int);
 char pad00[0x50];int m_xOrigin,m_yOrigin,m_width;WorldHeightMap*m_map;char pad60[0x28];int m_baseDivisor;
};

void W3DTerrainBackground::setFlipRecursive(int xOffset,int yOffset,int width,float tolerance) {
 int minX=m_xOrigin+xOffset,minY=m_yOrigin+yOffset;
 int limitX=m_map->width-1,limitY=m_map->height-1;
 bool match=true;
 int maxX=minX+width;maxX=maxX<limitX?maxX:limitX;
 int maxY=minY+width;maxY=maxY<limitY?maxY:limitY;
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
  map=m_map;
  map->setFlipState(minX,minY,true);
  m_map->setFlipState(right,minY,true);
  m_map->setFlipState(right,bottom,true);
  m_map->setFlipState(minX,bottom,true);
  return;
 }
 int halfWidth=width/2;
 setFlipRecursive(xOffset,yOffset,halfWidth,tolerance);
 setFlipRecursive(xOffset,yOffset+halfWidth,halfWidth,tolerance);
 setFlipRecursive(xOffset+halfWidth,yOffset,halfWidth,tolerance);
 setFlipRecursive(xOffset+halfWidth,yOffset+halfWidth,halfWidth,tolerance);
}
