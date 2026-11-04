// cl: /O1 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

// FILE: InstantDeathBehavior.cpp ///////////////////////////////////////////////////////////////////////
// Author:
// Desc:  
///////////////////////////////////////////////////////////////////////////////////////////////////


// Retail 0x0045D35F registers DieMuxData at +8 and the four-entry table
// at VA 0x00C41FA8. The table binds FX to the shared vector parser at
// 0x00339B9A with offset +0x38; OCL, Weapon and Sound use the module's
// rowed callbacks, which take the complete instance and apply their offsets.
// The former ZH-only destructor/snapshot methods have no retail rows.

#include <vector>
#include "../../../../Include/Common/INI/FieldParse.h"
#include "../../../../Include/GameLogic/Module/DestroyDieModuleData.h"

class InstantDeathBehaviorModuleData : public DestroyDieModuleData
{
public:
    InstantDeathBehaviorModuleData();
    virtual ~InstantDeathBehaviorModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static void parseOCL(INI *, void *, void *, const void *);
    static void parseWeapon(INI *, void *, void *, const void *);

private:
    // Match the existing constructor's element-neutral views. The retail
    // field table establishes the offsets; it does not establish C++ types.
    _STL::vector<int> m_vec38;
    _STL::vector<int> m_vec44;
    _STL::vector<int> m_vec50;
    _STL::vector<int> m_vec5C;
};

void iniParseFXListVec(INI *, void *, void *, const void *);
void Rva0045D2F6Parse(INI *, void *, void *, const void *);

// ?buildFieldParse@InstantDeathBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z
void InstantDeathBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    static const FieldParse dataFieldParse[] =
    {
        { "FX", iniParseFXListVec, 0, 0x38 },
        { "OCL", parseOCL, 0, 0 },
        { "Weapon", parseWeapon, 0, 0 },
        { "Sound", Rva0045D2F6Parse, 0, 0 },
        { 0, 0, 0, 0 }
    };
    parse.add(DieMuxData::getFieldParse(), 8);
    parse.add(dataFieldParse);
}
