// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/nullrobj.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
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
 *                     $Archive:: /Commando/Code/ww3d2/nullrobj.cpp                           $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 12/01/01 12:18p                                             $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "nullrobj.h"
#include "chunkio.h"

#include <string.h>


NullLoaderClass _NullLoader;




// Byte-exact /G7 copies live in Null3DObjClassCopyCtor.cpp; these stay inline
// (select-any) so this TU still emits Clone and the Set_ObjectScale gen-alias
// without a duplicate plain definition.

inline Null3DObjClass::Null3DObjClass(const char * name)																	
{
	strcpy(Name, name);
}

inline Null3DObjClass::Null3DObjClass(const Null3DObjClass & src)									
{
	strcpy(Name, src.Name);
}

inline Null3DObjClass & Null3DObjClass::operator = (const Null3DObjClass & that)				
{
	strcpy(Name, that.Name);

	RenderObjClass::operator = (that); return *this; 
}

// ?Null3DObjClass::Class_ID present-unmatched
int Null3DObjClass::Class_ID(void) const													
{ 
	return CLASSID_NULL; 
}

RenderObjClass * Null3DObjClass::Clone(void) const									
{ 
	return NEW_REF( Null3DObjClass, (*this)); 
}

// ?Null3DObjClass::Render present-unmatched
void Null3DObjClass::Render(RenderInfoClass & rinfo)
{ 
}

// Null3DObjClass::Get_Obj_Space_Bounding_Sphere and _Box: defined in
// Null3DObjClassCopyCtor.cpp (their rows' unit; retail stores them with SSE).

/*
** NullPrototypeClass
*/

// ?NullPrototypeClass::NullPrototypeClass present-unmatched
NullPrototypeClass::NullPrototypeClass (void)
{
	// Note that the other members of the definition are uninitialized..
	// So don't rely on them if the name is "NULL".
	strcpy(Definition.Name, "NULL");
}

// ?NullPrototypeClass::NullPrototypeClass present-unmatched
NullPrototypeClass::NullPrototypeClass (const W3dNullObjectStruct &null)
{
	Definition = null;
}


/*
** NullLoaderClass
*/

// ?NullLoaderClass::Load_W3D present-unmatched
PrototypeClass * NullLoaderClass::Load_W3D (ChunkLoadClass &cload)
{
	W3dNullObjectStruct null;
	cload.Read(&null,sizeof(null));
	return W3DNEW NullPrototypeClass(null);
}