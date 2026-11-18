// cl: /O1 /G7 /arch:SSE /MD
// Reference: clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngine/Source/Common/Bezier/BezierSegment.cpp, splitSegmentAtT.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later.
// Target Ghidra55A40C+520/RET12, between verified copy55A3C5 and
// separate existing19B destructor55A614. One call reaches evaluator55A0DD.
// Donor de Casteljau arithmetic supplies purpose; target proves the48B prefix
// of twelve floats, two output prefixes and every operation/call in this body.
// Original class/method names and full identity are unknown.
// Difference locals are float triples with trivial copy/destruction constructed before scaling; only
// copies of their three floats use intrinsic memcpy into live point objects.
#include "../../Include/Common/ScalarTypes.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Rva0055A246
{
public:
	Rva0055A246();
	Rva0055A246(const Rva0055A246 &other);
	Rva0055A246(float x0, float y0, float z0, float x1, float y1, float z1,
	             float x2, float y2, float z2, float x3, float y3, float z3);
	Rva0055A246(float coordinates[12]);
	Rva0055A246(const Coord3D &cp0, const Coord3D &cp1,
	             const Coord3D &cp2, const Coord3D &cp3);
	void rva0055A0DD(float t, Coord3D *result) const;
	float rva0055A627(float tolerance) const;
	void rva0055A40C(float t, Rva0055A246 &left, Rva0055A246 &right) const;
	Coord3D m_arr[4];
};
#include <string.h>
#pragma intrinsic(memcpy)
// ?Rva0055A40CDifference present-unmatched
struct Rva0055A40CDifference { float x,y,z; Rva0055A40CDifference(float a,float b,float c):x(a),y(b),z(c) {} void scale(float t) { x*=t;y*=t;z*=t; } void add(const Coord3D *p) { x+=p->x;y+=p->y;z+=p->z; } void add(const Rva0055A40CDifference *p) { x+=p->x;y+=p->y;z+=p->z; } };
void Rva0055A246::rva0055A40C(Real tValue, Rva0055A246 &outSeg1, Rva0055A246 &outSeg2) const
{
	// I think there are faster ways to do this. Could someone clue me in?

	Rva0055A40CDifference p0p1( m_arr[1].x - m_arr[0].x,
									 m_arr[1].y - m_arr[0].y,
									 m_arr[1].z - m_arr[0].z);

	Rva0055A40CDifference p1p2( m_arr[2].x - m_arr[1].x,
									 m_arr[2].y - m_arr[1].y,
									 m_arr[2].z - m_arr[1].z);

	Rva0055A40CDifference p2p3( m_arr[3].x - m_arr[2].x,
									 m_arr[3].y - m_arr[2].y,
									 m_arr[3].z - m_arr[2].z);

	p0p1.scale(tValue);
	p1p2.scale(tValue);
	p2p3.scale(tValue);

	p0p1.add(&m_arr[0]);
	p1p2.add(&m_arr[1]);
	p2p3.add(&m_arr[2]);

	Rva0055A40CDifference triLeft( p1p2.x - p0p1.x, 
											p1p2.y - p0p1.y, 
											p1p2.z - p0p1.z);

	Rva0055A40CDifference triRight( p2p3.x - p1p2.x, 
											 p2p3.y - p1p2.y, 
											 p2p3.z - p1p2.z);

	triLeft.scale(tValue);
	triRight.scale(tValue);

	triLeft.add(&p0p1);
	triRight.add(&p1p2);

	outSeg1.m_arr[0] = m_arr[0];
	memcpy(&outSeg1.m_arr[1], &p0p1, sizeof(p0p1));
	memcpy(&outSeg1.m_arr[2], &triLeft, sizeof(triLeft));
	rva0055A0DD(tValue, &outSeg1.m_arr[3]);

	outSeg2.m_arr[0] = outSeg1.m_arr[3];
	memcpy(&outSeg2.m_arr[1], &triRight, sizeof(triRight));
	memcpy(&outSeg2.m_arr[2], &p2p3, sizeof(p2p3));
	outSeg2.m_arr[3] = m_arr[3];	
}

