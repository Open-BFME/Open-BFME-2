// cl: /MD /DNDEBUG /Ireference/shims/moduledata
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// W3DGhostObject scene and list members, ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObject.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference) onto the
// BFME 2 layout. The ZH-layout W3DGhostObject.cpp beside this file places the
// members elsewhere.
//
// BFME 2 layout, from the W3DGhostObject constructor (0x00063912) and the
// bodies below: m_parentObject +0x0C, m_partitionData +0x7C,
// m_parentSnapshots[20] +0x80, DrawableInfo +0xD0, m_nextSystem +0xE0,
// m_prevSystem +0xE4. The class carries virtual bases (vbptrs at +0x08 and
// +0xEC), which none of these members touch. W3DRenderObjectSnapshot keeps
// ZH's m_robj +0x04 and m_next +0x08. W3DGhostObjectManager keeps ZH's
// m_localPlayer +0x04, the lock flags +0x08/+0x09, m_freeModules +0x0C and
// m_usedModules +0x10. In BFME 2 removeGhostObject is no longer virtual: the
// manager vftable (0x00BC59B8) has no slot for it and reset calls it directly.

#include "Common/Snapshot.h"

typedef int Int;
typedef bool Bool;

class HAnimClass;
class Matrix3D;
struct DrawableInfo;

// The BFME 2 TextureMapperClass, VertexMaterialClass and MaterialInfoClass
// members disableUVAnimations reads: Mapper_ID is slot 2, the stage-0 mapper
// sits at +0x20 and the vertex material count at +0x18.
class TextureMapperClass
{
public:
	enum { MAPPER_ID_LINEAR_OFFSET = 1 };
	virtual void v00();
	virtual void v01();
	virtual int Mapper_ID( void ) const;																			///< slot 2
};

class VertexMaterialClass
{
public:
	TextureMapperClass *Peek_Mapper( int stage = 0 ) { return Mapper[ stage ]; }
private:
	char m_unrecovered00[ 0x20 ];
	TextureMapperClass *Mapper[ 2 ];																					///< 0x20
};

class RefCountClass
{
public:
	virtual void Delete_This( void );																					///< slot 0
	virtual ~RefCountClass();																									///< slot 1
	void Release_Ref( void ) { NumRefs--; if (NumRefs == 0) Delete_This(); }
private:
	int NumRefs;																															///< 0x04
};

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

class MaterialInfoClass : public RefCountClass
{
public:
	int Vertex_Material_Count( void ) const { return VertexMaterialCount; }
	VertexMaterialClass *Peek_Vertex_Material( int index ) const
	{
		if (index < VertexMaterialCount) {
			return VertexMaterials[ index ];
		}
		return 0;
	}
private:
	char m_unrecovered08[ 0x0C - 0x08 ];
	VertexMaterialClass **VertexMaterials;																		///< 0x0C
	char m_unrecovered10[ 0x18 - 0x10 ];
	int VertexMaterialCount;																									///< 0x18
};

// BFME 2 RenderObjClass slots used here (vftable 0x00BD2F68).
class RenderObjClass : public RefCountClass
{
public:
	enum { CLASSID_MESH = 0, CLASSID_HLOD = 0x19 };
	virtual RenderObjClass *Clone( void ) const;															///< slot 2
	virtual int Class_ID( void ) const;																				///< slot 3
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void Remove( void );																							///< slot 16
	virtual void v17();
	virtual void *Peek_Scene( void );																					///< slot 18
	virtual void v19();
	virtual void Validate_Transform( void ) const;														///< slot 20
	virtual void Set_Transform( const Matrix3D &m );													///< slot 21
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual int Get_Num_Sub_Objects( void ) const;														///< slot 28
	virtual void v29();
	virtual RenderObjClass *Get_Sub_Object( int index ) const;								///< slot 30
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void Set_Animation( HAnimClass *motion, float frame, int anim_mode = 0 );	///< slot 45
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual MaterialInfoClass *Get_Material_Info( void );											///< slot 85
	virtual void Set_User_Data( void *value, bool recursive = false );				///< slot 86

	const Matrix3D &Get_Transform( void ) const { Validate_Transform(); return *(const Matrix3D *)&Transform; }
private:
	char m_unrecovered08[ 0x18 - 0x08 ];
	float Transform[ 12 ];																										///< 0x18
};

// BFME 2 HLodClass (Animatable3DObjClass) appends Peek_Animation_And_Info as a
// virtual at slot 130 of its table.
class HLodClass : public RenderObjClass
{
public:
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual HAnimClass *Peek_Animation_And_Info( float &frame, int &numFrames, int &mode, float &mult );	///< slot 130
};

class RTS3DScene
{
public:
	virtual void v00();
	virtual void v01();
	virtual void Add_Render_Object( RenderObjClass *obj );										///< slot 2
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

// Draw modules: BFME 2 asks a draw module for its render object through a
// virtual (slot 49) where Zero Hour cast getObjectDrawInterface() to
// W3DModelDraw and read its render object inline.
class DrawModule
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual RenderObjClass *getRenderObject( void );													///< slot 49
};

class Drawable
{
public:
	void setFullyObscuredByShroud( Bool fullyObscured );
	DrawModule **getDrawModules( void );
};

class Object
{
public:
	Drawable *getDrawable( void ) const;
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID
};

class PartitionData
{
public:
	ObjectShroudStatus getShroudedStatus( Int playerIndex );
};

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager();
	inline Int getLocalPlayerIndex( void ) { return m_localPlayer; }
protected:
	Int m_localPlayer;																					///< 0x04
	Bool m_lockGhostObjects;																		///< 0x08
	Bool m_saveLockGhostObjects;																///< 0x09
};
extern GhostObjectManager *TheGhostObjectManager;

class GhostObject;
class W3DGhostObjectManager;

/**This class will hold all information about a W3D RenderObject needed to
reconstruct it if necessary*/
class W3DRenderObjectSnapshot : public Snapshot
{
	friend class W3DGhostObject;

	W3DRenderObjectSnapshot(RenderObjClass *m_parentRobj, DrawableInfo *drawInfo, Bool cloneParentRobj = true);
	~W3DRenderObjectSnapshot();
	void update(RenderObjClass *robj, DrawableInfo *drawInfo, Bool cloneParentRobj=true);	///<refresh the current snapshot with latest state

protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	RenderObjClass *m_robj;																			///< 0x04
	W3DRenderObjectSnapshot *m_next;														///< 0x08
};

//Dummy material override which we assign to all ghost objects to disable their
//texture animation.
struct Material_Override
{
	char m_unrecovered00[ 0x10 ];
};
static Material_Override animationDisableOverride;

//Helper function used to disable all UV mapper animations on a given model.
//BFME 2 no longer hides MUZZLEFX sub-objects here.
void disableUVAnimations(RenderObjClass *robj)
{
	if (robj && robj->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		//Also disable any animations that may be playing using mappers (texture scrolling)
		for (Int i=0; i < robj->Get_Num_Sub_Objects(); i++)
		{
			RenderObjClass *subObj=robj->Get_Sub_Object(i);
			if (subObj && subObj->Class_ID() == RenderObjClass::CLASSID_MESH)
			{	//check if sub-object has the correct material to do texture scrolling.
				MaterialInfoClass *mat=subObj->Get_Material_Info();
				if (mat)
				{	for (Int j=0; j<mat->Vertex_Material_Count(); j++)
					{
						VertexMaterialClass *vmaterial=mat->Peek_Vertex_Material(j);
						TextureMapperClass *mapper=vmaterial->Peek_Mapper();
						if (mapper && mapper->Mapper_ID() == TextureMapperClass::MAPPER_ID_LINEAR_OFFSET)
						{	
							subObj->Set_User_Data(&animationDisableOverride);	//tell W3D about custom material settings
						}
					}
					REF_PTR_RELEASE(mat);
				}
			}
			REF_PTR_RELEASE(subObj);
		}
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void W3DRenderObjectSnapshot::update(RenderObjClass *robj, DrawableInfo *drawInfo,
																		 Bool cloneParentRobj)
{
	if (m_robj)
	{
		m_robj->Remove();
		REF_PTR_RELEASE(m_robj);
	}

	if( cloneParentRobj == true )
	{

		m_robj=robj->Clone();
		//Set cloned object to same state as original object.
		m_robj->Set_Transform(robj->Get_Transform());
		if (robj->Class_ID() == RenderObjClass::CLASSID_HLOD)
		{	
			float frame,mult;
			int mode,numFrames;

			HAnimClass *hanim=((HLodClass *)robj)->Peek_Animation_And_Info(frame,numFrames,mode,mult);
			m_robj->Set_Animation(hanim,frame);
			disableUVAnimations(m_robj);
		}	//HLOD
	}
	else
		m_robj=robj;

	m_robj->Set_User_Data(drawInfo);

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
W3DRenderObjectSnapshot::W3DRenderObjectSnapshot(RenderObjClass *robj, DrawableInfo *drawInfo,
																								 Bool cloneParentRobj)
{
	m_robj=0;
	m_next=0;
	update(robj, drawInfo, cloneParentRobj);
}

// ------------------------------------------------------------------------------------------------
// BFME 2 takes the render object out of the scene before releasing it
// ------------------------------------------------------------------------------------------------
W3DRenderObjectSnapshot::~W3DRenderObjectSnapshot()
{
	if (m_robj)
		m_robj->Remove();
	REF_PTR_RELEASE(m_robj);
}

class W3DGhostObject
{
	friend class W3DGhostObjectManager;
protected:
	void removeParentObject( void );
	void restoreParentObject( void );
	void addToScene( int playerIndex );
	void removeFromScene( int playerIndex );
	void getShroudStatus( int playerIndex );
	void freeAllSnapShots( void );

	char m_unrecovered00[ 0x0C ];
	Object *m_parentObject;																			///< 0x0C
	char m_unrecovered10[ 0x7C - 0x10 ];
	PartitionData *m_partitionData;																			///< 0x7C
	W3DRenderObjectSnapshot *m_parentSnapshots[ 20 ];						///< 0x80
	char m_unrecoveredD0[ 0xE0 - 0xD0 ];
	W3DGhostObject *m_nextSystem;																///< 0xE0
	W3DGhostObject *m_prevSystem;																///< 0xE4
};

class W3DGhostObjectManager : public GhostObjectManager
{
public:
	virtual void setLocalPlayerIndex( int index );
	void removeGhostObject( GhostObject *object );
protected:
	W3DGhostObject *m_freeModules;															///< 0x0C
	W3DGhostObject *m_usedModules;															///< 0x10
};

// ------------------------------------------------------------------------------------------------
/** Remove the original object from our 3D scene*/
// ------------------------------------------------------------------------------------------------
void W3DGhostObject::removeParentObject(void)
{

	// sanity
	if( m_parentObject == 0 )
		return;

	Drawable *draw=m_parentObject->getDrawable();

	//After we remove the unfogged object, we also disable
	//anything that should be hidden inside fog - shadow, particles, etc.
	draw->setFullyObscuredByShroud(true);

	//walk through all W3D render objects used by this object
	for (DrawModule ** dm = draw->getDrawModules(); *dm; ++dm)
	{
		RenderObjClass *robj=(*dm)->getRenderObject();
		if (robj)
		{
			robj->Remove();
		}
	}
}

// ------------------------------------------------------------------------------------------------
/** Reinsert the original object into our 3D scene*/
// ------------------------------------------------------------------------------------------------
void W3DGhostObject::restoreParentObject(void)
{
	Drawable *draw=m_parentObject->getDrawable();
	if (!draw)
		return;

	//Notify drawable that it's okay to render its render objects again.
	draw->setFullyObscuredByShroud(false);

	//walk through all W3D render objects used by this object
	for (DrawModule ** dm = draw->getDrawModules(); *dm; ++dm)
	{
		RenderObjClass *robj=(*dm)->getRenderObject();
		//robj may be null for modules which have no render objects such
		//as for build-ups that are currently disabled.
		if (robj)
		{	//if we have a render object that's not in the scene, it must have been
			//removed by the ghost object manager, so restore it.
			if (robj->Peek_Scene() == 0)
				W3DDisplay::m_3DScene->Add_Render_Object(robj);
		}
	}
}

// ------------------------------------------------------------------------------------------------
/**Remove the dummy render objects from scene that belong to given player*/
// ------------------------------------------------------------------------------------------------
void W3DGhostObject::removeFromScene(int playerIndex)
{
	W3DRenderObjectSnapshot *snap=m_parentSnapshots[playerIndex];

	while (snap)
	{
		snap->m_robj->Remove();
		snap=snap->m_next;
	}
}

// ------------------------------------------------------------------------------------------------
/**Add the dummy render objects to scene so player sees the correct version within the fog*/
// ------------------------------------------------------------------------------------------------
void W3DGhostObject::addToScene(int playerIndex)
{
	W3DRenderObjectSnapshot *snap=m_parentSnapshots[playerIndex];

	while (snap)
	{
		W3DDisplay::m_3DScene->Add_Render_Object(snap->m_robj);
		snap=snap->m_next;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void W3DGhostObject::getShroudStatus(int playerIndex)
{
	// BFME 2 tolerates a ghost object with no partition data
	if (m_partitionData)
		m_partitionData->getShroudedStatus(playerIndex);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void W3DGhostObject::freeAllSnapShots(void)
{
	Int playerIndex;

	playerIndex = TheGhostObjectManager->getLocalPlayerIndex();
		if (m_parentSnapshots[playerIndex])
		{	//if we have a snapshot for this object, remove it from
			//scene.
			removeFromScene(playerIndex);

			//Restore actual objects assuming they are still alive.
			if (m_parentObject)
				restoreParentObject();

			W3DRenderObjectSnapshot *snap=m_parentSnapshots[playerIndex];
			W3DRenderObjectSnapshot *nextSnap;
			while (snap)
			{	nextSnap = snap->m_next;
				::delete snap;
				snap = nextSnap;
			}
			m_parentSnapshots[playerIndex]=0;
		}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void W3DGhostObjectManager::removeGhostObject(GhostObject *object)
{
	if (!object)
		return;

	W3DGhostObject *mod = (W3DGhostObject *)object;

	mod->freeAllSnapShots();

	// BFME 2: only a module on the used list, and not on the free list, is moved
	W3DGhostObject *it;
	for (it = m_usedModules; it; it = it->m_nextSystem)
		if (it == mod)
			break;
	if (!it)
		return;
	for (it = m_freeModules; it; it = it->m_nextSystem)
		if (it == mod)
			break;
	if (it)
		return;

	// remove module from used list
	if( mod->m_nextSystem )
		mod->m_nextSystem->m_prevSystem = mod->m_prevSystem;
	if( mod->m_prevSystem )
		mod->m_prevSystem->m_nextSystem = mod->m_nextSystem;
	else
		m_usedModules = mod->m_nextSystem;

	// add module to free list
	mod->m_prevSystem = 0;
	mod->m_nextSystem = m_freeModules;
	if( m_freeModules )
		m_freeModules->m_prevSystem = mod;
	m_freeModules = mod;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void W3DGhostObjectManager::setLocalPlayerIndex(int index)
{
	//Whenever we switch local players, we need to remove all ghost objects belonging
	//to another player from the map.  We then insert the current local player's
	//ghost objects into the map.

	W3DGhostObject *mod = m_usedModules;

	while (mod)
	{
		mod->removeFromScene(m_localPlayer);
		if (mod->m_parentSnapshots[index])
		{	//new player has his own snapshot
			if (!mod->m_parentSnapshots[m_localPlayer] && mod->m_parentObject)
			{	//previous player didn't have a snapshot so real object must
				//have been in the scene.  Replace it with our snapshot.
				mod->removeParentObject();
			}
			mod->addToScene(index);
		}
		//new player doesn't have a snapshot which means restore original object
		//if it was replaced by a snapshot by the previous player.
		else
		if (mod->m_parentSnapshots[m_localPlayer] && mod->m_parentObject)
			mod->restoreParentObject();

		mod=mod->m_nextSystem;
	}

	m_localPlayer = index;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?handleNode@Rva006BDB00@@QAEXPAVRva006BDB00Node@@@Z=?removeGhostObject@W3DGhostObjectManager@@QAEXPAVGhostObject@@@Z")
