// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??1Module@@QAE@XZ=??1Module@@MAE@XZ")

// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/Thing/Module.cpp); this unit had no counterpart under Code/.
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

// FILE: Module.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Desc:	 Object and drawable modules and actions.  These are simply just class
//				 instances that we can assign to objects, drawables, and things to contain
//				 data and code for specific events, or just to hold data
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/Module.h"
#include "Common/Thing.h"
#include "Common/INI.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DamageModule.h"
#include "GameLogic/Module/DieModule.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/UpgradeModule.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma message("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// this method should NEVER be overridden by user code, only via the MAKE_STANDARD_MODULE_xxx macros!
// it should also NEVER be called directly; it's only for use by ModuleFactory!
/*static*/ ModuleData* Module::friend_newModuleData(INI* ini) 
{ 
	ModuleData* data = MSGNEW("Module::friend_newModuleData") ModuleData;	// no need to memorypool these since we never allocate more than one of each
	if (ini)
		ini->initFromINI(data, 0);	// this is just so that an "end" token is required
	return data;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?Module::~Module present-unmatched
Module::~Module()
{

}  // end ~Module

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?Module::crc present-unmatched
void Module::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?Module::xfer present-unmatched
void Module::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** load post process */
// ------------------------------------------------------------------------------------------------
// ?Module::loadPostProcess present-unmatched
void Module::loadPostProcess( void )
{

}  // end loadPostProcess

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ObjectModule::ObjectModule: defined in ObjectModuleCtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?ObjectModule::~ObjectModule present-unmatched
ObjectModule::~ObjectModule( void )
{

}  // end ~ObjectModule

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?ObjectModule::crc present-unmatched
void ObjectModule::crc( Xfer *xfer )
{

	// extend base class
	Module::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void ObjectModule::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	Module::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** load post process */
// ------------------------------------------------------------------------------------------------
// ?ObjectModule::loadPostProcess present-unmatched
void ObjectModule::loadPostProcess( void )
{

	// extend base class
	Module::loadPostProcess();

}  // end loadPostProcess

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// DrawableModule::DrawableModule: defined in DrawableModuleCtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?DrawableModule::~DrawableModule present-unmatched
DrawableModule::~DrawableModule( void )
{

}  // end ~DrawableModule

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?DrawableModule::crc present-unmatched
void DrawableModule::crc( Xfer *xfer )
{

	// extend base class
	Module::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?DrawableModule::xfer present-unmatched
void DrawableModule::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	Module::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** load post process */
// ------------------------------------------------------------------------------------------------
// ?DrawableModule::loadPostProcess present-unmatched
void DrawableModule::loadPostProcess( void )
{

	// extend base class
	Module::loadPostProcess();

}  // end loadPostProcess

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ?UpgradeMuxData::performUpgradeFX present-unmatched
void UpgradeMuxData::performUpgradeFX(Object* obj) const
{
	if (m_fxListUpgrade)
	{
		FXList::doFXObj(m_fxListUpgrade, obj);
	}
}

//-------------------------------------------------------------------------------------------------
// ?UpgradeMuxData::muxDataProcessUpgradeRemoval present-unmatched
void UpgradeMuxData::muxDataProcessUpgradeRemoval(Object* obj) const
{
	if( !m_removalUpgradeNames.empty() )
	{
		std::vector<AsciiString>::const_iterator it;
		for( it = m_removalUpgradeNames.begin();
					it != m_removalUpgradeNames.end();
					it++)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade( *it );
			if( !theTemplate && !it->isEmpty() && !it->isNone())
			{
				DEBUG_CRASH(("An upgrade module references %s, which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}

			obj->removeUpgrade(theTemplate);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?UpgradeMuxData::isTriggeredBy present-unmatched
Bool UpgradeMuxData::isTriggeredBy(const std::string &upgrade) const
{
	std::vector<AsciiString>::const_iterator it;
	for( it = m_triggerUpgradeNames.begin(); it != m_triggerUpgradeNames.end();	++it)
	{
		AsciiString trigger = *it;
		if (stricmp(trigger.str(), upgrade.c_str()) == 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

//-------------------------------------------------------------------------------------------------
void UpgradeMuxData::getUpgradeActivationMasks(UpgradeMaskType& activation, UpgradeMaskType& conflicting) const
{
	// already computed.
	if (!m_activationUpgradeNames.empty() || !m_conflictingUpgradeNames.empty())
	{
		m_activationMask.clear();
		m_conflictingMask.clear();
		
		std::vector<AsciiString>::const_iterator it;
		for( it = m_activationUpgradeNames.begin();
					it != m_activationUpgradeNames.end();
					it++)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade( *it );
			if( !theTemplate && !it->isEmpty() && !it->isNone())
			{
				DEBUG_CRASH(("An upgrade module references %s, which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}

			m_activationMask.set( theTemplate->getUpgradeMask() );
		}

		for( it = m_conflictingUpgradeNames.begin();
					it != m_conflictingUpgradeNames.end();
					it++)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade( *it );
			if( !theTemplate && !it->isEmpty() && !it->isNone())
			{
				DEBUG_CRASH(("An upgrade module references %s, which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}
			m_conflictingMask.set( theTemplate->getUpgradeMask() );
		}

		// We set the trigger upgrade names with the activationUpgradeNames entries to be used later.
		// We have to do this because the activationUpgradeNames are toasted just below.
		m_triggerUpgradeNames = m_activationUpgradeNames;

		//Clear the names now that we've cached the values!
		m_activationUpgradeNames.clear();
		m_conflictingUpgradeNames.clear();
	}
	activation = m_activationMask;
	conflicting = m_conflictingMask;
}
