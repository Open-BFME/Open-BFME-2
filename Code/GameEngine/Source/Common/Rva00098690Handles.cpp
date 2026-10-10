// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00098690@Rva00098690@@QAEXXZ, retail 0x00098690, 87 bytes.
// Two contiguous BfmeParticleSystemHandles at +0x4C/+0x58: if m_system then
// get()->destroy() (null-or-Make fallback via pinned Make001FCBD7 then rowed
// destroy 0x001F462C), then if still set dtor via rowed 0x0004CBC0 and clear.
// Spelt from W3DTankTruckDraw::tossEmitters precedent (volatile m_system
// preserves retail's redundant null-or-Make chases that /O1 folds).
// Callees rowed/pinned; callers 0x000986E7 (dtor) and 0x0009873C. Owner
// unproven so honest address-derived struct (no vtable).

#include "ascii_string.h"

class RvaSmartPtr12
{
public:
    RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw();
    void rva0004CBC0() throw();
};

class ParticleSystem
{
public:
	void destroy();
	void rva001F45F4(bool flag);
};

ParticleSystem *Make001FCBD7();

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw() { if (m_system) reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0(); }
    BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other)
    { reinterpret_cast<RvaSmartPtr12 *>(this)->operator=(*reinterpret_cast<const RvaSmartPtr12 *>(&other)); return *this; }
	ParticleSystem *volatile m_system;
	void *m_previous;
	void *m_next;
	ParticleSystem *get() const
	{
		ParticleSystem *target = m_system;
		if (!target)
            return Make001FCBD7();
        return target;
	}
};

class GameClient;
extern GameClient *TheGameClient;
class W3DFireClientView { public: virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B(); virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v1A(); virtual void v1B(); virtual void v1C(); virtual void v1D(); virtual void v1E(); virtual unsigned int getFrame(); };
class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_distribution;
	float m_low;
	float m_high;
};

class Rva00098690
{
public:
	void rva00098690();
    bool rva0009873C();
	void rva00098894();
	__forceinline bool isScorchDue() const { return ((W3DFireClientView *)TheGameClient)->getFrame() > m_nextScorchFrame; }
private:
	unsigned char m_pad[0x2C];
	bool m_active; // +0x2C
	GameClientRandomVariable m_delayFrames; // +0x30
	GameClientRandomVariable m_scorchRadius; // +0x3C
	float m_scorchChance; // +0x48
	BfmeParticleSystemHandle m_first; // +0x4C
	BfmeParticleSystemHandle m_second; // +0x58
	unsigned int m_nextScorchFrame; // +0x64
};

void Rva00098690::rva00098690()
{
	if (m_first.m_system)
	{
		m_first.get()->destroy();
		if (m_first.m_system)
		{
			reinterpret_cast<RvaSmartPtr12 *>(&m_first)->rva0004CBC0();
			m_first.m_system = 0;
		}
	}
	if (m_second.m_system)
	{
		m_second.get()->destroy();
		if (m_second.m_system)
		{
			reinterpret_cast<RvaSmartPtr12 *>(&m_second)->rva0004CBC0();
			m_second.m_system = 0;
		}
	}
}

class Rva00564E0D { public: AsciiString rva00564E0D(); };
namespace FXParticleSystem { class ParticleSystemTemplate { public: AsciiString getTextureFilename() const; }; }
class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
    ParticleSystemTemplate *findTemplate(const AsciiString &) const;
    BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *, bool);
};
extern ParticleSystemManager *TheParticleSystemManager;
class GameLODManager { public: __forceinline int getLevel() const { return level; } char unmodelled[0x1778]; int level; };
extern GameLODManager *TheGameLODManager;
class Rva001F384AByteZeroSetter { public: void disable(); };

// Native 9873C..98894 RET0: same complete receiver as the 87-byte cleanup
// above. The original product name is unknown; two names at0C/10 and two
// handles at4C/58 are independently witnessed by the called provider bodies.
bool Rva00098690::rva0009873C()
{
    rva00098690();
    if (TheParticleSystemManager)
    {
        AsciiString name = reinterpret_cast<Rva00564E0D *>(this)->rva00564E0D();
        const ParticleSystemTemplate *first = TheParticleSystemManager->findTemplate(name);
        if (first && !m_first.m_system)
        {
            m_first = TheParticleSystemManager->createParticleSystem(first, true);
            m_first.get()->rva001F45F4(false);
            reinterpret_cast<Rva001F384AByteZeroSetter *>(m_first.get())->disable();
        }
        if (TheGameLODManager && TheGameLODManager->level > 1)
        {
            AsciiString other = reinterpret_cast<const FXParticleSystem::ParticleSystemTemplate *>(this)->getTextureFilename();
            const ParticleSystemTemplate *second = TheParticleSystemManager->findTemplate(other);
            if (second && !m_second.m_system)
            {
                m_second = TheParticleSystemManager->createParticleSystem(second, true);
                m_second.get()->rva001F45F4(false);
                reinterpret_cast<Rva001F384AByteZeroSetter *>(m_second.get())->disable();
            }
        }
    }
    return true;
}

// Native 98894..98A53 RET0, same receiver. GameClientRandomValueReal's file
// argument is retail's W3DFire.cpp path (lines 162/166/167), so this unit is
// W3DFire.cpp; the class and method names stay address-derived. Behaviour:
// re-create the particle systems when the first handle is gone, then, while
// active, at LOD above 1 and once the client frame passes the stored frame,
// re-arm that frame by a random delay and give each burning cell of the fire
// logic set (+0x84 of the 0xDFEC68 global) a random chance to add a scorch
// (type 8 when global data +0x138 is 1, else 7) of random radius at a random
// +-10 offset, one unit above the ground.
class Vector3
{
public:
	float X, Y, Z;
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
};
struct W3DFireCoord { float x, y, z; void set(float ax, float ay, float az) { x = ax; y = ay; z = az; } };
enum Scorches { SCORCH_7 = 7, SCORCH_8 = 8 };
class BaseHeightMapRenderObjClass { public: void addScorch(Vector3 location, float radius, Scorches type); };
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
struct Coord3D;
class W3DFireTerrainView { public: virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const; };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct W3DFireGlobalView { char gap[0x138]; int m_138; };
float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);
#define W3DFIRE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DFire.cpp"
namespace _STL
{
	struct _Rb_tree_node_base { int _M_color; _Rb_tree_node_base *_M_parent; _Rb_tree_node_base *_M_left; _Rb_tree_node_base *_M_right; };
	template <class _Dummy> class _Rb_global { public: static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *); };
}
struct W3DFireCellNode : _STL::_Rb_tree_node_base { int m_key0; int m_key1; int m_cellX; int m_cellY; };
struct W3DFireCellSet { _STL::_Rb_tree_node_base *m_header; unsigned int m_count; };
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
struct W3DFireLogicView { char gap[0x84]; W3DFireCellSet m_cells; };

void Rva00098690::rva00098894()
{
	if (!m_first.m_system)
		rva0009873C();
	if (!m_active || !TheGameLODManager)
		return;
	int lodLevel = TheGameLODManager->level;
	if (lodLevel <= 1)
		return;
	bool due = ((W3DFireClientView *)TheGameClient)->getFrame() > m_nextScorchFrame;
	if (!due)
		return;
	int delay = (int)m_delayFrames.getValue();
	m_nextScorchFrame = ((W3DFireClientView *)TheGameClient)->getFrame() + delay;
	W3DFireCellSet &cells = ((W3DFireLogicView *)TheTriggerManager)->m_cells;
	if (!(cells.m_count > 0))
		return;
	for (_STL::_Rb_tree_node_base *it = cells.m_header->_M_left; it != cells.m_header; it = _STL::_Rb_global<bool>::_M_increment(it))
	{
		W3DFireCellNode *cell = (W3DFireCellNode *)it;
		float chance = m_scorchChance;
		if (chance > GetGameClientRandomValueReal(0.0f, 1.0f, W3DFIRE_FILE, 162) && TheTerrainRenderObject)
		{
			W3DFireCoord pos;
			pos.set(
				GetGameClientRandomValueReal(-10.0f, 10.0f, W3DFIRE_FILE, 166) + cell->m_cellX,
				GetGameClientRandomValueReal(-10.0f, 10.0f, W3DFIRE_FILE, 167) + cell->m_cellY,
				((W3DFireTerrainView *)TheTerrainLogic)->getGroundHeight((float)cell->m_cellX, (float)cell->m_cellY) + 1.0f);
			Scorches type = SCORCH_7;
			if (((W3DFireGlobalView *)TheWritableGlobalData)->m_138 == 1)
				type = SCORCH_8;
			TheTerrainRenderObject->addScorch(Vector3(pos.x, pos.y, pos.z), m_scorchRadius.getValue(), type);
		}
	}
}
