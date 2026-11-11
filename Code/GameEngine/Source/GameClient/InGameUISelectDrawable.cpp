// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME 1 donor 6583b3c1ff21db4a561285717028fdafc780b7db:
// game/GameEngine/Source/GameClient/InGameUISelectDrawable.cpp, with ZH's
// selectDrawable as its semantic source. Target vtables at RVA 0x007C7AB0
// and 0x007FD438 both put 0x002A3805 in slot 56; slot 57 deselects and slots
// 88/89 are the matched selectMatching pair. The native 259B extent ends
// at ret 4 immediately before 0x002A3908 (absent from the old inventory).
// Retail supplies every changed offset below, the bit at template+0x119,
// GateOpenAndCloseBehavior/GateProxyBehavior strings, and each direct callee.
// It reads the template directly and resets the 25 entries through the
// already-matched 0x0029ACC7 helper. Unknown callee names remain address-based.
// The selected-drawable list at +0x20 calls push_front 0x002A1B53 (28B),
// independently establishing that helper's pointer element type.
//
// Native list nodes use the existing pool at VA 0x00DBA5E0: this specialization
// emits the same 28B as rowed Rva00239BD8Alloc, and its insert caller emits
// the same 37B as rowed Rva00239D02Insert. Keep both existing ledger owners.
#define _STLP_NO_EXCEPTIONS 1

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

enum DrawableID { INVALID_DRAWABLE_ID = 0 };
class Drawable;
#include "../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DBA5E0;
#define g_pool00239BD8 g_freelistPool00DBA5E0
// ^ g_pool00239BD8 is only an alias of the owned global g_freelistPool00DBA5E0 (ledger names column).
namespace _STL
{
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
    _List_node<Drawable *> *node = (_List_node<Drawable *> *)g_pool00239BD8.pop();
    _Construct(&node->_M_data, value);
    return node;
}
}

typedef _STL::list<Drawable *> BfmeDrawableList;

enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmeSelectTemplateView
{
	unsigned char m_unmodelled000[0x10C];
	unsigned int m_kindOfWord10C;
	unsigned char m_unmodelled110[8];
	unsigned int m_kindOfWord118;							// +0x118; target tests bit 0x200
};

#include "../../Include/Common/Module.h"

// The module both gate behaviours are asked through: Module at +4, and the
// query 0x00498CB1; retail subtracts 4 from the found Module pointer.
class BfmeGateModuleBase
{
public:
	virtual ~BfmeGateModuleBase();
};

#include "../Common/GameLogicObjectLookupView.h"

class Player;

class Rva00498CB1Owner : public BfmeGateModuleBase, public Module
{
public:
	bool invoke();

	unsigned char m_pad00C[0x18];
	ObjectID m_objectID; // +0x24
};

class InGameUI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	friend class InGameUI;

protected:
	Module *findModule( NameKeyType key ) const;
public:
	Player *getControllingPlayer() const;
	void *m_vtable;
	const BfmeSelectTemplateView *m_template;
};

// Retail Drawable prefix used by selectDrawable.
#include "../../Include/GameClient/Drawable.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar;
class BfmeWorldRV { public: void rva0031AA34(int); };

extern ControlBar *TheControlBar;

extern GameLogic *TheGameLogic;

#include "../../Include/GameClient/InGameUI.h"

// ?selectDrawable@InGameUI@@UAEXPAVDrawable@@@Z
void InGameUI::selectDrawable( Drawable *draw )
{

	// only if not selected already
	if( draw->m_selected )
		return;

	Object *obj;
	if( (((const BfmeSelectTemplateView *)draw->m_template)->m_kindOfWord118 & 0x200) && (obj = draw->m_object) != 0 )
	{
		static NameKeyType key_GateOpenAndCloseBehavior = TheNameKeyGenerator->nameToKey( "GateOpenAndCloseBehavior" );

		Rva00498CB1Owner *gate = static_cast<Rva00498CB1Owner *>( obj->findModule( key_GateOpenAndCloseBehavior ) );
		if( !gate )
			gate = static_cast<Rva00498CB1Owner *>( obj->findModule( TheNameKeyGenerator->nameToKey( "GateProxyBehavior" ) ) );
		if( gate && gate->invoke() )
			return;
	}

	field570 = TheGameLogic->getFrame();

	// set the selected bit on the drawable
	draw->rva002796B8();

	// add to our list of selected drawables
	m_selectedDrawables.push_front( draw );

	// keep our own internal count happy
	++field568;

	// Donor evaluateSoloNexus role; retail tests the selected objects at +0xFC.
	evaluateSoloNexus( draw );

	// the control needs to update its context sensitive display now
	((BfmeWorldRV *)TheControlBar)->rva0031AA34((int)draw);

	expireAllHints(0);
}

// ZH InGameUI::evaluateSoloNexus (same source in the BFME 1 donor 6583b3c1):
// target 0x0029B967 (126B), called by the matched selectDrawable above.
// Target accesses establish the result at +0x980, the selected list at +0x20,
// Drawable's Object at +0xFC, and template flags at +0x10C. The same two-kind
// short-circuit and single-nexus count support the ZH role; native bits are
// 0x4000/0x8000. The ID read calls the matched retail 0x0055A88B getter.
void InGameUI::evaluateSoloNexus(Drawable *newlyAddedDrawable)
{
    m_soloNexusSelectedDrawableID = INVALID_DRAWABLE_ID;
    if (newlyAddedDrawable)
    {
        const Object *newObj = newlyAddedDrawable->m_object;
        if (newObj && !(newObj->m_template->m_kindOfWord10C & 0xC000))
            return;
    }
    unsigned short nexaeFound = 0;
    for (BfmeDrawableList::const_iterator it = m_selectedDrawables.begin();
         it != m_selectedDrawables.end(); ++it)
    {
        Drawable *draw = *it;
        const Object *obj = draw->m_object;
        if (!obj)
            continue;
        if (obj->m_template->m_kindOfWord10C & 0x4000)
        {
            ++nexaeFound;
            if (nexaeFound == 1)
                m_soloNexusSelectedDrawableID = draw->getID();
            else
            {
                m_soloNexusSelectedDrawableID = INVALID_DRAWABLE_ID;
                return;
            }
        }
        else if (!(obj->m_template->m_kindOfWord10C & 0x8000))
        {
            m_soloNexusSelectedDrawableID = INVALID_DRAWABLE_ID;
            return;
        }
    }
}

// Native selected-flag transition, 0x002796B8 (33B). BFME 1 donor
// 6583b3c1 game/GameEngine/Source/Common/BfmeConv553.cpp, bfmeGoBXF:
// update once when the selected flag changes, then always invoke the
// one-argument helper. The matched selection caller establishes Drawable;
// retail fixes the flag at +0x43C and calls at 0x2754E3/0x278C7C.
void Drawable::rva002796B8()
{
    if (!m_selected)
    {
        m_selected = true;
        rva002754E3();
    }
    rva00278C7C(0);
}

// ?invoke@Rva00498CB1Owner@@QAE_NXZ @0x00498CB1 149B: gate select probe.
// Evidence: caller 0x002A38A6 InGameUI::selectDrawable; ObjectID at +0x24;
// rowed findObjectByID 0x00049DC5 getControllingPlayer 0x0028AFA9
// appendBoolean 0x0030F963 appendObjectID 0x0030F979 getDrawable 0x005508E2;
// globals TheGameLogic ThePlayerList TheInGameUI MessageStreamSubsystem;
// InGameUI slots 0x110/0x108 MessageStream slot 0x48 type 0x3EA per
// ControlBarToggle0031AFDE precedent.
#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"

#include "../Common/Thing/thing.h"

#include "../../Include/Common/MessageStream.h"



extern PlayerList *ThePlayerList;
extern InGameUI *TheInGameUI;
extern class MessageStream *TheMessageStream;

bool Rva00498CB1Owner::invoke()
{
	if (m_objectID == INVALID_OBJECT_ID)
		return false;
	Object *obj = TheGameLogic->findObjectByID(m_objectID);
	if (!obj)
		return false;
	Player *player = obj->getControllingPlayer();
	Player *local = ThePlayerList->m_local;
	if (player && local && player == local)
	{
		TheInGameUI->deselectAllDrawables();
		GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP_NO_SOUND);
		msg->appendBooleanArgument(true);
		msg->appendObjectIDArgument(m_objectID);
		Drawable *draw = ((Thing *)obj)->getDrawable();
		if (draw)
			TheInGameUI->selectDrawable(draw);
		return true;
	}
	return false;
}
