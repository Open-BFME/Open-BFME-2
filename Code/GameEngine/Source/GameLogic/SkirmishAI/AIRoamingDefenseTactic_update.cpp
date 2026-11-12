// cl: /O1 /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "AIRoamingDefenseTactic" skirmish-AI tactic (vtable 0x008720E8; ctor
// 0x005AABC6 in Rva004ECECDTacticCtors.cpp, dtor 0x005AAB91 and ??_G, slot 9
// 0x005AADA7 in Rva004ECECDTacticCreate.cpp). Base chain, all
// address-derived: Rva005DCC24 over Rva005DC73C over the AITactic.cpp object
// Rva004ECECD. +0x58 is "roaming". The owner's TheSkirmishAIManager record
// keeps two keys: AIRoamingDefenseTactic_IsRunning and
// AIRoamingDefenseTactic_NextLogicFrameRun.
//
//   0x005AAC35  slot 1: never for an owner that 0x002A9BF2 answers; the first
//               time only schedule the next run 5 * g_Va00DBA4E4 frames on;
//               then once not running and the frame is reached
//   0x005AAD26  slot 2: clear both keys
//   0x005AADD9  slot 3: set the running key, then the AITactic's slot 3
//   0x005AABA5  slot 5: xfer: the AITactic's, then +0x58
//   0x005AAB9C  slot 6: start and mark roaming
//   0x005AB085  slot 7 (WB AIRoamingDefenseTactic::update): while roaming, send the first idle, unbusy (status
//               0x5A clear) owner unit of the owner's player to roam
//               (0x005AAE3F), then finish. The owner argument of the
//               0x002A8F24 lookup is an equal-arm conditional (late-folded
//               ?:), which reproduces retail's register order (W7-R1 lever).
//   The other slots are rowed in their own units; only slot 7 is defined here.
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
struct Coord3DBase;

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_5A = 0x5A
};

class Rva005AAB91AI
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual bool isIdle();		// slot 110 (+0x1B8)
};

class Team;
class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	char m_pad000[0x258];
	Rva005AAB91AI *m_ai;		// +0x258
	char m_pad25C[0x304 - 0x25C];
	Team *m_304;			// +0x304
};

extern GameLogic *TheGameLogic;

#include "../../../Include/Common/Rva002A8AB1Record.h"

struct Rva005AAB91IDs
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

#include "../../../Include/Common/Rva005C4AD1LeaField.h"

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

#include "../../../Include/Common/Player.h"

#include "../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

// 0x004ED748 on the tactic base is rowed as AITactic::end(bool, bool).
#include "../../../Include/Common/AITactic.h"

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual bool appliesTo(void *request);
	virtual void v2();
	virtual bool v3(void *unit, int count);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void update();
	virtual void v8();
	virtual Rva004ECECD *create();
};

class Rva005DC73C : public Rva004ECECD
{
public:
	virtual ~Rva005DC73C();
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x24 - 0x11];
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIRoamingDefenseTactic : public Rva005DC73C
{
public:
	virtual ~AIRoamingDefenseTactic();
	virtual bool appliesTo(void *request);
	virtual void v2();
	virtual bool v3(void *unit, int count);
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void update();
	void roam(Object *unit);	// 0x005AAE3F (row name)
private:
	bool m_roaming;		// +0x58
};

void AIRoamingDefenseTactic::update()
{
	if (!m_roaming)
		return;
	IntMap *objects = *(IntMap **)TheSkirmishAIManager->rva002A8F24( (m_roaming ? m_owner : m_owner));
	for (unsigned int i = 0; i < objects->bucket_count(); ++i) {
		Rva005AAB91IDs *ids = (Rva005AAB91IDs *)((Rva005C4AD1LeaField *)objects)->get();
		Object *obj = TheGameLogic->findObjectByID(ids->m_begin[i]);
		if (obj && obj->m_ai->isIdle() && !obj->testStatus(OBJECT_STATUS_5A)
			&& obj->m_304 == m_owner->m_defaultTeam) {
			roam(obj);
			break;
		}
	}
	reinterpret_cast<AITactic *>(static_cast<Rva004ECECD *>(this))->end(false, false);
}
