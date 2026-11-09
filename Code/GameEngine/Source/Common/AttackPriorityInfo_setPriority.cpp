// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /Ob2 /Ireference/shims/moduledata
// stlport
// ?setPriority@AttackPriorityInfo@@QAEXPBVThingTemplate@@H@Z @ 0x00358333 (116B).
// Lazy-init map at +0x0C then subscript-assign second arg keyed by final override of first arg.
// Evidence: cmp [esi+0x0C] null-check then push 0x0C new 0x0002FDA0 plus map ctor 0x0033C432
// with EH state 0 to -1; mov ecx [edi+4] test je mov eax edi else call 0x001E35DF then
// mov ecx [esi+0x0C] lea push subscript 0x002077D6 then store [ebp+0x0C]; ret 8 two args.
// Row 0x001E35DF types as void but body uses eax result: reached through
// Overridable::getFinalOverride's inline recursion per its pin (row-type exception per taskfile).
#include <map>

#include "Common/Snapshot.h"

#include "ascii_string.h"

class Image;

#include "../../Include/Common/ThingTemplate.h"

namespace _STL
{
template <>
class map<int, void *, less<int>, allocator<pair<const int, void *> > >
{
public:
	map();

private:
	void *m_pad[3];
};
}

typedef _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > MapIntVoid0033C432;

#include "../../Include/GameClient/ImageSubscriptMap.h"

#include "../../Include/GameLogic/AttackPriorityInfo.h"

void AttackPriorityInfo::setPriority(const ThingTemplate *thingTemplate, int priority)
{
	if (!thingTemplate)
		return;
	if (!m_priorityMap)
		m_priorityMap = (AttackPriorityMap *)new MapIntVoid0033C432;
	const Overridable *key = thingTemplate->getFinalOverride();
	((ImageSubscriptMap *)m_priorityMap)->operator[]((unsigned int)key) = (Image *)priority;
}
