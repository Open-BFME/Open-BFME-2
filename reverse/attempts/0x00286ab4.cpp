// ?rva00286AB4@FireLogicSystem@@QAEXPBUCoord3D@@0MHHHH_N@Z
// partial score=0.88 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /EHsc /MD /ICode/Libraries/Include
// Banked reconstruction: retail 0x00286AB4..0x00286CC4 (528B), WB
// 0x00C395D0 names FireLogicSystem::ChangeBurnRate and Map/FireLogicSystem.cpp.
// Native proves eight stack arguments (RET20), grid rows +70, counts +78/+7C,
// 20-byte cell stride, fuel +4, burn rate +6, and pending tree +84. Slot +4C
// of canonical TheTerrainLogic is isUnderwater (TerrainLogicWater.cpp).
// No applicable clean donor for this function exists at BFME1 ba7ddda7e8.
// Current emitted body is 525B, frame 2C versus retail 28. Bounds and inner
// saturation/removal behavior agree; coordinate evaluation and SSE register
// choices remain different. The native comparison processes unordered dot
// products (only threshold > dot skips), so retain that behavior.
// Native erase argument is constructed on the stack, consistent with the
// STLport iterator copy constructor. Existing 2860CF provider is declared int;
// this typed iterator interface is NOT yet a recovered provider and remains
// unresolved. Do not add a pin/alias: reconcile and verify that owner's ABI.
// No nonmatching body is installed in Code; this file is evidence only.
#include "Lib/Coord3D.h"
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class FireBurnTerrainView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
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
    virtual bool isUnderwater(float,float,float *,float *,int);
};
class Rva00285BEC {
public:
    Rva00285BEC(int,int);
    virtual ~Rva00285BEC();
    unsigned char state[16];
};
class Rva00285672;
struct Rva00286214Node;
class Rva00286214 { public: Rva00286214Node *rva00286214(const Rva00285672 *); };
struct Rva002860CFIterator {
    Rva00286214Node *node;
    Rva002860CFIterator(Rva00286214Node *value): node(value) {}
    Rva002860CFIterator(const Rva002860CFIterator &value): node(value.node) {}
};
class Rva002860CFHost { public: void rva002860CF(Rva002860CFIterator); };
struct FireBurnCellView {
    int type;
    unsigned short fuel,burnRate;
    unsigned int flammability;
    unsigned int other;
    void *objects;
};
struct FireBurnPendingView { Rva00286214Node *sentinel; int count; };
class FireLogicSystem {
public:
    void rva00286AB4(const Coord3D *,const Coord3D *,float,int,int,int,int,bool);
private:
    unsigned char prefix[0x70];
    FireBurnCellView **cells;
    int word74,rows,columns,word80;
    FireBurnPendingView pending;
};
void FireLogicSystem::rva00286AB4(const Coord3D *origin,const Coord3D *direction,float threshold,int first,int last,int y,int amount,bool existingOnly)
{
    if (y<0 || y>=columns || first>=rows || last<0) return;
    if (first<0) first=0;
    if (last>=rows) last=rows-1;
    double centerX=(first+0.5)*10.0;
    float centerY=(y+0.5)*10.0;
    Coord3D delta;
    delta.x=centerX-origin->x;
    delta.y=centerY-origin->y;
    delta.z=0.0f-origin->z;
    for (;first<=last;++first) {
        FireBurnCellView *cell=&cells[first][y];
        if (!existingOnly || cell->burnRate>=1) {
            float dot=delta.z*direction->z+delta.y*direction->y+delta.x*direction->x;
            if (!(threshold>dot)) {
                if (reinterpret_cast<FireBurnTerrainView *>(TheTerrainLogic)->isUnderwater((first+0.5)*10.0,centerY,0,0,0)) {
                    cell->burnRate=0;
                } else if (amount>0) {
                    if (cell->burnRate==0) cell->flammability|=0x40000000;
                    int increased=cell->burnRate+amount;
                    cell->burnRate=increased>0xffff ? 0xffff : increased;
                } else if (cell->burnRate>0) {
                    if (cell->burnRate<=-amount) {
                        if ((cell->flammability&0x40000000)==0) {
                            Rva00285BEC key(first*10+5,y*10+5);
                            Rva002860CFIterator node(reinterpret_cast<Rva00286214 *>(&pending)->rva00286214(reinterpret_cast<const Rva00285672 *>(&key)));
                            if (node.node!=pending.sentinel) reinterpret_cast<Rva002860CFHost *>(&pending)->rva002860CF(node);
                        }
                        cell->flammability&=~0x40000000;
                        cell->burnRate=0;
                    } else cell->burnRate+=amount;
                }
            }
        }
        delta.x+=10.0f;
    }
}
