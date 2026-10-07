// ?drawWaypoints@W3DWaypointBuffer@@QAEXAAVRenderInfoClass@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// stlport
// ?drawWaypoints@W3DWaypointBuffer@@QAEXAAVRenderInfoClass@@@Z, retail 0x000DFE31 (588 bytes).
// Evidence: HeightMap.cpp calls m_waypointBuffer->drawWaypoints(rinfo); BFME1 donor
// W3DWaypointBufferDrawWaypoints.cpp (waypoint-mode gate, ambient-only LightEnvironment,
// RenderInfo copy, 513-entry Vector3 array, WW3D::Render per node, Set_Points + line Render);
// retail offsets TheInGameUI+0x8b0 waypointMode, Object+0x258 AI, ThingTemplate+0x108 KindOf,
// AI+0x30 machine, AI+0x194 index, RenderInfo+0x28 light_environment, points 513*12.

#include <list>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
#define NULL 0
#define MAX_DISPLAY_NODES 512

enum KindOfType
{
	KINDOF_IGNORED_IN_GUI = 47
};

class Vector3
{
public:
	Vector3(void) throw() {}
	Vector3(float x, float y, float z) throw() { X = x; Y = y; Z = z; }
	void Set(const Vector3 &that) throw() { X = that.X; Y = that.Y; Z = that.Z; }

	float X;
	float Y;
	float Z;
};

class Matrix3D
{
public:
	unsigned char m_pad[0x30];
};

class BfmeVecHF
{
public:
	float x;
	float y;
	float z;
};

class Gen_0094AC70
{
public:
	void bfmeSetPair(const BfmeVecHF *a, const BfmeVecHF *b);

private:
	unsigned char m_pad[0x170];
};

template <typename T>
class StringBase
{
public:
	void debugIgnoreLeaks();

private:
	void *m_data;
};

class LightEnvironmentClass : public Gen_0094AC70
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void) { ((StringBase<unsigned short> *)this)->debugIgnoreLeaks(); }
	void Pre_Render_Update(const Matrix3D &camera_tm);

private:
	unsigned char m_tail[0x228 - 0x170];
};

class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void Render(class RenderInfoClass &rinfo);
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void Validate_Transform(void) const;
	virtual void slot21();
	virtual void Set_Position(const Vector3 &v);

	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *(const Matrix3D *)m_transform;
	}

	unsigned char m_unreconstructed_04[0x18 - 4];
	unsigned char m_transform[0x30];
};

class CameraClass : public RenderObjClass
{
};

class RenderInfoClass
{
public:
	RenderInfoClass(CameraClass &cam);
	~RenderInfoClass(void);

	CameraClass &Camera;
	float fog_scale;
	unsigned char m_pad08[0x28 - 0x08];
	LightEnvironmentClass *light_environment;
	unsigned char m_pad2C[0x148 - 0x2C];
};

class SegmentedLineClass : public RenderObjClass
{
public:
	void Set_Points(unsigned int num_points, Vector3 *locs);
};

class WW3D
{
public:
	static bool Render(RenderObjClass &obj, RenderInfoClass &rinfo);
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindof[t >> 5] & (1U << (t & 31)); }

	unsigned char m_unmodelled_08[0x108 - 8];
	UnsignedInt m_kindof[4];
};

class Thing
{
public:
	virtual void slot00(void);
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }

	ThingTemplate *m_template;
};

class Rva00346FA5
{
public:
	void *rva00346FA5(int index) const;
};

class AIUpdateInterface
{
public:
	virtual void v00(void);
	int rva00265143();
	Int friend_getCurrentGoalPathIndex(void) const { return m_currentGoalPathIndex; }
	Rva00346FA5 *getStateMachine(void) const { return m_stateMachine; }

private:
	unsigned char m_pad004[0x30 - 0x04];
	Rva00346FA5 *m_stateMachine;
	unsigned char m_pad034[0x194 - 0x34];
	Int m_currentGoalPathIndex;
};

class Object : public Thing
{
public:
	const Coord3D *getPosition(void) const { return &m_cachedPos; }
	AIUpdateInterface *getAI(void) { return m_ai; }

	unsigned char m_unmodelled_08[0x38 - 8];
	Coord3D m_cachedPos;
	unsigned char m_unmodelled_44[0x258 - 0x44];
	AIUpdateInterface *m_ai;
};

class Drawable
{
public:
	Object *getObject(void) { return m_object; }

	void *m_vtable;
	void *m_template;
	unsigned char m_unmodelled008[0xFC - 0x08];
	Object *m_object;
};

typedef _STL::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46();
	virtual void setGUICommand(const void *command);
	virtual const void *getGUICommand(void);
	virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72();
	virtual const DrawableList *getAllSelectedDrawables(void) const;

	Bool isInWaypointMode(void) const { return m_waypointMode; }

	unsigned char m_pad004[0x8B0 - 0x04];
	Bool m_waypointMode;
};

extern InGameUI *TheInGameUI;

class W3DWaypointBuffer
{
public:
	void drawWaypoints(RenderInfoClass &rinfo);

private:
	RenderObjClass *m_waypointNodeRobj;
	SegmentedLineClass *m_line;
};

void W3DWaypointBuffer::drawWaypoints(RenderInfoClass &rinfo)
{
	if (TheInGameUI && TheInGameUI->isInWaypointMode())
	{
		LightEnvironmentClass lightEnv;
		{
			BfmeVecHF ambient;
			BfmeVecHF center;
			ambient.x = 1.0f;
			ambient.y = 1.0f;
			ambient.z = 1.0f;
			center.x = 0.0f;
			center.y = 0.0f;
			center.z = 0.0f;
			lightEnv.bfmeSetPair(&center, &ambient);
		}
		lightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		RenderInfoClass localRinfo(rinfo.Camera);
		localRinfo.light_environment = &lightEnv;
		Vector3 points[MAX_DISPLAY_NODES + 1];

		const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
		Drawable *draw;
		for (DrawableListCIt it = selected->begin(); it != selected->end(); ++it)
		{
			draw = *it;
			Object *obj = draw->getObject();
			Int numPoints = 1;
			if (obj && !obj->isKindOf(KINDOF_IGNORED_IN_GUI))
			{
				AIUpdateInterface *ai = obj->getAI();
				Int goalSize = ai ? ai->rva00265143() : 0;
				Int gpIdx = ai ? ai->friend_getCurrentGoalPathIndex() : 0;
				if (ai && gpIdx >= 0 && gpIdx < goalSize)
				{
					const Coord3D *pos = obj->getPosition();
					points[0].Set(Vector3(pos->x, pos->y, pos->z));

					for (int i = gpIdx; i < goalSize; i++)
					{
						const Coord3D *waypoint = (const Coord3D *)ai->getStateMachine()->rva00346FA5(i);
						if (waypoint)
						{
							if (numPoints < MAX_DISPLAY_NODES + 1)
							{
								points[numPoints].Set(Vector3(waypoint->x, waypoint->y, waypoint->z));
								numPoints++;
							}

							m_waypointNodeRobj->Set_Position(Vector3(waypoint->x, waypoint->y, waypoint->z));
							WW3D::Render(*m_waypointNodeRobj, localRinfo);
						}
					}
					m_line->Set_Points(numPoints, points);
					m_line->Render(localRinfo);
				}
			}
		}
	}
}
