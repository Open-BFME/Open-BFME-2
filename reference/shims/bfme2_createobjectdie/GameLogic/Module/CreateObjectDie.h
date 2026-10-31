// Copied from reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateObjectDie.h; each change is marked "BFME 2:".
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

// FILE: CreateObjectDie.h /////////////////////////////////////////////////////////////////////////////
// Author: Michael S. Booth, January 2002
// Desc:   Create object at current object's death
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _CREATE_OBJECT_DIE_H_
#define _CREATE_OBJECT_DIE_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/INI.h"
#include "GameLogic/Module/DieModule.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Thing;
class ObjectCreationList;

//-------------------------------------------------------------------------------------------------
// BFME 2: the die family's data base. 0x00485D9B calls its constructor, row ??0DestroyDieModuleData@@QAE@XZ
// 0x00253510; 0x0078BFE7 unwinds through its destructor, row ??1DestroyDieModuleData@@UAE@XZ 0x0049B47C, the
// inline Snapshot table restore; 0x00253510 builds a DieMuxData at +8 through row 0x004CE534, and the table at
// 0x00C4A928 puts the first member after this class at +0x38.
class __declspec(novtable) DestroyDieModuleData : public ModuleData
{
public:
	DestroyDieModuleData();
	virtual ~DestroyDieModuleData() {}

private:
	DieMuxData m_dieMuxData;
	unsigned char m_pad[0x30 - sizeof(DieMuxData)];
};

//-------------------------------------------------------------------------------------------------
class CreateObjectDieModuleData : public DestroyDieModuleData
{

public:

	// BFME 2: fields of the table at 0x00C4A928. CreationList parses a list at +0x38, DebrisPortionOfSelf an
	// AsciiString at +0x3C and UpgradeRequired an AsciiString vector at +0x40; 0x0078BFFA destroys +0x40 through
	// row ??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ 0x0002CC70.
	const ObjectCreationList* m_ocl;			///< object creaton list to make
	AsciiString m_debrisPortionOfSelf;
	std::vector<AsciiString> m_upgradeRequired;

	CreateObjectDieModuleData();

	static void buildFieldParse(MultiIniFieldParse& p);

};

//-------------------------------------------------------------------------------------------------
/** When this object dies, create another object in its place */
//-------------------------------------------------------------------------------------------------
class CreateObjectDie : public DieModule
{

	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( CreateObjectDie, "CreateObjectDie"  )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( CreateObjectDie, CreateObjectDieModuleData );

public:

	CreateObjectDie( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype provided by memory pool declaration

	virtual void onDie( const DamageInfo *damageInfo ); 

	// BFME 2: row ?rva0004859EA@CreateObjectDie@@SA?AW4NameKeyType@@XZ 0x004859EA.
	static NameKeyType rva0004859EA();

};

#endif // _CREATE_OBJECT_DIE_H_

