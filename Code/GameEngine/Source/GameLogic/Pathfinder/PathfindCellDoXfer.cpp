// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
// NEW 0052D84C..0052DA1C 464B RET4 CRC-only PathfindCell::DoXfer.
// WB12D6610 names purpose and transfer order. Native offsets independently
// corroborated by PathfindCell constructor/reset and bitfield setters.
enum ObjectID{INVALID_OBJECT_ID=0};
struct ICoord2D{int x,y;};
class Xfer{public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual bool IsCRC()const;
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual Xfer&xferICoord2D(ICoord2D*);
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual Xfer&xferInt(int*);
virtual Xfer&xferUnsignedShort(unsigned short*);
};
void XferObjectID(Xfer*,ObjectID*);
struct CellXferObject{char pad[0x74];ObjectID id;};
struct CellXferLink{CellXferLink*next,*previous;CellXferObject*object;};
struct CellXferInfo{
 ICoord2D coordinates;char unknown8[8];unsigned short first,second;CellXferLink*lists[5];ObjectID owner;
 unsigned state0:1;unsigned state1:1;unsigned state2:1;unsigned state3:1;unsigned state4:1;unsigned unknown:27;
};
class PathfindCell{public:void DoXfer(Xfer*);
 CellXferInfo*info;unsigned unknown4;unsigned short first,second;
 unsigned type:4;unsigned layer:6;unsigned field10:6;unsigned pinched:1;unsigned gate:1;unsigned bit18:1;unsigned field19:2;unsigned bit21:1;unsigned bit22:1;unsigned bit23:1;unsigned high:8;
};
void PathfindCell::DoXfer(Xfer*xfer){
 if(!xfer->IsCRC())return;
 if(info){
  xfer->xferICoord2D(&info->coordinates);
  xfer->xferUnsignedShort(&info->first);xfer->xferUnsignedShort(&info->second);
  for(int i=0;i<5;++i)for(CellXferLink*p=info->lists[i];p;p=p->next){ObjectID id=p->object->id;XferObjectID(xfer,&id);}
  XferObjectID(xfer,&info->owner);
  int state0=info->state0;xfer->xferInt(&state0);
  int state1=info->state1;xfer->xferInt(&state1);
  int state2=info->state2;xfer->xferInt(&state2);
  int state3=info->state3;xfer->xferInt(&state3);
  int state4=info->state4;xfer->xferInt(&state4);
 }
 xfer->xferUnsignedShort(&first);
 int cellType=type;xfer->xferInt(&cellType);
 int cellLayer=layer;xfer->xferInt(&cellLayer);
 int cellField10=field10;xfer->xferInt(&cellField10);
 int cellPinched=pinched;xfer->xferInt(&cellPinched);
 int cellGate=gate;xfer->xferInt(&cellGate);
 int cellBit22=bit22;xfer->xferInt(&cellBit22);
 int cellBit23=bit23;xfer->xferInt(&cellBit23);
 int cellField19=field19;xfer->xferInt(&cellField19);
}
