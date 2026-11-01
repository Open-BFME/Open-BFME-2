// cl: /Ireference/shims/bfme_sphere_link /DBFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// Link view first: Vector3 operator== (and Length/Normalize/ctor/operator*) stay inline without emitting
// COMDAT copies that disagree with the first copy in link order.
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "../../../../../reference/shims/bfme_vector3_eq_link/vector3_eq_link.h"
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/collect.cpp); this unit had no counterpart under Code/.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
#include "../../../../../reference/shims/bfme_matrix3d_full_zh_link/matrix3d_full_zh_link.h"
#include "../WWMath/SphereClassLink.h"
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/collect.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 1/08/01 10:04a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   CollectionClass::CollectionClass -- default constructor for collection render object      *
 *   CollectionClass::CollectionClass -- constructor for collection render object              *
 *   CollectionClass::CollectionClass -- copy constructor                                      *
 *   CollectionClass::CollectionClass -- assignment operator                                   *
 *   CollectionClass::~CollectionClass -- destructor                                           *
 *   CollectionClass::Clone -- virtual copy constructor                                        *
 *   CollectionClass::Free -- releases all assets in use by this collection                    *
 *   CollectionClass::Class_ID -- returns class id for collection render objects               *
 *   CollectionClass::Get_Num_Polys -- returns the number of polygons in this collection       *
 *   CollectionClass::Render -- render this collection                                         *
 *   CollectionClass::Special_Render -- passes the special render call to all sub-objects      *
 *   CollectionClass::Set_Transform -- set the transform for this collection                   *
 *   CollectionClass::Set_Position -- set the position for this collection                     *
 *   CollectionClass::Get_Num_Sub_Objects -- returns the number of sub objects                 *
 *   CollectionClass::Get_Sub_Object -- returns a pointer to the desired sub object            *
 *   CollectionClass::Add_Sub_Object -- adds another object into this collection               *
 *   CollectionClass::Remove_Sub_Object -- removes a sub object from this collection           *
 *   CollectionClass::Cast_Ray -- passes the ray test to each sub object                       *
 *   CollectionClass::Cast_AABox -- passes the axis-aligned box test to each sub object        *
 *   CollectionClass::Cast_OBBox -- passes the oriented box test to each sub object            *
 *   CollectionClass::Intersect_AABox -- test for intersection with an AABox                   *
 *   CollectionClass::Intersect_OBBox -- test for intersection with an OBBox                   *
 *   CollectionClass::Get_Obj_Space_Bounding_Sphere -- returns the object space bounding spher *
 *   CollectionClass::Get_Obj_Space_Bounding_Box -- returns the object-space bounding box      *
 *   CollectionClass::Snap_Point_Count -- returns the number of snap points in this collecion  *
 *   CollectionClass::Get_Snap_Point -- return the desired snap point                          *
 *   CollectionClass::Scale -- scale the objects in this collection                            *
 *   CollectionClass::Scale -- scale the objects in this collection                            *
 *   CollectionClass::Update_Obj_Space_Bounding_Volumes -- recomputes the object space boundin *
 *   CollectionClass::Update_Sub_Object_Transforms -- recomputes all sub object transforms     *
 *   CollectionLoaderClass::Load -- reads a collection from a w3d file                         *
 *   CollectionDefClass::CollectionDefClass -- constructor                                     *
 *   CollectionDefClass::~CollectionDefClass -- destructor for collection definition           *
 *   CollectionDefClass::Free -- releases assets in use by a collection definition             *
 *   CollectionDefClass::Get_Name -- returns name of the collection                            *
 *   CollectionDefClass::Load -- loads a collection definition from a w3d file                 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


// Retail keeps WW3D2's ProxyClass special members (default ctor, dtor and
// assignment) in the Render2D vector<ProxyClass> units. This unit's select-any
// copies came first in link order and are not retail's, so define the class
// here (as HLodGetProxy.cpp does) with those three declared only: the link
// then keeps retail's owners. The remaining members are the ZH proxy.h ones;
// Get_Proxy and DynamicVectorClass<ProxyClass>::Add call the declared names.
#define __PROXY_H
#include "wwstring.h"
class ProxyClass
{
public:

	ProxyClass (void);
	ProxyClass (const char *name, const Matrix3D &tm) :
		Name (name),
		Transform (tm) { }
	~ProxyClass (void);
	ProxyClass & operator = (const ProxyClass &src);

	bool operator== (const ProxyClass &src)	{ return ((Name == src.Name) && (Transform == src.Transform)); }
	bool operator!= (const ProxyClass &src)	{ return ((Name != src.Name) || (Transform != src.Transform)); }

	const char *			Get_Name (void) const					{ return Name; }
	void						Set_Name (const char *name)			{ Name = name; }

	const Matrix3D &		Get_Transform (void) const				{ return Transform; }
	void						Set_Transform (const Matrix3D &tm)	{ Transform = tm; }

private:

	StringClass				Name;
	Matrix3D					Transform;
};

// Retail's SphereClass::Add_Sphere body is SphereClassAddSphere.cpp; this
// unit's select-any copy came first in link order and is not retail's. Compile
// this unit's sphere.h with the inline members imported (dllimport __forceinline,
// the vector3 link-view idiom) so no competing copy is emitted, then restore
// inline for the rest of the unit.
#define inline __declspec(dllimport) __forceinline
#include "sphere.h"
#undef inline

// Retail's RenderObjClass::Set_Force_Visible is BFME's out-of-line body
// (0x0013B720, RenderObjSetForceVisible.cpp). The ZH rendobj.h this header
// pulls in defines it inline, and the vtables this unit emits would make that
// set/clear-bit copy the first one in link order; the macro leaves the virtual
// declared only and moves the ZH body to an unreferenced non-virtual member.
#define Set_Force_Visible(onoff) Set_Force_Visible(onoff); void Zh_Inline_Set_Force_Visible(onoff)
#include "collect.h"
#undef Set_Force_Visible
#include "chunkio.h"
#include "camera.h"
#include "wwdebug.h"
// Declared before snappts.h instantiates it: declaring the dtor only stops cl
// synthesizing this unit's /G7 scalar deleting destructor copy, first in link
// order; retail's is 0x000F1CF7 (vector_class_vector3_ctor.cpp).
template <> VectorClass<Vector3>::~VectorClass();
template <> bool VectorClass<Vector3>::operator==(VectorClass<Vector3> const &) const;
#include "snappts.h"
#include "assetmgr.h"
#include "ww3d.h"
#include "w3derr.h"
// bfme link decl-only begin
// Retail keeps one VectorClass<Vector3>::Resize, 0x000F0BF1 (vector_class_vector3_resize.cpp);
// this unit only calls it and lists it in the vtable.
template <> bool VectorClass<Vector3>::Resize(int newsize, Vector3 const * array);
// Native 0x000F1C7A is supplied by FXShaderRendererSkin.cpp.
template <> DynamicVectorClass<Vector3>::DynamicVectorClass(unsigned, Vector3 const *);
template <> bool DynamicVectorClass<Vector3>::Resize(int, Vector3 const *);
template <> VectorClass<Vector3>::VectorClass(int, Vector3 const *);
template <> VectorClass<ProxyClass> & VectorClass<ProxyClass>::operator=(VectorClass<ProxyClass> const &);
// Retail keeps the VectorClass<ProxyClass> virtual set in the Render2D
// vector<ProxyClass> units; this unit only lists them in ProxyList's vtable,
// and its copies, first in link order, are not retail's.
template <> bool VectorClass<ProxyClass>::operator==(VectorClass<ProxyClass> const &) const;
template <> bool VectorClass<ProxyClass>::Resize(int, ProxyClass const *);
template <> void VectorClass<ProxyClass>::Clear();
template <> int VectorClass<ProxyClass>::ID(ProxyClass const &);
template <> int VectorClass<ProxyClass>::ID(ProxyClass const *);
// Declaring the dtor only also stops cl synthesizing this unit's non-retail
// scalar deleting destructor copy, ??_G?$VectorClass@VProxyClass@@@@UAEPAXI@Z.
template <> VectorClass<ProxyClass>::~VectorClass();
// bfme link decl-only end
//#include "sr.hpp"


CollectionLoaderClass _CollectionLoader;

/*
** CollectionDefClass.  This is the "blueprint" for a collection object
** The asset manager will store these until someone actually asks it to
** create an instance of the collection object
*/
class CollectionDefClass
{
public:

	CollectionDefClass(void);
	~CollectionDefClass(void);

	const char *	Get_Name(void) const;
	WW3DErrorType	Load(ChunkLoadClass & cload);

protected:

	void				Free(void);

	char								Name[W3D_NAME_LEN];
	DynamicVectorClass<char *> ObjectNames;
	SnapPointsClass *				SnapPoints;

	DynamicVectorClass <ProxyClass>	ProxyList;

	friend class CollectionClass;
};


/*
** CollectionPrototypeClass this is the render object prototype for 
** Collections.
*/
class CollectionPrototypeClass : public W3DMPO, public PrototypeClass
{
	W3DMPO_GLUE(CollectionPrototypeClass)
public:
	CollectionPrototypeClass(CollectionDefClass * def)		{ ColDef = def; WWASSERT(ColDef); }

	virtual const char *			Get_Name(void) const			{ return ColDef->Get_Name(); }	
	virtual int								Get_Class_ID(void) const	{ return RenderObjClass::CLASSID_COLLECTION; }
	virtual RenderObjClass *	Create(void)							{ return NEW_REF( CollectionClass, (*ColDef)); }	
	virtual void							DeleteSelf()							{ delete this; }

	CollectionDefClass *			ColDef;

protected:
	virtual ~CollectionPrototypeClass(void)					{ delete ColDef; }						 
};


/***********************************************************************************************
 * CollectionClass::CollectionClass -- constructor for collection render object                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?CollectionClass::CollectionClass present-unmatched
CollectionClass::CollectionClass(const CollectionDefClass & def) :
	SubObjects(def.ObjectNames.Count()),	
	SnapPoints(NULL)
{
	// Set our name
	Set_Name (def.Get_Name ());

	// create the sub objects
	SubObjects.Resize(def.ObjectNames.Count());
	for (int i=0; i<def.ObjectNames.Count(); i++) {
		WWASSERT(SubObjects.Count() == i);
		SubObjects.Add(WW3DAssetManager::Get_Instance()->Create_Render_Obj(def.ObjectNames[i]));
		SubObjects[i]->Set_Container(this);
	}

	// Copy the list of placeholder objects from the definition
	ProxyList = def.ProxyList;
		
	// grab ahold of the snap points.	
	SnapPoints = def.SnapPoints;
	if (SnapPoints) SnapPoints->Add_Ref();

	// set up our collision typeas the union of all of our sub-objects
	Update_Sub_Object_Bits();

	// update the object bounding volumes
	Update_Obj_Space_Bounding_Volumes();
}


/***********************************************************************************************
 * CollectionClass::Get_Num_Sub_Objects -- returns the number of sub objects                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
int CollectionClass::Get_Num_Sub_Objects(void) const
{
	return SubObjects.Count();
}


/***********************************************************************************************
 * CollectionDefClass::CollectionDefClass -- constructor                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?CollectionDefClass::CollectionDefClass present-unmatched
CollectionDefClass::CollectionDefClass(void)
{
	SnapPoints = NULL;
}

