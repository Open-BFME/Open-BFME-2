// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// MeshModelClass::get_sort_flags(int), retail 0x00189270, 125 bytes.
// Dedicated TU so meshmdlio.cpp keeps its matched bodies.
// Shader[pass] is at MatDesc+0x98; ShaderArray[pass] at +0xF8.

#include "MeshMatDescClass.h"
#include "MeshModelClass.h"

template <class T> class ShareBufferClass
{
	int Vptr;
	int NumRefs;
	T *RawBuffer;
	T *Array;
	int Count;
public:
	int Get_Count() { return Count; }
	T &Get_Element(int index) { return Array[index]; }
};

inline ShaderClass MeshMatDescClass::Get_Single_Shader(int pass) const
{
	return Shader[pass];
}

inline bool MeshMatDescClass::Has_Shader_Array(int pass) const
{
	return ShaderArray[pass] != 0;
}

inline bool MeshModelClass::Has_Shader_Array(int pass) const
{
	return CurMatDesc->Has_Shader_Array(pass);
}

inline ShaderClass MeshModelClass::Get_Single_Shader(int pass) const
{
	return CurMatDesc->Get_Single_Shader(pass);
}

unsigned int MeshModelClass::get_sort_flags(int pass) const
{
	unsigned int flags = 0;
	ShaderClass::StaticSortCategoryType scat;
	if (Has_Shader_Array(pass)) {
		for (int tri = 0; tri < CurMatDesc->ShaderArray[pass]->Get_Count(); tri++) {
			scat = CurMatDesc->ShaderArray[pass]->Get_Element(tri).Get_SS_Category();
			flags |= (1 << scat);
		}
	} else {
		scat = Get_Single_Shader(pass).Get_SS_Category();
		flags |= (1 << scat);
	}
	return flags;
}
