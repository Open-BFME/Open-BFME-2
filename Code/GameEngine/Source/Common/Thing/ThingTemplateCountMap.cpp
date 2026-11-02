// cl: /O1 /G7 /EHsc /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Clean donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/ScriptEngine/ScoreKeeperXferObjectCountMap.cpp.
// The donor supplies count-map save/load and missing-template exception semantics;
// its direct BFME2 compile/place trial found no new bodies. Target WB1416A60
// names xferThingTemplateCountMap. Native55AC77..55AD90 proves CRC early return,
// Version1, string slot27, int slot31, ushort slot32, template name64 and the
// 2D06CA lookup ABI. ThingTemplate is forward-declared; name64 is a local view.
// Eight genuine emitted map helpers independently match complete existing
// retail bodies and every resolved call. Their pointer-key ordering is unsigned;
// mapped count storage is four bytes. Folds assert no Image application identity.

#include <map>
namespace _STL { template<class T,class L,class R> static inline bool operator!=(const _Rb_tree_iterator<T,L>&a,const _Rb_tree_iterator<T,R>&b){return a._M_node!=b._M_node;} }

typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#include "ascii_string.h"

#include "../System/XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

class ThingTemplate;
struct ScoreThingTemplateView { unsigned char opaque00[0x64]; AsciiString name; };

// Local ABI key wrapper: retail compares the stored template address as unsigned
// and stores it in one word. This is a view of that storage, not a claim that
// retail declares this wrapper. Keep its optimized helpers distinct from the
// established, larger ScoreKeeper ThingTemplate tree instantiations.
struct TemplateCountKey {
 const ThingTemplate *pointer;
 __forceinline TemplateCountKey() {}
 __forceinline TemplateCountKey(const ThingTemplate *thingTemplate) : pointer(thingTemplate) {}
 __forceinline bool operator<(const TemplateCountKey &other) const { return pointer < other.pointer; }
};
typedef _STL::map<TemplateCountKey, Int> ObjectCountMap;

#include "../../../Include/Common/ThingFactory.h"
// ThingFactory.cpp owns the singleton; ThingFactory is this unit's lookup view.
class ThingFactory;
extern ThingFactory *TheThingFactory;
#include "../../../Include/Common/XferException.h"
// ?xferThingTemplateCountMap@@YAXPAVXfer@@PAV?$map@UTemplateCountKey@@HU?$less@UTemplateCountKey@@@_STL@@V?$allocator@U?$pair@$$CBUTemplateCountKey@@H@_STL@@@3@@_STL@@@Z
void xferThingTemplateCountMap(Xfer *xfer, ObjectCountMap *map)
{
	if (xfer->IsCRC()) return;
	xfer->Version1();

	UnsignedShort mapSize = map->size();
	*xfer == mapSize;

	Int count;
	TemplateCountKey thingTemplate;
	AsciiString thingTemplateName;

	if (xfer->IsStoring())
	{
		ObjectCountMap::iterator it;
		for (it = map->begin(); it != map->end(); ++it)
		{
			thingTemplate = it->first;
			thingTemplateName = reinterpret_cast<const ScoreThingTemplateView *>(thingTemplate.pointer)->name;
			*xfer == thingTemplateName;

			count = it->second;
			*xfer == count;
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < mapSize; ++i)
		{
			*xfer == thingTemplateName;
			thingTemplate.pointer = static_cast<const ThingTemplate *>((void *)reinterpret_cast<ThingFactory *>(TheThingFactory)->findTemplate(thingTemplateName));
			if (thingTemplate.pointer == 0)
			{
				throw XferException(5,0);
			}

			*xfer == count;
			(*map)[thingTemplate] = count;
		}
	}
}
