// cl: /DNDEBUG /MD
// stlport
//
// AIGroup::getCommandButtonSourceObject(GUICommandType), retail 0x0036E158
// (107 bytes), pinned. Zero Hour's body (GameLogic/AI/AIGroup.cpp): the
// first member (list at +0x04) whose command set (looked up on
// TheControlBar 0x00E01CFC through the rowed 0x0031D5F8, by the member's
// command-set name from the rowed Object accessor 0x00290E67) holds a button
// of the given type (+0x14) among its 32 slots (rowed
// CommandSet::getCommandButton 0x00409EE8).
#include "../../../Include/Common/ScalarTypes.h"



enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

#include "../../../Include/GameClient/CommandButton.h"

#include "../../../Include/GameClient/CommandSet.h"

#include "../../../Include/Common/Rva0031D5F8.h"
class ControlBar;
extern ControlBar *TheControlBar;

#include "../Object/object.h"

#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

enum
{
	MAX_COMMANDS_PER_SET = 32
};

#include "../../../Include/GameLogic/AIGroup.h"

Object *AIGroup::getCommandButtonSourceObject( GUICommandType type )
{
	for( _STL::list<Object *>::iterator it = m_memberList.begin(); it != m_memberList.end(); ++it )
	{
		Object *obj = *it;
		if( !obj )
			continue;

		const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8( obj->rva00290E67() );
		if( commandSet )
		{
			for( Int j = 0; j < MAX_COMMANDS_PER_SET; j++ )
			{
				const CommandButton *commandButton = commandSet->getCommandButton( j );
				if( commandButton && commandButton->getCommandType() == type )
					return obj;
			}
		}
	}
	return 0;
}
