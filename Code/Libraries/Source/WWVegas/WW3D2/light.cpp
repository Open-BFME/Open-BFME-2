// cl: /arch:SSE2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4  // BFME renamed it
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
 *                     $Archive:: /Commando/Code/ww3d2/light.cpp                              $*
 *                                                                                             *
 *                      $Author:: Ian_l                                                       $*
 *                                                                                             *
 *                     $Modtime:: 7/10/01 2:27p                                               $*
 *                                                                                             *
 *                    $Revision:: 8                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   LightClass::LightClass -- Constructor                                                     *
 *   LightClass::LightClass -- copy constructor                                                *
 *   LightClass::operator == -- assignment operator                                            *
 *   LightClass::~LightClass -- destructor                                                     *
 *   LightClass::Clone -- virtual copy constructor                                             *
 *   LightClass::Get_Attenuation_Range -- returns a dist beyond which the light is attenuated  *
 *   LightClass::Get_Obj_Space_Bounding_Sphere -- returns the object space bounding sphere     *
 *   LightClass::Get_Obj_Space_Bounding_Box -- returns the object space bounding box           *
 *   LightClass::Vertex_Processor_Push -- pushes the light into the GERD                       *
 *   LightClass::Vertex_Processor_Pop -- pops the light from the GERD                          *
 *   LightClass::Set_Transform -- sets transform and marks srLight transform as dirty.         *
 *   LightClass::Set_Position -- sets position and marks srLight transform as dirty.           *
 *   LightClass::Notify_Added -- lights add themselves to the VP list when added               *
 *   LightClass::Notify_Removed -- lights remove themselves from the VP list when removed      *
 *   LightClass::Load_W3D -- Initialize this light from a W3D file                             *
 *   LightClass::Save_W3D -- Save this light's settings into a W3D file                        *
 *   LightClass::Get_Factory -- get the PersistFactory for LightClass                          *
 *   LightClass::Save -- persistant object support                                             *
 *   LightClass::Load -- persistant object support                                             *
 *   LightImpClass::LightImpClass -- constructor                                               *
 *   LightImpClass::Process_Push -- exposes the "push" process for an srLight                  *
 *   LightImpClass::Process_Pop -- exposes the "pop" process for an srLight                    *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// Keep this inlined header helper private to the unit. Its O2 copy is
// not retail's shared 106-byte out-of-line Float_To_Int_Floor provider.
// Fast_Cos at 179950 is owned by the exact PointGroupClassInit header copy.
// This donor view emits a 182-byte helper, so keep that private like its floor helper.
#define Fast_Cos BfmeLightInlineFastCos
#define Float_To_Int_Floor BfmeLightInlineFloatFloor
// Link view first: Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x0004C91A, 0x0006645C).
#include "../../../../../reference/shims/bfme_matrix3d_copy_zh_link/matrix3d_copy_zh_link.h"
#include "light.h"
#include "ww3d.h"
#include "ww3dids.h"
#include "w3d_file.h"
#include "w3d_util.h"
#include "w3derr.h"
#include "chunkio.h"
#include "rinfo.h"
#include "scene.h"
#include "persistfactory.h"
#include "statistics.h"
#undef Float_To_Int_Floor
#undef Fast_Cos



/*
** PersistFactory for LightClasses - lights have custom save-load support.
** BFME: RenderObjClass dropped its PersistClass base, so
** SimplePersistFactoryClass<LightClass> cannot instantiate (its Load returns
** the new object as PersistClass *). Hand-written copy of that template's
** body with a cast, mirroring RenderObjPersistFactoryClass in rendobj.cpp.
*/
class LightPersistFactoryClass : public PersistFactoryClass
{
public:

	virtual uint32				Chunk_ID(void) const;
	virtual PersistClass *	Load(ChunkLoadClass & cload) const;
	virtual void				Save(ChunkSaveClass & csave,PersistClass * obj) const;

	/*
	** Internal chunk id's
	*/
	enum 
	{
		SIMPLEFACTORY_CHUNKID_OBJPOINTER		=	 0x00100100,
		SIMPLEFACTORY_CHUNKID_OBJDATA
	};
};

uint32 LightPersistFactoryClass::Chunk_ID(void) const
{
    return WW3D_PERSIST_CHUNKID_LIGHT;
}

/***********************************************************************************************
 * LightClass::LightClass -- Constructor                                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 * type - type of light to create.                                                             *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/21/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// LightClass::LightClass(LightType): defined in LightClassCopyCtor.cpp (its row's unit).

/***********************************************************************************************
 * LightClass::LightClass -- copy constructor                                                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/21/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// LightClass::LightClass(const LightClass &): defined in LightClassCopyCtor.cpp (its row's unit).


/***********************************************************************************************
 * LightClass::operator == -- assignment operator                                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/21/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// LightClass::operator=: defined in LightClassCopyCtor.cpp (its row's unit).

/***********************************************************************************************
 * LightClass::~LightClass -- destructor                                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/21/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// LightClass::~LightClass: defined in LightClassCopyCtor.cpp (its row's unit).


/***********************************************************************************************
 * LightClass::Clone -- virtual copy constructor                                               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/21/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// LightClass::Clone: defined in LightClassCopyCtor.cpp (its row's unit).


/* NOTE: LightClass::Notify_Added lives in light_notify.cpp (split TU: direct
** BFME1 scene.h keeps Scene::Register at retail vtable +0x38). */


/***********************************************************************************************
 * LightClass::Notify_Removed -- lights remove themselves from the VP list when removed        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/26/99    GTH : Created.                                                                 *
 *=============================================================================================*/
/* NOTE: LightClass::Notify_Removed lives in light_notify.cpp (same split as Notify_Added). */



/***********************************************************************************************
 * LightClass::Get_Obj_Space_Bounding_Sphere -- returns the object space bounding sphere       *
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
// LightClass::Get_Obj_Space_Bounding_Sphere: defined in LightClassCopyCtor.cpp (its row's unit).


/***********************************************************************************************
 * LightClass::Get_Obj_Space_Bounding_Box -- returns the object space bounding box             *
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
// LightClass::Get_Obj_Space_Bounding_Box: defined in LightClassCopyCtor.cpp (its row's unit).
