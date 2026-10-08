// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "AIRoamingDefenseTactic" skirmish-AI tactic (vtable 0x008720E8; ctor
// 0x005AABC6 in Rva004ECECDTacticCtors.cpp, dtor 0x005AAB91 and ??_G, slot 9
// 0x005AADA7 in Rva004ECECDTacticCreate.cpp). Base chain, all
// address-derived: Rva005DCC24 over AITacticOffensive over the AITactic.cpp object
// AITactic. +0x58 is "roaming". The owner's TheSkirmishAIManager record
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
//   0x005AB085  slot 7 (not here yet): while roaming, send the first idle, unbusy (status
//               0x5A clear) owner unit of the owner's player to roam
//               (0x005AAE3F), then finish
#include "ascii_string.h"

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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};

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

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	char m_pad000[0x258];
	Rva005AAB91AI *m_ai;		// +0x258
	char m_pad25C[0x304 - 0x25C];
	int m_304;			// +0x304
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned int getFrame() const { return m_40; }
	char m_pad000[0x40];
	unsigned int m_40;		// +0x40, the frame
};
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
};

struct Rva005AAB91IDs
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

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

class Player
{
public:
	char m_pad000[0x2EC];
	int m_2EC;			// +0x2EC
};

class Rva002A9BF2
{
public:
	void *rva002A9BF2();
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, int count);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x24 - 0x11];
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIRoamingDefenseTactic : public AITacticOffensive
{
public:
	virtual ~AIRoamingDefenseTactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, int count);
	virtual void xfer(Xfer *xfer);
	virtual void run();
private:
	bool m_roaming;		// +0x58
};

bool AIRoamingDefenseTactic::canRun(void *)
{
	if (!((Rva002A9BF2 *)m_owner)->rva002A9BF2()) {
		Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
		int running = record->rva002C7196(AsciiString("AIRoamingDefenseTactic_IsRunning"));
		unsigned int next = record->rva002C7196(AsciiString("AIRoamingDefenseTactic_NextLogicFrameRun"));
		if (!next) {
			record->rva002C717E(AsciiString("AIRoamingDefenseTactic_NextLogicFrameRun"),
				g_Va00DBA4E4 * 5 + TheGameLogic->getFrame());
		} else if (!running && TheGameLogic->getFrame() >= next) {
			return true;
		}
	}
	return false;
}

void AIRoamingDefenseTactic::cleanUp()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	record->rva002C717E(AsciiString("AIRoamingDefenseTactic_IsRunning"), 0);
	record->rva002C717E(AsciiString("AIRoamingDefenseTactic_NextLogicFrameRun"), 0);
}

bool AIRoamingDefenseTactic::initializeTeamTemplate(void *unit, int count)
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	record->rva002C717E(AsciiString("AIRoamingDefenseTactic_IsRunning"), 1);
	return AITactic::initializeTeamTemplate(unit, count);
}

void AIRoamingDefenseTactic::xfer(Xfer *xfer)
{
	AITactic::xfer(xfer);
	*xfer == m_roaming;
}

void AIRoamingDefenseTactic::run()
{
	m_running = true;
	m_roaming = true;
}
