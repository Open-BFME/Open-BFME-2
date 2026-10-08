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

class Xfer
{
public:
	void Version1();
	virtual void slot00();
	virtual void slot01();
	virtual bool isStoring();
	virtual bool IsCRC() const;
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
};

class ThingTemplate;
struct ScoreThingTemplateView { unsigned char opaque00[0x64]; AsciiString name; };

// Local ABI key wrapper: retail compares the stored template address as unsigned
// and stores it in one word. This is a view of that storage, not a claim that
// retail declares this wrapper. Keep its optimized helpers distinct from the
// established, larger ScoreKeeper ThingTemplate tree instantiations.
struct TemplateCountKey {
 const ThingTemplate *pointer;
 __forceinline TemplateCountKey() {}
 __forceinline TemplateCountKey(const ThingTemplate *p) : pointer(p) {}
 __forceinline bool operator<(const TemplateCountKey &other) const { return pointer < other.pointer; }
};
typedef _STL::map<TemplateCountKey, Int> ObjectCountMap;

class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
// ThingFactory.cpp owns the singleton; Rva002D06CA is this unit's lookup view.
class ThingFactory;
extern ThingFactory *TheThingFactory;
class XferException { public: XferException(int,const char *,...); XferException(const XferException &); ~XferException(); char *text; int tag; };
// ?xferThingTemplateCountMap@@YAXPAVXfer@@PAV?$map@UTemplateCountKey@@HU?$less@UTemplateCountKey@@@_STL@@V?$allocator@U?$pair@$$CBUTemplateCountKey@@H@_STL@@@3@@_STL@@@Z
void xferThingTemplateCountMap(Xfer *xfer, ObjectCountMap *map)
{
	if (xfer->IsCRC()) return;
	xfer->Version1();

	UnsignedShort mapSize = map->size();
	xfer->xferUnsignedShort(&mapSize);

	Int count;
	TemplateCountKey thingTemplate;
	AsciiString thingTemplateName;

	if (xfer->isStoring())
	{
		ObjectCountMap::iterator it;
		for (it = map->begin(); it != map->end(); ++it)
		{
			thingTemplate = it->first;
			thingTemplateName = reinterpret_cast<const ScoreThingTemplateView *>(thingTemplate.pointer)->name;
			xfer->xferAsciiString(&thingTemplateName);

			count = it->second;
			xfer->xferInt(&count);
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < mapSize; ++i)
		{
			xfer->xferAsciiString(&thingTemplateName);
			thingTemplate.pointer = static_cast<const ThingTemplate *>(reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06CA(&thingTemplateName));
			if (thingTemplate.pointer == 0)
			{
				throw XferException(5,0);
			}

			xfer->xferInt(&count);
			(*map)[thingTemplate] = count;
		}
	}
}
