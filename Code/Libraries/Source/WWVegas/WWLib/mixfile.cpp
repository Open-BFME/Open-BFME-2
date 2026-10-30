// cl: /DBFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /Ireference/shims/wwstring_teardown/zhmd /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
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
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando                                                     * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/wwlib/mixfile.cpp                            $* 
 *                                                                                             * 
 *                      $Author:: Patrick                                                     $* 
 *                                                                                             * 
 *                     $Modtime:: 9/12/01 7:39p                                               $* 
 *                                                                                             * 
 *                    $Revision:: 4                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "../../../../../reference/shims/ffactory_o1_dtor/ffactory.h"
#include "ffactory.h"
#include "wwstring.h"
#include "vector.h"

// The surface holder W3DRadarResetSurface (dtor 0x00176CB0): a COM pointer
// released through vtable slot 2 and add-refed through slot 1 on copy.
class W3DRadarResetSurfaceInterface
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that)
	{
		if (that.m_surface)
			that.m_surface->AddRef();
		if (m_surface)
			m_surface->Release();
		m_surface = that.m_surface;
		return *this;
	}

	W3DRadarResetSurfaceInterface *m_surface;
};

// The rowed VectorClass/DynamicVectorClass members here keep the Zero Hour
// element spelling, but retail's element is not Zero Hour's two StringClass
// record: its __ehvec ctor/dtor pair is 0x00154300 (clears +4 only) and
// 0x00001E13 (add ecx,4; jmp ~W3DRadarResetSurface), and the VectorClass
// vtable 0x007D3BC8 slot 2 is the Resize at 0x00155690, whose copy loop
// AddRef/Releases the +4 word. That is this 8-byte layout. (This unit is
// /Od, so the element ctor clears the holder itself rather than calling an
// out-of-line holder ctor.)
class MixFileFactoryClass
{
public:
	struct AddInfoStruct
	{
		bool operator== (const AddInfoStruct &src)	{ return false; }
		bool operator!= (const AddInfoStruct &src)	{ return true; }

		AddInfoStruct() { m_04.m_surface = 0; }

		int m_00;
		W3DRadarResetSurface m_04;
	};
};

// The native base resize at 0x00155690 is already owned by this vector
// instantiation. Both views carry an eight-byte element with a reference-
// counted surface at +4; keep the qualified base call bound to that owner.
class EnumParameterClass
{
public:
	struct _ENUM_VALUE;
};
template <> bool VectorClass<EnumParameterClass::_ENUM_VALUE>::operator==(
	const VectorClass<EnumParameterClass::_ENUM_VALUE> &) const;
template <> int VectorClass<EnumParameterClass::_ENUM_VALUE>::ID(
	const EnumParameterClass::_ENUM_VALUE *);
template <> int VectorClass<EnumParameterClass::_ENUM_VALUE>::ID(
	const EnumParameterClass::_ENUM_VALUE &);
template <> bool VectorClass<EnumParameterClass::_ENUM_VALUE>::Resize(
	int newsize, const EnumParameterClass::_ENUM_VALUE *array);
template <> inline bool
DynamicVectorClass<MixFileFactoryClass::AddInfoStruct>::Resize(
	int newsize, const MixFileFactoryClass::AddInfoStruct *array)
{
	if (((VectorClass<EnumParameterClass::_ENUM_VALUE> *)this)
		->VectorClass<EnumParameterClass::_ENUM_VALUE>::Resize(newsize,
			(const EnumParameterClass::_ENUM_VALUE *)array))
	{
		if (Length() < ActiveCount) ActiveCount = Length();
		return true;
	}
	return false;
}

// Retail has no MixFileFactoryClass bodies (no row; nothing imports the
// GetFileAttributesA/MoveFileA/_stricmp the Zero Hour ones call, and no
// MixFileCreator member exists). Only the template members below are
// rowed here, so they are instantiated directly.
template class DynamicVectorClass<MixFileFactoryClass::AddInfoStruct>;

SimpleFileFactoryClass _SimpleFileFactory;

// The unrecovered MixFileCreator/makemix helpers remain in the BFME1 donor
// at a2c8039e61ad4dfb20c095d8eafe048248d31f25. Its StringClass file-info
// record differs from the retail AsciiString record at 0x002174DF; compiling
// those helpers here emitted a competing nonretail assignment body.
