// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Keep MSVC math.h float overloads local; matched operations already inline.
#pragma push_macro("inline")
#define inline static inline
#include <math.h>
#pragma pop_macro("inline")
// Link view first: Vector3::Length (and Normalize/Vector3(x,y,z) in the full view) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000692B3, 0x0006924F, 0x006CD510).
#include "../../../../../reference/shims/bfme_vector3_lenfull_link/vector3_lenfull_link.h"
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
 *                 Project Name : LevelEdit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwmath/vehiclecurve.cpp        $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 6/12/01 10:02a                                              $*
 *                                                                                             *
 *                    $Revision:: 8                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "../../../../../reference/shims/bfme_matrix3d_invrot_link/matrix3d_generals.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "vehiclecurve.h"
#include "vector3.h"
#include "matrix3d.h"
#include "persistfactory.h"
#include "wwmathids.h"
#include "wwmemlog.h"


//////////////////////////////////////////////////////////////////////
// Save-Load stuff
//////////////////////////////////////////////////////////////////////
// BFME 2 has no VehicleCurve persistence: game.dat holds neither its factory's
// Chunk_ID body (B8 05 01 08 00 C3) nor the chunk IDs 0x11071217/0x00080105,
// so the Zero Hour factory and its Save/Load/Evaluate bodies are not ported.
// The arc-list vector members retail does keep are instantiated here.
struct VehicleCurveArcListView : VehicleCurveClass { typedef ArcInfoStruct Elem; };
template DynamicVectorClass<VehicleCurveArcListView::Elem>::DynamicVectorClass(unsigned, VehicleCurveArcListView::Elem const *);
template void DynamicVectorClass<VehicleCurveArcListView::Elem>::Delete_All(void);

////////////////////////////////////////////////////////////////
//	Save/Load constants
////////////////////////////////////////////////////////////////
enum
{
	CHUNKID_PARENT					= 0x11071217,
	CHUNKID_ARC_INFO,
	CHUNKID_VARIABLES
};

enum
{
	VARID_IS_DIRTY					= 1,
	VARID_RADIUS,
};


//////////////////////////////////////////////////////////////////////
//	Local prototypes
//////////////////////////////////////////////////////////////////////
bool	Find_Tangent (const Vector3 &center, float radius, const Vector3 &point, bool clockwise, float *result);
float	Get_Angle_Delta (float angle1, float angle2, bool clockwise);
void	Find_Turn_Arc (const Matrix3D &transform, float radius, const Vector3 &prev_pt, const Vector3 &curr_pt, const Vector3 &next_pt, Vector3 *arc_center, bool *is_right_turn);
void	Find_Tangents (float radius, const Vector3 &prev_pt, const Vector3 &curr_pt, const Vector3 &next_pt, const Vector3 &arc_center, bool is_right_turn, float *point_angle, float *angle_in_delta, float *angle_out_delta);


//////////////////////////////////////////////////////////////////////
//
//	Find_Tangent
//
//////////////////////////////////////////////////////////////////////
bool
Find_Tangent
(
	const Vector3 &	center,
	float					radius,
	const Vector3 &	point,
	bool					clockwise,
	float	*				result
)
{
	bool retval = false;

	//
	//	Calculate the distance from the point to the center of the circle
	//
	float delta_x = point.X - center.X;
	float delta_y = point.Y - center.Y;
	float dist = ::sqrt (delta_x * delta_x + delta_y * delta_y);
	if (dist >= radius) {

		//
		//	Determine the offset angle (from the line between the point and center)
		// where the 2 tangent points lie.
		//
		float angle_offset	= WWMath::Acos (radius / dist);
		float base_angle		= WWMath::Atan2 (delta_x, -delta_y);
		base_angle = WWMath::Wrap (base_angle, 0, DEG_TO_RADF (360));

		//
		//	Determine which tangent angle we would come across first, depending
		// on our orientation
		//
		float angle = 0;
		if (clockwise) {
			angle = base_angle - angle_offset;
		} else {
			angle = base_angle + angle_offset;
		}
		angle = WWMath::Wrap (angle, 0, DEG_TO_RADF (360));
		(*result) = angle;

		retval = true;
	}

	return retval;
}


//////////////////////////////////////////////////////////////////////
//
//	Get_Angle_Delta
//
//	Angle deltas need to be wrapped around 360 degrees differently
// depending on the orientation (clockwise/counterclockwise).  This
// function takes orientation into consideration when determining
// the delta.
//
//////////////////////////////////////////////////////////////////////
float
Get_Angle_Delta
(
	float	angle1,
	float angle2,
	bool	clockwise
)
{
	float result = angle1 - angle2;

	if (clockwise) {
		if (angle1 < angle2) {
			result = angle1 - (angle2 - DEG_TO_RADF (360));
		}
	} else {
		if (angle1 > angle2) {
			result = (angle1 - DEG_TO_RADF (360)) - angle2;
		}
	}

	return result;
}


//////////////////////////////////////////////////////////////////////
//
//	Find_Turn_Arc
//
//////////////////////////////////////////////////////////////////////
void
Find_Turn_Arc
(
	const Matrix3D &	transform,
	float					radius,
	const Vector3 &	prev_pt,
	const Vector3 &	curr_pt,
	const Vector3 &	next_pt,
	Vector3 *			arc_center,
	bool *				is_right_turn
)
{
	//
	//	The center of the turn arc can lie anywhere on the circle centered
	// at the current point and 'radius' meters in radius.
	//
	//	We will assume the optimal center of the turn arc will lie at
	// the point halfway between the angles formed by the (prev-curr) and
	// (next-curr) vectors.
	//
	float angle1 = ::WWMath::Atan2 ((prev_pt.Y - curr_pt.Y), prev_pt.X - curr_pt.X);
	angle1 = WWMath::Wrap (angle1, 0, DEG_TO_RADF (360));

	float angle2 = ::WWMath::Atan2 ((next_pt.Y - curr_pt.Y), next_pt.X - curr_pt.X);
	angle2 = WWMath::Wrap (angle2, 0, DEG_TO_RADF (360));

	float avg_angle = (angle1 + angle2) * 0.5F;

	//
	//	Find the shortest delta between the two angles (either clockwise or
	// counterclockwise).
	//
	float delta1 = WWMath::Fabs (::Get_Angle_Delta (angle1, angle2, true));
	float delta2 = WWMath::Fabs (::Get_Angle_Delta (angle1, angle2, false));
	if (delta1 < delta2) {
		avg_angle = angle1 - (delta1 * 0.5F);
	} else {
		avg_angle = angle1 + (delta2 * 0.5F);
	}

	//
	//	Find the point on the circle at this angle
	//
	arc_center->X = curr_pt.X + (radius * ::WWMath::Cos (avg_angle));
	arc_center->Y = curr_pt.Y + (radius * ::WWMath::Sin (avg_angle));
	arc_center->Z = curr_pt.Z;	

	//
	//	Will we be making a right turn or a left turn?
	//
	Vector3 rel_center;
	Matrix3D::Inverse_Transform_Vector (transform, *arc_center, &rel_center);
	(*is_right_turn) = (rel_center.Y > 0);
	return ;
}


//////////////////////////////////////////////////////////////////////
//
//	Find_Tangents
//
//////////////////////////////////////////////////////////////////////
void
Find_Tangents
(
	float					radius,
	const Vector3 &	prev_pt,
	const Vector3 &	curr_pt,
	const Vector3 &	next_pt,
	const Vector3 &	arc_center,
	bool					is_right_turn,
	float *				point_angle,
	float *				angle_in_delta,
	float *				angle_out_delta
)
{

	//
	//	Find the 'in' and 'out' tangent angles
	//
	float angle_in	= 0;
	float angle_out = 0;
	bool valid_in = ::Find_Tangent (arc_center, radius, prev_pt, is_right_turn, &angle_in);
	bool valid_out = ::Find_Tangent (arc_center, radius, next_pt, !is_right_turn, &angle_out);

	//
	//	Find the angle where the current position lies on the turn arc
	//
	(*point_angle) = ::WWMath::Atan2 (curr_pt.X - arc_center.X, -(curr_pt.Y - arc_center.Y));	
	(*point_angle) = WWMath::Wrap ((*point_angle), 0, DEG_TO_RADF (360));

	//
	//	If the tangent-in is valid, find its delta from the 'point angle.
	//
	if (valid_in) {
		(*angle_in_delta) = ::Get_Angle_Delta (angle_in, (*point_angle), is_right_turn);
	} else {
		(*angle_in_delta) = 0;
	}

	//
	//	If the tangent-out is valid, find its delta from the 'point angle.
	//
	if (valid_out) {
		(*angle_out_delta) = ::Get_Angle_Delta (angle_out, (*point_angle), !is_right_turn);
	} else {
		(*angle_out_delta) = 0;
	}

	return ;
}


//////////////////////////////////////////////////////////////////////
//
//	Update_Arc_List
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
//	Evaluate
//
//////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////
//
//	Save
//
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
//
//	Load
//
////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
//
//	Load_Variables
//
///////////////////////////////////////////////////////////////////////

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0GadgetCreateView@@QAE@XZ=??0_ArcInfoStruct@VehicleCurveClass@@QAE@XZ")
