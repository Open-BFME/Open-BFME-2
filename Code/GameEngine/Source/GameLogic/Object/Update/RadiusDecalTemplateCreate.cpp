// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// BFME1 RadiusDecalTemplate creation donors9cbfb551 and ZH RadiusDecal.cpp
// guide creation/visibility semantics. Native calls use a measured40B two
// string descriptor; AudioEventRTS is the existing ctor/dtor provider
// spelling79514/793FA, not a new claim that this descriptor is a sound.
// Native Shadow fields position8,angle20,color setter330995 established by
// creation callers plus exact RadiusDecal update330F98 and clear330DBA.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class AudioEventRTS { public:
 AudioEventRTS();~AudioEventRTS();
 AsciiString first,second;int style;float sizeX,sizeY,offsetX,offsetY,at1C,scale;
 unsigned char at24,allowUpdates,worldAlign;
};
class Shadow { public:
 void rva00330995(int);
 __forceinline void setAngle(float a) {angle=a;}
 __forceinline void setPosition(const Coord3D &p) {position=p;}
 char pad00[8];Coord3D position;char pad14[0xC];float angle;
 char pad24[0x40];bool at64;
};
class RadiusDecal { public:void clear();const void *data;Shadow *decal;bool empty;float previousFrame; };
class AudioManager0029E159 { public:virtual void slot0()=0;virtual void slot1()=0;virtual Shadow *create(AudioEventRTS *)=0; };
extern AudioManager0029E159 *g_00DEC2D4;
class Player { public:char pad00[0x54];int index;char pad58[0x280-0x58];unsigned color; };
class PlayerList { public:char pad00[0x10];Player *local; };
extern PlayerList *ThePlayerList;
static __forceinline void setCoordinates(Coord3D *to,float x,float y,float z) {to->x=x;to->y=y;to->z=z;}
class RadiusDecalTemplate { public:
 void rva0033132D(const Coord3D *,float,const unsigned *,RadiusDecal *);
 void createRadiusDecal(const Coord3D &,float,const Player *,RadiusDecal &) const;
 void rva0033121F(Coord3D,unsigned,void *,RadiusDecal *,float);
 float rva00330D3E(void *);
 AsciiString first,second;int style;float minOpacity,maxOpacity,throbTime;unsigned color;bool onlyOwner;
 char pad1D[3];float sizeX,sizeY;unsigned at28;float rotationSpeed,shrinkRate;
};
void RadiusDecalTemplate::rva0033132D(const Coord3D *pos,float angle,const unsigned *color,RadiusDecal *out) {
 if(first.isEmpty()==true) return;
 if(!pos) return;
 if(sizeX==0.0f) return;
 if(sizeY==0.0f) return;
 out->clear();out->empty=false;
 AudioEventRTS descriptor;
 descriptor.first.set(first);descriptor.second.set(second);
 descriptor.sizeX=sizeY;descriptor.sizeY=sizeY;
 descriptor.allowUpdates=1;descriptor.worldAlign=1;
 descriptor.style=style;descriptor.offsetX=0.0f;descriptor.offsetY=0.0f;
 out->decal=g_00DEC2D4->create(&descriptor);
 if(!out->decal) return;
 out->decal->setAngle(angle);
 out->decal->rva00330995((int)*color);
 Coord3D adjusted;
 setCoordinates(&adjusted,pos->x+descriptor.offsetX,pos->y+descriptor.offsetY,pos->z);
 out->decal->setPosition(adjusted);
 out->data=this;
}
