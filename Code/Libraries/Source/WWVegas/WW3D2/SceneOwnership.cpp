// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
// Scoped BFME2 Scene prefix: Notify_Added/Removed are RenderObj slots26/27.
// Scene's independently anchored table has Add at slot2 and Remove at slot3.
// Later Scene virtual contracts remain unclaimed; see bfme2scene/scene.h.
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
#define Matrix4x4 Matrix4
#include "camera.h"
#include "rinfo.h"
#include "coltest.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];
typedef char SimpleSceneSizeMatchesRetail[(sizeof(SimpleSceneClass) == 0x108) ? 1 : -1];

void SceneClass::Add_Render_Object(RenderObjClass *obj)
{
    obj->Notify_Added(this);
}

void SceneClass::Remove_Render_Object(RenderObjClass *obj)
{
    obj->Notify_Removed(this);
}

// BFME2 keeps an owning render list and separate non-owning update queues.
// Register reason3 uses the same changed-object list; forced visibility uses4.
void SimpleSceneClass::Add_Render_Object(RenderObjClass *obj)
{
    SceneClass::Add_Render_Object(obj);
    RenderList.Add(obj);
    _bfme_changed_objects.Add(obj);
    if (obj->Is_Force_Visible()) {
        _bfme_forced_objects.Add(obj);
    }
}

// Peek retains ownership until the virtual removal path has unlinked the object.
void SimpleSceneClass::Remove_All_Render_Objects(void)
{
    RenderObjClass *obj;
    while ((obj = RenderList.Peek_Head()) != NULL) {
        Remove_Render_Object(obj);
    }
}

float SimpleSceneClass::Compute_Point_Visibility
(	
	RenderInfoClass & rinfo,
	const Vector3 & point
)
{
	CastResultStruct res;
	LineSegClass ray(rinfo.Camera.Get_Position(),point);
	RayCollisionTestClass raytest(ray,&res,COLL_TYPE_PROJECTILE);

	RefRenderObjListIterator it(&RenderList);
	for (it.First(); !it.Is_Done(); it.Next()) {
		RenderObjClass * robj = it.Peek_Obj();
		robj->Cast_Ray(raytest);
	}

	if (res.Fraction == 1.0f) {
		return 1.0f;
	} else {
		return 0.0f;
	}
}

void BFME2SceneSpatialIndex::Remove(RenderObjClass *obj)
{
    int token = SceneClass::_bfme_spatial_token(obj);
    int y = token >> 20;
    int x = (token >> 10) % 1024;
    int level = token % 1024;
    unsigned mask = Dimension >> 1;
    BFME2SceneSpatialNode *node = Nodes;
    unsigned stride = NodeCount >> 2;
    while (stride) {
        if (level & mask) break;
        --node->DescendantCount;
        unsigned quadrant = ((x & mask) ? 2 : 0) + ((y & mask) ? 1 : 0);
        node += quadrant * stride + 1;
        stride >>= 2;
        mask >>= 1;
    }
    node->Objects.Remove(obj);
    SceneClass::_bfme_spatial_token(obj) = -1;
}

typedef char SpatialNodeSizeMatchesRetail[(sizeof(BFME2SceneSpatialNode) == 0x1C) ? 1 : -1];
typedef char SpatialIndexSizeMatchesRetail[(sizeof(BFME2SceneSpatialIndex) == 0x28) ? 1 : -1];

void SimpleSceneClass::Remove_Render_Object(RenderObjClass *obj)
{
    SceneClass::Remove_Render_Object(obj);
    _bfme_changed_objects.Remove(obj);
    if (obj->Is_Force_Visible()) _bfme_forced_objects.Remove(obj);
    _bfme_visible_objects.Remove(obj);
    if (SceneClass::_bfme_spatial_token(obj) >= 0) _bfme_spatial_index.Remove(obj);
    RenderList.Remove(obj);
}


void BFME2SceneSpatialIndex::Insert(RenderObjClass *obj, int y, int x, int level)
{
    BFME2SceneSpatialNode *node = Nodes;
    unsigned mask = Dimension >> 1;
    unsigned stride = NodeCount >> 2;
    while (stride) {
        if (level & mask) break;
        ++node->DescendantCount;
        unsigned quadrant = ((y & mask) ? 1 : 0) + ((x & mask) ? 2 : 0);
        node += quadrant * stride + 1;
        stride >>= 2;
        mask >>= 1;
    }
    node->Objects.Add(obj, false);
    SceneClass::_bfme_spatial_token(obj) = (((y << 10) | x) << 10) | level;
}

void SimpleSceneClass::Register(RenderObjClass *obj, RegType reason)
{
    switch (reason) {
    case ON_FRAME_UPDATE: UpdateList.Add(obj); break;
    case LIGHT: LightList.Add_Tail(obj); break;
    case RELEASE: ReleaseList.Add(obj); break;
    case BFME_CHANGED_OBJECT: _bfme_changed_objects.Add(obj); break;
    case BFME_FORCED_OBJECT: _bfme_forced_objects.Add(obj); break;
    }
}

void SimpleSceneClass::Unregister(RenderObjClass *obj, RegType reason)
{
    switch (reason) {
    case ON_FRAME_UPDATE: UpdateList.Remove(obj); break;
    case LIGHT: LightList.Remove(obj); break;
    case RELEASE: ReleaseList.Remove(obj); break;
    case BFME_CHANGED_OBJECT: _bfme_changed_objects.Remove(obj); break;
    case BFME_FORCED_OBJECT: _bfme_forced_objects.Remove(obj); break;
    }
}
