// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// GeneralsMD Anim2D.cpp constructor guide at Open-BFME-1@575ba2b.
// BFME2 WB C34010 names the same constructor; native2D6D63..2D6E02
// fixes all accessed members and adds cached size at2C/30 after registration.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Anim2D;
class Anim2DCollection
{
public:
    void registerAnimation(Anim2D *animation);
};
class Anim2DTemplate
{
public:
    unsigned short getNumFrames() const { return m_numFrames; }
    unsigned short getNumFramesBetweenUpdates() const { return m_framesBetweenUpdates; }
    bool isRandomizedStartFrame() const { return m_randomizeStartFrame; }
private:
    char m_unreconstructed000[0x10];
    unsigned short m_numFrames, m_framesBetweenUpdates;
    int m_animMode;
    bool m_randomizeStartFrame;
};
class Anim2D : public Snapshot
{
public:
    Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collectionSystem);
    void randomizeCurrentFrame();
    void reset();
    unsigned int getCurrentFrameHeight() const;
    unsigned int getCurrentFrameWidth() const;
protected:
    virtual ~Anim2D();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    unsigned short m_currentFrame;
    unsigned int m_lastUpdateFrame;
    Anim2DTemplate *m_template;
    unsigned char m_status;
    unsigned short m_minFrame, m_maxFrame;
    unsigned int m_framesBetweenUpdates;
    float m_alpha;
    Anim2DCollection *m_collectionSystem;
    Anim2D *m_collectionSystemNext, *m_collectionSystemPrev;
    unsigned int m_cachedWidth, m_cachedHeight;
};
Anim2D::Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collectionSystem)
{
    m_currentFrame=0;
    m_minFrame=0;
    m_template=animTemplate;
    m_status=0;
    m_alpha=1.0f;
    if (m_template->isRandomizedStartFrame()) randomizeCurrentFrame();
    else reset();
    m_maxFrame=m_template->getNumFrames()-1;
    m_framesBetweenUpdates=m_template->getNumFramesBetweenUpdates();
    m_collectionSystemNext=0;
    m_collectionSystemPrev=0;
    m_lastUpdateFrame=0;
    m_collectionSystem=collectionSystem;
    if(m_collectionSystem) m_collectionSystem->registerAnimation(this);
    m_cachedHeight=getCurrentFrameHeight();
    m_cachedWidth=getCurrentFrameWidth();
}
