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

// RenderObjClass::Get_Sub_Object_By_Name at 0x0013B8D0, on the same
// bfme2renderobj model the other RenderObj*.cpp units use.  Zero Hour's body
// with one BFME change in the second pass: the sub-object's name is fetched
// once and a null name is skipped before strchr, where Zero Hour fetches it
// twice and hands strchr whatever comes back.  The comparisons import
// msvcr71's _strcmpi (0x00BBA518), not _stricmp.

#include "rendobj.h"
#include <string.h>

RenderObjClass * RenderObjClass::Get_Sub_Object_By_Name(const char * name, int *index) const
{
	int i;

	// first try to find an exact match
	for (i=0; i<Get_Num_Sub_Objects(); i++) {
		RenderObjClass * robj = Get_Sub_Object(i);
		if (robj) {
			if (robj->Get_Name() && _strcmpi(robj->Get_Name(),name) == 0) {
				if (index) *index = i;
				return robj;
			}
			robj->Release_Ref();
		}
	}

	// check for a match without the prefix
	for (i=0; i<Get_Num_Sub_Objects(); i++) {
		RenderObjClass * robj = Get_Sub_Object(i);
		if (robj) {
			const char * robjname = robj->Get_Name();
			if (robjname) {
				const char * subobjname = strchr(robjname,'.');
				if (subobjname == NULL) {
					subobjname = robjname;
				} else {
					// skip past the period.
					subobjname = subobjname+1;
				}
				if (subobjname && _strcmpi(subobjname,name) == 0) {
					if (index) *index = i;
					return robj;
				}
			}
			robj->Release_Ref();
		}
	}

	return NULL;
}

// Zero Hour's by-name overload at 0x0013B9E0, with BFME's trailing offset
// forwarded to the index overload.
int RenderObjClass::Add_Sub_Object_To_Bone(RenderObjClass * subobj,const char * bname, const Vector3 * offset)
{
	int bindex = Get_Bone_Index(bname);
	return Add_Sub_Object_To_Bone(subobj,bindex,offset);
}
