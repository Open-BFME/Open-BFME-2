// ?clientUpdate@LaserUpdate@@UAEXXZ
// ?clientUpdate@LaserUpdate@@UAEXXZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// BFME1 LaserUpdateClientUpdate.cpp donor 575ba2b04743f190f069805fbdc59936123c45da; ZH widening/decaying spine.
// Target 0x00363233..0x0036355C: complete 809B thiscall body.
// Named midpoint sums plus a same-valued endpoint pointer conditional preserve
// retail SSE operand order; all endpoint updates and handle cleanups are retained.
// Target measured deltas: GameClient frame31/find16/destroy29; Object geometry+A8.
// Handle return/assignment use existing BFME2 12-byte call views and conditional cleanup.
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
class Drawable {
public:
    bool rva00272835(int, int);
 __forceinline bool getCurrentWorldspaceClientBonePositions(const char *name, Matrix3D &matrix) const { return const_cast<Drawable *>(this)->rva00272835(reinterpret_cast<int>(name),reinterpret_cast<int>(&matrix)); }
    void setPosition(const Coord3D *);
    const Coord3D *getPosition() const;
    char m_unmodelled_000[0xfc];
    Rva00603BB0ObjectView *m_object;
    Rva00603BB0ObjectView *getObject() const { return m_object; }
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
struct Rva001F3899Arg { float x,y,z; };
class Rva001F3899Slot { public: void set(const Rva001F3899Arg &); };
class ParticleSystem { public: __forceinline void setPosition(const Coord3D *pos) { reinterpret_cast<Rva001F3899Slot *>(this)->set(*reinterpret_cast<const Rva001F3899Arg *>(pos)); } };
class RvaSmartPtr12 {
	public: void rva0004CBC0() throw(); // 0x0004CBC0, the unlink the inline dtor null test calls
private:
 public: RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw(); };
struct BfmeParticleSystemHandle { ~BfmeParticleSystemHandle() throw(); ParticleSystem *m_system; void *m_previous,*m_next; };
struct BfmeW3DParticleHandle {
 BfmeW3DParticleHandle():m_system(0),m_previous(0),m_next(0) {}
 __forceinline ~BfmeW3DParticleHandle() throw() { if(m_system) reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0(); }
 BfmeW3DParticleHandle &operator=(const BfmeW3DParticleHandle &other) throw() {
  *((RvaSmartPtr12 *)this)=*((const RvaSmartPtr12 *)&other);return *this;
 }
 ParticleSystem *m_system; void *m_previous,*m_next;
};
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class ParticleSystemManager {
private: BfmeW3DParticleHandle findParticleSystemByID(ParticleSystemID);
    friend class LaserUpdate;
};
extern ParticleSystemManager *TheParticleSystemManager;
class LaserUpdateModuleData {
public:
    char m_unmodelled_00[8];
    AsciiString m_particleSystemName;
    AsciiString m_parentFireBoneName;
};
class LaserUpdate {
public:
    virtual void clientUpdate();
 Drawable *getDrawable() const { return m_drawable; }
    const LaserUpdateModuleData *m_moduleData;
    Drawable *m_drawable;
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
                Matrix3D matrix(true);
                parent->getCurrentWorldspaceClientBonePositions(data->m_parentFireBoneName.str(),matrix);
                coordSet(&m_startPos,matrix.Get_X_Translation(),matrix.Get_Y_Translation(),matrix.Get_Z_Translation());
            } else {
                coordSet(&m_startPos,parent->getPosition());
                m_startPos.z+=parent->getObject()->getGeometryInfo().getMaxHeightAbovePosition()*0.5f;
            }
            coordSet(&m_endPos,target->getPosition());
            m_endPos.z+=target->getObject()->getGeometryInfo().getMaxHeightAbovePosition()*0.83f;
            BfmeW3DParticleHandle system;
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
