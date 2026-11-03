// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
// NEW 0052D84C..0052DA1C 464B RET4 CRC-only PathfindCell::DoXfer.
// WB12D6610 names purpose and transfer order. Native offsets independently
// corroborated by PathfindCell constructor/reset and bitfield setters.
enum ObjectID{INVALID_OBJECT_ID=0};
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"
void XferObjectID(Xfer*,ObjectID*);
struct CellXferObject{char pad[0x74];ObjectID id;};
struct CellXferLink{CellXferLink*next,*previous;CellXferObject*object;};
struct CellXferInfo{
 ICoord2D coordinates;char unknown8[8];unsigned short first,second;CellXferLink*lists[5];ObjectID owner;
 unsigned state0:1;unsigned state1:1;unsigned state2:1;unsigned state3:1;unsigned state4:1;unsigned unknown:27;
};
#include "../../../Include/GameLogic/PathfindCell.h"
struct CellXferBits{
 unsigned type:4;unsigned layer:6;unsigned field10:6;unsigned pinched:1;unsigned gate:1;unsigned bit18:1;unsigned field19:2;unsigned bit21:1;unsigned bit22:1;unsigned bit23:1;unsigned high:8;
};
static __forceinline CellXferInfo*cellInfo(const PathfindCell*cell){return (CellXferInfo*)cell->m_info;}
void PathfindCell::DoXfer(Xfer*xfer){
 if(!xfer->IsCRC())return;
 const CellXferBits&bits=*reinterpret_cast<const CellXferBits*>(&m_0C);
 if(m_info){
  xfer->operator==(cellInfo(this)->coordinates);
  xfer->operator==(cellInfo(this)->first);xfer->operator==(cellInfo(this)->second);
  for(int i=0;i<5;++i)for(CellXferLink*cellXferLink=cellInfo(this)->lists[i];cellXferLink;cellXferLink=cellXferLink->next){ObjectID id=cellXferLink->object->id;XferObjectID(xfer,&id);}
  XferObjectID(xfer,&cellInfo(this)->owner);
  int state0=cellInfo(this)->state0;xfer->operator==(state0);
  int state1=cellInfo(this)->state1;xfer->operator==(state1);
  int state2=cellInfo(this)->state2;xfer->operator==(state2);
  int state3=cellInfo(this)->state3;xfer->operator==(state3);
  int state4=cellInfo(this)->state4;xfer->operator==(state4);
 }
 xfer->operator==(m_zone);
 int cellType=bits.type;xfer->operator==(cellType);
 int cellLayer=bits.layer;xfer->operator==(cellLayer);
 int cellField10=bits.field10;xfer->operator==(cellField10);
 int cellPinched=bits.pinched;xfer->operator==(cellPinched);
 int cellGate=bits.gate;xfer->operator==(cellGate);
 int cellBit22=bits.bit22;xfer->operator==(cellBit22);
 int cellBit23=bits.bit23;xfer->operator==(cellBit23);
 int cellField19=bits.field19;xfer->operator==(cellField19);
}
