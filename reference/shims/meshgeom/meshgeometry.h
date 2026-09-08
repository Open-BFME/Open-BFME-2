// Header shim: reference/open-bfme-1's WW3D2 meshgeometry.h with a corrected
// MeshGeometryClass layout. sizeof(MeshGeometryClass) is 0x8C, not the
// vendored copy's 0x94 (padded to 0x1c) or this shim's own first cut (padded
// to 0x8, see the correction note near the tail pad below) -- the member
// order/positions below this line are NOT what the vendored header declares.
// They are read directly out of retail bodies that are already `matched`
// (byte-verified) or pinned from a REL32 call-site address, never derived
// from a header or from Ghidra decompilation.
//
// Evidence, one retail body per anchored offset:
//
//   UserText @ +0x10   MeshGeometryClass::Set_User_Text  0x0016A6C0 (matched)
//                      writes its ShareBufferClass<char>* to [ecx+0x10].
//   MeshName @ +0x14   MeshGeometryClass::Get_Name  0x0016A780 (matched) reads
//                      [ecx+0x14]; ::Set_Name 0x0016A790 (matched) writes it.
//   Flags    @ +0x18   MeshGeometryClass::Compute_Bounds  0x0016A9F0 (matched)
//                      clears DIRTY_BOUNDS with `and [esi+0x18],0xFFFFFFFE`;
//                      ::Compute_Plane_Equations  0x0016A850 (matched) clears
//                      DIRTY_PLANES with `and [ecx+0x18],0xFFFFFFFD`. Both
//                      bits (0x1, 0x2) match FlagsType exactly.
//   PolyCount @ +0x24  MeshGeometryClass::Generate_Culling_Tree  0x0016AD10
//                      (matched) pushes [esi+0x24] as the poly count arg to
//                      the AABTreeBuilderClass; ::Compute_Plane_Equations
//                      loops `cmp eax,[ecx+0x24]`.
//   VertexCount @ +0x28  Generate_Culling_Tree pushes [esi+0x28]; the
//                      mesh_get_shade_indices.cpp local-struct workaround
//                      (matched row, see below) independently reads the same
//                      +0x28 as the array length.
//   Poly @ +0x2C       Generate_Culling_Tree reads [esi+0x2c]->Get_Array();
//                      Compute_Plane_Equations reads [ecx+0x2c]; aabtree.cpp
//                      AABTreeClass::Cast_Ray_To_Polys  0x001981F0 (matched)
//                      reads [eax+0x2c] off the Mesh pointer.
//   Vertex @ +0x30     same three matched bodies read +0x30 next to Poly.
//   VertexShadeIdx @ +0x4C
//                      MeshGeometryClass::get_shade_indices  0x0016A010
//                      (matched via mesh_get_shade_indices.cpp's independent
//                      local-struct overlay, which never includes this real
//                      class definition) reads/writes [edi+0x4c].
//   PolySurfaceType @ +0x58
//                      Cast_Ray_To_Polys  0x001981F0 (matched) reads
//                      [edx+0x58]->Get_Array()[polyhit] for SurfaceType.
//   BoundBoxMin/Max, BoundSphereCenter/Radius @ +0x60..+0x88
//                      Compute_Bounds  0x0016A9F0 (matched) zeroes and then
//                      writes all of [esi+0x60..0x74] (min/max) and
//                      [esi+0x78..0x84] (center/radius); retail's own
//                      Get_Bounding_Box (0x001692F0) and Get_Bounding_Sphere
//                      (0x00169370) read the identical offsets.
//   CullTree @ +0x88   Generate_Culling_Tree stores the built tree pointer
//                      (or NULL on the failure path) to [esi+0x88].
//
// VertexNorm, PlaneEq and VertexBoneLink are real members -- other TUs
// (constructors, copy-assign, meshmdlio.cpp, dx8renderer.cpp) reference them
// by name and must keep compiling -- but NO retail body found so far reads
// them at any offset. Only the SIZE of the space they (plus truly-unknown
// BFME2 additions) occupy is proven, by subtraction between the anchors
// above: 0x18 bytes between Vertex and VertexShadeIdx, and 0x8 bytes between
// VertexShadeIdx and PolySurfaceType. This header places the three named
// pointers at the front of each gap and burns the remainder as a named
// unknown pad -- that placement is a CHOICE for compilation, not evidence.
// Likewise SortLevel/W3dAttributes: no body was found reading them, but the
// 8-byte gap between Flags and PolyCount fits exactly one `char` + 3 bytes of
// natural alignment + one `uint32`, in the same order the upstream ZH header
// uses, so upstream's order is kept rather than invented.
//
// There is NO trailing pad. First cut of this shim added one anyway (0x8
// bytes, to preserve the vendored header's historical sizeof of 0x94) -- that
// was a bug, caught while starting the MeshModelClass follow-on: preserving a
// number the vendored header only had because of ITS OWN wrong "CurMatDesc
// sits at this+0x9c" guess is not a reason to pad anything. DefMatDesc,
// AlternateMatDesc and CurMatDesc are declared (meshmdl.h) as the first three
// members MeshModelClass adds, all pointers, no gap between them or before
// them (no data member precedes DefMatDesc there -- everything above it is
// member functions), so CurMatDesc sits at sizeof(MeshGeometryClass)+8. This
// is no longer resting on the pin alone: wiring this shim into meshmdlio.cpp
// (-Ireference/shims/meshgeom first, plus #include "meshgeometry.h" before
// "meshmdl.h" so this copy wins the include guard ahead of the reference
// tree's own) put CurMatDesc at [this+0x94] and made THREE bodies byte-exact
// against retail: MeshModelClass::get_sort_flags(void) 0x001892F0,
// ::Set_Shader 0x00188040 and ::Set_Single_Shader 0x00149520 (the latter two
// found by place_bodies.py's masked search only after this fix -- the second
// and third bodies the corrected layout was supposed to unlock). That forces
// sizeof(MeshGeometryClass) == 0x8C exactly -- which is exactly where CullTree
// ends (+0x88, 4 bytes) with zero slack. No pad reproduces the anchor; padding
// here was simply arithmetic sloppiness in the first pass. (get_sort_flags(int
// pass), the fourth candidate, does NOT byte-match yet -- its mismatch is
// entirely inside MeshMatDescClass's own ShaderArray/Shader layout, a
// different class this fix does not touch.)
//
// Opt-in per unit: -Ireference/shims/meshgeom FIRST on the `// cl:` line and
// #include "meshgeometry.h" before any header that would reach the reference
// copy out of its own directory.
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
 *                     $Archive:: /Commando/Code/ww3d2/meshgeometry.h                         $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/24/01 7:28p                                              $*
 *                                                                                             *
 *                    $Revision:: 11                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef MESHGEOMETRY_H

#pragma message("USING_CODE_MESHGEOMETRY_H")
#define MESHGEOMETRY_H

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "simplevec.h"
#include "sharebuf.h"
#include "w3derr.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "wwdebug.h"
#include "multilist.h"
#include "coltest.h"
#include "inttest.h"


class AABoxClass;
class OBBoxClass;
class SphereClass;
class ChunkLoadClass;
class AABTreeClass;
class HTreeClass;
class RenderInfoClass;

// Define which kind of index vector to use (16- or 32 bit)
typedef Vector3i16 TriIndex;
//typedef Vector3i TriIndex;

/*
** The following two defines control two space-saving optimizations.  In Renegade I've found
** that the plane equations are about 8% of the geometry space and vertex normals are about 10%
** so I'm trying to see if we can get by without them.  The plane equations are mainly used
** by collision detection functions and those are culled pretty well.  Anyway, collision is
** already so expensive that adding a cross product to it doesn't seem to matter.
**
** NOTE: currently with optimizations enabled, memory gets trashed if you use OPTIMIZE_VNORM_RAM
** I suspect this is due to the way Dynamesh uses (abuses) MeshGeometryClass and haven't had
** time to track it down yet.
*/
#define OPTIMIZE_PLANEEQ_RAM			1
#define OPTIMIZE_VNORM_RAM				0

/**
** MeshGeometryClass
** This class encapsulates the geometry data for a triangle mesh.
*/

// BFME2 layout: see the evidence block at the top of this file. Do not treat
// this as the upstream/ZH layout -- it is not.
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
	//W3DMPO_GLUE(MeshGeometryClass)

public:

	MeshGeometryClass(void);
	MeshGeometryClass(const MeshGeometryClass & that);
	virtual ~MeshGeometryClass(void);

	MeshGeometryClass & operator = (const MeshGeometryClass & that);

	enum FlagsType
	{
		DIRTY_BOUNDS							= 0x00000001,
		DIRTY_PLANES							= 0x00000002,
		DIRTY_VNORMALS							= 0x00000004,

		SORT										= 0x00000010,
		DISABLE_BOUNDING_BOX					= 0x00000020,
		DISABLE_BOUNDING_SPHERE				= 0x00000040,
		DISABLE_PLANE_EQ						= 0x00000080,
		TWO_SIDED								= 0x00000100,

		ALIGNED									= 0x00000200,
		SKIN										= 0x00000400,
		ORIENTED									= 0x00000800,
		CAST_SHADOW								= 0x00001000,

		PRELIT_MASK								= 0x0000E000,
		PRELIT_VERTEX							= 0x00002000,
		PRELIT_LIGHTMAP_MULTI_PASS			= 0x00004000,
		PRELIT_LIGHTMAP_MULTI_TEXTURE		= 0x00008000,

		ALLOW_NPATCHES							= 0x00010000,
	};

	void							Reset_Geometry(int polycount,int vertcount);

	const char *				Get_Name(void) const;
	void							Set_Name(const char * newname);

	const char *				Get_User_Text(void);
	void							Set_User_Text(char * usertext);

	void							Set_Flag(FlagsType flag,bool onoff)						{ if (onoff) {	Flags |= flag;	} else {	Flags &= ~flag; } }
	int							Get_Flag(FlagsType flag)									{ return Flags & flag; }

	void							Set_Sort_Level(int level)									{ SortLevel = level; }
	int							Get_Sort_Level(void) const									{ return SortLevel; }

	int							Get_Polygon_Count(void) const								{ return PolyCount; }
	int							Get_Vertex_Count(void) const								{ return VertexCount; }
	int							Compute_Ram_Size(void);

	const TriIndex*			Get_Polygon_Array(void)										{ return get_polys(); }
	Vector3 *					Get_Vertex_Array(void)										{ WWASSERT(Vertex); return Vertex->Get_Array(); }
	const Vector3 *			Get_Vertex_Normal_Array(void);
	const Vector4 *			Get_Plane_Array(bool create = true);
	void							Compute_Plane(int pidx,PlaneClass * set_plane) const;
	const uint32 *				Get_Vertex_Shade_Index_Array(bool create = true)	{ return get_shade_indices(create); }
	const uint16 *				Get_Vertex_Bone_Links(void)								{ return get_bone_links(); }
	uint8 *						Get_Poly_Surface_Type_Array(void)						{ WWASSERT(PolySurfaceType); return PolySurfaceType->Get_Array(); }
	uint8							Get_Poly_Surface_Type(int poly_index) const;

	void							Get_Bounding_Box(AABoxClass * set_box);
	void							Get_Bounding_Sphere(SphereClass * set_sphere);

	// exposed culling support
	bool							Has_Cull_Tree(void)											{ return CullTree != NULL; }

	void							Generate_Rigid_APT(const Vector3 & view_dir, SimpleDynVecClass<uint32> & apt);
	void							Generate_Rigid_APT(const OBBoxClass & local_box, SimpleDynVecClass<uint32> & apt);
	void							Generate_Rigid_APT(const OBBoxClass & local_box, const Vector3 & view_dir, SimpleDynVecClass<uint32> & apt);

	void							Generate_Skin_APT(const OBBoxClass & world_box, SimpleDynVecClass<uint32> & apt, const Vector3 *world_vertex_locs);

	// containment
	bool							Contains(const Vector3 &point);

	// ray casting and intersection (takes a transform for the mesh). Note that unlike the MeshClass
	// functions with similar names, these work in object space.
	bool							Cast_Ray(RayCollisionTestClass & raytest);
	bool							Cast_AABox(AABoxCollisionTestClass & boxtest);
	bool							Cast_OBBox(OBBoxCollisionTestClass & boxtest);
	bool							Intersect_OBBox(OBBoxIntersectionTestClass & boxtest);

	// This function analyses the transform passed into it to call various optimized functions if
	// the transform is identity or a simple rotation about the z-axis. Otherwise it transforms
	// boxtest into object space, performs an oob cast and transforms the result back.
	bool							Cast_World_Space_AABox(AABoxCollisionTestClass & boxtest, const Matrix3D &transform);

	// W3D File Format support.  Note that derived classes have to override these functions completely
	// so that they can handle their extra chunks.  Using these functions you could load mesh data out
	// of a W3D file while ignoring all materials, textures, etc.
	virtual WW3DErrorType	Load_W3D(ChunkLoadClass & cload);

	void							Scale(const Vector3 &sc);

protected:

	// internal accessor functions that are not exposed to the user (non-const...)
	TriIndex *					get_polys(void);
	Vector3 *					get_vert_normals(void);
	uint32 *						get_shade_indices(bool create = true);
	Vector4 *						get_planes(bool create = true);
	uint16 *						get_bone_links(bool create = true);

	// Utility functions (used by collision/intersection functions)
	int							cast_semi_infinite_axis_aligned_ray(const Vector3 & start_point, int axis_dir, unsigned char & flags);

	bool							cast_aabox_identity(AABoxCollisionTestClass & boxtest,const Vector3 & trans);
	bool							cast_aabox_z90(AABoxCollisionTestClass & boxtest,const Vector3 & trans);
	bool							cast_aabox_z180(AABoxCollisionTestClass & boxtest,const Vector3 & trans);
	bool							cast_aabox_z270(AABoxCollisionTestClass & boxtest,const Vector3 & trans);

	bool							intersect_obbox_brute_force(OBBoxIntersectionTestClass & localtest);
	bool							cast_ray_brute_force(RayCollisionTestClass & raytest);
	bool							cast_aabox_brute_force(AABoxCollisionTestClass & boxtest);
	bool							cast_obbox_brute_force(OBBoxCollisionTestClass & boxtest);

	// functions to recompute dirty normals and bounding volumes.
	virtual void				Compute_Plane_Equations(Vector4 * array);
	virtual void				Compute_Vertex_Normals(Vector3 * array);
	virtual void				Compute_Bounds(Vector3 * verts);
	void							Generate_Culling_Tree(void);

	// W3D chunk reading
	WW3DErrorType				read_chunks(ChunkLoadClass & cload);
	WW3DErrorType				read_vertices(ChunkLoadClass & cload);
	WW3DErrorType				read_vertex_normals(ChunkLoadClass & cload);
	WW3DErrorType				read_triangles(ChunkLoadClass & cload);
	WW3DErrorType				read_user_text(ChunkLoadClass & cload);
	WW3DErrorType				read_vertex_influences(ChunkLoadClass & cload);
	bool						read_vertex_shade_indices(ChunkLoadClass & cload);
	WW3DErrorType				read_aabtree(ChunkLoadClass &cload);

	// functions to compute the deformed vertices of skins.
	// Destination pointers MUST point to arrays large enough to hold all vertices
	void get_deformed_vertices(Vector3 *dst_vert, Vector3 *dst_norm, const HTreeClass * htree);
	void get_deformed_vertices(Vector3 *dst_vert, const HTreeClass * htree);
	void get_deformed_screenspace_vertices(Vector4 *dst_vert,const RenderInfoClass & rinfo,const Matrix3D & mesh_tm,const HTreeClass * htree);

	// General info -- BFME2 order, see the evidence block at the top of this
	// file. UserText precedes MeshName here (upstream has it the other way
	// round, after Flags).
	ShareBufferClass<char> *							UserText;			// +0x10 (proven)
	ShareBufferClass<char> *							MeshName;			// +0x14 (proven)
	int														Flags;				// +0x18 (proven)
	char														SortLevel;			// +0x1C (fits the gap; not independently read)
	uint32													W3dAttributes;		// +0x20 (fits the gap; not independently read)

	// Geometry
	int														PolyCount;			// +0x24 (proven)
	int														VertexCount;		// +0x28 (proven)

	ShareBufferClass<TriIndex> *						Poly;					// +0x2C (proven)
	ShareBufferClass<Vector3> *						Vertex;				// +0x30 (proven)
	// CHOICE, not evidence: no retail body was found reading VertexNorm or
	// PlaneEq at any offset. Only the total gap size before VertexShadeIdx
	// (0x18 bytes) is proven; these two pointers are placed at its front so
	// every other TU that names them keeps compiling, and the remainder is an
	// honestly-unknown pad rather than a guessed shape.
	ShareBufferClass<Vector3> *						VertexNorm;			// +0x34 (unverified placement)
	ShareBufferClass<Vector4> *						PlaneEq;				// +0x38 (unverified placement)
	char														_bfme_unk_3C[0x10];	// +0x3C..+0x4C: unidentified BFME2 fields
	ShareBufferClass<uint32> *						VertexShadeIdx;	// +0x4C (proven)
	// Same as VertexNorm/PlaneEq above: VertexBoneLink's existence is real
	// (dx8renderer.cpp, meshmdlio.cpp reference it by name) but its exact
	// sub-offset within this proven 8-byte gap is a placement choice.
	ShareBufferClass<uint16> *						VertexBoneLink;	// +0x50 (unverified placement)
	char														_bfme_unk_54[0x4];	// +0x54..+0x58: unidentified BFME2 fields
	ShareBufferClass<uint8> *							PolySurfaceType;	// +0x58 (proven)
	char														_bfme_unk_5C[0x4];	// +0x5C..+0x60: unidentified BFME2 fields

	Vector3													BoundBoxMin;		// +0x60 (proven)
	Vector3													BoundBoxMax;		// +0x6C (proven)
	Vector3													BoundSphereCenter;// +0x78 (proven)
	float														BoundSphereRadius;// +0x84 (proven)
	AABTreeClass *											CullTree;			// +0x88 (proven)
	// sizeof(MeshGeometryClass) == 0x8C. No tail pad: see the evidence block
	// at the top of this file -- CullTree ends exactly where MeshModelClass's
	// DefMatDesc must begin for CurMatDesc to land at the retail-proven +0x94.

};

/*
** Inline functions for MeshGeometryClass
*/
inline TriIndex * MeshGeometryClass::get_polys(void)
{
	WWASSERT(Poly);
	return Poly->Get_Array();
}


inline uint32 * MeshGeometryClass::get_shade_indices(bool create)
{
	// Was a hardcoded this+0x54 cast (the BFME1 spelling, per
	// mesh_get_shade_indices.cpp's comment) that no longer applies now that
	// VertexShadeIdx and VertexCount resolve to their proven retail offsets
	// (+0x4C, +0x28) through this corrected layout.
	if (create && !VertexShadeIdx) {
		VertexShadeIdx = NEW_REF(ShareBufferClass<uint32>,(VertexCount, "MeshGeometryClass::VertexShadeIdx"));
	}
	if (VertexShadeIdx) {
		return VertexShadeIdx->Get_Array();
	}
	return NULL;
}

inline uint16 * MeshGeometryClass::get_bone_links(bool create)
{
	if (create && !VertexBoneLink) {
		VertexBoneLink = NEW_REF(ShareBufferClass<uint16>,(VertexCount, "MeshGeometryClass::VertexBoneLink"));
	}
	if (VertexBoneLink) {
		return VertexBoneLink->Get_Array();
	}
	return NULL;
}

inline uint8 MeshGeometryClass::Get_Poly_Surface_Type(int poly_index) const
{
	WWASSERT(PolySurfaceType);
	WWASSERT(poly_index >= 0 && poly_index < PolyCount);
	uint8 *type = PolySurfaceType->Get_Array();
	return type[poly_index];
}

#endif //MESHGEOMETRY_H
