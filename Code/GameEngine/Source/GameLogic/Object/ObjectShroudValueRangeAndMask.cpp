// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-
// Object::ShroudGetValueRangeAndMask, retail28E5E0..28E775 (405B).
// Identity: WB CE1020 names this Object.cpp method (line11108), and its
// named controlling-player/vision/shroud/status calls map independently to
// existing retail providers. No clean BF1/ZH implementation was found for
// this BFME-specific selector; reuse existing ObjectPartitionShroudQueries
// inheritance shape, with target bytes proving incoming secondary base+64.
// Target layout: template4, body254, status438, active454; template kind7,
// radii4AC/530/540, special count5D4, vision/reveal ushort5DA/5DE. The view
// covers only accessed prefixes, not full object/template extents.
// Status2/38 and selector0/1/2 are observed indices; original enum names
// remain unresolved. Named playerIndex keeps getControllingPlayer before
// relationship argument pushes; original float conversion and return paths
// retained, including -1 with untouched mask and early inactive count.

class Player{public:char pad[0x54];int index;};
class PlayerList{public:int getPlayersWithRelationship(int,unsigned,bool);};extern PlayerList *ThePlayerList;
enum ObjectStatusTypes{STATUS2=2,STATUS38=38};
class BodyModuleInterface{public:virtual void s0();virtual void s4();virtual void s8();virtual void sC();virtual float getHealth()const;};
struct ShroudTemplateView{char pad0[0x108];unsigned char kinds[0x20];char pad128[0x4ac-0x128];float radius;char pad4B0[0x530-0x4b0];float reveal;char pad534[12];float special;char pad544[0x5d4-0x544];unsigned specialCount;char pad5d8[2];unsigned short visionCount;char pad5dc[2];unsigned short revealCount;};
class ObjectThingBase{public:virtual ~ObjectThingBase();protected:const ShroudTemplateView *m_template;char pad8[0x64-8];};
class ObjectShroudClient{public:virtual bool ShroudHideIfFogged(int)const=0;virtual float ShroudGetValueRangeAndMask(int,unsigned*,unsigned*)const=0;char pad4[4];};
class Object:public ObjectThingBase,public ObjectShroudClient{public:
 Player *getControllingPlayer()const;float getShroudClearingRange()const;float getVisionRange()const;bool testStatus(ObjectStatusTypes)const;
 virtual bool ShroudHideIfFogged(int)const;virtual float ShroudGetValueRangeAndMask(int,unsigned*,unsigned*)const;
private:char pad6C[0x254-0x6c];BodyModuleInterface *body;char pad258[0x438-0x258];unsigned char status;char pad439[0x454-0x439];bool active;
};
float Object::ShroudGetValueRangeAndMask(int type,unsigned *count,unsigned *mask)const{
 if(!active)return -1.0f;
 if(!getControllingPlayer() || (status&1) || getShroudClearingRange()<=0.0f || testStatus(STATUS38)){*count=0;return -1.0f;}
 switch(type){
 case 0:
  if(testStatus(STATUS2))break;
  *count=m_template->visionCount;*mask=1U<<getControllingPlayer()->index;return getVisionRange();
 case 1:
  if(testStatus(STATUS2))break;
  *count=m_template->revealCount;*mask=1U<<getControllingPlayer()->index;
  {float range=m_template->reveal;if(range==-1.0f && !(m_template->kinds[0]&0x80)){*count=(unsigned)body->getHealth();range=m_template->radius;}return range;}
 case 2:
  if(m_template->kinds[0]&0x80){*count=m_template->specialCount;if(*count>0){int playerIndex=getControllingPlayer()->index;*mask=ThePlayerList->getPlayersWithRelationship(playerIndex,3,false);return m_template->special;}return -1.0f;}
  break;
 }
 *count=0;return -1.0f;
}
