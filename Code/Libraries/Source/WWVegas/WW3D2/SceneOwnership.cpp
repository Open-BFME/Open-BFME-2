// cl: /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
