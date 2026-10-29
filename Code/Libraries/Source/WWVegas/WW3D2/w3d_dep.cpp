// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport46
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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
 *                 Project Name : G                                                            *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/w3d_dep.cpp                            $*
 *                                                                                             *
 *                      $Author:: Byon_g                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/23/01 6:17p                                               $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Get_W3D_Dependencies -- Scans a W3D file to determine which other files it depends on.    *
 *   Scan_Chunk -- Chooses the correct chunk loader for this chunk.                            *
 *   Scan_Mesh -- Scans a mesh for references to other files.                                  *
 *   Scan_Mesh_Header -- Scans a mesh's header for file references.                            *
 *   Scan_Mesh_Textures -- Scans a mesh's textures.                                            *
 *   Scan_HTree -- Scans an HTree for references to other files.                               *
 *   Scan_Anim -- Scans an animation for references to other files.                            *
 *   Scan_Compressed_Anim -- Scans an animation for references to other files.                 *
 *   Scan_HModel -- Scans an HModel for references to other files.                             *
 *   Scan_Emitter -- Scans an emitter for references to other files.                           *
 *   Scan_Aggregate -- Scans an aggregate for references to other files.                       *
 *   Scan_HLOD -- Scans an HLOD for references to other files.                                 *
 *   Get_W3D_Name -- Gets a W3D object name from a W3D filename.                               *
 *   Make_W3D_Filename -- Converts a W3D object name into a W3D filename.                      *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//-----------------------------------------------------------------------------
// srj sez: hack festival :-(
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class STLSpecialAlloc
{
public:
  // this one is needed for proper simple_alloc wrapping
  static void*  allocate(size_t __n) {  return ::operator new(__n); }
  static void deallocate(void* __p, size_t) { ::operator delete(__p); }
};


#include "w3d_dep.h"

namespace _STL {

template <> void _List_base<basic_string<char, char_traits<char>, allocator<char> >,
                            allocator<basic_string<char, char_traits<char>, allocator<char> > > >::clear();

template <> _List_iterator<basic_string<char, char_traits<char>, allocator<char> >,
                           _Nonconst_traits<basic_string<char, char_traits<char>, allocator<char> > > >
list<basic_string<char, char_traits<char>, allocator<char> >,
     allocator<basic_string<char, char_traits<char>, allocator<char> > > >::erase(
    _List_iterator<basic_string<char, char_traits<char>, allocator<char> >,
                   _Nonconst_traits<basic_string<char, char_traits<char>, allocator<char> > > >);
template <> bool equal_to<basic_string<char, char_traits<char>, allocator<char> > >::operator()(
    basic_string<char, char_traits<char>, allocator<char> > const &,
    basic_string<char, char_traits<char>, allocator<char> > const &) const;
template <> void _Destroy(basic_string<char, char_traits<char>, allocator<char> > *);
template <> bool operator<(basic_string<char, char_traits<char>, allocator<char> > const &,
                           basic_string<char, char_traits<char>, allocator<char> > const &);
template <> bool less<basic_string<char, char_traits<char>, allocator<char> > >::operator()(
    basic_string<char, char_traits<char>, allocator<char> > const &,
    basic_string<char, char_traits<char>, allocator<char> > const &) const;
}
// bfme link decl-only begin
namespace _STL { template <> void _Construct<basic_string<char, char_traits<char>, allocator<char> >, basic_string<char, char_traits<char>, allocator<char> > >(basic_string<char, char_traits<char>, allocator<char> > *, basic_string<char, char_traits<char>, allocator<char> > const &); }
// bfme link decl-only end

// The Generals dependency scanner (Get_W3D_Dependencies, its Scan_* helpers,
// Get_W3D_Name and Make_W3D_Filename) has no row: its donor body called a
// ChunkLoadClass(FileClass *) constructor retail does not have, so it is left
// out until a row recovers it.

template bool _STL::operator==(basic_string<char, char_traits<char>, allocator<char> > const &, basic_string<char, char_traits<char>, allocator<char> > const &);
