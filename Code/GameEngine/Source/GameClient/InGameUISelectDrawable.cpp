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
class FreelistPool { public: void *pop(); };
extern FreelistPool g_pool00239BD8;
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

class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmeSelectTemplateView
{
	unsigned char m_unmodelled000[0x10C];
	unsigned int m_kindOfWord10C;
	unsigned char m_unmodelled110[8];
	unsigned int m_kindOfWord118;							// +0x118; target tests bit 0x200
};

class Module
{
public:
	virtual ~Module();
};

// The module both gate behaviours are asked through: Module at +4, and the
// query 0x00498CB1; retail subtracts 4 from the found Module pointer.
class BfmeGateModuleBase
{
public:
	virtual ~BfmeGateModuleBase();
};

enum ObjectID { OBJECTID_INVALID = 0 };

class Player;

class Rva00498CB1Owner : public BfmeGateModuleBase, public Module
{
public:
	bool invoke();

	unsigned char m_pad008[0x1C];
	ObjectID m_objectID; // +0x24
};

class Rva0029ACA0 { public: void rva0029ACC7(int); };
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
class Drawable
{
public:
	void rva002796B8();
	void rva002754E3();
	void rva00278C7C(int);
	DrawableID getID() const;
	void *m_vtable;
	const BfmeSelectTemplateView *m_template;							///< this+0x04
	unsigned char m_unmodelled008[0xf4];
	Object *m_object;										///< this+0xFC
	unsigned char m_unmodelled100[0x33c];
	bool m_selected;										// +0x43C

};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar;
class BfmeWorldRV { public: void rva0031AA34(int); };

extern ControlBar *TheControlBar;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() { return m_frame; }
	Object *findObjectByID(ObjectID id);

private:
	unsigned char m_unmodelled000[0x40];
	unsigned int m_frame;									// +0x40
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	virtual void selectDrawable( Drawable *draw );

protected:
	void evaluateSoloNexus( Drawable *newlyAddedDrawable = 0 );

private:
	unsigned char m_unmodelled004[0x1c];
	BfmeDrawableList m_selectedDrawables;					// +0x20
	unsigned char m_unmodelled024[0x544];
	int m_selectCount;										// +0x568
	unsigned char m_unmodelled56C[0x4];
	unsigned int m_frameSelectionChanged;					// +0x570
	unsigned char m_unmodelled574[0x40C];
	DrawableID m_soloNexusSelectedDrawableID; // +0x980
};

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

	m_frameSelectionChanged = TheGameLogic->getFrame();

	// set the selected bit on the drawable
	draw->rva002796B8();

	// add to our list of selected drawables
	m_selectedDrawables.push_front( draw );

	// keep our own internal count happy
	++m_selectCount;

	// Donor evaluateSoloNexus role; retail tests the selected objects at +0xFC.
	evaluateSoloNexus( draw );

	// the control needs to update its context sensitive display now
	((BfmeWorldRV *)TheControlBar)->rva0031AA34((int)draw);

	((Rva0029ACA0 *)this)->rva0029ACC7(0);
}

// ZH InGameUI::evaluateSoloNexus (same source in the BFME 1 donor 6583b3c1):
// target 0x0029B967 (126B), called by the matched selectDrawable above.
// Target accesses establish the result at +0x980, the selected list at +0x20,
// Drawable's Object at +0xFC, and template flags at +0x10C. The same two-kind
// short-circuit and single-nexus count support the ZH role; native bits are
// 0x4000/0x8000. getID uses the independently pinned retail 0x0055A88B getter.
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
class Player
{
public:
	unsigned char m_pad[1];
};

class PlayerList
{
public:
	unsigned char m_pad000[0x10];
	Player *m_local; // +0x10
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class GameMessage
{
public:
	void appendBooleanArgument(bool arg);
	void appendObjectIDArgument(ObjectID arg);
};

class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};

class InGameUI167View
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual void w31();
	virtual void w32();
	virtual void w33();
	virtual void w34();
	virtual void w35();
	virtual void w36();
	virtual void w37();
	virtual void w38();
	virtual void w39();
	virtual void w40();
	virtual void w41();
	virtual void w42();
	virtual void w43();
	virtual void w44();
	virtual void w45();
	virtual void w46();
	virtual void w47();
	virtual void w48();
	virtual void w49();
	virtual void w50();
	virtual void w51();
	virtual void w52();
	virtual void w53();
	virtual void w54();
	virtual void w55();
	virtual void w56();
	virtual void w57();
	virtual void w58();
	virtual void w59();
	virtual void w60();
	virtual void w61();
	virtual void w62();
	virtual void w63();
	virtual void w64();
	virtual void w65();
	virtual void w66(Drawable *draw);
	virtual void w67();
	virtual void w68();
};

extern PlayerList *ThePlayerList;
extern InGameUI *TheInGameUI;
extern MessageStream *MessageStreamSubsystem;

bool Rva00498CB1Owner::invoke()
{
	if (m_objectID == OBJECTID_INVALID)
		return false;
	Object *obj = TheGameLogic->findObjectByID(m_objectID);
	if (!obj)
		return false;
	Player *player = obj->getControllingPlayer();
	Player *local = ThePlayerList->m_local;
	if (player && local && player == local)
	{
		((InGameUI167View *)TheInGameUI)->w68();
		GameMessage *msg = MessageStreamSubsystem->appendType(0x3EA);
		msg->appendBooleanArgument(true);
		msg->appendObjectIDArgument(m_objectID);
		Drawable *draw = ((Thing *)obj)->getDrawable();
		if (draw)
			((InGameUI167View *)TheInGameUI)->w66(draw);
		return true;
	}
	return false;
}
