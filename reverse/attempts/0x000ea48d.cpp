// ?topple@Rva000EA48DTreeBuffer@@QAE_NHPBUCoord3D@@M@Z
// partial score=0.95 date=2026-10-08
// Banked reference reconstruction of 0x000EA48D..0x000EA644 (439 bytes).
// Primary guide: ZH W3DTreeBuffer::applyTopplingForce at verified BFME1
// donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
// Native wrapper additionally searches 1200 E8-byte tree records by +58 id;
// count +44540; type table stride5C and data +44578; guards state80 and C8.
// TheTerrainLogic +1918 overrides speed when positive. Data38 is the minimum.
// The standalone trial requires adding the independently rowed declaration
// void normalize(); to Coord3D's canonical contract/header (provider35B6 86B).
// A generated scratch header with that declaration emitted 434 versus439:
// return-block placement differs; the reference Matrix3D helpers preserve
// all native identity stores and the subsequent translation. Do not row this
// near miss or add a private canonical Coord3D view. Receiver spelling unknown.
// cl: /ICode/Libraries/Include /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "Lib/Coord3D.h"
#include "matrix3d.h"
class FXList {public: static void doFXPos(const FXList *,const Coord3D *,const Matrix3D *,float,const Coord3D *);};
class TerrainLogic {public: char unknown00[0x1918]; float toppleSpeed;};
extern TerrainLogic *TheTerrainLogic;
struct Rva000EA48DData {
    char unknown00[0x20]; const FXList *fx;
    char unknown24[8]; float velocity,acceleration;
    char unknown34[4]; float minimumSpeed;
};
struct Rva000EA48DTree {
    Vector3 location; char unknown0C[0x34]; int type;
    char unknown44[0x14]; int id;
    char unknown5C[0x10]; float velocity,acceleration; Coord3D direction;
    int state; float angle; char unknown88[4]; unsigned options;
    Matrix3D matrix; char unknownC0[8]; int blocked; char unknownCC[0x1C];
};
struct Rva000EA48DTreeType {char unknown00[0x30]; Rva000EA48DData *data; char unknown34[0x28];};
class Rva000EA48DTreeBuffer {
public:
    char unknown00[0x5C0]; Rva000EA48DTree trees[1200]; int count;
    char unknown44544; bool changed; char unknown44546[2]; Rva000EA48DTreeType types[1];
    bool topple(int id,const Coord3D *direction,float speed);
};
bool Rva000EA48DTreeBuffer::topple(int id,const Coord3D *direction,float speed)
{
    if (!id) return false;
    Rva000EA48DTree *tree=0;
    for (int i=0;i<count;++i) {
        if (trees[i].id==id) {tree=&trees[i];break;}
    }
    if (tree && !tree->state && !tree->blocked) {
    Rva000EA48DData *data=types[tree->type].data;
    float overrideSpeed=TheTerrainLogic->toppleSpeed;
    if (overrideSpeed>0.0f) speed=overrideSpeed;
    else if (speed<data->minimumSpeed) speed=data->minimumSpeed;
    tree->direction=*direction;
    tree->direction.normalize();
    tree->angle=0.0f;
    tree->velocity=speed*data->velocity;
    tree->acceleration=speed*data->acceleration;
    tree->state=1;
    tree->options=0;
    Coord3D pos;
    pos.x=tree->location.X;pos.y=tree->location.Y;pos.z=tree->location.Z;
    FXList::doFXPos(data->fx,&pos,0,0.0f,0);
    changed=true;
    tree->matrix.Make_Identity();
    tree->matrix.Set_Translation(tree->location);
    return true;
    }
    return false;
}
