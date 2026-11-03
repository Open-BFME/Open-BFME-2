// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7
// Native2F4D8B..2F4E54 RET16 full201; callback address independently
// recovered from caller2F6C22. Layer/type bits at cell+C and opaque state
// bytes1C..20 are target-observed. Existing QuickDoesPathExist pin owns
// the four-argument target2F477E. No original names asserted for state bits.
// WB debug shape: the two zero exits are separate return sites, not one ||
// test, which is what keeps retail's single inline exit block.
#include "Lib/Coord3D.h"
typedef bool Bool;
class Object;
#include "../../../Include/GameLogic/PathfindCell.h"
static __forceinline char cellLayerByte(const PathfindCell *cell) {return (char)((cell->m_0C>>4)&0x3F);}
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};
void *rva002EBC59(void *,void *,int,int,int);
#include "../../../Include/GameLogic/AIPathfind.h"
struct LayerProbeObjectView {char pad00[0x38];Coord3D position;};
struct Rva002F4D8BInfo
{
public:
	int cellCallback(void *previousCell, void *currentCell, int cellX, int cellY);
	int cellCallback(PathfindCell *,PathfindCell *,int,int);
	Pathfinder *pathfinder; // +0x00
	Object *object; // +0x04
	void *word08; // +0x08
	Coord3D position; // +0x0C
	int word18; // +0x18
	Bool flag1C; // +0x1C
	Bool flag1D; // +0x1D
	Bool flag1E; // +0x1E
	Bool flag1F; // +0x1F
	Bool flag20; // +0x20
	char m_pad21[0x3];
};
int Rva002F4D8BInfo::cellCallback(PathfindCell *from,PathfindCell *to,int x,int y)
{
 unsigned flags=to->m_0C;
 if(((unsigned char)((flags>>17)&1)!=0 || (char)((flags>>4)&0x3F)>1) && !flag1D && !flag1E && flag1F)return 1;
 if((flags&0xF)==4)return 0;
 if((char)((flags>>4)&0x3F)>1 && !flag1D && flag1E)return 0;
 flag1E=false;
 if(!((Rva002E6DC4 *)pathfinder)->rva002E6DC4(&position,to))return 0;
 Coord3D point;rva002EBC59(&point,object,x,y,cellLayerByte(to));
 if(pathfinder->QuickDoesPathExist(object,&((LayerProbeObjectView *)object)->position,&point,0)) {
  flag1C=true;return 1;
 }
 flag1F=true;
 if(flag20)return 1;
 return flag1D!=0;
}
