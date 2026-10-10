// ?rva002E916A@Rva002E7388Owner@@QAE_NHH@Z
// partial score=0.9031511900771035 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ZH checkDestination supplies the rectangular footprint loop as a semantic
// guide. Native2E916A..2E931F RET8 independently adds layer compatibility,
// height variation and an exempt-cell line check; original method is unknown.
enum PathfindLayerEnum { LAYER_UNKNOWN=0,LAYER_GROUND=1 };
struct Coord3D;
struct ICoord2DBase { int x,y; };
struct ICoord2D:public ICoord2DBase { public:bool operator!=(const ICoord2DBase &)const; };
struct Rva002E8145Info;
class PathfindCell;
class Pathfinder {public:PathfindCell *getCell(PathfindLayerEnum,int,int);private:int rva002E8145(const ICoord2D*,const ICoord2D*,PathfindLayerEnum,Rva002E8145Info*);friend class Rva002E7388Owner;};
class Rva002E6DC4 {public:bool rva002E6DC4(void*,void*);};
class PathfindCell {public:char pad[12];unsigned int flags;};
class TerrainLogic {public:virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();virtual float getGroundHeight(float,float,Coord3D*);virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D*,bool);};
extern TerrainLogic *TheTerrainLogic;
int Rva002E6E8AGet(int);
bool Rva001E3679(int);
int Rva002E6E6CGet(int);
extern "C" double __cdecl fabs(double);
struct Rva002E8145Info {Pathfinder *pathfinder;int skipX,skipY;};
class Rva002E7388Owner {public:bool rva002E916A(int,int);private:Pathfinder *m_00;void *m_04;ICoord2D m_08;PathfindLayerEnum m_10,m_14;ICoord2D m_18;int m_20,m_24;};
bool Rva002E7388Owner::rva002E916A(int cellX,int cellY) {
 bool first=true;float baseline=0.0f;
 for(int i=cellX-m_20;i<cellX+m_24;++i) {
  for(int j=cellY-m_20;j<cellY+m_24;++j) {
   PathfindCell *cell=m_00->getCell(m_10,i,j);
   if(!cell)return false;
   unsigned int flags=cell->flags;
   PathfindLayerEnum layer=(PathfindLayerEnum)((flags>>4)&63);
   if((unsigned char)(flags>>16)&1)return false;
   if(m_14!=layer) {
    if(m_14==LAYER_GROUND) {if(layer!=16)return false;}
    else if(m_14!=16 && ((unsigned char)Rva002E6E8AGet(m_14) || Rva001E3679(m_14))) {if(layer!=16)return false;}
   }
   if(!reinterpret_cast<Rva002E6DC4*>(m_00)->rva002E6DC4(m_04,cell))return false;
   double cx=i*10,cy=j*10;cx+=5.0f;cy+=5.0f;float height=TheTerrainLogic->getLayerHeight(float(cx),float(cy),layer,0,true);
   if(first){baseline=height;first=false;}else if(fabs(double(height)-baseline)>10.0f)return false;
  }
 }
 m_08.x=cellX;m_08.y=cellY;
 cellX=m_14;
 if((unsigned char)Rva002E6E6CGet(cellX) && m_08!=m_18) {
  Rva002E8145Info info={m_00,m_18.x,m_18.y};
  if(m_00->rva002E8145(&m_08,&m_18,(PathfindLayerEnum)cellX,&info))return false;
 }
 return true;
}
