// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport46
// addRecentLadder at 0x005E03F6 follows the Open-BFME-1 donor
// game/GameEngine/Source/Common/UserPreferences.cpp (6d943426).
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: UserPreferences.cpp
// Author: Matthew D. Campbell, April 2002
// Description: Saving/Loading of user preferences
///////////////////////////////////////////////////////////////////////////////////////

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include "../../Include/Common/UserPreferences.h"
#include "../../Include/GameNetwork/LadderPref.h"

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// Preserve the compiler-generated member assignment and destruction bodies.
inline LadderPref &LadderPref::operator=(const LadderPref &other)
{
    name = other.name;
    address = other.address;
    port = other.port;
    lastPlayDate = other.lastPlayDate;
    return *this;
}
inline LadderPref::~LadderPref() {}

typedef std::map<long, LadderPref> LadderPrefMap;
class LadderPreferences : public UserPreferences
{
public:
    LadderPreferences();
    virtual ~LadderPreferences();
    bool loadProfile(int profileID);
    virtual bool write(void);
    const LadderPrefMap &getRecentLadders(void);
    void addRecentLadder(LadderPref ladder);
private:
    LadderPrefMap m_ladders;
};
// bfme link decl-only begin
namespace _STL { template <> void _Construct<pair<long const, LadderPref>, pair<long const, LadderPref> >(pair<long const, LadderPref> *, pair<long const, LadderPref> const &); }
namespace _STL { template <> LadderPref & map<long, LadderPref, less<long>, allocator<pair<long const, LadderPref> > >::operator[](long const &); }
// bfme link decl-only end

void LadderPreferences::addRecentLadder( LadderPref ladder )
{
	for (LadderPrefMap::iterator it = m_ladders.begin(); it != m_ladders.end(); ++it)
	{
		if (it->second == ladder)
		{
			m_ladders.erase(it);
			break;
		}
	}

	m_ladders[ladder.lastPlayDate] = ladder;
}
