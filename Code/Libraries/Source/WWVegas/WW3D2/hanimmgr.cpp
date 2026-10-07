// cl: /DBFME_WWSTRING_NATIVE_COPY_ASSIGN /DBFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR /G7 /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/hanimmgr.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

/* $Header: /Commando/Code/ww3d2/hanimmgr.cpp 3     1/16/02 9:51a Jani_p $ */
/*********************************************************************************************** 
 ***                            Confidential - Westwood Studios                              *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Commando / G 3D Library                                      * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Code/ww3d2/hanimmgr.cpp                           $* 
 *                                                                                             * 
 *                       Author:: Greg_h                                                       * 
 *                                                                                             * 
 *                     $Modtime:: 1/16/02 9:49a                                               $* 
 *                                                                                             * 
 *                    $Revision:: 3                                                           $* 
 *                                                                                             * 
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 *   HAnimManagerClass::HAnimManagerClass -- constructor                                       * 
 *   HAnimManagerClass::~HAnimManagerClass -- destructor                                       * 
 *   HAnimManagerClass::Load_Anim -- loads a set of motion data from a file                    * 
 *   HAnimManagerClass::Get_Anim_ID -- looks up the ID of a named Hierarchy Animation          * 
 *   HAnimManagerClass::Get_Anim -- returns a pointer to the specified animation data          * 
 *   HAnimManagerClass::Get_Anim -- returns a pointer to the specified Hierarchy Animation     * 
 *   HAnimManagerClass::Free -- de-allocate all memory in use                                  * 
 *   HAnimManagerClass::Free_All_Anims -- de-allocate all currently loaded animations          * 
 *   HAnimManagerClass::Load_Raw_Anim -- Load a raw anim                                       *
 *   HAnimManagerClass::Load_Compressed_Anim -- load a compressed animation                    *
 *	  HAnimManagerClass::Add_Anim -- Adds an externally created animation to the manager		  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// Retail Release_Ref at 0x005D1A7D uses dec-dword, while this unit needs
// /G7 for StringClass::Get_Length. Keep the refcount inlines at size optimization.
#include "wwstring.h"
#include "vector3.h"
#pragma optimize("t", off)
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "hanimmgr.h"
#include <string.h>
#include "hanim.h"
#include "hrawanim.h"
#include "hcanim.h"
#include "hmorphanim.h"
#include "chunkio.h"
#include "wwmemlog.h"
#include "w3dexclusionlist.h"
#include "animatedsoundmgr.h"


/*********************************************************************************************** 
 * HAnimManagerClass::HAnimManagerClass -- constructor                                         * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ??0HAnimManagerClass@@ present-unmatched
HAnimManagerClass::HAnimManagerClass(void) 
{
	// Create the hash tables
	AnimPtrTable = W3DNEW HashTableClass( 2048 );
	MissingAnimTable = W3DNEW HashTableClass( 2048 );
}


/*********************************************************************************************** 
 * HAnimManagerClass::~HAnimManagerClass -- destructor                                         * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ??1HAnimManagerClass@@ present-unmatched
HAnimManagerClass::~HAnimManagerClass(void)
{
	Free_All_Anims();
	Reset_Missing();	// Jani: Deleting missing animations as well

	delete AnimPtrTable;
	AnimPtrTable = NULL;

	Reset_Missing();
	delete MissingAnimTable;
	MissingAnimTable = NULL;
}


/*********************************************************************************************** 
 * HAnimManagerClass::Load_Anim -- loads a set of motion data from a file                      * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?Load_Anim@HAnimManagerClass@@ present-unmatched
int HAnimManagerClass::Load_Anim(ChunkLoadClass & cload)
{
	WWMEMLOG(MEM_ANIMATION);

	switch (cload.Cur_Chunk_ID()) 
	{
	case W3D_CHUNK_ANIMATION:
		return Load_Raw_Anim(cload);
		break;

	case W3D_CHUNK_COMPRESSED_ANIMATION:
		return Load_Compressed_Anim(cload);
		break;

	case W3D_CHUNK_MORPH_ANIMATION:
		return Load_Morph_Anim(cload);
		break;
	}

	return 0;
}


/***********************************************************************************************
 * HAnimManagerClass::Load_Morph_Anim -- Load a HMorphAnimClass										  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/23/2000  pds : Created.                                                                 *
 *=============================================================================================*/
// ?Load_Morph_Anim@HAnimManagerClass@@ present-unmatched
int HAnimManagerClass::Load_Morph_Anim(ChunkLoadClass & cload)
{
	HMorphAnimClass * newanim = W3DNEW HMorphAnimClass;

	if (newanim == NULL) {
		goto Error;
	}

	SET_REF_OWNER( newanim );

	if (newanim->Load_W3D(cload) != HMorphAnimClass::OK) {
		// load failed!
		newanim->Release_Ref();
		goto Error;
	} else if (Peek_Anim(newanim->Get_Name()) != NULL) {
		// duplicate exists!
		newanim->Release_Ref();	// Release the one we just loaded
		goto Error;
	} else {
		Add_Anim( newanim );
		newanim->Release_Ref();
	}

	return 0;

Error:

	return 1;
}


/***********************************************************************************************
 * HAnimManagerClass::Load_Raw_Anim -- Load a raw anim                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/23/2000  gth : Created.                                                                 *
 *=============================================================================================*/
// ?Load_Raw_Anim@HAnimManagerClass@@ present-unmatched
int HAnimManagerClass::Load_Raw_Anim(ChunkLoadClass & cload)
{
	HRawAnimClass * newanim = W3DNEW HRawAnimClass;

	if (newanim == NULL) {
		goto Error;
	}

	SET_REF_OWNER( newanim );

	if (newanim->Load_W3D(cload) != HRawAnimClass::OK) {
		// load failed!
		newanim->Release_Ref();
		goto Error;
	} else if (Peek_Anim(newanim->Get_Name()) != NULL) {
		// duplicate exists!
		newanim->Release_Ref();	// Release the one we just loaded
		goto Error;
	} else {
		Add_Anim( newanim );
		newanim->Release_Ref();
	}

	return 0;

Error:

	return 1;
}


/***********************************************************************************************
 * HAnimManagerClass::Load_Compressed_Anim -- load a compressed animation                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   5/23/2000  gth : Created.                                                                 *
 *=============================================================================================*/
// ?Load_Compressed_Anim@HAnimManagerClass@@ present-unmatched
int HAnimManagerClass::Load_Compressed_Anim(ChunkLoadClass & cload)
{
	HCompressedAnimClass * newanim = W3DNEW HCompressedAnimClass;

	if (newanim == NULL) {
		goto Error;
	}

	SET_REF_OWNER( newanim );

	if (newanim->Load_W3D(cload) != HCompressedAnimClass::OK) {
		// load failed!
		newanim->Release_Ref();
		goto Error;
	} else if (Peek_Anim(newanim->Get_Name()) != NULL) {
		// duplicate exists!
		newanim->Release_Ref();	// Release the one we just loaded
		goto Error;
	} else {
		Add_Anim( newanim );
		newanim->Release_Ref();
	}

	return 0;

Error:

	return 1;
}

/*********************************************************************************************** 
 * HAnimManagerClass::Peek_Anim -- returns a pointer to the specified animation data            * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
#pragma optimize("s", on)
HAnimClass * HAnimManagerClass::Peek_Anim(const char * name)
{
	return (HAnimClass*)AnimPtrTable->Find( name );
}
#pragma optimize("", on)


/*********************************************************************************************** 
 * HAnimManagerClass::Get_Anim -- returns a pointer to the specified animation data            * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// HAnimManagerClass::Get_Anim: defined in hanimmgr_GetAnim.cpp (its row's unit).


/*********************************************************************************************** 
 * HAnimManagerClass::Free_All_Anims -- de-allocate all currently loaded animations            * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?Free_All_Anims@HAnimManagerClass@@ present-unmatched
void HAnimManagerClass::Free_All_Anims(void)
{
	// Make an iterator, and release all ptrs
	HAnimManagerIterator it( *this );
	for( it.First(); !it.Is_Done(); it.Next() ) {
		HAnimClass *anim = it.Get_Current_Anim();
		anim->Release_Ref();
	}

	// Then clear the table
	AnimPtrTable->Reset();
}
	
/*********************************************************************************************** 
 * HAnimManagerClass::Free_All_Anims_With_Exclusion_List -- release animations not in the list * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   12/12/2002 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?Free_All_Anims_With_Exclusion_List@HAnimManagerClass@@ present-unmatched
void HAnimManagerClass::Free_All_Anims_With_Exclusion_List(const W3DExclusionListClass & exclusion_list)
{
	// Remove and Release_Ref any animation not in the exclusion list.
	HAnimManagerIterator it( *this );
	for( it.First(); !it.Is_Done(); it.Next() ) {
		HAnimClass *anim = it.Get_Current_Anim();

		if ((anim->Num_Refs() == 1) && (exclusion_list.Is_Excluded(anim) == false)) {
			//WWDEBUG_SAY(("deleting HAnim %s\n",anim->Get_Name()));
			AnimPtrTable->Remove(anim);
			anim->Release_Ref();
		}
		//else
		//{
		//	WWDEBUG_SAY(("keeping HAnim %s (ref %d)\n",anim->Get_Name(),anim->Num_Refs()));
		//}
	}
}


/*********************************************************************************************** 
 * HAnimManagerClass::Create_Asset_List -- Create a list of the W3D files that are loaded      * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   12/12/2002 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?Create_Asset_List@HAnimManagerClass@@ present-unmatched
void HAnimManagerClass::Create_Asset_List(DynamicVectorClass<StringClass> & exclusion_list)
{
	HAnimManagerIterator it( *this );
	for( it.First(); !it.Is_Done(); it.Next() ) {
		HAnimClass *anim = it.Get_Current_Anim();

		// File that this anim came from should be the name after the '.'
		// Anims are named in the format: <skeleton>.<animname>
		const char * anim_name = anim->Get_Name();
		char * filename = strchr(anim_name,'.');
		if (filename != NULL) {	
			exclusion_list.Add(StringClass(filename+1));
		}
	}
}


/*********************************************************************************************** 
 * HAnimManagerClass::Add_Anim -- Adds an externally created animation to the manager			  *
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   05/31/2000 PDS  : Created.                                                                * 
 *=============================================================================================*/
// Retail Add_Anim at 0x000F0BAB keeps the short inc-dword form.
// Size optimization preserves it while this unit uses /G7 for Get_Length.
#pragma optimize("t", off)
#pragma optimize("s", on)
bool HAnimManagerClass::Add_Anim(HAnimClass *new_anim)
{
	WWASSERT (new_anim != NULL);

	// Increment the refcount on the W3DNEW animation and add it to our table.
	new_anim->Add_Ref ();
	AnimPtrTable->Add( new_anim );
	
	return true;
}
#pragma optimize("", on)


/*
** Missing Anims
**
** The idea here, allow the system to register which anims are determined to be missing
** so that if they are asked for again, we can quickly return NULL, without searching the
** disk again.
*/
// ?Register_Missing@HAnimManagerClass@@ present-unmatched
void	HAnimManagerClass::Register_Missing( const char * name )
{
	MissingAnimTable->Add( W3DNEW MissingAnimClass( name ) );
}

#pragma optimize("s", on)
bool	HAnimManagerClass::Is_Missing( const char * name )
{
	return ( MissingAnimTable->Find( name ) != NULL );
}
#pragma optimize("", on)

// ?Reset_Missing@HAnimManagerClass@@ present-unmatched
void	HAnimManagerClass::Reset_Missing( void )
{
	// Make an iterator, and release all ptrs
	HashTableIteratorClass it( *MissingAnimTable );
	for( it.First(); !it.Is_Done(); it.Next() ) {
		MissingAnimClass *missing = (MissingAnimClass *)it.Get_Current();
		delete missing;
	}

	// Then clear the table
	MissingAnimTable->Reset();
}


/*
** Iterator converter from HashableClass to HAnimClass
*/
// ?Get_Current_Anim@HAnimManagerIterator@@ present-unmatched
HAnimClass * HAnimManagerIterator::Get_Current_Anim( void )	
{ 
	return (HAnimClass *)Get_Current(); 
}

