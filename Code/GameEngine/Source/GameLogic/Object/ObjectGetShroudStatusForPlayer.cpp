// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// ?getShroudStatusForPlayer@Object@@QBE?AW4CellShroudStatus@@H@Z @0x0028D2A2 (35B).
// Object shroud gate: when the PartitionData at +0x4C4 is missing or the
// template byte at +0x10E carries 0x20, returns CELLSHROUD_FOGGED (1);
// otherwise tail-calls PartitionData::getShroudedStatus with the same player
// index. Retail shape is mov eax,ecx plus helper null test plus template flag
// test plus tail jmp, else xor/inc. Pinned name and callee pin from packet;
// layout from retail immediates and sibling Object TUs; no donor.

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED,
	CELLSHROUD_COUNT
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED,
	OBJECTSHROUD_COUNT
};

struct ObjectTemplate
{
	unsigned char m_pad[0x10E];
	unsigned char m_byte10E;
	char pad10f[4];
	unsigned char m_kind113;
};

class PartitionData
{
public:
	ObjectShroudStatus getShroudedStatus(int playerIndex);
};

enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Rva00271BCC {public:void rva00271BCC(int,int);};
class Rva002039B6Host {public:void rva002039B6();};
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
class Object;
struct Rva002D76C6Owner;
class Radar {public:void addObject(Object*);void removeObject(Rva002D76C6Owner*);};
extern Radar *TheRadar;
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct ObjectDeadGameLogicState {char pad00[0x40];unsigned frame;char pad44[0x180-0x44];unsigned changedFrame;};
class ObjectDeadModuleInterface {public:virtual void rva0028D2FBCallback(int);};

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	void setEffectivelyDead(bool);
	void rva0028AD7C();
protected:
	Module *findModule(NameKeyType)const;

private:
	char m_pad00[4];
	ObjectTemplate *m_template;
	char m_pad08[0x84-8];
 Rva00271BCC *m_drawable;
 char m_pad88[0x260-0x88];void *m_radarData;
 char m_pad264[0x438-0x264];unsigned char m_privateStatus;
 char m_pad439[0x4C4-0x439];
	PartitionData *m_partition;
};

CellShroudStatus Object::getShroudStatusForPlayer(int playerIndex) const
{
	if (m_partition == 0)
		return CELLSHROUD_FOGGED;
	if ((m_template->m_byte10E & 0x20) == 0)
		return (CellShroudStatus)m_partition->getShroudedStatus(playerIndex);
	return CELLSHROUD_FOGGED;
}

// ZH Object.cpp setEffectivelyDead supplies the dead-bit/radar operation.
// WB CCB470 callgraph corroborates HeroDie, drawable loop,
// radar revival and frame notification; native28D2FB..28D412 proves offsets.
// Existing pin: InactiveBody ctor4BD8BD calls this on getObject() with true,
// exactly as the ZH InactiveBody donor; bit0/private438 proves its purpose.
void Object::setEffectivelyDead(bool dead) {
 if(dead) {
  if(m_privateStatus&1)return;
  m_privateStatus|=1;
  if(m_radarData)TheRadar->removeObject((Rva002D76C6Owner*)this);
  ObjectDeadGameLogicState *logic=(ObjectDeadGameLogicState*)TheGameLogic;
  logic->changedFrame=logic->frame;
  ((Rva002039B6Host*)TheScriptEngine)->rva002039B6();
  if(m_template->m_kind113&4) {
   static NameKeyType heroDie=TheNameKeyGenerator->nameToKey("HeroDie");
   Module *module=findModule(heroDie);
   if(module)((ObjectDeadModuleInterface*)((char*)module+0x10))->rva0028D2FBCallback(0);
  }
  Rva00271BCC *drawable=m_drawable;
  if(drawable)for(int i=1;i<9;++i)drawable->rva00271BCC(i,0);
 } else {
  if(!(m_privateStatus&1))return;
  m_privateStatus&=~1;
  if(!m_radarData)TheRadar->addObject(this);
  ObjectDeadGameLogicState *logic=(ObjectDeadGameLogicState*)TheGameLogic;
  logic->changedFrame=logic->frame;
  ((Rva002039B6Host*)TheScriptEngine)->rva002039B6();
  rva0028AD7C();
 }
}
