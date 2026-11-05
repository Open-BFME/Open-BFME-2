// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /Ireference/shims/bfme2_ascii
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Include/Common/BfmeAudioEventPrefix136.h"
#include "Code/GameEngine/Source/Common/RTS/XYDistanceCallView.h"

// Native 0x00296065..0x0029660A RET4; the owned queued caller 0x002975AC supplies Rva00297612Entry.
// ZH Object::attemptDamage's shockwave section is the guide; the audio, airborne, recoil and AI
// feedback extensions follow native and WB 0xCC92C0 (Object.cpp).
class Rva0036CA00Str
{
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
	__forceinline ~Rva0036CA00Str() { if (ref) ref->Release_Ref(); }
	OpaqueRefCounted *ref;
};

class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &);
	int index;
	OpaqueRefElement4 name;
	__forceinline const Rva0036CA00Str &getSound() const { return *(const Rva0036CA00Str *)&name; }
};

struct Rva00297612Entry
{
	char pad0[0x2c];
	int visualState;
	ObjectID source;
	Coord3D vector;
	float amount, radius, taper, up;
	bool radial;
	char pad51[3];
	float extraDistance, secondary;
	Coord3D origin;
	float mode;
};

// 0x0027B18C's bank names its parameter DamageInfo; the call passes this entry unchanged.
struct DamageInfo;
#include "../../../Include/GameClient/Drawable.h"
class Rva002D9531
{
public:
	void rva002D9531(int value);
};
class Rva00294D61 { public: void report(Object *, int); };

template<int N> class ShockSlots : public ShockSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template<> class ShockSlots<0> {};

#include "../../../Include/Common/GameAudio.h"
extern AudioManager *TheAudio;

class Rva003909FAObj
{
public:
	void consume(void*,int,int);
};
class PhysicsBehavior
{
public:
	void rva003906BF();
	void rva00390557(const Coord3D *, float, float, int, int);
	void rva00390629(bool);
	char pad0[0x5c];
	bool flag5c;
};
#include "../../../Include/GameLogic/Module/AttributeModifierPoolUpdate.h"
struct ShockBodyEntry { char pad0[8]; ObjectID source; };
#include "../../../Include/GameLogic/Module/BodyModuleClass.h"
class AIUpdateInterface : public ShockSlots<153>
{
public:
	virtual void slot153() = 0;
	int getCurrentStateID() const;
};
enum PathfindLayerEnum { LAYER_UNKNOWN0 = 0 };
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/Common/ThingTemplate.h"
class Rva001E438B { public: float *rva00261988(float *, Rva001E438B *); };
enum DamageType { DAMAGE_UNKNOWN8 = 8 };
enum DeathType { DEATH_UNKNOWN0 = 0 };

class ShockFlags
{
public:
	unsigned words[19];
	unsigned test(int bit) const { return words[bit >> 5] & (1u << (bit & 31)); }
	void SetBit(int bit) { words[bit >> 5] |= 1u << (bit & 31); }
};

class Object
{
public:
	void rva00296065(Rva00297612Entry *);
	void rva0028AE9B(int);
	bool rva0028DB0F(bool) const;
	PhysicsBehavior *getPhysics() const { return physics; }
	Drawable *getDrawable() const { return drawable; }
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
public:
	void rva0028AE6D();
	void kill(DamageType, DeathType);
	char pad0[4];
	ThingTemplate *templ;
	char pad8[0x38 - 8];
	Coord3D position;
	char pad44[0x74 - 0x44];
	ObjectID id;
	char pad78[0x84 - 0x78];
	Drawable *drawable;
	char pad88[0x10c - 0x88];
	ShockFlags flags;
	char pad158[0x254 - 0x158];
	BodyModuleInterface *body;
	AIUpdateInterface *ai;
	PhysicsBehavior *physics;
	char pad260[0x438 - 0x260];
	unsigned char status;
	__forceinline unsigned getCondition(int bit) const { return flags.test(bit); }
	// The caller tests the bit; this unchecked helper differs from setCondition's guarded body.
	__forceinline void setShockConditionUnchecked(int bit) { flags.SetBit(bit); rva0028AE6D(); }
};

extern GameLogic *TheGameLogic;
float GetGameLogicRandomValueReal(float, float, char *, int);
static inline const float &shockMin(const float &a, const float &b) { return a < b ? a : b; }
static inline const float &shockMax(const float &a, const float &b) { return a > b ? a : b; }
static const char shockFile[] = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Object.cpp";

void Object::rva00296065(Rva00297612Entry *entry)
{
	rva0028AE9B(0);
	Drawable *draw = getDrawable();
	// Process any shockwave forces that might affect this object due to the incurred damage
	if (entry->amount > 0.0f && entry->radius > 0.0f)
	{
		PhysicsBehavior *behavior = getPhysics();
		bool force = entry->mode != 0.0f;
		bool blocked = behavior ? behavior->flag5c : false;
		if (!behavior || (blocked && !force)) goto end;
		if (draw && !blocked)
		{
			Rva0036CA00Str sound((force ? draw->rva0028F8F9() : draw->rva0028F8E0()).getSound());
			BfmeAudioEventPrefix136 event(*(OpaqueRefElement4 *)&sound, 0);
			((Rva002D9531 *)&event)->rva002D9531(id);
			TheAudio->addAudioEvent(&event);
		}
		if (rva0028DB0F(force))
		{
			behavior->rva003906BF();
			goto end;
		}
		float resistance;
		AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
		if (pool) pool->rva00403382(10, &resistance, 0);
		if (resistance >= 1.0f) return;
		// Calculate the shockwave taperoff amount due to distance from ground zero
		const Coord3D *shockVector = &entry->vector;
		float distance = shockVector->length();
		float percent = shockMin(1.0f, distance / entry->radius);
		float random = GetGameLogicRandomValueReal(0.85f, 1.15f, (char *)shockFile, 4093);
		if (entry->radial)
		{
			float extra = shockMax(0.0f, entry->extraDistance);
			Coord3D destination;
			destination.x = shockVector->x;
			destination.y = shockVector->y;
			destination.z = 0.0f;
			destination.normalize();
			float scale = entry->radius + (entry->radius * extra * random * percent);
			// Scalar local reads preserve retail's SSE load order.
			float dx = *(volatile float *)&destination.x;
			float dy = *(volatile float *)&destination.y;
			destination.x = dx * scale;
			destination.y = dy * scale;
			destination.z *= scale;
			destination.x += entry->origin.x;
			destination.y += entry->origin.y;
			destination.z += entry->origin.z;
			destination.z = TheTerrainLogic->getLayerHeight(destination.x, destination.y,
				TheTerrainLogic->getLayerForDestination(0, &destination), 0, true);
			behavior->rva00390557(&destination, entry->secondary * random, ((entry->amount)), 0, 0);
		}
		else
		{
			float taper = 1.0f - percent * (1.0f - entry->taper);
			// Set up the shockwave force to use apply on object
			Coord3D forceVector;
			forceVector.x = shockVector->x;
			forceVector.y = shockVector->y;
			forceVector.z = shockVector->z;
			forceVector.normalize();
			if (!force)
			{
				float scale = (1 ? entry->amount * taper * random : entry->amount * taper * random);
				forceVector.x *= scale;
				float fy = *(volatile float *)&forceVector.y;
				forceVector.y = fy * scale;
				forceVector.z *= scale;
				float vertical = forceVector.length();
				vertical *= entry->up;
				vertical *= random;
				forceVector.z = vertical;
			}
			else
			{
				Object *source = TheGameLogic->findObjectByID(entry->source);
				if (source && entry->radius > 0.0f)
				{
					float relative[3];
					float *point = ((Rva001E438B *)this)->rva00261988(relative, (Rva001E438B *)source);
					float negativeHeight = point[2] * -1.0f;
					float factor = 1.0f - (random ? negativeHeight : negativeHeight) / entry->radius;
					float scale = entry->amount * factor * taper * random;
					random = GetGameLogicRandomValueReal(0.65f, 1.35f, (char *)shockFile, 4169);
					if (factor < 0.0f) scale *= 2.0f;
					float vx = *(volatile float *)&forceVector.x;
					forceVector.x = vx * scale;
					float vy = *(volatile float *)&forceVector.y;
					forceVector.y = vy * scale;
					forceVector.z *= scale;
					float r = entry->radius;
					float vertical = (1.0f - ((Rva000CBA20 *)this)->distSq((Rva000CBA20Point *)&source->position) / (r * r));
					vertical *= 0.5f;
					vertical *= entry->amount;
					vertical *= random;
					forceVector.z = vertical;
				}
			}
			if (templ->m_kindof[5] & 0x80000000)
			{
				if (forceVector.z > 0.0f) forceVector.z = -forceVector.z;
			}
			else
			{
				if (forceVector.z < 0.0f) forceVector.z = -forceVector.z;
			}
			// Apply the shock to the object
			((Rva003909FAObj *)behavior)->consume(&forceVector, 0, 0);
		}
		if (!getCondition(127)) setShockConditionUnchecked(127);
		// Set stunned state due to the shock for the object
		behavior->rva00390629(true);
		if (ai && ai->getCurrentStateID() == 45)
		{
			const ShockBodyEntry *data = (const ShockBodyEntry *)body->getLastDamageInfo();
			Object *source = TheGameLogic->findObjectByID(data ? ((const ShockBodyEntry *)body->getLastDamageInfo())->source : INVALID_OBJECT_ID);
			if (source && !(status & 1)) ((Rva00294D61 *)source)->report(this, 1);
			kill(DAMAGE_UNKNOWN8, DEATH_UNKNOWN0);
			kill(DAMAGE_UNKNOWN8, DEATH_UNKNOWN0);
		}
		{
			AIUpdateInterface *aiCopy = ai;
			if (aiCopy) aiCopy->slot153();
		}
		rva0028AE9B(entry->visualState);
	}
end:
	if (draw) draw->rva0027B18C((DamageInfo *)entry);
}
