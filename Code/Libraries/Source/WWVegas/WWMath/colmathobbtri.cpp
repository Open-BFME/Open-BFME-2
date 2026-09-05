// cl: /G7 /arch:SSE2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /DNDEBUG
// Shared box/triangle intersection source from Open-BFME-1, verified against
// BFME2 retail. The SSE2 code generation matches this game.

#include "colmath.h"
#include "obbox.h"
#include "tri.h"
#include "wwdebug.h"

#define AXISLEN_EPSILON2	WWMATH_EPSILON * WWMATH_EPSILON	// squared length of a separating axis must be larger than this

struct BTIntersectStruct
{
	BTIntersectStruct(const OBBoxClass &box,const TriClass &tri) :
		Box(box),															
		Tri(tri)
	{
		Vector3::Subtract(*tri.V[0],box.Center,&D);				// vector from center of box to vertex 0
		Vector3::Subtract(*tri.V[1],*tri.V[0],&E[0]);			
		Vector3::Subtract(*tri.V[2],*tri.V[0],&E[1]);			
		Vector3::Subtract(E[1],E[0],&E[2]);

		A[0].Set(box.Basis[0][0],box.Basis[1][0],box.Basis[2][0]);
		A[1].Set(box.Basis[0][1],box.Basis[1][1],box.Basis[2][1]);
		A[2].Set(box.Basis[0][2],box.Basis[1][2],box.Basis[2][2]);
	
		Vector3::Cross_Product(E[0],E[1],&N);	
	}

	Vector3					D;						// Vector from the center of the box to v0
	float						AE[3][3];			// Dot products of the Basis vectors and edges
	float						AN[3];				// Dot products of the Basis vectors and the normal
	Vector3					AxE[3][3];			// Cross produts of the Basis vectors and edges

	Vector3					A[3];					// basis vectors for the box
	Vector3					E[3];					// edge vectors for the triangle 
	Vector3					N;						// normal (NOT normalized!!!)

	Vector3					TestAxis;			// separating axis currently being tested

	const OBBoxClass &	Box;
	const TriClass &		Tri;

private:
	
	// not implemented
	BTIntersectStruct(const BTIntersectStruct &);
	BTIntersectStruct & operator = (const BTIntersectStruct &);
};

static inline bool obbtri_intersection_separation_test
(
	BTIntersectStruct &	context,
	float						lp,
	float						leb0
)
{
	/*
	** Only compute the normalized epsilon if we need to.
	** - compute 'EPSILON' normalized to the length of the axis
	** - If (I'm no more than 'EPSILON' embedded in the polygon) then the box and tri are separated
	*/
	float eps = 0.0f;
	if (lp - leb0 <= 0.0f) {
		eps = COLLISION_EPSILON * context.TestAxis.Length();	// trying to only compute epsilon if I have to
	}

	return (lp - leb0 > -eps);
}

static inline bool obbtri_check_intersection_cross_axis
(
	BTIntersectStruct &	context,
	float						dp,
	float						leb0
)
{
	float		p0;						// distance from box center to vertex 0
	float		lp;						// leading edge of the polygon.

	p0 = Vector3::Dot_Product(context.D,context.TestAxis);

	// I want the axis centered at the box, pointing towards the triangle
	if (p0 < 0) {		
		context.TestAxis = -context.TestAxis;
		p0 = -p0;
		dp = -dp;
	}

	// compute coordinate of "leading edge of the triangle" relative to the box center.
	lp = 0;
	if (dp < 0) { lp = dp; }
	lp = p0 + lp;	

	return obbtri_intersection_separation_test(context,lp,leb0);
}

static inline bool obbtri_check_intersection_basis_axis
(
	BTIntersectStruct &	context,
	float						leb0,
	float						dp1,
	float						dp2
)
{
	float		dist;						// separation along the axis
	float		lp;						// leading edge of the polygon.

	dist = Vector3::Dot_Product(context.D,context.TestAxis);

	// we want the axis centered at the box, pointing towards the triangle
	if (dist < 0) {		
		context.TestAxis = -context.TestAxis;
		dist = -dist;
		dp1 = -dp1;
		dp2 = -dp2;
	} 

	// compute coordinate of "leading edge of the polygon" relative to the box center.
	lp = 0;
	if (dp1 < lp) { lp = dp1; }
	if (dp2 < lp) { lp = dp2; }
	lp = dist + lp;	

	return obbtri_intersection_separation_test(context,lp,leb0);
}

static inline bool obbtri_check_intersection_normal_axis
(
	BTIntersectStruct &	context
)
{
	float		dist;						// separation along the axis
	float		leb0;						// initial coordinate of the leading edge of the box
	float		lp;						// leading edge of the polygon.

	dist = Vector3::Dot_Product(context.D,context.TestAxis);

	// we want the axis centered at the box, pointing towards the triangle
	if (dist < 0) {
		context.TestAxis = -context.TestAxis;
		dist = -dist;
	}

	leb0 =	context.Box.Extent.X * WWMath::Fabs(context.AN[0]) +
				context.Box.Extent.Y * WWMath::Fabs(context.AN[1]) + 
				context.Box.Extent.Z * WWMath::Fabs(context.AN[2]);
	lp = dist;	// this is the "optimization", don't have to find lp

	return obbtri_intersection_separation_test(context,lp,leb0);
}

// ?Intersection_Test@CollisionMath@@ present-unmatched
bool CollisionMath::Intersection_Test(const OBBoxClass & box,const TriClass & tri)
{
	float dp,leb0;
	BTIntersectStruct	context(box,tri);

	/*
	** AXIS_N
	*/
	context.TestAxis = context.N;
	context.AN[0] = Vector3::Dot_Product(context.A[0],context.N);
	context.AN[1] = Vector3::Dot_Product(context.A[1],context.N);
	context.AN[2] = Vector3::Dot_Product(context.A[2],context.N);
	if (obbtri_check_intersection_normal_axis(context)) return false;

	/*
	** AXIS_A0
	*/
	context.TestAxis = context.A[0];
	context.AE[0][0] = Vector3::Dot_Product(context.A[0],context.E[0]);
	context.AE[0][1] = Vector3::Dot_Product(context.A[0],context.E[1]);
	if (obbtri_check_intersection_basis_axis(context,box.Extent.X,context.AE[0][0],context.AE[0][1])) return false;

	/*
	** AXIS_A1
	*/
	context.TestAxis = context.A[1];
	context.AE[1][0] = Vector3::Dot_Product(context.A[1],context.E[0]);
	context.AE[1][1] = Vector3::Dot_Product(context.A[1],context.E[1]);
	if (obbtri_check_intersection_basis_axis(context,box.Extent.Y,context.AE[1][0],context.AE[1][1])) return false;

	/*
	** AXIS_A2
	*/
	context.TestAxis = context.A[2];
	context.AE[2][0] = Vector3::Dot_Product(context.A[2],context.E[0]);
	context.AE[2][1] = Vector3::Dot_Product(context.A[2],context.E[1]);
	if (obbtri_check_intersection_basis_axis(context,box.Extent.Z,context.AE[2][0],context.AE[2][1])) return false;

	/*
	** AXIS_A0xE0
	*/
	Vector3::Cross_Product(context.A[0],context.E[0],&context.AxE[0][0]);
	context.TestAxis = context.AxE[0][0];
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = context.AN[0];
		leb0 = box.Extent[1]*WWMath::Fabs(context.AE[2][0]) + box.Extent[2]*WWMath::Fabs(context.AE[1][0]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	/*
	** AXIS_A0xE1
	*/
	Vector3::Cross_Product(context.A[0],context.E[1],&context.AxE[0][1]);
	context.TestAxis = context.AxE[0][1];
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = -context.AN[0];
		leb0 = box.Extent[1]*WWMath::Fabs(context.AE[2][1]) + box.Extent[2]*WWMath::Fabs(context.AE[1][1]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	/*
	** AXIS_A0xE2
	*/
	Vector3::Cross_Product(context.A[0],context.E[2],&context.AxE[0][2]);
	context.TestAxis = context.AxE[0][2];
	context.AE[1][2] = Vector3::Dot_Product(context.A[1],context.E[2]);
	context.AE[2][2] = Vector3::Dot_Product(context.A[2],context.E[2]);
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = -context.AN[0];
		leb0 = box.Extent[1]*WWMath::Fabs(context.AE[2][2]) + box.Extent[2]*WWMath::Fabs(context.AE[1][2]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	/*
	** AXIS_A1xE0
	*/
	Vector3::Cross_Product(context.A[1],context.E[0],&context.AxE[1][0]);
	context.TestAxis = context.AxE[1][0];
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = context.AN[1];
		leb0 = box.Extent[0]*WWMath::Fabs(context.AE[2][0]) + box.Extent[2]*WWMath::Fabs(context.AE[0][0]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	/*
	** AXIS_A1xE1
	*/
	Vector3::Cross_Product(context.A[1],context.E[1],&context.AxE[1][1]);
	context.TestAxis = context.AxE[1][1];
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = -context.AN[1];
		leb0 = box.Extent[0]*WWMath::Fabs(context.AE[2][1]) + box.Extent[2]*WWMath::Fabs(context.AE[0][1]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	/*
	** AXIS_A1xE2
	*/
	Vector3::Cross_Product(context.A[1],context.E[2],&context.AxE[1][2]);
	context.TestAxis = context.AxE[1][2];
	context.AE[0][2] = Vector3::Dot_Product(context.A[0],context.E[2]);
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = -context.AN[1];
		leb0 = box.Extent[0]*WWMath::Fabs(context.AE[2][2]) + box.Extent[2]*WWMath::Fabs(context.AE[0][2]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	/*
	** AXIS_A2xE0
	*/
	Vector3::Cross_Product(context.A[2],context.E[0],&context.AxE[2][0]);
	context.TestAxis = context.AxE[2][0];
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = context.AN[2];
		leb0 = box.Extent[0]*WWMath::Fabs(context.AE[1][0]) + box.Extent[1]*WWMath::Fabs(context.AE[0][0]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	/*
	** AXIS_A2xE1
	*/
	Vector3::Cross_Product(context.A[2],context.E[1],&context.AxE[2][1]);
	context.TestAxis = context.AxE[2][1];
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = -context.AN[2];
		leb0 = box.Extent[0]*WWMath::Fabs(context.AE[1][1]) + box.Extent[1]*WWMath::Fabs(context.AE[0][1]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}
	
	/*
	** AXIS_A2xE2
	*/
	Vector3::Cross_Product(context.A[2],context.E[2],&context.AxE[2][2]);
	context.TestAxis = context.AxE[2][2];
	if (context.TestAxis.Length2() > AXISLEN_EPSILON2) {
		dp = -context.AN[2];
		leb0 = box.Extent[0]*WWMath::Fabs(context.AE[1][2]) + box.Extent[1]*WWMath::Fabs(context.AE[0][2]);
		if (obbtri_check_intersection_cross_axis(context,dp,leb0)) return false;
	}

	return true;
}

