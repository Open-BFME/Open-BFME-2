// cl: /Ireference/shims/nat /Ireference/shims/bfme2_ascii_native_copy /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: ThingFactory.cpp /////////////////////////////////////////////////////////////////////////
// Created:   Colin Day, April 2001
// Desc:		This is how we go and make our things, we make our things, we make our things!	
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// Retail's releaseBuffer is StringBase<char>'s (export at 0x00036410), which AsciiString
// befriends. The unit's AsciiString shim only declares its own, which nothing provides.
#include "../../../../../reference/shims/bfme2_ascii/string_base.h"
// ?AsciiString::releaseBuffer absent-from-retail
__forceinline void AsciiString::releaseBuffer()
{
	((StringBase<char> *)this)->releaseBuffer();
}

// PrereqUnitRec is private in the reference header; open only that header so
// the declaration-only vector assignment below can name it.
#include "Common/Science.h"
#define private public
#include "Common/ProductionPrerequisite.h"
#undef private

#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/FileSystem.h"
#include "Common/GameAudio.h"
#include "Common/MapObject.h"
#include "Common/ModuleFactory.h"
#include "Common/RandomValue.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/CreateModule.h"
#include "Common/ProductionPrerequisite.h"
#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"
#include "Common/INI.h"

// Bottom-loop overload: this TU's flags compile the generic range-destroy to
// a non-retail form; the overload wins for (AsciiString*,AsciiString*) and
// offers the link no competing template copy (row 32 family2-LK3).
namespace _STL {
inline void _Destroy(AsciiString * __first, AsciiString * __last)
{ for (; __first != __last; ++__first) __first->~AsciiString(); }
}

// The PrereqUnitRec vector assignment roots this unit's whole PrereqUnitRec
// helper cascade (_M_clear, _Destroy, _Construct, the copy constructor and
// assignment); first in link order, its non-retail copies would be kept over
// ProductionPrerequisiteCtor.cpp's and StlSweepW5Rva002D044B.cpp's retail ones.
namespace _STL { template <> vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> > &vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> >::operator=(const vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> > &); }

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

enum { TEMPLATE_HASH_SIZE = 12288 };

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
ThingFactory *TheThingFactory = NULL;  ///< Thing manager singleton declaration

// STATIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Free all data loaded into this template database */
//-------------------------------------------------------------------------------------------------
// BFME2 freeDatabase is recovered in ThingFactoryReset.cpp.

//-------------------------------------------------------------------------------------------------
/** add the thing template passed in, into the databse */
//-------------------------------------------------------------------------------------------------
// BFME2 addTemplate, including its replacement path, is recovered in ThingFactoryReset.cpp.

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME2's complete85B constructor is recovered at002D0E14 in
// Rva002D0E14Ctor.cpp. The unmatched ZH constructor formerly left here
// also emitted a non-retail30B deleting destructor; keep that competing
// construction/vtable copy out of the link. ThingFactoryDtor.cpp emits
// the native28B deleting destructor with its verified71B out-of-line dtor.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1ThingFactory@@ present-unmatched
// BFME2's newTemplate and newOverride are recovered in ThingFactoryNewTemplate.cpp
// and ThingFactoryNewOverride.cpp. The unmatched ZH copies formerly left here
// emitted a non-retail 1216-byte ThingTemplate::operator= (Zero Hour layout)
// ahead of retail's 0x002D1101 in link order; keep them out of the link.

//-------------------------------------------------------------------------------------------------
/** Init */
//-------------------------------------------------------------------------------------------------
// ?init@ThingFactory@@ present-unmatched
void ThingFactory::init( void )
{

}  // end init

//-------------------------------------------------------------------------------------------------
/** Reset */
//-------------------------------------------------------------------------------------------------
// BFME2 reset is recovered in ThingFactoryReset.cpp.

//-------------------------------------------------------------------------------------------------
/** Update */
//-------------------------------------------------------------------------------------------------
// ?update@ThingFactory@@ present-unmatched
void ThingFactory::update( void )
{

}  // end update

//-------------------------------------------------------------------------------------------------
/** Return the template with the matching database name */
//-------------------------------------------------------------------------------------------------
// BFME ThingTemplate: m_nextTemplate @+0x38c, m_templateID @+0x478 (ZH headers differ).
// ?ThingFactory::findByTemplateID present-unmatched
const ThingTemplate *ThingFactory::findByTemplateID( UnsignedShort id )
{
	struct BFMEThingTemplateLinks {
		unsigned char padNext[0x38c];
		ThingTemplate *nextTemplate;
		unsigned char padId[0x478 - 0x38c - sizeof(ThingTemplate *)];
		UnsignedShort templateID;
	};
	for (ThingTemplate *thingTemplate = m_firstTemplate; thingTemplate; )
	{
		BFMEThingTemplateLinks *links = reinterpret_cast<BFMEThingTemplateLinks *>(thingTemplate);
		if (links->templateID == id)
			return thingTemplate;
		thingTemplate = links->nextTemplate;
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------------
/** Return the template with the matching database name */
//-------------------------------------------------------------------------------------------------
// ?findTemplateInternal@ThingFactory@@ present-unmatched
ThingTemplate *ThingFactory::findTemplateInternal( const AsciiString& name, Bool check )
{
	ThingTemplateHashMapIt tIt = m_templateHashMap.find(name);

	if (tIt != m_templateHashMap.end()) {
		return tIt->second;
	}

// BFME 2's lookup has no Zero Hour load-test-assets branch: retail
// ThingFactory::findTemplate (0x002D06CA, 38 bytes) is the hash find and
// returns the node's template or NULL. Its initForLTA/public newTemplate
// callees have no BFME 2 definer (newTemplate is private, 0x002D1B2E).
	
	if( check && name.isNotEmpty() )
	{
		DEBUG_CRASH( ("Failed to find thing template %s (case sensitive) This issue has a chance of crashing after you ignore it!", name.str() ) );
	}
	return NULL;

}  // end getTemplate

//=============================================================================

//=============================================================================

#if defined(_DEBUG) || defined(_INTERNAL)
AsciiString TheThingTemplateBeingParsedName;
#endif

//-------------------------------------------------------------------------------------------------

//#define CHECK_THING_NAMES
#ifdef CHECK_THING_NAMES

#include "Common/STLTypedefs.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<ProductionPrerequisite::PrereqUnitRec *>(ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *); }
namespace _STL { template <> ScienceType * __copy<ScienceType const *, ScienceType *, int>(ScienceType const *, ScienceType const *, ScienceType *, random_access_iterator_tag const &, int *); }
namespace _STL { template <> unsigned int const * __lower_bound<unsigned int const *, unsigned int, less<unsigned int>, int>(unsigned int const *, unsigned int const *, unsigned int const &, less<unsigned int>, int *); }
namespace _STL { template <> void advance<unsigned int const *, int>(unsigned int const *&, int); }
namespace _STL { template <> unsigned int hash<char const *>::operator()(char const *) const; }
namespace _STL { template <> pair<AsciiString const, ThingTemplate *> & hashtable<pair<AsciiString const, ThingTemplate *>, AsciiString, rts::hash<AsciiString>, _Select1st<pair<AsciiString const, ThingTemplate *> >, rts::equal_to<AsciiString>, allocator<pair<AsciiString const, ThingTemplate *> > >::_M_insert(pair<AsciiString const, ThingTemplate *> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$_Destroy@PAUPrereqUnitRec@ProductionPrerequisite@@@_STL@@YAXPAUPrereqUnitRec@Production:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Destroy<ProductionPrerequisite::PrereqUnitRec *>(ProductionPrerequisite::PrereqUnitRec *,ProductionPrerequisite::PrereqUnitRec *); }
// Suppress this TU's non-retail copy of ??$_M_find@VAsciiString@@@?$hashtable@U?$pair@$$CBVAsciiString@@PAVThingTemplate@@@_STL@@V:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; class ThingTemplate;
namespace _STL { template <> template <> _Hashtable_node<pair<AsciiString const ,ThingTemplate *> > * hashtable<pair<AsciiString const ,ThingTemplate *>,AsciiString,rts::hash<AsciiString>,_Select1st<pair<AsciiString const ,ThingTemplate *> >,rts::equal_to<AsciiString>,allocator<pair<AsciiString const ,ThingTemplate *> > >::_M_find<AsciiString>(AsciiString const &) const; }
// Suppress this TU's non-retail copy of ?_M_insert@?$hashtable@U?$pair@$$CBVAsciiString@@PAVThingTemplate@@@_STL@@VAsciiString@@U?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; class ThingTemplate;
namespace _STL { template <> pair<AsciiString const ,ThingTemplate *> & hashtable<pair<AsciiString const ,ThingTemplate *>,AsciiString,rts::hash<AsciiString>,_Select1st<pair<AsciiString const ,ThingTemplate *> >,rts::equal_to<AsciiString>,allocator<pair<AsciiString const ,ThingTemplate *> > >::_M_insert(pair<AsciiString const ,ThingTemplate *> const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UPrereqUnitRec@ProductionPrerequisite@@V?$allocator@UPrereqUnitRec@Prod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<ProductionPrerequisite::PrereqUnitRec,allocator<ProductionPrerequisite::PrereqUnitRec> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_Construct@U?$pair@$$CBVAsciiString@@PAVThingTemplate@@@_STL@@U12@@_STL@@YAXPAU?$pair@$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; class ThingTemplate;
namespace _STL { template <> void _Construct<pair<AsciiString const ,ThingTemplate *>,pair<AsciiString const ,ThingTemplate *> >(pair<AsciiString const ,ThingTemplate *> *,pair<AsciiString const ,ThingTemplate *> const &); }
// Suppress this TU's non-retail copy of ?__stl_hash_string@_STL@@YAIPBD@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned int __stl_hash_string(char const *); }
// Suppress this TU's non-retail copy of ??$advance@PBIH@_STL@@YAXAAPBIH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void advance<unsigned int const *,int>(unsigned int const * &,int); }
// Suppress this TU's non-retail copy of ??$_M_allocate_and_copy@PBW4ScienceType@@@?$vector@W4ScienceType@@V?$allocator@W4ScienceTy:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum ScienceType;
namespace _STL { template <> template <> ScienceType * vector<ScienceType,allocator<ScienceType> >::_M_allocate_and_copy<ScienceType const *>(unsigned int,ScienceType const *,ScienceType const *); }
// Suppress this TU's non-retail copy of ??$_M_allocate_and_copy@PBW4ScienceType@@@?$vector@W4ScienceType@@V?$allocator@W4ScienceTy:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum ScienceType;
namespace _STL { template <> ScienceType * vector<ScienceType,allocator<ScienceType> >::_M_allocate_and_copy<ScienceType const *>(unsigned int,ScienceType const *,ScienceType const *); }
// Suppress this TU's non-retail copy of ??$__advance@PBIH@_STL@@YAXAAPBIHABUrandom_access_iterator_tag@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void __advance<unsigned int const *,int>(unsigned int const * &,int,random_access_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??$__lower_bound@PBIIU?$less@I@_STL@@H@_STL@@YAPBIPBI0ABIU?$less@I@0@PAH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> const unsigned int *__lower_bound<const unsigned int *, unsigned int, less<unsigned int>, int>(const unsigned int *, const unsigned int *, const unsigned int &, less<unsigned int>, int *); }

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> >&);
}

const char *outFilenameINI				= "thing.txt";
const char *outFilenameStringFile	= "thingString.txt";

void resetReportFile( void )
{
	FILE *fp = fopen(outFilenameINI, "w");
	if (fp)
	{
		fprintf(fp, "-- ThingTemplate INI Report --\n\n");
		fclose(fp);
	}

	fp = fopen(outFilenameStringFile, "w");
	if (fp)
	{
		fprintf(fp, "-- ThingTemplate String File Report --\n\n");
		fclose(fp);
	}
}

AsciiStringList missingStrings;
void reportMissingNameInStringFile( AsciiString templateName )
{
	// see if we've seen it before
	AsciiStringListConstIterator cit = std::find(missingStrings.begin(), missingStrings.end(), templateName);
	if (cit != missingStrings.end())
		return;

	missingStrings.push_back(templateName);
}

void dumpMissingStringNames( void )
{
	missingStrings.sort();
	FILE *fp = fopen(outFilenameStringFile, "w");
	if (fp)
	{
		fprintf(fp, "-- ThingTemplate String File Report --\n\n");
		for (AsciiStringListConstIterator cit = missingStrings.begin(); cit!=missingStrings.end(); cit++)
		{
			fprintf(fp, "OBJECT:%s\n\"%s\"\nEND\n\n", cit->str(), cit->str());
		}
		fclose(fp);
	}
}

AsciiStringList missingNames;
void reportMissingNameInTemplate( AsciiString templateName )
{
	// see if we've seen it before
	AsciiStringListConstIterator cit = std::find(missingNames.begin(), missingNames.end(), templateName);
	if (cit != missingNames.end())
		return;

	missingNames.push_back(templateName);

	FILE *fp = fopen(outFilenameINI, "a+");
	if (fp)
	{
		fprintf(fp, "  DisplayName      = OBJECT:%s\n", templateName.str());
		fclose(fp);
	}

	//reportMissingNameInStringFile( templateName );
}

#endif

//-------------------------------------------------------------------------------------------------
/** Post process phase after loading the database files */
//-------------------------------------------------------------------------------------------------
// BFME2 postProcessLoad is recovered in ThingFactoryReset.cpp.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// Retain this unit's existing header-inline row after the unfinished
// freeDatabase caller moves to its verified BFME2 unit. This pointer is
// a compile anchor, not a retail data claim.
extern ThingTemplate *(ThingTemplate::*const _bfmeInlineAnchorFriendNext)() const =
    &ThingTemplate::friend_getNextTemplate;

// The same for the header-inline rows that the ZH ThingTemplate::operator=
// used to pull in: compile anchors, not retail data claims.
// (0x0042816E is VersionBlockEntry's op= in VersionBlockParser.cpp's range, not
// ProductionPrerequisite's; 0x00200BC0 lives in INIWater.cpp.)
extern std::vector<ProductionPrerequisite>::size_type (std::vector<ProductionPrerequisite>::*const _bfmeInlineAnchorPrereqSize)() const =
    &std::vector<ProductionPrerequisite>::size;
