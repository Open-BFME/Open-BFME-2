// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
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

// Donor: GeneralsMD ProcessAnimateWindow.cpp and ProcessAnimateWindow.h at
// BFME1 revision 10af19f44a89ab7ecc23195bb9a842ceafbc02c9.
// The constructor was already verified at RVA0x005C4FEF. It installs the
// BottomTimed vtable VA0x00C7481C, whose slot0 targets the shared deleting
// destructor RVA0x005C5990/28B. That wrapper calls RVA0x005C6317/7B before
// optional operator delete. The empty donor derived destructor runs the
// inline base destructor and therefore restores the BASE vptr VA0x00C74804.
// Native base table: deleting destructor RVA0x005C4F88/29B; four __purecall
// entries at RVA0x0003B810; no-op setMaxDuration ret4 at RVA0x0047A69C.
// This independently matches the donor abstract base's virtual hierarchy.
// Derived dtors fold to this body; only BottomTimed claims its address.
#include "GameClient/ProcessAnimateWindow.h"

ProcessAnimateWindowSlideFromBottomTimed::~ProcessAnimateWindowSlideFromBottomTimed()
{
}

ProcessAnimateWindowSlideFromBottomTimed::ProcessAnimateWindowSlideFromBottomTimed()
{
    m_maxDuration = 1000;
}
