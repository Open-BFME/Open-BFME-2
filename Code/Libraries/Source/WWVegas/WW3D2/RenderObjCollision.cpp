// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#include "rendobj.h"
#include "aabox.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];

// ?Set_Collision_Type@RenderObjClass@@UAEXH_N@Z present-unmatched
void RenderObjClass::Set_Collision_Type(int type, bool recurse)
{
	_bfme_unk_14 = type & 0xFFF;
	if (recurse) {
		for (int ni = 0; ni < Get_Num_Sub_Objects(); ni++) {
			RenderObjClass * robj = Get_Sub_Object(ni);
			robj->Set_Collision_Type(type, true);
			robj->Release_Ref();
		}
	}
	Update_Sub_Object_Bits();
}

void RenderObjClass::Update_Sub_Object_Bits(void)
{
	// Retail RVA0x13BB60: with no sub-objects, fold the stored collision
	// type back into Bits; otherwise union collision/alpha/additive/flag
	// (0x01000000) over the sub-objects.  No translucent handling in retail.
	if (Get_Num_Sub_Objects() == 0) {
		Bits = (Bits & 0xFFFFF000) | _bfme_unk_14;
		return;
	}

	int coltype = _bfme_unk_14;
	int isalpha = 0;
	int isadditive = 0;
	int isflag = 0;

	for (int ni = 0; ni < Get_Num_Sub_Objects(); ni++) {
		RenderObjClass * robj = Get_Sub_Object(ni);
		coltype |= robj->Get_Collision_Type();
		isalpha |= robj->Is_Alpha();
		isadditive |= robj->Is_Additive();
		isflag |= robj->_bfme_ro_flag115();
		robj->Release_Ref();
	}

	Bits = (Bits & 0xFFFFF000) | coltype;
	Set_Alpha(isalpha);
	Set_Additive(isadditive);
	_bfme_ro_flag116(isflag);

	// if we are a sub-object, tell our container to do this
	if (Container) {
		Container->Update_Sub_Object_Bits();
	}
}
