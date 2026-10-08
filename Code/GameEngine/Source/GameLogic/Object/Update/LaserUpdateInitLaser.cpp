// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 LaserUpdate_initLaser.cpp donor 9cbfb551fe20dae985f91f2319d8997287b6a705;
// ZH initLaser supplies the widening/decaying, bone and particle initialization semantics.
// Target identity: WB 0xF16CF0 names LaserUpdate::initLaser and pairs by callgraph;
// native 0x36355C is the complete 759B four-argument body (ret 16).
// Target layout/calls: GameClient frame31/destroy29, ParticleSystem ID+A8,
// 12B handles and frame-per-millisecond global g_00DBA500 measured in retail.
// Module layout carried from BFME1, corroborated by native field accesses.
// Bone-on-turret callee identity uses native Object drawable/AI guards and
// pristine-bone/turret-transform spine; WB's automatic Matrix3D pairing is not evidence.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class GeometryInfo { public: float getMaxHeightAbovePosition() const; };
class Matrix3D { public: float m[12];
 __forceinline Matrix3D(bool identity) { if(identity) {
 m[0]=1.0F;m[1]=0;m[2]=0;m[3]=0;m[4]=0;m[5]=1.0F;m[6]=0;m[7]=0;m[8]=0;m[9]=0;m[10]=1.0F;m[11]=0; } }
 float Get_X_Translation() const {return m[3];}
 float Get_Y_Translation() const {return m[7];}
 float Get_Z_Translation() const {return m[11];}
};
static inline void coordSet(Coord3D *to,const Coord3D *from) {to->x=from->x;to->y=from->y;to->z=from->z;}
static inline void coordSet(Coord3D *to,float x,float y,float z) {to->x=x;to->y=y;to->z=z;}
static inline void coordAdd(Coord3D *to,const Coord3D *from) {to->x=to->x+from->x;to->y=to->y+from->y;to->z=to->z+from->z;}
static inline void coordScale(Coord3D *to,float scale) {to->x*=scale;to->y*=scale;to->z*=scale;}
class Rva00603BB0ObjectView {
public:
    char m_unmodelled_000[0xa8];
    const GeometryInfo &getGeometryInfo() const { return *(const GeometryInfo *)((const char *)this+0xa8); }
};
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
class Drawable {
public:
    bool rva00272835(int, int);
 __forceinline bool getCurrentWorldspaceClientBonePositions(const char *name, Matrix3D &matrix) const { return const_cast<Drawable *>(this)->rva00272835(reinterpret_cast<int>(name),reinterpret_cast<int>(&matrix)); }
    void setPosition(const Coord3D *);
    const Coord3D *getPosition() const { return ((const BFMERopeDrawable *)this)->getPosition(); }
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
extern float g_00DBA500; // Existing frame/millisecond scalar; native Laser loads this writable global.
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
struct Rva001F3899Arg { float x,y,z; };
class Rva001F3899Slot { public: void set(const Rva001F3899Arg &); };
class ParticleSystem { public:
 ParticleSystemID getSystemID() const { return *reinterpret_cast<const ParticleSystemID *>(reinterpret_cast<const char *>(this)+0xA8); } __forceinline void setPosition(const Coord3D *pos) { reinterpret_cast<Rva001F3899Slot *>(this)->set(*reinterpret_cast<const Rva001F3899Arg *>(pos)); } };
class RvaSmartPtr12 { public: RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw(); void rva0004CBC0() throw(); };
class BfmeParticleSystemHandle { public:
 BfmeParticleSystemHandle():m_system(0),m_previous(0),m_next(0) {}
 __forceinline ~BfmeParticleSystemHandle() throw() { if(m_system) ((RvaSmartPtr12 *)this)->rva0004CBC0(); }
 BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other) throw() {
  *((RvaSmartPtr12 *)this)=*((const RvaSmartPtr12 *)&other);return *this;
 }
 ParticleSystem *m_system; void *m_previous,*m_next;
};

class ParticleSystemTemplate;
class ParticleSystemManager {
public:
 ParticleSystemTemplate *findTemplate(const AsciiString &) const;
 BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *,bool);
private: BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);
    friend class LaserUpdate;
};
extern ParticleSystemManager *TheParticleSystemManager;
class LaserUpdateModuleData {
public:
    char m_unmodelled_00[8];
    AsciiString m_particleSystemName;
    AsciiString m_parentFireBoneName;
 bool m_parentFireBoneOnTurret; char m_pad11[3];
 AsciiString m_targetParticleSystemName; float m_rva00603FE0LifetimeMsec;
};
class Object;
class LaserUpdate {
public:
    virtual void clientUpdate();
 Drawable *getDrawable() const { return m_drawable; }
    const LaserUpdateModuleData *getLaserUpdateModuleData() const { return m_moduleData; }
 void initLaser(const Object *parent,const Coord3D *startPos,const Coord3D *endPos,int sizeDeltaFrames);
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


enum WhichTurretType { TURRET_INVALID=-1,TURRET_MAIN=0 };
class Object { public:
 bool getSingleLogicalBonePosition(const char *,Coord3D *,Matrix3D *) const;
 bool getSingleLogicalBonePositionOnTurret(WhichTurretType,const char *,Coord3D *,Matrix3D *) const;
};
void LaserUpdate::initLaser(const Object *parent, const Coord3D *startPos, const Coord3D *endPos, int sizeDeltaFrames)
{
    const LaserUpdateModuleData *data = getLaserUpdateModuleData();
    BfmeParticleSystemHandle system;
    if( sizeDeltaFrames > 0 )
    {
        m_widening = true;
        m_widenStartFrame = TheGameClient->getFrame();
        m_widenFinishFrame = m_widenStartFrame + sizeDeltaFrames;
        m_currentWidthScalar = 0.0f;
    }
    else if( sizeDeltaFrames < 0 )
    {
        m_decaying = true;
        m_decayStartFrame = TheGameClient->getFrame();
        m_decayFinishFrame = m_decayStartFrame - sizeDeltaFrames;
        m_currentWidthScalar = 1.0f;
    }

    m_rva00603BB0ExpiryFrame = (unsigned)((float)TheGameClient->getFrame() + g_00DBA500 * data->m_rva00603FE0LifetimeMsec);

    if( parent && !data->m_parentFireBoneName.isEmpty() )
    {
        if( data->m_parentFireBoneOnTurret )
        {
            if( !parent->getSingleLogicalBonePositionOnTurret( TURRET_MAIN, data->m_parentFireBoneName.str(), &m_startPos, 0 ) )
            {
                TheGameClient->destroyDrawable( getDrawable() );
                return;
            }
        }
        else if( !parent->getSingleLogicalBonePosition( data->m_parentFireBoneName.str(), &m_startPos, 0 ) )
        {
            TheGameClient->destroyDrawable( getDrawable() );
            return;
        }
    }
    else if( startPos )
    {
        m_startPos = *startPos;
    }
    else
    {
        TheGameClient->destroyDrawable( getDrawable() );
        return;
    }

    if( endPos )
    {
        m_endPos = *endPos;
    }
    else
    {
        TheGameClient->destroyDrawable( getDrawable() );
        return;
    }

    if( !m_particleSystemID )
    {
        if( !data->m_particleSystemName.isEmpty() )
        {
            const ParticleSystemTemplate *tmp = TheParticleSystemManager->findTemplate( data->m_particleSystemName );
            if( tmp )
            {
                system = TheParticleSystemManager->createParticleSystem( tmp, true );
                if( system.m_system )
                    m_particleSystemID = system.m_system->getSystemID();
            }
        }

        if( !data->m_targetParticleSystemName.isEmpty() )
        {
            const ParticleSystemTemplate *tmp = TheParticleSystemManager->findTemplate( data->m_targetParticleSystemName );
            if( tmp )
            {
                system = TheParticleSystemManager->createParticleSystem( tmp, true );
                if( system.m_system )
                    m_targetParticleSystemID = system.m_system->getSystemID();
            }
        }
    }

    if( m_particleSystemID )
    {
        system = TheParticleSystemManager->findParticleSystemByID( m_particleSystemID );
        if( system.m_system )
            system.m_system->setPosition( &m_startPos );
    }

    if( m_targetParticleSystemID )
    {
        system = TheParticleSystemManager->findParticleSystemByID( m_targetParticleSystemID );
        if( system.m_system )
            system.m_system->setPosition( &m_endPos );
    }

    Coord3D posToUse;
    coordSet(&posToUse,startPos);
    coordAdd(&posToUse,endPos);
    coordScale(&posToUse,0.5f);
    getDrawable()->setPosition( &posToUse );
    m_dirty = true;
}
