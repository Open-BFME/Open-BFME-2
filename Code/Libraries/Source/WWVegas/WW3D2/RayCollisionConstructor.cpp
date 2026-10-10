// cl: /O1 /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#include "lineseg.h"
#include "castres.h"
class RenderObjClass;
// TU-private flattened view of bfme2ray/coltest.h's RayCollisionTestClass:
// the CollisionTestClass base's three members (Result, CollisionType,
// CollidedRenderObj at +0/+4/+8) lead the class as they do in the base, and the
// constructor initialises them first, as the inlined base constructor does.
// Spelling the base here made this unit emit its own /O1 copy of
// ??0CollisionTestClass@@QAE@PAUCastResultStruct@@H@Z (unreferenced: the ray
// constructor inlines it) ahead of retail's /O2 row 0x0065D070 in coltest.cpp.
class RayCollisionTestClass
{
public:
	RayCollisionTestClass(const LineSegClass & ray,CastResultStruct * res,int collision_type,bool check_translucent, bool check_hidden);

	CastResultStruct *			Result;
	int								CollisionType;
	RenderObjClass *				CollidedRenderObj;
	LineSegClass 		Ray;
	bool CheckTranslucent;
	bool CheckHidden;
	bool _bfme_flag42; // Retail primary constructor initializes this extra flag to false.
};
inline RayCollisionTestClass::RayCollisionTestClass(const LineSegClass &ray, CastResultStruct *res, int collision_type, bool check_translucent, bool check_hidden) :
    Result(res), CollisionType(collision_type), CollidedRenderObj(NULL), Ray(ray),
    CheckTranslucent(check_translucent), CheckHidden(check_hidden), _bfme_flag42(false)
{}

typedef char RayCollisionTestSizeMatchesRetail[(sizeof(RayCollisionTestClass) == 0x44) ? 1 : -1];

// Header inline that other units including the header emit as select-any
// copies, which a plain definition here collided with. The anchor keeps this
// unit's copy for the row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRayCollisionConstructor@@YAXPAVRayCollisionTestClass@@ABVLineSegClass@@PAUCastResultStruct@@H_N3@Z present-unmatched
void bfmeEmitRayCollisionConstructor(RayCollisionTestClass *p, const LineSegClass &ray, CastResultStruct *res, int collision_type, bool check_translucent, bool check_hidden)
{
    p->RayCollisionTestClass::RayCollisionTestClass(ray, res, collision_type, check_translucent, check_hidden);
}
#pragma inline_depth()
