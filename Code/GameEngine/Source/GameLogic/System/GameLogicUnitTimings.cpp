// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// platformsdk
//
// ?rva002431CB@Rva002431CB@@QAEXXZ  retail 0x002431CB..0x00243B48 (2429 bytes).
// The unit-timings benchmark step GameLogic::update calls each frame (Zero
// Hour's DO_UNIT_TIMINGS unitTimings in GameLogic.cpp, made an object whose
// members hold Zero Hour's statics). WorldBuilder twin 0x00CEEC50
// (GameLogic.cpp) and the Zero Hour body give the flow: settle frames then
// QueryPerformanceCounter timing over the time frames; per mode store the
// time and draw-call rate and switch the camera/particle/spawn setup; log a
// comma line through 0x0023C641; destroy every object and pick the next
// template by side, kind and name filters; create a 10x10 grid of it (trees
// go to TerrainLogic) and look at it.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
// windows.h must not declare stdio.h's sprintf: GameLogic.cpp's sprintf calls reach the import.
#define NOMINMAX
#define _INC_STDIO
#include <windows.h>
#undef _INC_STDIO
#include <string.h>

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

class ThingTemplate;
class Team;
class Player;
class ModuleData;

// The native benchmark zeroes 76 bytes for this virtual model-name query.
// Its original flag-container identity is unknown; retain a local storage view.
struct UnitTimingModelState
{
	UnitTimingModelState() { memset(this, 0, sizeof(*this)); }
	void clear() { memset(this, 0, sizeof(*this)); }
	unsigned char m_bits[0x4C];
};

struct CreateMask
{
	char m_data[0x10];
};

class ModuleData
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D)
#undef V
	virtual AsciiString getBestModelNameForWB(const UnitTimingModelState &state) const; // +0x38
};

class ModuleInfo
{
public:
	__declspec(dllimport) __forceinline int getCount() const { return (m_end - m_begin) / 0x14; }
	const ModuleData *getNthData(int index) const;

	unsigned char *m_begin;
	unsigned char *m_end;
};

// Retail loads the read-only 1.0f pool slot before zeroing the matrix.
// A volatile read preserves that load; this local constant is a codegen
// stand-in for the observed pool value, not an original global identity.
static const volatile float IdentityDiagonal=1.0f;
#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
static __forceinline void makeIdentityAndTakeScale(Matrix3D &mtx, float &scale, const float &factor)
{
	float one = IdentityDiagonal;
	mtx.Row[0].Y = 0.0f;
	mtx.Row[0].Z = 0.0f;
	mtx.Row[0].W = 0.0f;
	mtx.Row[1].X = 0.0f;
	mtx.Row[1].Z = 0.0f;
	mtx.Row[1].W = 0.0f;
	mtx.Row[2].X = 0.0f;
	mtx.Row[2].Y = 0.0f;
	mtx.Row[2].W = 0.0f;
	scale = factor;
	mtx.Row[0].X = one;
	mtx.Row[1].Y = one;
	mtx.Row[2].Z = one;
}

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline const ModuleInfo &drawModules() const { return m_drawModuleInfo; }
	__forceinline unsigned int kindOfWord(int word) const { return ((const unsigned int *)m_kindOf)[word]; }
	const ThingTemplate *friend_getNextTemplate() const { return m_nextTemplate; }

	unsigned char m_pad00[0x64];
	AsciiString m_name;              // +0x64
	unsigned char m_pad68[0x6C - 0x68];
	AsciiString m_side;              // +0x6C
	unsigned char m_pad70[0x108 - 0x70];
	unsigned char m_kindOf[0x20];    // +0x108
	unsigned char m_pad128[0x2F0 - 0x128];
	ModuleInfo m_drawModuleInfo;     // +0x2F0
	unsigned char m_pad2F8[0x484 - 0x2F8];
	const ThingTemplate *m_nextTemplate; // +0x484
	unsigned char m_pad488[0x4E0 - 0x488];
	float m_treeScale;               // +0x4E0
	unsigned char m_pad4E4[0x5F4 - 0x4E4];
	unsigned char m_editorSorting;             // +0x5F4
};

class Thing
{
public:
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getNextObject() const { return m_next; }

	void *m_vtbl;                    // +0x00
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x8C - 8];
	Object *m_next;                  // +0x8C
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

#include "../../../Include/Common/TeamBFME2.h"

class Player
{
public:
	Team *getDefaultTeam() const { return m_team; }

	unsigned char m_pad00[0x2EC];
	Team *m_team; // +0x2EC
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
};

enum ObjectID; class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID flag);
	const ThingTemplate *firstTemplate() const { return m_firstTemplate; }

	unsigned char m_pad00[0xC];
	const ThingTemplate *m_firstTemplate; // +0x0C
};

class LocomotorSet;
class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object*);
	bool AdjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dst, const Coord3D *group);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pf; }

	unsigned char m_pad00[0x10];
	Pathfinder *m_pf; // +0x10
};

class TerrainLogic
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05)
#undef V
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const; // +0x18

	void addTree(const ThingTemplate *tmplate, const Coord3D *pos, const Matrix3D *mtx, float scale);
	void rva00280176(const ThingTemplate *tmplate, const Coord3D *pos, const Matrix3D *mtx, float scale);
	void rva0027D3D9(const ThingTemplate *tmplate, const Coord3D *pos, const Matrix3D *mtx, float scale);
};

class Display
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E) V(0F)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(1A) V(1B) V(1C) V(1D) V(1E) V(1F)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(2A) V(2B) V(2C) V(2D) V(2E) V(2F)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(3A) V(3B) V(3C) V(3D) V(3E) V(3F)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(4A) V(4B) V(4C) V(4D) V(4E) V(4F)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(5A) V(5B) V(5C)
#undef V
	virtual int getLastFrameDrawCalls(); // +0x174
	virtual void slot178(int *stats);    // +0x178
};

class View
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06)
	virtual void slot1C(int value); // +0x1C
	V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E) V(0F)
	V(10) V(11) V(12) V(13) V(14)
	virtual void lookAt(const Coord3D *pos); // +0x54
	V(16) V(17) V(18) V(19) V(1A) V(1B) V(1C) V(1D) V(1E) V(1F)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(2A) V(2B) V(2C) V(2D) V(2E) V(2F)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(3A) V(3B) V(3C) V(3D) V(3E) V(3F)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
#undef V
	virtual void slot128(float value); // +0x128
	virtual float slot12C();           // +0x12C
	virtual void slot130(float value); // +0x130
};

class ParticleSystemManager
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
#undef V
	virtual void reset(); // +0x24

	unsigned char m_pad04[0x50 - 4];
	unsigned int m_particleCount; // +0x50
};

class G00DFF080Inner
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
#undef V
	virtual void slot24(); // +0x24
};

class G00DFF080Obj
{
public:
	unsigned char m_pad00[4];
	G00DFF080Inner m_inner; // +0x04
};

class MessageStream
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(0A) V(0B) V(0C) V(0D) V(0E) V(0F)
	V(10) V(11)
#undef V
	virtual void *appendMessage(int type); // +0x48
};

class GameEngine
{
public:
	unsigned char m_pad00[0x38];
	int m_38; // +0x38
};

class GlobalData
{
public:
	unsigned char m_pad00[0x26];
	bool m_useFpsLimit;            // +0x26
	unsigned char m_pad27[0x28 - 0x27];
	int m_framesPerSecondLimit;    // +0x28
};

struct GameLogicObjectListView
{
	unsigned char m_pad00[0xAC];
	Object *m_firstObject; // +0xAC
};

class Rva0023C641
{
public:
	void rva0023C641(const char *line);
};

class Rva00382AA0
{
public:
	void release();
};

void HideControlBar(bool immediate);

extern GameEngine *TheGameEngine;
extern Display *TheDisplay;
extern View *TheTacticalView;
extern ParticleSystemManager *TheParticleSystemManager;
extern GameLogic *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern PlayerList *ThePlayerList;
extern ThingFactory *TheThingFactory;
extern AI *TheAI;
extern G00DFF080Obj *TheTerrainVisual;
extern MessageStream *TheMessageStream;
extern GlobalData *TheWritableGlobalData;
// Native benchmark saves/restores this view value and normalizes three display
// counters for its CSV output. Descriptive names; original identifiers unknown.
// Retail initial values are 100.0f at VA 0x00DBA6D0 and twelve zero bytes at
// VA 0x00DFE948. The benchmark owns these cells; no other provider is rowed.
float BfmeUnitTimingSavedViewValue = 100.0f;
int BfmeUnitTimingDisplayStats[3] = { 0, 0, 0 };

class Rva002431CB
{
public:
	void rva002431CB();
	bool isTiming() const { return m_startTiming; }

private:
	void *m_vtbl;                        // +0x00
	AsciiString m_singleUnit;            // +0x04
	AsciiString m_side;                  // +0x08
	bool m_gotUnit;                      // +0x0C
	const ThingTemplate *m_curThing;     // +0x10
	bool m_startTiming;                  // +0x14
	unsigned char m_pad15[0x1C - 0x15];
	int m_settleFrames;                  // +0x1C
	int m_timeFrames;                    // +0x20
	int m_unitTypes;                     // +0x24
	bool m_veryFirstTime;                // +0x28
	unsigned char m_pad29[0x30 - 0x29];
	LARGE_INTEGER m_startTime;                 // +0x30
	LARGE_INTEGER m_endTime;                   // +0x38
	LARGE_INTEGER m_freq;                      // +0x40
	int m_drawCallTotal;                 // +0x48
	int m_mode;                          // +0x4C
	double m_timeAll;                    // +0x50
	double m_timeAllNoAnim;              // +0x58
	double m_60;                         // +0x60
	double m_timeNoPart;                 // +0x68
	double m_timeNoSpawn;                // +0x70
	double m_timeLogic;                  // +0x78
	unsigned char m_pad80[0x88 - 0x80];
	float m_drawCallAll;                 // +0x88
	float m_drawCallNoPart;              // +0x8C
	float m_drawCallNoSpawn;             // +0x90
	float m_drawCallLogic;               // +0x94
};

void Rva002431CB::rva002431CB()
{
	float frames = TheGameEngine->m_38 * 2.0f;

	if (!isTiming())
		return;

	if (m_settleFrames > 0)
	{
		m_settleFrames--;
		if (m_settleFrames > 0)
			return;
		QueryPerformanceCounter(&m_startTime);
		QueryPerformanceFrequency(&m_freq);
		m_drawCallTotal = 0;
		m_timeFrames = 2;
		return;
	}

	if (m_timeFrames > 0)
	{
		m_timeFrames--;
		if (m_timeFrames > 0)
			return;

		m_drawCallTotal = TheDisplay->getLastFrameDrawCalls();
		QueryPerformanceCounter(&m_endTime);
		double timeToUpdate = (double)(m_endTime.QuadPart - m_startTime.QuadPart) / (double)m_freq.QuadPart;
		Coord3D thePos;
		thePos.x = 400.0f;
		thePos.y = 300.0f;
		thePos.z = 0.0f;
		timeToUpdate = timeToUpdate * 1000000.0 / (frames * 100.0f);

		if (m_mode == 0)
		{
			m_timeLogic = timeToUpdate;
			m_drawCallLogic = m_drawCallTotal * 0.01f;
			m_mode = 4;
			m_settleFrames = 2;
			BfmeUnitTimingSavedViewValue = TheTacticalView->slot12C();
			TheTacticalView->lookAt(&thePos);
			return;
		}
		if (m_mode == 4)
		{
			m_timeAll = timeToUpdate;
			m_drawCallAll = m_drawCallTotal * 0.01f;
			TheDisplay->slot178(BfmeUnitTimingDisplayStats);
			BfmeUnitTimingDisplayStats[1] /= 100;
			BfmeUnitTimingDisplayStats[2] /= 100;
			BfmeUnitTimingDisplayStats[0] /= 100;
			m_mode = 3;
			m_settleFrames = 2;
			TheTacticalView->slot1C(0);
			TheTacticalView->slot130(700.0f);
			TheTacticalView->slot128(2.2f);
			return;
		}
		if (m_mode == 3)
		{
			m_timeAllNoAnim = timeToUpdate;
			m_mode = 1;
			m_settleFrames = 2;
			if (TheParticleSystemManager->m_particleCount > 1)
				TheParticleSystemManager->reset();
			TheTacticalView->slot128(1.0f);
			TheTacticalView->slot130(BfmeUnitTimingSavedViewValue);
			TheTacticalView->lookAt(&thePos);
			return;
		}
		if (m_mode == 1)
		{
			m_timeNoPart = timeToUpdate;
			m_drawCallNoPart = m_drawCallTotal * 0.01f;
			m_mode = 2;
			Object *obj = ((GameLogicObjectListView *)TheGameLogic)->m_firstObject;
			bool gotSpawn = false;
			while (obj)
			{
				if (obj->getTemplate() != m_curThing && !obj->testStatus(OBJECT_STATUS_26))
				{
					TheGameLogic->destroyObject(obj);
					gotSpawn = true;
				}
				obj = obj->getNextObject();
			}
			if (gotSpawn)
			{
				m_settleFrames = 2;
				return;
			}
		}
		if (m_mode == 2)
		{
			m_timeNoSpawn = timeToUpdate;
			m_drawCallNoSpawn = m_drawCallTotal * 0.01f;
		}

		if (m_curThing == 0)
			return;

		AsciiString remark;
		AsciiString thingName = m_curThing->getName();
		if (m_veryFirstTime)
			thingName = "No Object";

		{
		AsciiString type;
		if (m_unitTypes == 0)
			type = "Infantry";
		else if (m_unitTypes == 1)
			type = "Machine";
		else if (m_unitTypes == 3)
			type = "Monster";
		else if (m_unitTypes == 2)
			type = "Cavalry";
		else if (m_unitTypes == 4)
			type = "Structure";
		else
			type = "Other";

		AsciiString modelName;
		UnitTimingModelState state;
		state.clear();
		const ModuleInfo &mi = m_curThing->drawModules();
		if (mi.getCount() > 0)
		{
			const ModuleData *mdd = mi.getNthData(0);
			if (mdd)
				modelName = mdd->getBestModelNameForWB(state);
		}
		if (m_veryFirstTime)
		{
			modelName = "**NO MODEL**";
			m_veryFirstTime = false;
		}

		remark.format("%.1f,%d/%d/%d,%.1f,%.1f,%.1f,%.1f,%s,%s,%s,%s,%.1f,%.1f,%.1f\n",
			m_timeAll, BfmeUnitTimingDisplayStats[0], BfmeUnitTimingDisplayStats[1], BfmeUnitTimingDisplayStats[2],
			m_timeAllNoAnim, m_timeNoPart, m_timeNoSpawn, m_timeLogic,
			thingName.str(), modelName.str(), type.str(), m_side.str(),
			(double)m_drawCallAll, (double)m_drawCallNoPart, (double)m_drawCallNoSpawn);
		((Rva0023C641 *)this)->rva0023C641(remark.str());
		}

		TheParticleSystemManager->reset();
		m_gotUnit = false;
	}

	if (!((StringBase<char> *)&m_singleUnit)->isEmpty() && m_curThing && m_startTiming)
	{
		if (m_curThing->getName().compare(m_singleUnit) == 0)
		{
			((Rva00382AA0 *)this)->release();
			return;
		}
		while (m_curThing->friend_getNextTemplate() && m_curThing->friend_getNextTemplate()->getName().compare(m_singleUnit) != 0)
			m_curThing = m_curThing->friend_getNextTemplate();
	}

	Object *obj = ((GameLogicObjectListView *)TheGameLogic)->m_firstObject;
	while (obj)
	{
		TheGameLogic->destroyObject(obj);
		obj = obj->getNextObject();
	}
	TheTerrainVisual->m_inner.slot24();

	if (m_startTiming && m_curThing && !m_gotUnit)
	{
		TheWritableGlobalData->m_framesPerSecondLimit = 10000;
		TheWritableGlobalData->m_useFpsLimit = false;
		while (!m_gotUnit)
		{
			if (m_veryFirstTime)
			{
				m_gotUnit = true;
				break;
			}
			m_curThing = m_curThing->friend_getNextTemplate();
			if (m_curThing == 0)
			{
				m_unitTypes++;
				if (m_unitTypes == 6)
				{
					m_startTiming = false;
					((Rva00382AA0 *)this)->release();
					TheMessageStream->appendMessage(0x1D);
					break;
				}
				m_curThing = TheThingFactory->firstTemplate();
			}

			const ThingTemplate *cur = m_curThing;
			bool single = cur->getName().compare(m_singleUnit) == 0;
			const ThingTemplate *btt = m_curThing;
			if (!single && !((StringBase<char> *)&m_side)->isEmpty())
			{
				if (((StringBase<char> &)(btt->m_side)).compareNoCase((const StringBase<char> &)(m_side)) != 0)
					continue;
				if (m_unitTypes == 0)
				{
					if (!(btt->kindOfWord(0) & 0x100))
						continue;
					if (btt->kindOfWord(0) & 0x800)
						continue;
					if (btt->kindOfWord(0) & 0x80)
						continue;
				}
				else if (m_unitTypes == 1)
				{
					if (!(btt->kindOfWord(0) & 0x800))
						continue;
					if (btt->kindOfWord(0) & 0x400)
						continue;
					if (btt->kindOfWord(0) & 0x80)
						continue;
				}
				else if (m_unitTypes == 2)
				{
					if (!(btt->kindOfWord(0) & 0x200))
						continue;
					if (btt->kindOfWord(0) & 0xC00)
						continue;
					if (btt->kindOfWord(0) & 0x80)
						continue;
				}
				else if (m_unitTypes == 3)
				{
					if (!(btt->kindOfWord(0) & 0x400))
						continue;
					if (btt->kindOfWord(0) & 0x80)
						continue;
				}
				else if (m_unitTypes == 4)
				{
					if (!(btt->kindOfWord(0) & 0x80))
						continue;
				}
				else
				{
					if (btt->kindOfWord(0) & 0xF00)
						continue;
					if (btt->kindOfWord(0) & 0x80)
						continue;
				}
			}

			if (btt->getName().startsWith("CINE"))
				continue;
			if (btt->getName().compare("GLAInfantryAngryMobNexus") == 0)
				continue;
			if (btt->getName().compare("FlockOfBirds") == 0)
				continue;
			if (btt->m_editorSorting == 0xD)
				continue;
			if (((const unsigned char *)btt)[0x120] & 1)
				continue;
			if (!((StringBase<char> *)&m_singleUnit)->isEmpty() && ((StringBase<char> &)(btt->getName())).compareNoCase((const StringBase<char> &)(m_singleUnit)) != 0)
				continue;

			Coord3D pos;
			Matrix3D mtx;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					pos.x = i * 20.0f + 300.0f;
					pos.y = j * 20.0f + 300.0f;
					pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
					if (!(((const unsigned char *)btt)[0x114] & 0x10) && !(((const unsigned char *)btt)[0x113] & 0xC0))
					{
						Team *team = ThePlayerList->getNthPlayer(1)->getDefaultTeam();
						CreateMask mask;
						memset(&mask, 0, 0x10);
						Object *newObj = TheThingFactory->newObject(btt, team, &mask, (ObjectID)0);
						if (newObj == 0)
							break;
						m_gotUnit = true;
						newObj->setOrientation(0.0f);
						newObj->setPosition(&pos);
						((Rva0028CBFD *)newObj)->rva0028CBFD();
						team->setActive();
						TheAI->pathfinder()->AddObjectToPathfindMap(newObj);
					}
					else
					{
						float scale;
						makeIdentityAndTakeScale(mtx, scale, btt->m_treeScale);
						if (btt->kindOfWord(2) & 0x40000000)
							TheTerrainLogic->addTree(btt, &pos, &mtx, scale);
						else if (btt->kindOfWord(2) & 0x80000000)
							TheTerrainLogic->rva00280176(btt, &pos, &mtx, scale);
						else
							TheTerrainLogic->rva0027D3D9(btt, &pos, &mtx, scale);
						m_gotUnit = true;
					}
				}
			}
		}

		if (m_gotUnit)
		{
			m_settleFrames = 4;
			if (m_veryFirstTime)
			{
				HideControlBar(true);
				m_settleFrames *= 100;
			}
			Coord3D lookPos;
			lookPos.x = 800.0f;
			lookPos.y = 800.0f;
			lookPos.z = 0.0f;
			TheTacticalView->lookAt(&lookPos);
			m_mode = 0;
		}
	}
}
