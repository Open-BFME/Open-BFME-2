// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /O2 /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/rinfo.cpp                              $*
 *                                                                                             *
 *                   Org Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/27/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 15                                                          $*
 *                                                                                             *
 * 06/27/02 KM Render to shadow buffer texture support														*
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// BFME2's RenderInfoClass, in this unit rather than through the Zero Hour
// rinfo.h, whose layout this build does not have. Target evidence, all from
// the retail bodies at 0x00142BA0..0x00143070:
//   - the ctor 0x00142EE0 zeroes six floats at +0x04..+0x18 where Zero Hour
//     has three fog floats, sets the three 1.0f overrides at +0x1C..+0x24,
//     clears +0x28/+0x2C, the pass array +0x30..+0xAC, the counts at +0xB0
//     and +0xB4, the override level at +0x138 and three words at
//     +0x13C..+0x144;
//   - MeshClass::Render (0x0014BB90) copies +0x08..+0x10 into the mesh by
//     value (a Vector3), passes a RefCountPtr<FXShader::RenderingMethod> by
//     value to 0x001431B0 and hands the +0x13C member to the FX renderer as a
//     const vector reference (0x00142C40), which makes +0x13C the STLport
//     vector of rendering methods that 0x001431B0 pushes and 0x00142DF0 pops;
//   - the dtor 0x00142FE0 pops every remaining material pass, then runs the
//     vector's destructor 0x00142E30.
// The Zero Hour fog names on +0x04, +0x14 and +0x18 are carried from the
// donor; which float is which is not proven by target code.

#include <stl/_algobase.h>
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row);
// this unit-local overload keeps the inlined code and offers the link no
// second copy (as Rva00142DF0StringVector.cpp does for the same vector).
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}

#include <vector>

class CameraClass;
class LightEnvironmentClass;
class TexProjectClass;
class VisRasterizerClass;
class BWRenderClass;
class DummyPtrType;

class RefCountClass
{
public:
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }
	virtual void Delete_This(void);

private:
	int NumRefs;
};

class MaterialPassClass : public RefCountClass
{
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
};
}

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent) {
			Referent->Add_Ref();
		}
	}
	~RefCountPtr(void)
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}
	const RefCountPtr<T> &operator =(const RefCountPtr<T> &rhs);

private:
	T *Referent;
};

class Vector3
{
public:
	Vector3(void) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>, _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

namespace _STL
{
// cl declines a plain `inline` through a template specialisation, so the
// range destroy the vector's destructor expands is forced here (see
// reference/shims/bfmealloc/README.md and Rva00142DF0StringVector.cpp).
template <>
__forceinline void __destroy_aux<RefCountPtr<FXShader::RenderingMethod> *>(RefCountPtr<FXShader::RenderingMethod> *__first, RefCountPtr<FXShader::RenderingMethod> *__last, const __false_type &)
{
	for ( ; __first != __last; ++__first)
		_Destroy(&*__first);
}

template <>
__forceinline void __destroy<RefCountPtr<FXShader::RenderingMethod> *, RefCountPtr<FXShader::RenderingMethod> >(RefCountPtr<FXShader::RenderingMethod> *__first, RefCountPtr<FXShader::RenderingMethod> *__last, RefCountPtr<FXShader::RenderingMethod> *)
{
	__destroy_aux(__first, __last, __false_type());
}

template <>
__forceinline void _Destroy<RefCountPtr<FXShader::RenderingMethod> *>(RefCountPtr<FXShader::RenderingMethod> *__first, RefCountPtr<FXShader::RenderingMethod> *__last)
{
	__destroy(__first, __last, (RefCountPtr<FXShader::RenderingMethod> *)0);
}
}

const unsigned MAX_ADDITIONAL_MATERIAL_PASSES=32;
const unsigned MAX_OVERRIDE_FLAG_LEVEL=32;

class RenderInfoClass
{
public:
	RenderInfoClass(CameraClass & cam);
	~RenderInfoClass(void);

	enum RINFO_OVERRIDE_FLAGS {
		RINFO_OVERRIDE_DEFAULT						= 0x0000,	// No overrides
		RINFO_OVERRIDE_FORCE_TWO_SIDED			= 0x0001,	// Override mesh settings to force no backface culling
		RINFO_OVERRIDE_FORCE_SORTING				= 0x0002,	// Override mesh settings to force sorting
		RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY	= 0x0004,	// Do not render base passes (only additional passes)
		RINFO_OVERRIDE_SHADOW_RENDERING			= 0x0008		// Hint: we are rendering a shadow
	};

	void								Push_Material_Pass(MaterialPassClass * matpass);
	void								Pop_Material_Pass(void);

	int								Additional_Pass_Count(void);
	MaterialPassClass *			Peek_Additional_Pass(int i);

	void								Push_Override_Flags(RINFO_OVERRIDE_FLAGS flg);
	void								Pop_Override_Flags(void);
	RINFO_OVERRIDE_FLAGS &		Current_Override_Flags(void);

	const RenderingMethodStackType & Get_Rendering_Method_Stack(void) const;

	CameraClass &					Camera;						// +0x00

	float								fog_scale;					// +0x04
	Vector3							FogColor;					// +0x08
	float								fog_start;					// +0x14
	float								fog_end;						// +0x18
	float								alphaOverride;				// +0x1C
	float								materialPassAlphaOverride;	// +0x20
	float								materialPassEmissiveOverride;	// +0x24

	LightEnvironmentClass*		light_environment;		// +0x28

	TexProjectClass*				Texture_Projector;		// +0x2C

protected:
	MaterialPassClass*			AdditionalMaterialPassArray[MAX_ADDITIONAL_MATERIAL_PASSES];	// +0x30
	unsigned							AdditionalMaterialPassCount;	// +0xB0
	unsigned							RejectedMaterialPasses;			// +0xB4
	RINFO_OVERRIDE_FLAGS			OverrideFlag[MAX_OVERRIDE_FLAG_LEVEL];	// +0xB8
	unsigned							OverrideFlagLevel;				// +0x138
	RenderingMethodStackType	RenderingMethodStack;			// +0x13C
};

class SpecialRenderInfoClass : public RenderInfoClass
{
public:
	SpecialRenderInfoClass(CameraClass & cam,int render_type);
	~SpecialRenderInfoClass(void);

	enum
	{
		RENDER_VIS,
		RENDER_SHADOW
	};
	int								RenderType;
	VisRasterizerClass *			VisRasterizer;
	BWRenderClass *				BWRenderer;
};


/***********************************************************************************************
**
** RenderInfoClass Implementation
**
***********************************************************************************************/
RenderInfoClass::RenderInfoClass(CameraClass & cam) :
	Camera(cam),
	fog_scale(0.0f),
	FogColor(0.0f, 0.0f, 0.0f),
	fog_start(0.0f),
	fog_end(0.0f),
	light_environment(0),
	AdditionalMaterialPassCount(0),
	RejectedMaterialPasses(0),
	OverrideFlagLevel(0),
	Texture_Projector(0),
	alphaOverride(1.0f),
	materialPassAlphaOverride(1.0f),
	materialPassEmissiveOverride(1.0f)
{
	// Need to have one entry in the override flags stack, initialize it to default values.
	OverrideFlag[OverrideFlagLevel]=RINFO_OVERRIDE_DEFAULT;
	for (int i=0; i<MAX_ADDITIONAL_MATERIAL_PASSES; i++) {
		AdditionalMaterialPassArray[i]=0;
	}
}

RenderInfoClass::~RenderInfoClass(void)
{
	while (AdditionalMaterialPassCount != 0) {
		Pop_Material_Pass();
	}
}

void RenderInfoClass::Push_Material_Pass(MaterialPassClass * matpass)
{
	// add to the end of the array
	if (AdditionalMaterialPassCount<MAX_ADDITIONAL_MATERIAL_PASSES-1) {

		if (matpass) {
			matpass->Add_Ref();
		}
		AdditionalMaterialPassArray[AdditionalMaterialPassCount++]=matpass;
	} else {
		RejectedMaterialPasses++;
	}
}

void RenderInfoClass::Pop_Material_Pass(void)
{
	if (RejectedMaterialPasses == 0) {
		// remove from the end of the array
		AdditionalMaterialPassCount--;
		MaterialPassClass * mpass = AdditionalMaterialPassArray[AdditionalMaterialPassCount];
		if (mpass != 0) {
			mpass->Release_Ref();
		}
	} else {
		RejectedMaterialPasses--;
	}
}

int RenderInfoClass::Additional_Pass_Count(void)
{
	return AdditionalMaterialPassCount;
}

MaterialPassClass * RenderInfoClass::Peek_Additional_Pass(int i)
{
	return AdditionalMaterialPassArray[i];
}

const RenderingMethodStackType & RenderInfoClass::Get_Rendering_Method_Stack(void) const
{
	return RenderingMethodStack;
}

void RenderInfoClass::Push_Override_Flags(RINFO_OVERRIDE_FLAGS flg)
{
	// copy to the end of the array
	OverrideFlagLevel++;
	OverrideFlag[OverrideFlagLevel]=flg;
}

void RenderInfoClass::Pop_Override_Flags(void)
{
	OverrideFlagLevel--;
}

RenderInfoClass::RINFO_OVERRIDE_FLAGS & RenderInfoClass::Current_Override_Flags(void)
{
	return OverrideFlag[OverrideFlagLevel];
}



/***********************************************************************************************
**
** SpecialRenderInfoClass Implementation
**
***********************************************************************************************/

// ??0SpecialRenderInfoClass@@QAE@AAVCameraClass@@H@Z present-unmatched
SpecialRenderInfoClass::SpecialRenderInfoClass(CameraClass & cam,int render_type) :
	RenderInfoClass(cam),
	RenderType(render_type),
	VisRasterizer(0),
	BWRenderer(0)
{
}

// ??1SpecialRenderInfoClass@@QAE@XZ present-unmatched
SpecialRenderInfoClass::~SpecialRenderInfoClass(void)
{
}
