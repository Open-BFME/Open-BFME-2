// cl: /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
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
//
// W3DRenderObjectSnapshot::xfer (0x00063CE9) reads RenderObjClass slots the
// primary table 0x00BD2F68 confirms by name: Get_Sub_Object_By_Name (32),
// Is_Not_Hidden_At_All (97) and Set_Hidden (101); slot 6 is the name getter.
// It clears the sub-object transforms-dirty bit (0x00200000 of the word at
// +0x10) and sets the HLod hierarchy-valid byte +0xF4 on a CLASSID_HLOD
// sub-object. Donor-carried: the names and the Zero Hour body.
//
// W3DGhostObject::xfer (0x00063F78, slot 3 of the table 0x00BC5994) extends
// the rowed GhostObject::xfer 0x003059F5, whose class is the Snapshot at +0x00
// with the parent object at +0x0C. The DrawableInfo at +0xD0 is Zero Hour's
// (object ID, drawable, ghost object, flags); the drawable's ID comes from the
// pinned Drawable::getID 0x0055A88B and is resolved through slot 16 of
// TheGameClient. Snapshots are rebuilt with the loader 0x00137364, the rowed
// disableUVAnimations and W3DRenderObjectSnapshot's constructor, and added to
// W3DDisplay::m_3DScene. The render object's scale is the float at +0x48;
// ThePlayerList's local player is +0x10 and its index +0x54. Both refusals
// throw XferException tag 4. Donor-carried: the names and the Zero Hour body.

#include "ascii_string.h"
#include "Common/Snapshot.h"

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

enum { MAX_PLAYER_COUNT = 20 };

class HAnimClass;
struct DrawableInfo;

class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

// BFME 2 Xfer surface (the TeamInQueueXfer.cpp view): overloads of operator==
// fill the table in reverse declaration order.
class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

// The rowed 0x003062FE (Zero Hour xferMatrix3D) sends the three rows of four floats.
void Rva003062FEXfer(Xfer *xfer, float *vals);

enum ObjectID
{
	INVALID_ID = 0
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);
void XferDrawableID(Xfer *xfer, Int *drawableID);

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class Vector4
{
public:
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	Matrix3D( void ) {}
	__forceinline Matrix3D &operator=(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; return *this; }

	Vector4 Row[3];
};

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
	virtual const char *Get_Name( void ) const;																///< slot 6
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
	virtual RenderObjClass *Get_Sub_Object_By_Name( const char *name, int *index = 0 ) const;	///< slot 32
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
	virtual int Is_Not_Hidden_At_All( void );																	///< slot 97
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void Set_Hidden( int onoff );																			///< slot 101

	enum { SUBOBJ_TRANSFORMS_DIRTY = 0x00200000 };
	void Set_Sub_Object_Transforms_Dirty( bool onoff )
	{
		if (onoff) { Bits |= SUBOBJ_TRANSFORMS_DIRTY; } else { Bits &= ~SUBOBJ_TRANSFORMS_DIRTY; }
	}

	const Matrix3D &Get_Transform( void ) const { Validate_Transform(); return Transform; }
	float Get_ObjectScale( void ) const { return ObjectScale; }
private:
	char m_unrecovered08[ 0x10 - 0x08 ];
	unsigned int Bits;																												///< 0x10
	char m_unrecovered14[ 0x18 - 0x14 ];
	Matrix3D Transform;																												///< 0x18
	float ObjectScale;																												///< 0x48
};

// BFME 2 HLodClass (Animatable3DObjClass) appends Peek_Animation_And_Info as a
// virtual at slot 130 of its table. W3DRenderObjectSnapshot::xfer marks a
// sub-object's hierarchy valid through the byte at +0xF4.
class HLodClass : public RenderObjClass
{
public:
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

	void Friend_Set_Hierarchy_Valid( bool onoff ) const { IsTreeValid = onoff; }
private:
	char m_unrecovered4C[ 0xF4 - 0x4C ];
	mutable bool IsTreeValid;																									///< 0xF4
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

// The asset manager's loader: the free 0x00137364 (name, scale, options) with
// the option block call sites build empty (W3DMouseInitW3DAssets.cpp).
class Rva0013101E
{
public:
	Rva0013101E() : m_a( 0 ), m_b( 0 ), m_c( 0 ), m_d1( 0 ), m_d2( 0 ), m_d3( 0 ) {}

	unsigned m_a : 3;
	unsigned m_b : 27;
	unsigned m_c : 1;
	unsigned m_keep : 1;
	unsigned m_d1;
	unsigned m_d2;
	unsigned m_d3;
};

RenderObjClass *Rva00137364CreateRenderObj( const char *name, float scale, const Rva0013101E &options = Rva0013101E() );

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
	DrawableID getID( void ) const;
	void setFullyObscuredByShroud( Bool fullyObscured );
	DrawModule **getDrawModules( void );
};

// BFME 2 GameClient: findDrawableByID is slot 16 of TheGameClient's table.
class GameClient
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
	virtual Drawable *findDrawableByID( const DrawableID id );								///< slot 16
};
extern GameClient *TheGameClient;

class Player
{
public:
	Int getPlayerIndex( void ) const { return m_playerIndex; }
private:
	char m_unrecovered00[ 0x54 ];
	Int m_playerIndex;																					///< 0x54
};

class PlayerList
{
public:
	Player *getLocalPlayer( void ) { return m_local; }
private:
	char m_unrecovered00[ 0x10 ];
	Player *m_local;																						///< 0x10
};
extern PlayerList *ThePlayerList;

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

class GhostObject : public Snapshot
{
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	char m_unrecovered04[ 0x0C - 0x04 ];
	Object *m_parentObject;																			///< 0x0C
	char m_unrecovered10[ 0x7C - 0x10 ];
	PartitionData *m_partitionData;															///< 0x7C
};

struct DrawableInfo
{
	ObjectID m_shroudStatusObjectID;														///< 0xD0 in W3DGhostObject
	Drawable *m_drawable;																				///< 0xD4
	GhostObject *m_ghostObject;																	///< 0xD8
	Int m_flags;																								///< 0xDC
};

class W3DGhostObjectManager;

/**This class will hold all information about a W3D RenderObject needed to
reconstruct it if necessary*/
class W3DRenderObjectSnapshot : public Snapshot
{
	friend class W3DGhostObject;

	W3DRenderObjectSnapshot(RenderObjClass *m_parentRobj, DrawableInfo *drawInfo, Bool cloneParentRobj = true);
	~W3DRenderObjectSnapshot();
	void update(RenderObjClass *robj, DrawableInfo *drawInfo, Bool cloneParentRobj=true);	///<refresh the current snapshot with latest state
	void addToScene(void) { W3DDisplay::m_3DScene->Add_Render_Object(m_robj); }

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
/** Xfer method
	* Version Info:
	* 1: Initial version
	* BFME 2 versions through Xfer::Version1 and sends the transforms through
	* the rowed xferMatrix3D helper (0x003062FE) where Zero Hour used xferUser. */
// ------------------------------------------------------------------------------------------------
void W3DRenderObjectSnapshot::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	// transform on the main render object
	Matrix3D transform;
	transform = m_robj->Get_Transform();
	Rva003062FEXfer( xfer, (float *)&transform );
	if( xfer->IsLoading() )
		m_robj->Set_Transform( transform );

	// how many sub objects of data will follow
	Int subObjectCount = m_robj->Get_Num_Sub_Objects();
	*xfer == subObjectCount;

	Bool visible;
	RenderObjClass *subObject;
	AsciiString subObjectName;
	for( Int i = 0; i < subObjectCount; ++i )
	{

		//
		// when saving we get sub objects by index and xfer their name, when loading
		// we read the name and find that sub object
		//
		if( xfer->IsStoring() )
		{

			// get sub object
			subObject = m_robj->Get_Sub_Object( i );

			// xfer sub object name which is unique among those in this render object
			subObjectName.set( subObject->Get_Name() );
			*xfer == subObjectName;

		}  // end if, save
		else
		{

			// read sub object name
			*xfer == subObjectName;

			// find this sub object on the object
			subObject = m_robj->Get_Sub_Object_By_Name( subObjectName.str() );

		}  // end else load

		// visible/hidden status of this sub object
		if( subObject )
			visible = subObject->Is_Not_Hidden_At_All();
		*xfer == visible;
		if( subObject && xfer->IsLoading() )
			subObject->Set_Hidden( !visible );

		// transform of this sub object
		if( subObject )
			transform = subObject->Get_Transform();
		Rva003062FEXfer( xfer, (float *)&transform );
		if( subObject && xfer->IsLoading() )
			subObject->Set_Transform( transform );

		// need to tell W3D that this sub object transforms are ok
		if( subObject )
		{

			// need to cast to HLod if we can to validate the hierarchy
			if( subObject->Class_ID() == RenderObjClass::CLASSID_HLOD )
				((HLodClass *)subObject)->Friend_Set_Hierarchy_Valid( true );

		}  // end if

		// release reference to sub object
		if( subObject )
			REF_PTR_RELEASE( subObject );

	}  // end for, i

	// tell W3D that the transforms for our sub objects are all OK cause we've done them ourselves
	m_robj->Set_Sub_Object_Transforms_Dirty( false );

}  // end xfer

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

class W3DGhostObject : public GhostObject
{
	friend class W3DGhostObjectManager;
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	void removeParentObject( void );
	void restoreParentObject( void );
	void addToScene( int playerIndex );
	void removeFromScene( int playerIndex );
	void getShroudStatus( int playerIndex );
	void freeAllSnapShots( void );

	W3DRenderObjectSnapshot *m_parentSnapshots[ MAX_PLAYER_COUNT ];		///< 0x80
	DrawableInfo m_drawableInfo;																///< 0xD0
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
/** Xfer method
	* Version Info:
	* 1: Initial version
	* BFME 2 extends the base class first and stops there on a light CRC, then
	* versions through Xfer::Version1. It writes no render object colour, refuses
	* a render object the loader cannot create and no longer saves the partition
	* shroudedness that Zero Hour appended. */
// ------------------------------------------------------------------------------------------------
void W3DGhostObject::xfer( Xfer *xfer )
{

	// extend base class
	GhostObject::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// xfer the drawable info object id
	XferObjectID( xfer, &m_drawableInfo.m_shroudStatusObjectID );

	// drawable info flags
	*xfer == m_drawableInfo.m_flags;

	// drawable info drawable pointer
	DrawableID drawableID = m_drawableInfo.m_drawable ? m_drawableInfo.m_drawable->getID() : INVALID_DRAWABLE_ID;
	XferDrawableID( xfer, (Int *)&drawableID );
	if( xfer->IsLoading() )
	{

		// reconnect the drawable pointer
		m_drawableInfo.m_drawable = TheGameClient->findDrawableByID( drawableID );

	}  // end if

	// xfer snapshot array
	UnsignedByte snapshotCount;
	for( Int i = 0; i < MAX_PLAYER_COUNT; ++i )
	{

		// count the snapshots at this index
		snapshotCount = 0;
		W3DRenderObjectSnapshot *objectSnapshot = m_parentSnapshots[ i ];
		while( objectSnapshot )
		{

			// increment count
			snapshotCount++;

			// on to the next snapshot
			objectSnapshot = objectSnapshot->m_next;

		}  // end while

		// xfer the snapshot count at this index
		*xfer == snapshotCount;

		//
		// sanity, this catches when we read from the file a count of zero, but our data
		// structure already has something allocated in this snapshot index
		//
		if( snapshotCount == 0 && m_parentSnapshots[ i ] != 0 )
			throw XferException( 4, 0 );

		// xfer each of the snapshots at this index
		Real scale;
		UnsignedInt color;
		AsciiString name;
		if( xfer->IsStoring() )
		{

			// iterate through list
			objectSnapshot = m_parentSnapshots[ i ];
			while( objectSnapshot )
			{

				// write name from render object
				name.set( objectSnapshot->m_robj->Get_Name() );
				*xfer == name;

				// write scale from render object
				scale = objectSnapshot->m_robj->Get_ObjectScale();
				*xfer == scale;

				// BFME 2 keeps the colour field but always writes zero
				color = 0;
				*xfer == color;

				// xfer data
				*xfer == *objectSnapshot;

				// onto the next
				objectSnapshot = objectSnapshot->m_next;

			}  // end while

		}  // end if, save
		else
		{
			RenderObjClass *renderObject;
			W3DRenderObjectSnapshot *prevObjectSnapshot = 0;

			for( UnsignedByte j = 0; j < snapshotCount; ++j )
			{

				// read render object name
				*xfer == name;

				// read scale
				*xfer == scale;

				// read color
				*xfer == color;

				// create the render object
				renderObject = Rva00137364CreateRenderObj( name.str(), scale );
				if( renderObject == 0 )
					throw XferException( 4, 0 );
				disableUVAnimations(renderObject);

				// we're loading, allocate new snapshot
				objectSnapshot = new W3DRenderObjectSnapshot( renderObject, &m_drawableInfo, false );

				// attach to list
				if( prevObjectSnapshot )
					prevObjectSnapshot->m_next = objectSnapshot;
				else
					m_parentSnapshots[ i ] = objectSnapshot;
				prevObjectSnapshot = objectSnapshot;

				// xfer data
				*xfer == *objectSnapshot;

				// add snapshot to the scene
				objectSnapshot->addToScene();

			}  // end for, j

		}  // end else, load

	}  // end for, i

	//
	// since there is a snapshot for this object, there cannot be a regular object/drawable
	// in the world, we need to remove it
	//
	if( m_parentObject &&
			m_parentSnapshots[ ThePlayerList->getLocalPlayer()->getPlayerIndex() ] != 0 &&
			xfer->IsLoading() )
		removeParentObject();

}  // end xfer

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
