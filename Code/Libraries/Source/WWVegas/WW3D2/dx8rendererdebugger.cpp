// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /Ireference/shims/wwstring_teardown/zhmd /Ob2 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
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
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "dx8rendererdebugger.h"
#include "hashtemplate.h"
#include "mesh.h"
#include "meshmdl.h"

static HashTemplateClass<unsigned, MeshClass*> MeshHash;

bool DX8RendererDebugger::Enabled;

// ?Enable@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Enable(bool enable)
{
	Enabled=true;
}

// ?Get_String@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Get_String(StringClass& string)
{
	if (!Enabled) {
		string="";
		return;
	}
	string="\n\n\n\n";

	int cnt=0;

	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		StringClass tmp(0,true);
		MeshClass* mesh=ite.Peek_Value();
		MeshModelClass* mmc=mesh->Peek_Model();
		int polys=0;
		int verts=0;
		if (mmc) {
			polys=mmc->Get_Polygon_Count();
			verts=mmc->Get_Vertex_Count();
		}
		tmp.Format("id: %5.5d mesh: %s %d polys, %d verts",
			ite.Peek_Key(),
			mesh->Get_Name(),
			polys,
			verts);
		string+=tmp;
		if (mesh->Is_Disabled_By_Debugger()) {
			string+=" (disabled)\n";
		}
		else {
			string+="\n";
		}
		cnt++;
		if (cnt>20) break;
	}

}

// ?Update@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Update()
{
	// Release references to all meshes and empty the hash
	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		ite.Peek_Value()->Release_Ref();
	}
	MeshHash.Remove_All();

//	if (!Enabled) return;
}

#ifdef WWDEBUG
// ?Add_Mesh@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Add_Mesh(MeshClass* mesh)
{
	if (!Enabled) return;

	// Don't insert the same mesh twice
	if (MeshHash.Get(mesh->Get_Debug_Id())) return;

	mesh->Add_Ref();
	MeshHash.Insert(mesh->Get_Debug_Id(),mesh);
}
#endif

// ?Disable_Mesh@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Disable_Mesh(unsigned id)
{
	if (!Enabled) return;
	MeshClass* mesh=MeshHash.Get(id);
	if (!mesh) return;
	mesh->Set_Debugger_Disable(true);
}

// ?Enable_Mesh@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Enable_Mesh(unsigned id)
{
	if (!Enabled) return;
	MeshClass* mesh=MeshHash.Get(id);
	if (!mesh) return;
	mesh->Set_Debugger_Disable(false);
}

// ?Disable_All@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Disable_All()
{
	if (!Enabled) return;

	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		ite.Peek_Value()->Set_Debugger_Disable(true);
	}
}

// ?Enable_All@DX8RendererDebugger@@ present-unmatched
void DX8RendererDebugger::Enable_All()
{
	if (!Enabled) return;

	HashTemplateIterator<unsigned,MeshClass*> ite(MeshHash);
	for (ite.First();!ite.Is_Done();ite.Next()) {
		ite.Peek_Value()->Set_Debugger_Disable(false);
	}
}

