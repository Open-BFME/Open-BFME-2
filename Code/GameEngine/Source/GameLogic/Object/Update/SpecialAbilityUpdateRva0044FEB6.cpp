// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva0044FEB6@SpecialAbilityUpdate@@QAEPAVObject@@XZ, retail 0x0044FEB6, 183 bytes.
// SpecialAbilityUpdate helper that spawns one special object via ThingFactory.
// Evidence: prev row 0x0044F996 xfer same TU dir; callee 0x0044F72E same class
// (list clear plus count zero); ModuleData +0x40 AsciiString lookup via rowed
// 0x002D06CA through TheThingFactory; 16-byte zeroed CreateMask via memset thunk
// 0x006291AE; ThingFactory::newObject pin 0x002D0A23 (template team mask false);
// list<int> push_back row 0x0005548F at +0x64 plus count inc at +0x68;
// Thing::setPosition row 0x0030AA80 at +0x38; AIUpdateInterface
// setLastCommandSource row 0x003B23AF via +0x264 with +0x74 source.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include <list>
#include <string.h>
// bfme link decl-only begin
namespace _STL { template <> _STL::_List_node<int> * list<int,_STL::allocator<int> >::_M_create_node(int const &); }
namespace _STL { template <> _STL::_List_node<int> * _STLP_alloc_proxy<_STL::_List_node<int> *,_STL::_List_node<int>,_STL::allocator<_STL::_List_node<int> > >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> _STL::_List_node<int> * allocator<_STL::_List_node<int> >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_List_node<int> *,_STL::_List_node<int>,_STL::allocator<_STL::_List_node<int> > >::deallocate(_STL::_List_node<int> *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_List_node<int> >::deallocate(_STL::_List_node<int> *,unsigned int) const; }
// bfme link decl-only end
// Keep integer construction inline; stlport_deque_int.cpp owns retail's
// out-of-line _Construct<int, int> body at 0x00620140.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void _Construct<int, int>(int *p, const int &value) { new (p) int(value); }
}

#pragma function(memset)

class Team;
class ThingTemplate;

struct CreateMask
{
	unsigned int words[4];
};

enum ObjectID; class ThingFactory
{
public:
	class Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID flag);
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

enum CommandSourceType
{
	CMD_SOURCE_ZERO = 0
};

class SpecialAbilityUpdate;

class AIUpdateInterface
{
protected:
	void setLastCommandSource(CommandSourceType source);
	friend class SpecialAbilityUpdate;
};

#include "../../../Common/Thing/thing.h"

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_coord38;
	char m_pad44[0x74 - 0x44];
	int m_id74;
	char m_pad78[0x264 - 0x78];
	AIUpdateInterface *m_ai264;
	char m_pad268[0x304 - 0x268];
	Team *m_team304;
};

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

Object *SpecialAbilityUpdate::rva0044FEB6()
{
	const SpecialAbilityUpdateModuleData *md = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	Object *newObj = 0;
	if (m_68 == md->m_maxSpecialObjects) {
		if (md->m_specialObjectsPersistent)
			return 0;
		killSpecialObjects();
	}
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(md->m_specialObjectName);
	if (thingTemplate != 0) {
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		Team *team = m_object->m_team304;
		newObj = TheThingFactory->newObject(thingTemplate, team, &mask, (ObjectID)0);
		if (newObj != 0) {
			int id = newObj->m_id74;
			m_specialObjectIDList.push_back(id);
			++m_68;
			((Thing *)newObj)->setPosition(&m_object->m_coord38);
			AIUpdateInterface *ai = newObj->m_ai264;
			if (ai != 0)
				ai->setLastCommandSource((CommandSourceType)m_object->m_id74);
		}
	}
	return newObj;
}
