// cl: /O1 /Ob2 /Oy- /MD /arch:SSE /G7 /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ParticleSystem::update, retail 0x001FAB59 (1704 B, RET 4): Zero Hour ParticleSystem::update plus BFME 2's
// profiling timer, master-system skip and bone-attached parent transform (WB debug body 0xB11B60).
// Matrix3D, Vector3 and Vector4 come from WWMath's matrix3d.h; the Object transform is at +0x8.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "matrix3d.h"

static __forceinline void setCoord(Coord3D *c, Real x, Real y, Real z)
{
	c->x = x;
	c->y = y;
	c->z = z;
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *);

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct ParticleGlobalDataView
{
	char pad[0x9AF];
	Bool m_useFX;		// +0x9AF
	char pad9B0[0x9C2 - 0x9B0];
	Bool m_profileFX;	// +0x9C2
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	Int getCurrentClientBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms, Int maxBones) const;
	Bool isShroudedDrawable() const { return m_shrouded; }
	Bool isVisibleDrawable() const { return m_visible; }
private:
	char pad[0x440];
	Bool m_shrouded;	// +0x440
	Bool m_visible;		// +0x441
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED,
	CELLSHROUD_COUNT
};

class Object : public Thing
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
private:
	char pad[0x8];
	Matrix3D m_transform;	// +0x8
};

class GameClient
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual Drawable *findDrawableByID(Int id);	// +0x40
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
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
	virtual UnsignedInt getFrame();	// +0x7C
};
extern GameClient *TheGameClient;
extern GameLogic *TheGameLogic;

struct Rva001F38C1Arg { int v[12]; };
class Rva001F38C1Slot { public: void set(const Rva001F38C1Arg &); };
class Rva001F3C9AHelper;
class Rva001F3C9A
{
public:
	bool rva001F3C9A();
	char m_pad00[0xC];
private:
	int m_0C; // +0x0C
	char m_pad10[0x94];
	Rva001F3C9AHelper *m_A4; // +0xA4
	char m_padA8[0x80];
	int m_128; // +0x128
	char m_pad12C[0x76];
	bool m_1A2; // +0x1A2
	char m_pad1A3[0x1];
	bool m_1A4; // +0x1A4
	char m_pad1A5[0x3];
};
class Rva001FA7F8 { public: void rva001FA7F8(); UnsignedInt data[12]; };

class ControlParticleView
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	char pad[0x1C];
	Coord3D m_pos;	// +0x1C
};

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };
class GameClientRandomVariable { public: Int type; Real low, high; };
struct ParticleRegion
{
public:
	float x1; // +0x00
	float y1; // +0x04
	float x2; // +0x08
	float y2; // +0x0C
};
struct ParticleSystemHandleView { void *ptr; Int prev, next; };

// The constructor's (ParticleSystemConstructor.cpp) layout and virtual slots; +0x7C is Zero Hour's m_priority.
namespace FXParticleSystem {
class ParticleSystemTemplate;
class ParticleSystemInfo : public Snapshot
{
public:
	ParticleSystemInfo(); virtual ~ParticleSystemInfo(); virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
	unsigned char oneShot; UnsignedInt shader, particleType; AsciiString typeName;
	GameClientRandomVariable angle; UnsignedInt lifetime, depth; GameClientRandomVariable angularRate, angularDamping;
	UnsignedInt windMotion; GameClientRandomVariable velocityDamping, life, startSize;
	AsciiString slaveName; Coord3D slaveOffset; AsciiString attachedName; Int m_priority;
	unsigned char hollow, ground, above, up, windMoving; ParticleRegion uv; UnsignedInt unknown98;
};
}

class ParticleSystem : public FXParticleSystem::ParticleSystemInfo
{
public:
	virtual ~ParticleSystem();
	virtual Bool update(Int localPlayerIndex);
	void destroy();
	void rva001F4696(void *, void *, bool, void *);
private:
	Int getPriority() const { return m_priority; }

	void *m_head, *m_tail, *m_drawer;	// +0x9C
	ParticleSystemID m_systemID;		// +0xA8
	Real m_updateTime;			// +0xAC
	Int m_attachedToDrawableID;		// +0xB0
	ObjectID m_attachedToObjectID;		// +0xB4
	AsciiString m_attachedBoneName;		// +0xB8
	Matrix3D m_localTransform;		// +0xBC
	Matrix3D m_transform;			// +0xEC
	UnsignedInt m_burstDelayLeft;		// +0x11C
	UnsignedInt m_delayLeft;		// +0x120
	UnsignedInt m_startTimestamp;		// +0x124
	UnsignedInt m_systemLifetimeLeft;	// +0x128
	UnsignedInt m_count;			// +0x12C
	Coord3D m_velCoeff;			// +0x130
	Real m_countCoeff, m_delayCoeff;	// +0x13C
	Coord3D m_pos;				// +0x144
	Coord3D m_lastPos;			// +0x150
	ParticleSystemHandleView m_slaveSystem;	// +0x15C
	UnsignedInt m_slaveSystemID;		// +0x168
	ParticleSystemHandleView m_masterSystem;	// +0x16C
	UnsignedInt m_masterSystemID;		// +0x178
	Real m_sizeCoeff, m_unknown180, m_unknown184;	// +0x17C
	Coord3D m_unknown188;			// +0x188
	unsigned char m_unknown194;		// +0x194
	const FXParticleSystem::ParticleSystemTemplate *m_template;	// +0x198
	ControlParticleView *m_controlParticle;	// +0x19C
	Bool m_isLocalIdentity;			// +0x1A0
	Bool m_isIdentity;			// +0x1A1
	Bool m_isForever;			// +0x1A2
	Bool m_isStopped;			// +0x1A3
	Bool m_isDestroyed;			// +0x1A4
	Bool m_1A5;
	Bool m_1A6;
	Bool m_1A7;
	Bool m_skipParentXfrm;			// +0x1A8
	Rva001FA7F8 m_modules;			// +0x1AC
};
typedef char ParticleExtent[sizeof(ParticleSystem) == 0x1DC ? 1 : -1];

Bool ParticleSystem::update(Int localPlayerIndex)
{
	m_updateTime = 0.0f;
	__int64 startTime, frequency, endTime;
	if (((const ParticleGlobalDataView *)TheWritableGlobalData)->m_profileFX)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&startTime);
	}

	if (((const ParticleGlobalDataView *)TheWritableGlobalData)->m_useFX == false)
		return false;

	// do initial delay ... note, this currently delays the lifetime
	if (m_delayLeft)
	{
		--m_delayLeft;

		// system actually "starts" once initial delay is over
		/// @todo reset start time when system is stopped/started
		if (m_delayLeft == 0)
			m_startTimestamp = TheGameClient->getFrame();

		return true;
	}

	Bool isHidden = false;
	Bool isShrouded = false;

	if (m_masterSystem.ptr == NULL)
	{
		// if this system is attached to a Drawable/Object, update the current transform
		// matrix so generated particles' are relative to the parent Drawable's
		// position and orientation
		Bool transformSet = false;
		const Matrix3D *parentXfrm = NULL;
		Vector3 pos;

		if (m_attachedToDrawableID)
		{
			Drawable *attachedTo = TheGameClient->findDrawableByID(m_attachedToDrawableID);

			if (attachedTo)
			{
				if (!attachedTo->isVisibleDrawable())
					isHidden = true;
				if (attachedTo->isShroudedDrawable())
					isShrouded = true;

				parentXfrm = attachedTo->getTransformMatrix();

				m_lastPos = m_pos;
				parentXfrm->Get_Translation(&pos);
				setCoord(&m_pos, pos.X, pos.Y, pos.Z);

				if (!m_attachedBoneName.isEmpty())
				{
					Matrix3D boneXfrm;
					if (attachedTo->getCurrentClientBonePositions(m_attachedBoneName.str(), 0, NULL, &boneXfrm, 1))
						((Rva001F38C1Slot *)this)->set((const Rva001F38C1Arg &)boneXfrm);
				}
			}
			else
			{
				// Drawable has been destroyed - lose our attachment to it
				m_attachedToDrawableID = 0;

				// destroy ourselves
				destroy();
			}
		}
		else if (m_attachedToObjectID)
		{
			Object *objectAttachedTo = TheGameLogic->findObjectByID(m_attachedToObjectID);

			if (objectAttachedTo)
			{
				if (!isShrouded)
					isShrouded = (objectAttachedTo->getShroudStatusForPlayer(localPlayerIndex) >= CELLSHROUD_COUNT);

				Drawable *draw = objectAttachedTo->getDrawable();
				if (draw)
				{
					if (!draw->isVisibleDrawable())
						isHidden = true;
					parentXfrm = draw->getTransformMatrix();

					if (!m_attachedBoneName.isEmpty())
					{
						Matrix3D boneXfrm;
						if (draw->getCurrentClientBonePositions(m_attachedBoneName.str(), 0, NULL, &boneXfrm, 1))
							((Rva001F38C1Slot *)this)->set((const Rva001F38C1Arg &)boneXfrm);
					}
				}
				else
					parentXfrm = objectAttachedTo->getTransformMatrix();

				m_lastPos = m_pos;
				parentXfrm->Get_Translation(&pos);
				setCoord(&m_pos, pos.X, pos.Y, pos.Z);
			}
			else
			{
				// Drawable has been destroyed - lose our attachment to it
				m_attachedToObjectID = INVALID_OBJECT_ID;

				// destroy ourselves
				destroy();
			}
		}

		if (parentXfrm)
		{
			if (m_skipParentXfrm)
			{
				//this particle system is already in world space so no need to apply parent xform.
				m_transform = m_localTransform;
			}
			else
			{
				// if system has its own local transform, concatenate them
				if (m_isLocalIdentity == false)
					m_transform.mul(*parentXfrm, m_localTransform);
				else
					m_transform = *parentXfrm;
			}

			m_isIdentity = false;
			transformSet = true;
		}

		if (transformSet == false)
		{
			if (m_isLocalIdentity == false)
			{
				m_transform = m_localTransform;
				m_isIdentity = false;
			}
			else
			{
				m_isIdentity = true;
			}
		}

		// if we are controlled by a particle, its position is local origin
		if (m_controlParticle)
		{
			const Coord3D *controlPos = m_controlParticle->getPosition();
			/// @todo Concatenate this, instead of overriding (MSB)
			m_transform.Set_X_Translation(controlPos->x);
			m_transform.Set_Y_Translation(controlPos->y);
			m_transform[2][3] = controlPos->z;	// same store as Set_Z_Translation, without emitting its /arch:SSE copy
			m_isIdentity = false;
			m_lastPos = m_pos;
			m_pos = *controlPos;
		}

		//
		// Generate new particles if the system hasn't been 'stopped' or 'destroyed'
		// If we are a slave system, do not generate particles ourselves - our master will force us to
		//
		if (m_isDestroyed == false)
		{
			if (m_isForever || (m_isForever == false && m_systemLifetimeLeft > 0))
			{
				if (!isShrouded && m_isStopped == false && !isHidden)
					rva001F4696(&m_pos, (void *)getPriority(), m_isIdentity, &m_transform);
			}
		}
	}

	m_modules.rva001FA7F8();
	Bool result = ((Rva001F3C9A *)this)->rva001F3C9A();

	if (((const ParticleGlobalDataView *)TheWritableGlobalData)->m_profileFX)
	{
		QueryPerformanceCounter(&endTime);
		m_updateTime = (Real)((endTime - startTime) * 1000.0f / frequency);
	}

	return result;
}
