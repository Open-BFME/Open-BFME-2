// ?create@GenericObjectCreationNugget@@QBEXPBVObject@@PBUCoord3D@@1I@Z
// stlport
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /ICode/Libraries/Include /DNDEBUG /MD /EHsc
// Native 001F2F0E..001F311B, 525 bytes; WB B03C80, ObjectCreationList.cpp808-841.
// Target facts: creator returns a three-word Object-pointer vector; movement
// uses AI command subobject +20 of Object's +258 AI receiver, then optional
// facing. WB supplies method identity and branch/temporary scopes. Flag names
// describe measured behavior; NuggetCreated is the rowed vector<Object*> that
// reallyCreate (0x001F1634) returns by value.
// The storage-base cleanup at1F1609 is pinned, not recovered in this unit.
// Keep the real AI move helper visible and the receiver as a typed subobject:
// spelling it as a raw +20 pointer changes the parent register allocation.
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <math.h>
#include <vector>

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum AICommandType { AICMD_MOVE_TO_POSITION = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
class Module;
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
struct AICommandParms {
 AICommandParms(AICommandType, CommandSourceType);
 ~AICommandParms();
 int command, source;
 Coord3D position;
 char remaining[0xC0 - 0x14];
};
class AICommandInterface { public:
 virtual void aiDoCommand(const AICommandParms *);
};
// AICommandInterface::aiMoveToPosition (rowed 0x0026C26D), inlined at this
// call site in retail. A file-local spelling keeps this unit from emitting a
// second out-of-line copy of the rowed member.
static __forceinline void aiMoveToPosition(AICommandInterface &ai, const Coord3D *pos, CommandSourceType source) {
 AICommandParms command(AICMD_MOVE_TO_POSITION, source);
 command.position = *pos;
 ai.aiDoCommand(&command);
}
class StrafeAreaUpdate { public: bool rva003A4F21(const Coord3D *, const Coord3D *); };
class AIUpdateView { public: char pad[0x20]; AICommandInterface command; };
#include "../../Common/Thing/thing.h"
float normalizeAngle(float);

class Player;

class Object
{
public:
	bool hasUpgradeMask(int bit) const;
	Player *getControllingPlayer() const;
	bool isSignificantlyAboveTerrain() const;
	char m_pad00[0x38];
	float m_position[3];	// +0x38
	float getOrientation() const { return m_pad44; }
	float m_pad44;		// +0x44 orientation
 char m_pad48[0x258 - 0x48];
 AIUpdateView *ai;
 AIUpdateView *getAI() const { return ai; }
protected:
 Module *findModule(NameKeyType) const;
 friend class GenericObjectCreationNugget;
};

struct NuggetNameList
{
	unsigned int size() const { return m_end - m_begin; }
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Coord3D;
class Matrix3D;

// The ordinary vector wrapper folds to the existing 5B cleanup at1F22A3.
// Its storage destructor remains an out-of-line native provider at1F1609.
namespace _STL { template<> _Vector_base<Object*,allocator<Object*> >::~_Vector_base(); }
typedef _STL::vector<Object*> NuggetCreated;

class GenericObjectCreationNugget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
	void create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, unsigned int lifetimeFrames) const;
 bool rva001F1513(const Object *obj) const;
	NuggetCreated reallyCreate(const Coord3D *pos, const Matrix3D *transform, float orientation,
		const Object *sourceObj, unsigned int lifetimeFrames) const;	// 0x001F1634
private:
	char m_pad04[0xAF - 4];
	bool m_skipIfSignificantlyAirborne;	// +0xAF
	char m_padB0[0x100 - 0xB0];
 bool m_moveToSecondary; // +100
 bool m_inheritOrientation; // +101
 bool m_faceSecondary; // +102
 bool m_strafe; // +103
 float m_orientationOffset; // +104
 char m_pad108[8];
 bool m_inheritTransform; // +110
 char m_pad111[3];
	NuggetNameList m_114;	// +0x114
	NuggetNameList m_120;	// +0x120
};

// Native 001F2F0E..001F311B (525B); WB B03C80 names this create overload.
// ZH/BF1 provide the creation spine; secondary movement and strafe handling
// are reconstructed from BFME2. Flag names describe observed behavior only.
void GenericObjectCreationNugget::create(const Object *primaryObj,
 const Coord3D *primary, const Coord3D *secondary, unsigned int lifetimeFrames) const
{
 if (primaryObj && !rva001F1513(primaryObj)) return;
 if (!primary) return;
 float orientation = 0.0f;
 const Matrix3D *transform = 0;
 if (m_inheritOrientation) orientation = primaryObj->getOrientation() + m_orientationOffset;
 if (m_inheritTransform) transform = (const Matrix3D *)((const char *)primaryObj + 8);
 NuggetCreated created = reallyCreate(primary, transform, orientation, primaryObj, lifetimeFrames);
 if (secondary && m_moveToSecondary) {
   for (unsigned int i = 0; i < created.size(); ++i) {
    Object *object = created[i];
    if (!object || !object->ai) continue;
    if (m_strafe) {
     static const NameKeyType key = TheNameKeyGenerator->nameToKey("StrafeAreaUpdate");
     StrafeAreaUpdate *strafe = (StrafeAreaUpdate *)object->findModule(key);
     if (strafe && strafe->rva003A4F21(primary, secondary)) continue;
    }
    aiMoveToPosition(object->getAI()->command, secondary, CMD_FROM_PLAYER);
   }
  }
  if (secondary && m_faceSecondary) {
   for (unsigned int i = 0; i < created.size(); ++i) {
    Object *object = created[i];
    if (object) {
     float dx = secondary->x - object->m_position[0];
     float dy = secondary->y - object->m_position[1];
     ((Thing *)object)->setOrientation(normalizeAngle((float)atan2((double)dy, (double)dx) + m_orientationOffset));
    }
   }
  }
}
