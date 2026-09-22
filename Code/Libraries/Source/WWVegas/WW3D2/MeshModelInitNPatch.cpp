// cl: /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
class CameraClass;
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
 *                     $Archive:: /Commando/Code/ww3d2/meshmdl.cpp                            $*
 *                                                                                             *
 *                    Org Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               *
 *                                                                                             *
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 48                                                          $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "meshmdl.h"
#include "matinfo.h"
#include "aabtree.h"
#include "htree.h"
#include "vp.h"
#include "visrasterizer.h"
#include "dx8polygonrenderer.h"
#include "bwrender.h"
#include "camera.h"
#include "dx8renderer.h"
#include "hashtemplate.h"

struct TriangleSide
{
	Vector3 loc1;
	Vector3 loc2;
	TriangleSide(const Vector3& l1,const Vector3& l2)
	{
		int i1=*(int*)&l1[0];
		i1=37*i1+*(int*)&l1[1];
		i1=37*i1+*(int*)&l1[2];
		int i2=*(int*)&l2[0];
		i2=37*i2+*(int*)&l2[1];
		i2=37*i2+*(int*)&l2[2];
		if (i1<i2) {
			loc1=l1;
			loc2=l2;
		}
		else {
			loc2=l1;
			loc1=l2;
		}
	}
	TriangleSide() {}

	bool operator== (const TriangleSide& s)
	{
		unsigned i=*(unsigned*)&loc1[0]^*(unsigned*)&s.loc1[0];
		i|=*(unsigned*)&loc1[1]^*(unsigned*)&s.loc1[1];
		i|=*(unsigned*)&loc1[2]^*(unsigned*)&s.loc1[2];
		i|=*(unsigned*)&loc2[0]^*(unsigned*)&s.loc2[0];
		i|=*(unsigned*)&loc2[1]^*(unsigned*)&s.loc2[1];
		i|=*(unsigned*)&loc2[2]^*(unsigned*)&s.loc2[2];
		return !i;
	}
};

// Get_Hash_Value specialization for Vector3.

template <> inline unsigned int HashTemplateKeyClass<Vector3>::Get_Hash_Value(const Vector3& location)
{
	const unsigned char* buffer=(const unsigned char*)&location;
	unsigned int hval=0;
	for (unsigned int a=0;a<sizeof(Vector3);++a) {
		hval+=37*hval+buffer[a];
	}
	return hval;
}

// Get_Hash_Value specialization for TriangleSide.

template <> inline unsigned int HashTemplateKeyClass<TriangleSide>::Get_Hash_Value(const TriangleSide& side)
{
	const unsigned char* buffer=(const unsigned char*)&side;
	unsigned int hval=0;
	for (unsigned int a=0;a<sizeof(TriangleSide);++a) {
		hval+=37*hval+buffer[a];
	}
	return hval;
}

struct SideIndexInfo
{
	unsigned short vidx1;
	unsigned short vidx2;
	unsigned polygon_index;
	SideIndexInfo() {}
	SideIndexInfo(int i) { WWASSERT(0); }
};



extern unsigned char *BfmeCurrentCaps;
extern HashTemplateClass<Vector3,unsigned> LocationHash;
extern HashTemplateClass<Vector3,unsigned> DuplicateLocationHash;
extern HashTemplateClass<TriangleSide,SideIndexInfo> SideHash;

// BFME1 meshmdl.cpp body at 0x0094F660, compiled with /G7.
// Retail 0x172F90 ends at 0x173227; Ghidra 660B truncates the final epilogue.
// Caller 0x173230 sets HasBeenInUse and gates this call on N-patch settings.
// Matched caps/flag consumers establish supportNPatches +0x13B and flag 0x10000.
// Hash global names follow the donor; target helper types and use distinguish
// the unique-coordinate, duplicate-coordinate, and triangle-side tables.
void MeshModelClass::Init_For_NPatch_Rendering()
{
	if (!BfmeCurrentCaps[0x13b]) return;
	if (!Get_Flag(MeshGeometryClass::ALLOW_NPATCHES)) return;

	struct BfmeMeshGeometryFields {
		char pad[0x24];
		unsigned polygon_count;
		unsigned vertex_count;
		ShareBufferClass<TriIndex>* poly;
		ShareBufferClass<Vector3>* vertex;
	};
	BfmeMeshGeometryFields *fields = reinterpret_cast<BfmeMeshGeometryFields *>(this);
	const Vector3* locations=fields->vertex->Get_Array();
	unsigned vertex_count=fields->vertex_count;
	const TriIndex* polygon_indices=fields->poly->Get_Array();
	unsigned polygon_count=fields->polygon_count;

	LocationHash.Remove_All();
	DuplicateLocationHash.Remove_All();
	SideHash.Remove_All();

	for (unsigned i=0;i<vertex_count;++i) {
		if (LocationHash.Exists(locations[i])) {
			if (!DuplicateLocationHash.Exists(locations[i])) {
				DuplicateLocationHash.Insert(locations[i],i);
			}
		}
		else {
			LocationHash.Insert(locations[i],i);
		}
	}

	for (i=0;i<polygon_count;++i) {
		bool duplicates[3];
		duplicates[0]=DuplicateLocationHash.Exists(locations[polygon_indices[i][0]]);
		duplicates[1]=DuplicateLocationHash.Exists(locations[polygon_indices[i][1]]);
		duplicates[2]=DuplicateLocationHash.Exists(locations[polygon_indices[i][2]]);
		if (duplicates[0] && duplicates[1]) {
			TriangleSide tri(locations[polygon_indices[i][0]],locations[polygon_indices[i][1]]);
			if (!SideHash.Exists(tri)) {
				SideIndexInfo side_index;
				side_index.vidx1=polygon_indices[i][0];
				side_index.vidx2=polygon_indices[i][1];
				side_index.polygon_index=i;
				SideHash.Insert(tri,side_index);
			}
		}
		if (duplicates[1] && duplicates[2]) {
			TriangleSide tri(locations[polygon_indices[i][1]],locations[polygon_indices[i][2]]);
			if (!SideHash.Exists(tri)) {
				SideIndexInfo side_index;
				side_index.vidx1=polygon_indices[i][1];
				side_index.vidx2=polygon_indices[i][2];
				side_index.polygon_index=i;
				SideHash.Insert(tri,side_index);
			}
		}
		if (duplicates[2] && duplicates[0]) {
			TriangleSide tri(locations[polygon_indices[i][2]],locations[polygon_indices[i][0]]);
			if (!SideHash.Exists(tri)) {
				SideIndexInfo side_index;
				side_index.vidx1=polygon_indices[i][2];
				side_index.vidx2=polygon_indices[i][0];
				side_index.polygon_index=i;
				SideHash.Insert(tri,side_index);
			}
		}
	}

	LocationHash.Remove_All();
	DuplicateLocationHash.Remove_All();
	SideHash.Remove_All();
}
