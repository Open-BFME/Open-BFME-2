// ?rva0008CE2E@W3DView@@QAEIPAVCoord2D@@@Z
// cl: /ICode/Libraries/Include/Lib /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /MD /EHsc /Oy- /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native8CE2E..8D134; WB992220 confirms the algorithm and MathCoord3D
// operators. Reference W3DView::scrollBy establishes the scrolling purpose;
// BFME1 revision874e38488c7dcf8cf3343452e8e5371bb3a0e64c reviewed.
// Target member offsets and its boundary-mask return come from native bytes.
// Canonical Coord3D plus field-copy wrapper keep the target value shape.
// Exposing the independently verified inline length body restores readonly
// knowledge. Ending screen/ray-start lifetime after normalization reuses the
// displacement slots and closes the six offsets with retail's64-byte frame.
// Reference W3DView::scrollBy establishes scrolling purpose;
// target adds ray-normalized scrolling and unsigned boundary-mask return.
#include "vector3.h"
#include "vector2.h"
#include "Coord2D.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "W3DViewScrollMath.h"
struct BfmeScrollCoordinates : public Coord3D {
 BfmeScrollCoordinates(){}
 BfmeScrollCoordinates(const Coord3D &v){x=v.x;y=v.y;z=v.z;}
 BfmeScrollCoordinates(float xx,float yy,float zz){x=xx;y=yy;z=zz;}
 BfmeScrollCoordinates& operator+=(const Coord3D&d){x+=d.x;y+=d.y;z+=d.z;return *this;}
};
#include "../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
class Rva0008CE2ESettings
{
public:
	virtual void v0();
	virtual float v1();
	virtual float v2();
	virtual float v3();
	virtual float scrollScale();
	virtual void v5();
	virtual void v6();
	virtual void v7();
};
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class GameClient;extern GameClient *TheGameClient;
struct Rva0008CE2EClient {char pad[0xc0];bool blocked;};
class W3DView {public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual int getWidth();
 virtual void v016();
 virtual int getHeight();

 unsigned rva0008CE2E(Coord2D*);private:void getPickRay(const ICoord2D*,Vector3*,Vector3*);void setCameraTransform();void rva000860AF(Coord3D*);
 char prefix[8];Coord3D position;char gap18[0x3c-0x18];float zoom;char gap40[4];bool constrain;char gap45[0x104-0x45];CameraClass *camera;
 char gap108[0x1dc-0x108];bool rotating;char gap1dd[0x23fc-0x1dd];Coord2D scrollAmount;char gap2404[8];float loX,loY,hiX,hiY;
 char gap241c[0x24c8-0x241c];Rva0008CE2ESettings settings;char gap24cc[0x24f4-0x24cc];float travelled;char gap24f8[9];bool blocked;
};
unsigned W3DView::rva0008CE2E(Coord2D *delta){
 if((reinterpret_cast<Rva0008CE2EClient*>(TheGameClient)->blocked && constrain)||blocked)return 0;
 unsigned bounds=0;
 if(delta && (delta->x!=0 || delta->y!=0)){
  scrollAmount=*delta;
  Vector2 start;start.X=(float)(getWidth()/2);start.Y=(float)(getHeight()/2);
  float aspect=(float)(getWidth()/getHeight());
  Vector2 end;end.X=start.X+delta->x*250.0f;end.Y=start.Y+delta->y*aspect*250.0f;
  Vector3 world;
  {ICoord2D screen;Vector3 rayStart;screen.x=(int)start.X;screen.y=(int)start.Y;
   getPickRay(&screen,&rayStart,&world);world.X=world.X-rayStart.X;world.Y=world.Y-rayStart.Y;world.Z=world.Z-rayStart.Z;}
  world.Z=0;world.Normalize();
  Vector3 unusedStart,unusedEnd;camera->Device_To_World_Space(start,&unusedStart);camera->Device_To_World_Space(end,&unusedEnd);
  BfmeScrollCoordinates pos=position;
  Vector2 side,forward;side.X=-world.X;side.Y=-world.Y;forward.X=world.Y;forward.Y=-world.X;
  float scale=settings.scrollScale()*(zoom*0.25f);
  BfmeScrollCoordinates displacement((delta->x*forward.X+delta->y*side.X)*scale,(delta->x*forward.Y*aspect+delta->y*side.Y)*scale,0);
  travelled+=displacement.length();pos+=displacement;
  if(constrain)rva000860AF(&pos);
  position=pos;
  if(loX>pos.x)bounds=1;if(pos.x>hiX)bounds|=2;
  if(loY>pos.y)bounds|=4;if(pos.y>hiY)bounds|=8;
  rotating=false;setCameraTransform();if(TheTerrainRenderObject)TheTerrainRenderObject->vslot139(1);
 }
 return bounds;
}
