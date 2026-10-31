// ?clientUpdate@LaserUpdate@@UAEXXZ
// ?clientUpdate@LaserUpdate@@UAEXXZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// BFME1 LaserUpdateClientUpdate.cpp donor 575ba2b04743f190f069805fbdc59936123c45da; ZH widening/decaying spine.
// Target 0x00363233..0x0036355C: complete 809B thiscall body.
// Named midpoint sums plus a same-valued endpoint pointer conditional preserve
// retail SSE operand order; all endpoint updates and handle cleanups are retained.
// Target measured deltas: GameClient frame31/find16/destroy29; Object geometry+A8.
// Handle return/assignment use existing BFME2 12-byte call views and conditional cleanup.
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
class GeometryInfo { public: float getMaxHeightAbovePosition() const; };
#include "matrix3d.h"
static inline void coordSet(Coord3D *to,const Coord3D *from) {to->x=from->x;to->y=from->y;to->z=from->z;}
static inline void coordSet(Coord3D *to,float x,float y,float z) {to->x=x;to->y=y;to->z=z;}
static inline void coordAdd(Coord3D *to,const Coord3D *from) {to->x=to->x+from->x;to->y=to->y+from->y;to->z=to->z+from->z;}
static inline void coordScale(Coord3D *to,float scale) {to->x*=scale;to->y*=scale;to->z*=scale;}
class Rva00603BB0ObjectView {
public:
    char m_unmodelled_000[0xa8];
    const GeometryInfo &getGeometryInfo() const { return *(const GeometryInfo *)((const char *)this+0xa8); }
};
class Drawable
{
public:
	bool rva00272835(int, int);
	__forceinline bool getCurrentWorldspaceClientBonePositions(const char *name, Matrix3D &matrix) const { return const_cast<Drawable *>(this)->rva00272835(reinterpret_cast<int>(name),reinterpret_cast<int>(&matrix)); }
	void setPosition(const Coord3D *);
	const Coord3D *getPosition() const;
	Rva00603BB0ObjectView *getObject() const { return m_object; }
	char m_unmodelled_000[0xfc]; // +0x00
	Rva00603BB0ObjectView *m_object; // +0xFC
};
class GameClient {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10();
    virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();
 virtual Drawable *findDrawableByID(unsigned);
    virtual void slot17(); virtual void slot18(); virtual void slot19();
 virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
 virtual void slot24();virtual void slot25();virtual void slot26();virtual void slot27();virtual void slot28();
    virtual void destroyDrawable(Drawable *);
    virtual void slot30(); virtual unsigned getFrame();
};
extern GameClient *TheGameClient;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
struct Rva001F3899Arg { float x,y,z; };
class Rva001F3899Slot { public: void set(const Rva001F3899Arg &); };
class ParticleSystem
{
public:
	__forceinline void setPosition(const Coord3D *pos) { reinterpret_cast<Rva001F3899Slot *>(this)->set(*reinterpret_cast<const Rva001F3899Arg *>(pos)); }
	char m_pad00[0xA8];
	ParticleSystemID m_systemID; // +0xA8 +0xA8, verified by native initLaser loads.
};
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw(); // 0x0004CBC0, the unlink the inline dtor null test calls
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw();
};
class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle():m_system(0),m_previous(0),m_next(0) {}
	__forceinline ~BfmeParticleSystemHandle() throw() { if(m_system) ((RvaSmartPtr12 *)this)->rva0004CBC0(); }
	BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other) throw() {
	 *((RvaSmartPtr12 *)this)=*((const RvaSmartPtr12 *)&other);return *this;
	}
	ParticleSystem *m_system; // +0x00
	void *m_previous; // +0x04
	void *m_next; // +0x08
};
class ParticleSystemTemplate;
class AsciiString;
class ParticleSystemManager
{
private:
	friend class LaserUpdate;
public:
	void destroyParticleSystemByID(ParticleSystemID id);
private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *,bool);
};
extern ParticleSystemManager *TheParticleSystemManager;
class __declspec(novtable) LaserUpdateModuleData : public Snapshot {
public:
    virtual ~LaserUpdateModuleData();
    unsigned char m_pad[0x08 - 4];
    AsciiString m_particleSystemName;
    AsciiString m_parentFireBoneName;
    bool m_parentFireBoneOnTurret;
    unsigned char m_pad11[3];
    AsciiString m_targetParticleSystemName;
    float m_rva00603FE0LifetimeMsec;
};
enum NameKeyType { NK_UNKNOWN = 0 };
class Object;
class Rva0049B47C {
public:
    virtual ~Rva0049B47C();
protected:
    const LaserUpdateModuleData *m_moduleData;
    Drawable *m_drawable;
};
class LaserUpdate : public Rva0049B47C {
public:
    virtual ~LaserUpdate();
    virtual void clientUpdate();
    Drawable *getDrawable() const { return m_drawable; }
    const LaserUpdateModuleData *getLaserUpdateModuleData() const { return m_moduleData; }
    float getCurrentLaserRadius() const;
    void initLaser(const Object *parent, const Coord3D *startPos, const Coord3D *endPos, int sizeDeltaFrames);
    void initFromDrawables(void *primary, Drawable *parent, Drawable *target, void *d);
    static NameKeyType rva000363102();
    Coord3D m_startPos, m_endPos;
    bool m_dirty;
    char m_pad25[3];
    ParticleSystemID m_particleSystemID, m_targetParticleSystemID;
    bool m_widening, m_decaying;
    char m_pad32[2];
    unsigned m_widenStartFrame, m_widenFinishFrame;
    float m_currentWidthScalar;
    unsigned m_decayStartFrame, m_decayFinishFrame;
    unsigned m_rva00603BB0ExpiryFrame;
    unsigned m_parentID, m_targetID;
};

static void InitLaserMatrix3D(Matrix3D &matrix3D, bool init)
{
    if (init)
        matrix3D.Make_Identity();
}

void LaserUpdate::clientUpdate()
{
    const LaserUpdateModuleData *data=m_moduleData;
    unsigned now=TheGameClient->getFrame();
    if(now>m_rva00603BB0ExpiryFrame) goto expired;
    if(m_decaying) {
        m_currentWidthScalar=1.0f-(float)(now-m_decayStartFrame)/(float)(m_decayFinishFrame-m_decayStartFrame);
        m_dirty=true;
        if(m_currentWidthScalar<=0.0f) {
            m_currentWidthScalar=0.0f;
expired:
            TheGameClient->destroyDrawable(m_drawable); return;
        }
    } else if(m_widening) {
        m_currentWidthScalar=(float)(now-m_widenStartFrame)/(float)(m_widenFinishFrame-m_widenStartFrame);
        m_dirty=true;
        if(m_currentWidthScalar>=1.0f) { m_currentWidthScalar=1.0f; m_widening=false; }
    }
    m_dirty=true;
    if(m_parentID && m_targetID) {
        Drawable *parent=TheGameClient->findDrawableByID(m_parentID);
        Drawable *target=TheGameClient->findDrawableByID(m_targetID);
        if(parent && target) {
            if(!data->m_parentFireBoneName.isEmpty()) {
                Matrix3D matrix;
                InitLaserMatrix3D(matrix, true);
                parent->getCurrentWorldspaceClientBonePositions(data->m_parentFireBoneName.str(),matrix);
                coordSet(&m_startPos,matrix.Get_X_Translation(),matrix.Get_Y_Translation(),matrix.Get_Z_Translation());
            } else {
                coordSet(&m_startPos,parent->getPosition());
                m_startPos.z+=parent->getObject()->getGeometryInfo().getMaxHeightAbovePosition()*0.5f;
            }
            coordSet(&m_endPos,target->getPosition());
            m_endPos.z+=target->getObject()->getGeometryInfo().getMaxHeightAbovePosition()*0.83f;
            BfmeParticleSystemHandle system;
            if(m_particleSystemID) {
                system=TheParticleSystemManager->findParticleSystemByID(m_particleSystemID);
                if(system.m_system) system.m_system->setPosition(&m_startPos);
            }
            if(m_targetParticleSystemID) {
                system=TheParticleSystemManager->findParticleSystemByID(m_targetParticleSystemID);
                if(system.m_system) system.m_system->setPosition(&m_endPos);
            }
            Coord3D pos;coordSet(&pos,&m_startPos);float x=pos.x+m_endPos.x;const Coord3D *end=parent ? &m_endPos : &m_endPos;float y=pos.y+end->y;float z=pos.z+end->z;pos.x=x;pos.y=y;pos.z=z;coordScale(&pos,0.5f);
            getDrawable()->setPosition(&pos);
        }
    }
}
