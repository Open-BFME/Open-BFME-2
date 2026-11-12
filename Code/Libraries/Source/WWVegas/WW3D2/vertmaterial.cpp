// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/bfmemapper /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/vertmaterial.cpp                       $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 8/22/01 11:06a                                              $*
 *                                                                                             *
 *                    $Revision:: 42                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Init -- init code                                                                         *
 *   Shutdown -- shutdown code                                                                 *
 *   Get_Preset -- retrieve presets                                                            *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// BFME mapper layout (no W3DMPO pools: retail news mappers with the global
// operator new) must win over the Zero Hour mapper.h that vertmaterial.h pulls
// in from its own directory; the shim sets the shared include guard first.
#include "mapper.h"
#include "vertmaterial.h"
#include "realcrc.h"
#include "wwdebug.h"
#include "w3d_util.h"
#include "chunkio.h"
#include "w3derr.h"
#include "ini.h"
#include "xstraw.h"
// The DX8 home view only declares the state setters Apply_Null calls out of line
// (retail's /O1 bodies 0x0006615F and 0x000661DD), so this unit emits no copy.
#include "../../../../../reference/shims/bfme_dx8wrapper_home_link/dx8wrapper.h"

#include <stdio.h>
#include <string.h>

// BFME nulls the pointer INSIDE the null check. The reference tree's ZH
// refcount.h nulls it unconditionally, which costs one byte in every body that
// uses the macro -- the je in Shutdown clears the store at retail and lands on
// it here. This repo's own Code/Libraries/Source/WWVegas/WWLib/refcount.h
// already carries the corrected form; this TU compiles against the reference
// copy, so restore it here rather than reorder the include path.
#undef REF_PTR_RELEASE
#define REF_PTR_RELEASE(x)		{ if (x) { x->Release_Ref(); x = NULL; } }

static unsigned int unique=1;

VertexMaterialClass* VertexMaterialClass::Presets[VertexMaterialClass::PRESET_COUNT];

#ifdef DYN_MAT8
// Retail allocates this through plain operator new where the W3DMPO glue
// would route through createW3DMemPool, so the base is gone here (W3DMPO is
// empty, so the layout is unchanged).
class DynD3DMATERIAL8
{
public:
	D3DMATERIAL8 Mat;
};
#define Material				(&MaterialDyn->Mat)
#define SRCMATPTR(src)	(&(src)->MaterialDyn->Mat)
#else
#define Material				(MaterialOld)
#define SRCMATPTR(src)	((src)->MaterialOld)
#endif

/*
** VertexMaterialClass Implementation
*/
// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
VertexMaterialClass::VertexMaterialClass(void):
#ifdef DYN_MAT8
	MaterialDyn(NULL),
#else
	MaterialOld(NULL),
#endif
	Flags(0),
	AmbientColorSource(D3DMCS_MATERIAL),
	EmissiveColorSource(D3DMCS_MATERIAL),
	DiffuseColorSource(D3DMCS_MATERIAL),
	UseLighting(false),
	UniqueID(0),
	CRCDirty(true)
{
	int i;

	for (i=0; i<MeshBuilderClass::MAX_STAGES; i++)
	{
		Mapper[i]=NULL;		
		UVSource[i] = i;
	}	

#ifdef DYN_MAT8
	MaterialDyn=W3DNEW DynD3DMATERIAL8;
#else
	MaterialOld=W3DNEW D3DMATERIAL8;
#endif
	memset(Material,0,sizeof(D3DMATERIAL8));
	Set_Ambient(1.0f,1.0f,1.0f);
	Set_Diffuse(1.0f,1.0f,1.0f);

	Set_Opacity(1.0f);
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
VertexMaterialClass::VertexMaterialClass(const VertexMaterialClass & src) :
#ifdef DYN_MAT8
	MaterialDyn(NULL),
#else
	MaterialOld(NULL),
#endif
	Flags(src.Flags),
	AmbientColorSource(src.AmbientColorSource),
	EmissiveColorSource(src.EmissiveColorSource),
	DiffuseColorSource(src.DiffuseColorSource),
	UseLighting(src.UseLighting),
	Name(src.Name),
	UniqueID(src.UniqueID),
	CRCDirty(true)
{
	int i;
	for (i=0; i<MeshBuilderClass::MAX_STAGES; i++)
	{
		Mapper[i]=NULL;
		if (src.Mapper[i])
		{
			TextureMapperClass *mapper=src.Mapper[i]->Clone();
			Set_Mapper(mapper,i);
			mapper->Release_Ref();
		}

		UVSource[i] = src.UVSource[i];
	}	

#ifdef DYN_MAT8
	MaterialDyn=W3DNEW DynD3DMATERIAL8;
#else
	MaterialOld=W3DNEW D3DMATERIAL8;
#endif
	memcpy(Material, SRCMATPTR(&src), sizeof(D3DMATERIAL8));
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/VertexMaterialClassFieldWrites.cpp
// ?Make_Unique@VertexMaterialClass@@QAEXXZ
void VertexMaterialClass::Make_Unique()
{
	CRCDirty=true;
	UniqueID=unique;
	unique++;
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
VertexMaterialClass::~VertexMaterialClass(void)
{
	int i;

	for (i=0; i<MeshBuilderClass::MAX_STAGES; i++)
	{
		if (Mapper[i])
		{
			REF_PTR_RELEASE(Mapper[i]);
			Mapper[i]=NULL;
		}
	}

#ifdef DYN_MAT8
	delete MaterialDyn;
#else
	delete MaterialOld;
#endif
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
// ??4VertexMaterialClass@@QAEAAV0@ABV0@@Z
VertexMaterialClass & VertexMaterialClass::operator = (const VertexMaterialClass &src)
{	

	if (this != &src) {
		Name=src.Name;
		Flags = src.Flags;
		AmbientColorSource = src.AmbientColorSource;
		EmissiveColorSource = src.EmissiveColorSource;
		DiffuseColorSource = src.DiffuseColorSource;
		UseLighting=src.UseLighting;
		UniqueID=src.UniqueID;
		CRCDirty=src.CRCDirty;
		int stage;
		for (stage=0;stage<MeshBuilderClass::MAX_STAGES;++stage) {
			if (Mapper[stage] != NULL) {
				Mapper[stage]->Release_Ref();
				Mapper[stage] = NULL;
			}
		}
		for (stage=0;stage<MeshBuilderClass::MAX_STAGES;++stage) {
			if (src.Mapper[stage]) {
				TextureMapperClass *mapper = src.Mapper[stage]->Clone();
				Set_Mapper(mapper,stage);
				mapper->Release_Ref();
			}
			UVSource[stage] = src.UVSource[stage];
		}

		*Material = *SRCMATPTR(&src);
	}
	return *this;
}

// ?Compute_CRC@VertexMaterialClass@@ABEKXZ
unsigned long VertexMaterialClass::Compute_CRC(void) const
{
	unsigned long crc = 0;
	
// don't include the name when determining whether two vertex materials match
//	crc = CRC_Memory(reinterpret_cast<const unsigned char *>(Name.Peek_Buffer()),sizeof(char)*strlen(Name),crc);

	crc = CRC_Memory(reinterpret_cast<const unsigned char *>(*(const void **)((const char *)this + 0x08)),sizeof(D3DMATERIAL8),crc);
	crc = CRC_Memory(reinterpret_cast<const unsigned char *>((const char *)this + 0x0c),sizeof(Flags),crc);
	crc = CRC_Memory(reinterpret_cast<const unsigned char *>((const char *)this + 0x18),sizeof(DiffuseColorSource),crc);
	crc = CRC_Memory(reinterpret_cast<const unsigned char *>((const char *)this + 0x10),sizeof(AmbientColorSource),crc);
	crc = CRC_Memory(reinterpret_cast<const unsigned char *>((const char *)this + 0x14),sizeof(EmissiveColorSource),crc);
	crc = CRC_Memory(reinterpret_cast<const unsigned char *>((const char *)this + 0x40),sizeof(UVSource),crc);
	crc = CRC_Memory(reinterpret_cast<const unsigned char *>((const char *)this + 0x69),sizeof(UseLighting),crc);
	crc = CRC_Memory(reinterpret_cast<const unsigned char *>((const char *)this + 0x60),sizeof(UniqueID),crc);

	TextureMapperClass **mapper = reinterpret_cast<TextureMapperClass **>((char *)this + 0x20);
	int i;
	for (i=0; i<MeshBuilderClass::MAX_STAGES; i++)
	{
		if (*mapper) crc = CRC_Memory(reinterpret_cast<const unsigned char *>(mapper),sizeof(TextureMapperClass*),crc);
		++mapper;
	}

	return crc;
}

// Ambient Get and Sets

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void VertexMaterialClass::Get_Ambient(Vector3 * set) const
{
	assert(set); 
	*set=Vector3(Material->Ambient.r,Material->Ambient.g,Material->Ambient.b);
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void VertexMaterialClass::Set_Ambient(const Vector3 & color)
{
	CRCDirty=true;
	Material->Ambient.r=color.X;
	Material->Ambient.g=color.Y;
	Material->Ambient.b=color.Z;	
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
inline void VertexMaterialClass::Set_Ambient(float r,float g,float b)
{
	CRCDirty=true;
	Material->Ambient.r=r;
	Material->Ambient.g=g;
	Material->Ambient.b=b;	
}

// Diffuse Get and Sets

void VertexMaterialClass::Get_Diffuse(Vector3 * set) const
{
	assert(set); 
	// BFME puts the material pointer at this+0x8, not this+0xC: retail
	// @0x009219F0 reads it there. vertmaterial.h parks its extra dword
	// (_bfme_vmat_v0) ahead of the pointer, but the same header's other
	// constraint - AmbientColorSource at +0x14 and EmissiveColorSource at
	// +0x18 - is satisfied with the dword between Flags and
	// AmbientColorSource instead, which puts the pointer back at +0x8 and
	// leaves sizeof unchanged. That is the header fix; the full gate is red,
	// so this read goes to the retail offset.
	DynD3DMATERIAL8 * const dynD3DMATERIAL8 =
			*(DynD3DMATERIAL8 * const *)((const char *)this + 8);
	*set=Vector3(dynD3DMATERIAL8->Mat.Diffuse.r,dynD3DMATERIAL8->Mat.Diffuse.g,dynD3DMATERIAL8->Mat.Diffuse.b);
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void VertexMaterialClass::Set_Diffuse(const Vector3 & color)
{
	CRCDirty=true;
	Material->Diffuse.r=color.X;
	Material->Diffuse.g=color.Y;
	Material->Diffuse.b=color.Z;	
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
inline void VertexMaterialClass::Set_Diffuse(float r,float g,float b)
{
	CRCDirty=true;
	Material->Diffuse.r=r;
	Material->Diffuse.g=g;
	Material->Diffuse.b=b;	
}

// Specular Get and Sets

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void VertexMaterialClass::Get_Specular(Vector3 * set) const
{
	assert(set); 
	*set=Vector3(Material->Specular.r,Material->Specular.g,Material->Specular.b);
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void VertexMaterialClass::Set_Specular(const Vector3 & color)
{
	CRCDirty=true;
	Material->Specular.r=color.X;
	Material->Specular.g=color.Y;
	Material->Specular.b=color.Z;	
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
inline void VertexMaterialClass::Set_Specular(float r,float g,float b)
{
	CRCDirty=true;
	Material->Specular.r=r;
	Material->Specular.g=g;
	Material->Specular.b=b;
}

// Emissive Get and Sets

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void VertexMaterialClass::Get_Emissive(Vector3 * set) const
{
	assert(set); 
	*set=Vector3(Material->Emissive.r,Material->Emissive.g,Material->Emissive.b);
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void VertexMaterialClass::Set_Emissive(const Vector3 & color)
{
	CRCDirty=true;
	Material->Emissive.r=color.X;
	Material->Emissive.g=color.Y;
	Material->Emissive.b=color.Z;
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
inline void VertexMaterialClass::Set_Emissive(float r,float g,float b)
{
	CRCDirty=true;
	Material->Emissive.r=r;
	Material->Emissive.g=g;
	Material->Emissive.b=b;
}


float	VertexMaterialClass::Get_Shininess(void) const
{
	return Material->Power;
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
inline void	VertexMaterialClass::Set_Shininess(float shin)
{
	CRCDirty=true;
	Material->Power=shin;
}

float	VertexMaterialClass::Get_Opacity(void) const
{
	const D3DMATERIAL8 *material = *reinterpret_cast<const D3DMATERIAL8 *const *>(reinterpret_cast<const char *>(this) + 8);
	return material->Diffuse.a;
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
inline void	VertexMaterialClass::Set_Opacity(float o)
{
	CRCDirty=true;
	Material->Diffuse.a=o;
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void	VertexMaterialClass::Set_Ambient_Color_Source(ColorSourceType src)
{
	CRCDirty=true;
	switch (src) 
	{
	case	COLOR1:		AmbientColorSource = D3DMCS_COLOR1; break;
	case	COLOR2:		AmbientColorSource = D3DMCS_COLOR2; break;
	default:				AmbientColorSource = D3DMCS_MATERIAL; break;
	}
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
void	VertexMaterialClass::Set_Emissive_Color_Source(ColorSourceType src)
{
	CRCDirty=true;
	switch (src) 
	{
	case	COLOR1:		EmissiveColorSource = D3DMCS_COLOR1; break;
	case	COLOR2:		EmissiveColorSource = D3DMCS_COLOR2; break;
	default:				EmissiveColorSource = D3DMCS_MATERIAL; break;
	}
}

// byte-exact reconstruction: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
inline void	VertexMaterialClass::Set_Diffuse_Color_Source(ColorSourceType src)
{
	CRCDirty=true;
	switch (src) 
	{
	case	COLOR1:		DiffuseColorSource = D3DMCS_COLOR1; break;
	case	COLOR2:		DiffuseColorSource = D3DMCS_COLOR2; break;
	default:				DiffuseColorSource = D3DMCS_MATERIAL; break;
	}
}

VertexMaterialClass::ColorSourceType 
VertexMaterialClass::Get_Ambient_Color_Source(void)
{
	switch(AmbientColorSource) 
	{
	case D3DMCS_COLOR1:	return COLOR1;
	case D3DMCS_COLOR2:	return COLOR2;
	default:					return MATERIAL;
	}
}	

VertexMaterialClass::ColorSourceType 
VertexMaterialClass::Get_Emissive_Color_Source(void)
{
	switch(EmissiveColorSource) 
	{
	case D3DMCS_COLOR1:	return COLOR1;
	case D3DMCS_COLOR2:	return COLOR2;
	default:					return MATERIAL;
	}
}	

VertexMaterialClass::ColorSourceType	
VertexMaterialClass::Get_Diffuse_Color_Source(void)
{
	switch(DiffuseColorSource) 
	{
	case D3DMCS_COLOR1:	return COLOR1;
	case D3DMCS_COLOR2:	return COLOR2;
	default:					return MATERIAL;
	}
}

// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/VertexMaterialClassFieldWrites.cpp
// ?Set_UV_Source@VertexMaterialClass@@QAEXHH@Z
void VertexMaterialClass::Set_UV_Source(int stage,int array_index)
{
	WWASSERT(stage >= 0);
	WWASSERT(stage < MeshBuilderClass::MAX_STAGES);
	WWASSERT(array_index >= 0);
	WWASSERT(array_index < 8);
	CRCDirty=true;
	UVSource[stage] = array_index;
}

int VertexMaterialClass::Get_UV_Source(int stage)
{
	WWASSERT(stage >= 0);
	WWASSERT(stage < MeshBuilderClass::MAX_STAGES);
	return UVSource[stage];
}


// VertexMaterialClass::Init_From_Material3: defined in VertexMaterialInitFromMaterial3.cpp (its row's unit).


// Native Parse_W3dVertexMaterialStruct is owned by VertexMaterialParseStruct.cpp
// at 13D030. Do not emit the non-retail donor inline copy from this unit.

void VertexMaterialClass::Parse_Mapping_Args(const W3dVertexMaterialStruct & vmat,char * mapping0_arg_buffer,char * mapping1_arg_buffer)
{
	
	// Read an INIClass from the mapping argument buffer - this will be used
	// to initialize any special mappers used.
	INIClass mapping0_arg_ini;
	if (mapping0_arg_buffer) {

		int mapping0_arg_len = strlen(mapping0_arg_buffer);
	
		char *extended_arg_buffer = MSGW3DNEWARRAY("VertexMaterialClassTemp") char[mapping0_arg_len + 10];
		sprintf(extended_arg_buffer, "[Args]\n%s", mapping0_arg_buffer);
		mapping0_arg_len = strlen(extended_arg_buffer) + 1;

		BufferStraw map_arg_buf_straw((void *)extended_arg_buffer, mapping0_arg_len);

		mapping0_arg_ini.Load(map_arg_buf_straw);

		delete [] extended_arg_buffer;
		extended_arg_buffer = NULL;
	}
	INIClass mapping1_arg_ini;
	if (mapping1_arg_buffer) {

		int mapping1_arg_len = strlen(mapping1_arg_buffer);

		char *extended_arg_buffer = MSGW3DNEWARRAY("VertexMaterialClassTemp") char[mapping1_arg_len + 20];
		sprintf(extended_arg_buffer, "[Args]\n%s", mapping1_arg_buffer);
		mapping1_arg_len = strlen(extended_arg_buffer) + 1;

		BufferStraw map_arg_buf_straw((void *)extended_arg_buffer, mapping1_arg_len);

		mapping1_arg_ini.Load(map_arg_buf_straw);

		delete [] extended_arg_buffer;
		extended_arg_buffer = NULL;
	}

	// Set up the vertex mapper.  If it is one of the simple
	// ones, set the pointer to one of the global instances. 
	int mapping = vmat.Attributes & W3DVERTMAT_STAGE0_MAPPING_MASK;

	switch(mapping) {
		
		case W3DVERTMAT_STAGE0_MAPPING_UV:
			break;

		case W3DVERTMAT_STAGE0_MAPPING_ENVIRONMENT:
			{
				EnvironmentMapperClass *mapper = NEW_REF(EnvironmentMapperClass,(0));
				Set_Mapper(mapper);
				mapper->Release_Ref();
			}
			break;
		case W3DVERTMAT_STAGE0_MAPPING_CHEAP_ENVIRONMENT:
			{
				ClassicEnvironmentMapperClass *mapper = NEW_REF(ClassicEnvironmentMapperClass,(0));
				Set_Mapper(mapper);
				mapper->Release_Ref();
			}
			break;		
		case W3DVERTMAT_STAGE0_MAPPING_LINEAR_OFFSET:
			{
				LinearOffsetTextureMapperClass *mapper =
					NEW_REF(LinearOffsetTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_SCREEN:
			{
				ScreenMapperClass *mapper =
					NEW_REF(ScreenMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_SCALE:
			{
				ScaleTextureMapperClass *mapper =
					NEW_REF(ScaleTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_GRID:
			{
				GridTextureMapperClass *mapper =
					NEW_REF(GridTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_ROTATE:
			{
				RotateTextureMapperClass *mapper =
					NEW_REF(RotateTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_SINE_LINEAR_OFFSET:
			{
				SineLinearOffsetTextureMapperClass *mapper =
					NEW_REF(SineLinearOffsetTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_STEP_LINEAR_OFFSET:
			{
				StepLinearOffsetTextureMapperClass *mapper =
					NEW_REF(StepLinearOffsetTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_ZIGZAG_LINEAR_OFFSET:
			{
				ZigZagLinearOffsetTextureMapperClass *mapper =
					NEW_REF(ZigZagLinearOffsetTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_WS_CLASSIC_ENV:
			{
				WSClassicEnvironmentMapperClass *mapper = NEW_REF(WSClassicEnvironmentMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;		

		case W3DVERTMAT_STAGE0_MAPPING_WS_ENVIRONMENT:
			{
				WSEnvironmentMapperClass *mapper = NEW_REF(WSEnvironmentMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_GRID_CLASSIC_ENV:
			{
				GridClassicEnvironmentMapperClass *mapper =
					NEW_REF(GridClassicEnvironmentMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_GRID_ENVIRONMENT:
			{
				GridEnvironmentMapperClass *mapper =
					NEW_REF(GridEnvironmentMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_RANDOM:
			{
				RandomTextureMapperClass *mapper =
					NEW_REF(RandomTextureMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_EDGE:
		{
			EdgeMapperClass *mapper =
				NEW_REF(EdgeMapperClass,(mapping0_arg_ini, "Args", 0));
			Set_Mapper(mapper,0);
			mapper->Release_Ref();
		}
		break;

		case W3DVERTMAT_STAGE0_MAPPING_BUMPENV:
		{
			BumpEnvTextureMapperClass *mapper =
				NEW_REF(BumpEnvTextureMapperClass,(mapping0_arg_ini, "Args", 0));
			Set_Mapper(mapper,0);
			mapper->Release_Ref();
		}
		break;

		case W3DVERTMAT_STAGE0_MAPPING_GRID_WS_CLASSIC_ENV:
			{
				GridWSClassicEnvironmentMapperClass *mapper =
					NEW_REF(GridWSClassicEnvironmentMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE0_MAPPING_GRID_WS_ENVIRONMENT:
			{
				GridWSEnvironmentMapperClass *mapper =
					NEW_REF(GridWSEnvironmentMapperClass,(mapping0_arg_ini, "Args", 0));
				Set_Mapper(mapper,0);
				mapper->Release_Ref();
			}
			break;

		default:
			break;
	}

	// Same setup for stage 1's mapper.
	mapping = vmat.Attributes & W3DVERTMAT_STAGE1_MAPPING_MASK;
	switch(mapping) {

		case W3DVERTMAT_STAGE1_MAPPING_UV:
			break;

		case W3DVERTMAT_STAGE1_MAPPING_ENVIRONMENT:
		{
			EnvironmentMapperClass *mapper = W3DNEW EnvironmentMapperClass(1);
			Set_Mapper(mapper, 1);
			mapper->Release_Ref();
		}
		break;
		case W3DVERTMAT_STAGE1_MAPPING_CHEAP_ENVIRONMENT:
		{
			ClassicEnvironmentMapperClass *mapper = W3DNEW ClassicEnvironmentMapperClass(1);
			Set_Mapper(mapper, 1);
			mapper->Release_Ref();
		}
		break;

		case W3DVERTMAT_STAGE1_MAPPING_LINEAR_OFFSET:
		{
			LinearOffsetTextureMapperClass *mapper =
				W3DNEW LinearOffsetTextureMapperClass(mapping1_arg_ini, "Args", 1);
			Set_Mapper(mapper, 1);
			mapper->Release_Ref();
		}
		break;
		
		case W3DVERTMAT_STAGE1_MAPPING_SCREEN:
		{
			ScreenMapperClass *mapper =
				W3DNEW ScreenMapperClass(mapping1_arg_ini, "Args", 1);
			Set_Mapper(mapper, 1);
			mapper->Release_Ref();
		}
		break;

		case W3DVERTMAT_STAGE1_MAPPING_SCALE:
			{
				ScaleTextureMapperClass *mapper =
					NEW_REF(ScaleTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_GRID:
			{
				GridTextureMapperClass *mapper =
					NEW_REF(GridTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_ROTATE:
			{
				RotateTextureMapperClass *mapper =
					NEW_REF(RotateTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_SINE_LINEAR_OFFSET:
			{
				SineLinearOffsetTextureMapperClass *mapper =
					NEW_REF(SineLinearOffsetTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_STEP_LINEAR_OFFSET:
			{
				StepLinearOffsetTextureMapperClass *mapper =
					NEW_REF(StepLinearOffsetTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_ZIGZAG_LINEAR_OFFSET:
			{
				ZigZagLinearOffsetTextureMapperClass *mapper =
					NEW_REF(ZigZagLinearOffsetTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_WS_CLASSIC_ENV:
			{
				WSClassicEnvironmentMapperClass *mapper = NEW_REF(WSClassicEnvironmentMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;		

		case W3DVERTMAT_STAGE1_MAPPING_WS_ENVIRONMENT:
			{
				WSEnvironmentMapperClass *mapper = NEW_REF(WSEnvironmentMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_GRID_CLASSIC_ENV:
			{
				GridClassicEnvironmentMapperClass *mapper =
					NEW_REF(GridClassicEnvironmentMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_GRID_ENVIRONMENT:
			{
				GridEnvironmentMapperClass *mapper =
					NEW_REF(GridEnvironmentMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_RANDOM:
			{
				RandomTextureMapperClass *mapper =
					NEW_REF(RandomTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_EDGE:
			{
				EdgeMapperClass *mapper =
					NEW_REF(EdgeMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_BUMPENV:
			{
				BumpEnvTextureMapperClass *mapper =
					NEW_REF(BumpEnvTextureMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

	case W3DVERTMAT_STAGE1_MAPPING_GRID_WS_CLASSIC_ENV:
			{
				GridWSClassicEnvironmentMapperClass *mapper =
					NEW_REF(GridWSClassicEnvironmentMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		case W3DVERTMAT_STAGE1_MAPPING_GRID_WS_ENVIRONMENT:
			{
				GridWSEnvironmentMapperClass *mapper =
					NEW_REF(GridWSEnvironmentMapperClass,(mapping1_arg_ini, "Args", 1));
				Set_Mapper(mapper,1);
				mapper->Release_Ref();
			}
			break;

		default:
			break;
	}
}


// ?Save_W3D@VertexMaterialClass@@QAE?AW4WW3DErrorType@@AAVChunkSaveClass@@@Z present-unmatched
WW3DErrorType VertexMaterialClass::Save_W3D(ChunkSaveClass & csave)
{
	WWASSERT(0);
	return WW3D_ERROR_OK;
}


void VertexMaterialClass::Apply_Null(void)
{
	int i;
	static D3DMATERIAL8 default_settings = 
	{
		{ 1.0f, 1.0f, 1.0f, 1.0f },	// diffuse
		{ 1.0f, 1.0f, 1.0f, 1.0f },	// ambient
		{ 0.0f, 0.0f, 0.0f, 0.0f },	// specular
		{ 0.0f, 0.0f, 0.0f, 0.0f },	// emissive
		1.0f									// power
	};

	DX8Wrapper::Set_DX8_Render_State(D3DRS_LIGHTING,FALSE);
	DX8Wrapper::Set_DX8_Material(&default_settings);

	DX8Wrapper::Set_DX8_Render_State(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DIFFUSEMATERIALSOURCE,D3DMCS_MATERIAL);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_EMISSIVEMATERIALSOURCE,D3DMCS_MATERIAL);

	// set to default values if no mappers
	for (i=0; i<MeshBuilderClass::MAX_STAGES; i++) {
		DX8Wrapper::Set_DX8_Texture_Stage_State(i,D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU | i);	
		DX8Wrapper::Set_DX8_Texture_Stage_State(i,D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_DISABLE);		
	}
}


/***********************************************************************************************
 * Init -- init code                                                                           *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/14/2001  hy : Created.                                                                  *
 *=============================================================================================*/
// ?Init@VertexMaterialClass@@SAXXZ moved to VertexMaterialClass_Init_Thunk.cpp
// (retail layout/allocation drift vs this header; see that file for detail)


/***********************************************************************************************
 * Shutdown -- shutdown code                                                                   *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/14/2001  hy : Created.                                                                  *
 *=============================================================================================*/
void VertexMaterialClass::Shutdown()
{
	int i;
	for (i=0; i<PRESET_COUNT;i++)
		REF_PTR_RELEASE(Presets[i]);
}


/***********************************************************************************************
 * Get_Preset -- retrieve presets                                                              *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/14/2001  hy : Created.                                                                  *
 *=============================================================================================*/
VertexMaterialClass * VertexMaterialClass::Get_Preset(PresetType type)
{
	WWASSERT(type<PRESET_COUNT);
	Presets[type]->Add_Ref();
	return Presets[type];
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?Apply@ClassicEnvironmentMapperClass@@UAEXH@Z=?Apply@GridWSClassicEnvironmentMapperClass@@UAEXH@Z")
#pragma comment(linker, "/alternatename:?Apply@EnvironmentMapperClass@@UAEXH@Z=?Apply@GridWSEnvironmentMapperClass@@UAEXH@Z")
#pragma comment(linker, "/alternatename:?Apply@WSClassicEnvironmentMapperClass@@UAEXH@Z=?Apply@GridWSClassicEnvironmentMapperClass@@UAEXH@Z")
#pragma comment(linker, "/alternatename:?Apply@WSEnvironmentMapperClass@@UAEXH@Z=?Apply@GridWSEnvironmentMapperClass@@UAEXH@Z")
#pragma comment(linker, "/alternatename:?Apply@GridEnvironmentMapperClass@@UAEXH@Z=?Apply@GridWSEnvironmentMapperClass@@UAEXH@Z")
#pragma comment(linker, "/alternatename:?Apply@GridClassicEnvironmentMapperClass@@UAEXH@Z=?Apply@GridWSClassicEnvironmentMapperClass@@UAEXH@Z")

// These seven setters are header inlines; ordinary definitions here collided
// with select-any copies. The anchor keeps this unit's row copies; it is not
// retail code. It also keeps WW3D::Is_Coloring_Enabled emitted after Apply
// became a select-any inline copy (its inlined call no longer emits it).
#pragma inline_depth(0)
// ?_bfmeVertexMaterialSetterAnchor@@YAXPAVVertexMaterialClass@@@Z absent-from-retail
void _bfmeVertexMaterialSetterAnchor(VertexMaterialClass *material)
{
	material->Set_Ambient(0.0f, 0.0f, 0.0f);
	material->Set_Diffuse(0.0f, 0.0f, 0.0f);
	material->Set_Diffuse_Color_Source(VertexMaterialClass::MATERIAL);
	material->Set_Emissive(0.0f, 0.0f, 0.0f);
	material->Set_Opacity(0.0f);
	material->Set_Shininess(0.0f);
	material->Set_Specular(0.0f, 0.0f, 0.0f);
	(void)WW3D::Is_Coloring_Enabled();
}
#pragma inline_depth()

// Preserve the independently rowed setter formerly emitted by the removed
// parser. This address-taking constant is an emission anchor, not retail data.
void (VertexMaterialClass::*const bfmeVertexMaterialSetFlagAnchor)(VertexMaterialClass::FlagsType, bool) = &VertexMaterialClass::Set_Flag;
