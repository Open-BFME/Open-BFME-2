// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?rva002D7FAE@Rva002D7FAEOwner@@QAEXPAVObject@@@Z @0x002D7FAE 62B: list
// lookup with side effect (thiscall, 1 Object arg, void). Null arg or
// null controlling player bails; walks the intrusive list at m_14
// (data +4, next +8) for the arg; on a hit stores pinned cdecl
// 0x002D7BFD(player+0x280) into node+0xc. Callee is landed
// getControllingPlayer. Views minimal; exact identities unproven.
enum Relationship
{
	REL_ENEMY = 0,
	REL_NEUTRAL = 1,
	REL_ALLY = 2
};
class Team;
class Player
{
public:
	Relationship getRelationship(const Team *t) const;
	char m_pad00[0x280];
	int m_280; // +0x280
};

class Player;
class RadarObject;
class Team;
class Rva00373EC6;
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
class Object
{
public:
	Object *getNextObject() { return m_next; }
	void friend_setRadarData(RadarObject *data) { m_radarData = data; }
	ObjectID getID() const { return m_id; }
	bool isNeutralControlled() const;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	int getIndicatorColor() const;
	bool isLocallyControlled() const;
	unsigned char m_pad0[4];
	void *m_4;
	unsigned char m_pad8[0x38-8];
	Coord3D m_pos; // +0x38, retained for the existing list search
	unsigned char m_pad44[0x74-0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x8C-0x78];
	Object *m_next; // +0x8C
	unsigned char m_pad90[0x94-0x90];
	unsigned int m_destroyed; // native load-side radar guard
	unsigned char m_pad98[0x250-0x98];
	void *m_250;
	unsigned char m_pad254[0x260-0x254];
	RadarObject *m_radarData;
	unsigned char m_pad264[0x304-0x264];
	Team *m_304;
};

struct Rva002D7FAENode
{
	void *m_00;
	Object *m_04;
	Rva002D7FAENode *m_08;
	int m_0c;
};

class Rva002D7FAEOwner
{
public:
	void rva002D7FAE(Object *obj);

private:
	char m_pad[0x14];
	Rva002D7FAENode *m_14;
};

int __cdecl rva002D7BFD(int x);

// ?rva002D7FAE@Rva002D7FAEOwner@@QAEXPAVObject@@@Z
void Rva002D7FAEOwner::rva002D7FAE(Object *obj)
{
	if (obj == 0)
		return;
	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return;
	Rva002D7FAENode *node = m_14;
	while (node != 0) {
		if (node->m_04 == obj)
			goto FOUND;
		node = node->m_08;
	}
	return;
FOUND:
	node->m_0c = rva002D7BFD(player->m_280);
}


// BFME 1 ba7ddda7 Rva00107A50RadarColor.cpp supplies the RGB/HSV saturation
// semantic guide. Target 2D7BFD..2D7CC6 proves all 201 bytes: four unpacked
// floats, RGB/HSV temporaries, 1.6 saturation scale clamped to 1, then byte
// channel casts and ARGB packing. Direct float-to-byte casts preserve native
// x87 truncation under /arch:SSE; an intermediate int changes that codegen.
// The local RGB/HSV pair keeps target stack offsets; it is scratch storage,
// not a claimed persistent target class layout. Original helper name unknown.
class Vector3 {public:float X,Y,Z;};
void Rva002D2ACAGet(int,float*,float*,float*,float*);
void RGB_To_HSV(Vector3&,const Vector3&);
void HSV_To_RGB(Vector3&,const Vector3&);
int rva002D7BFD(int color) {
float red,green,blue,alpha;
struct {Vector3 rgb,hsv;} vectors;
Rva002D2ACAGet(color,&red,&green,&blue,&alpha);
vectors.rgb.X=red;vectors.rgb.Y=green;vectors.rgb.Z=blue;
RGB_To_HSV(vectors.hsv,vectors.rgb);
vectors.hsv.Y*=1.6f;
if(vectors.hsv.Y>1.0f)vectors.hsv.Y=1.0f;
HSV_To_RGB(vectors.rgb,vectors.hsv);
unsigned char alphaByte=(unsigned char)(alpha*255.0f);
unsigned char redByte=(unsigned char)(vectors.rgb.X*255.0f);
unsigned char greenByte=(unsigned char)(vectors.rgb.Y*255.0f);
unsigned char blueByte=(unsigned char)(vectors.rgb.Z*255.0f);
return (alphaByte<<24)|(redByte<<16)|(greenByte<<8)|blueByte;
}
