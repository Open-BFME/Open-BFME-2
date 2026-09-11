// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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

// Small RenderObjClass members from rendobj.cpp, on the bfme2renderobj model,
// each found through the retail RenderObjClass vtable at 0x00BD2F68:
//   0x0013B770 Get_Scene                     0x0013B780 Set_Container
//   0x0013BCA0 Remove                        0x0013BCF0 Get_Obj_Space_Bounding_Sphere
//   0x0013BAA0 Get_Cost                      0x0013BAC0 Calculate_Cost_Value_Arrays
//   0x0013BA80 Remove_Sub_Objects_From_Bone (by name)
//   0x0013BA10 Remove_Sub_Objects_From_Bone (by index)
// All are Zero Hour's bodies unchanged.

#include "rendobj.h"
#include "scene.h"

void RenderObjClass::Add(SceneClass * scene)
{
	Scene = scene;
	scene->Add_Render_Object(this);
}

SceneClass * RenderObjClass::Get_Scene(void)
{
	if (Scene != NULL) {
		Scene->Add_Ref();
	}
	return Scene;
}

void RenderObjClass::Set_Container(RenderObjClass * con)
{
	Container = con;
}

void RenderObjClass::Remove(void)
{
	// All render objects have their scene pointers set.  To check if this is a "top level"
	// object, (i.e. directly in the scene) you see if its Container pointer is NULL.
	if (Container == NULL) {
		if (Scene != NULL) {
			Scene->Remove_Render_Object(this);
			return;
		}
	} else {
		Container->Remove_Sub_Object(this);
		return;
	}
}

void RenderObjClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	sphere.Center.Set(0,0,0);
	sphere.Radius = 1.0f;
}

float RenderObjClass::Get_Cost(void) const
{
	int polycount = Get_Num_Polys();
	// If polycount is zero set Cost to a small nonzero amount to avoid divisions by zero.
	float cost = (polycount != 0)? polycount : 0.000001f;
	return( cost );
}

// ?Calculate_Cost_Value_Arrays@RenderObjClass@@UBEHMPAM0@Z present-unmatched
int RenderObjClass::Calculate_Cost_Value_Arrays(float screen_area, float *values, float *costs) const
{
	values[0] = AT_MIN_LOD;
	values[1] = AT_MAX_LOD;
	costs[0] = Get_Cost();
	return 0;
}

// BFME's Set_Visible at 0x0013B710 (vtable +0x18C) keeps only its second
// argument, the scene token at +0x88 that Is_Visible (+0x188, 0x0013B6D0)
// compares against the scene's; the on/off argument is ignored.
// ?Set_Visible@RenderObjClass@@UAEXHH@Z present-unmatched
void RenderObjClass::Set_Visible(int onoff, int unk)
{
	_bfme_unk_88 = unk;
}

// ?Remove_Sub_Objects_From_Bone@RenderObjClass@@UAEHPBD@Z present-unmatched
int RenderObjClass::Remove_Sub_Objects_From_Bone(const char * bname)
{
	// One expression: retail loads the vtable once for both calls, where
	// Zero Hour's separate bone-index statement rereads it after the first.
	return Remove_Sub_Objects_From_Bone(Get_Bone_Index(bname));
}

// ?Remove_Sub_Objects_From_Bone@RenderObjClass@@UAEHH@Z present-unmatched
int RenderObjClass::Remove_Sub_Objects_From_Bone(int boneindex)
{
	int count = Get_Num_Sub_Objects_On_Bone(boneindex);
	int remove_count = 0;
	for (int i = count - 1; i >= 0; i--) {
		RenderObjClass *robj = Get_Sub_Object_On_Bone(i, boneindex);
		if (robj) {
			remove_count += Remove_Sub_Object(robj);
			robj->Release_Ref();
		}
	}
	return remove_count;
}
