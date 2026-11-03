// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Anim2D constructor/layout rehomed from System/Anim2DConstructor.cpp; target159B/WB C34010.
// ZH constructor guide: Open-BFME-1@575ba2b; native cached dimensions2C/30 and Snapshot ABI retained.
// UI body: retail2A0F19..2A1111 and WB DBEEE0/assert7972; original method spelling remains unknown.
// stlport
#include <list>
// Keep integer construction inline; stlport_deque_int.cpp owns retail's
// out-of-line _Construct<int, int> body at 0x00620140.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void _Construct<int, int>(int *p, const int &value) { new (p) int(value); }
}
#include "GameClient/ClientRandomValue.h"
#define _OPERATOR_NEW_DEFINED_
#include "vector2.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Anim2D;
class Anim2DCollection
{
public:
    void registerAnimation(Anim2D *animation);
};
#include "../../Include/GameClient/Anim2DTemplate.h"
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
// Slot 2 of Anim2D's vtable 0x00C03358 (between the empty loadPostProcess
// and xfer 0x002D71BD): returns the class name string 0x00C03368.
const char *Anim2D::GetSnapshotName() const
{
    return "Anim2D";
}
class GlobalData;
class GameClient;
extern GlobalData *TheWritableGlobalData;
extern GameClient *TheGameClient;
extern Anim2DCollection *TheAnim2DCollection;
// Native2A0F19..2A1111 RET20. WB DBEEE0 locates this member in InGameUI.cpp.
// This prefix view claims only the observed list8D0 and incoming five words;
// the original member spelling and complete InGameUI layout are not asserted.
typedef char InGameUiNativeAnimSize[(sizeof(Anim2D)==0x34)?1:-1];
struct InGameUiAnimExtentView {char pad00[0x2C];int value2C,value30;};
struct InGameUiRandomFields {
 char pad00[0xD80];
 GameClientRandomVariable randomSpeedX,randomSpeedY,randomD98,randomDA4;
};
class InGameUiFrameView {
public:
#define FLOAT_FRAME_SLOT(N) virtual void slot##N();
 FLOAT_FRAME_SLOT(00) FLOAT_FRAME_SLOT(01) FLOAT_FRAME_SLOT(02) FLOAT_FRAME_SLOT(03)
 FLOAT_FRAME_SLOT(04) FLOAT_FRAME_SLOT(05) FLOAT_FRAME_SLOT(06) FLOAT_FRAME_SLOT(07)
 FLOAT_FRAME_SLOT(08) FLOAT_FRAME_SLOT(09) FLOAT_FRAME_SLOT(10) FLOAT_FRAME_SLOT(11)
 FLOAT_FRAME_SLOT(12) FLOAT_FRAME_SLOT(13) FLOAT_FRAME_SLOT(14) FLOAT_FRAME_SLOT(15)
 FLOAT_FRAME_SLOT(16) FLOAT_FRAME_SLOT(17) FLOAT_FRAME_SLOT(18) FLOAT_FRAME_SLOT(19)
 FLOAT_FRAME_SLOT(20) FLOAT_FRAME_SLOT(21) FLOAT_FRAME_SLOT(22) FLOAT_FRAME_SLOT(23)
 FLOAT_FRAME_SLOT(24) FLOAT_FRAME_SLOT(25) FLOAT_FRAME_SLOT(26) FLOAT_FRAME_SLOT(27)
 FLOAT_FRAME_SLOT(28) FLOAT_FRAME_SLOT(29) FLOAT_FRAME_SLOT(30)
#undef FLOAT_FRAME_SLOT
 virtual unsigned int getFrame();
};
class Rva0029B132 {
public:
 Rva0029B132 *rva0029B132();
 Anim2D *m_anim;
 float m_x,m_y;
 unsigned int m_endFrame;
 int m_10;
 float m_vx,m_vy,m_1C;
 int m_20;
};
extern int BfmeLogicFramesPerSecond;
class InGameFloatingAnimationHost {
public:
 void rva002A0F19(Anim2DTemplate *,const ICoord2D *,int,float,float);
private:
 char pad000[0x8D0];
 _STL::list<int> m_8D0;
};
#define INGAMEUI_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\InGameUI.cpp"
void InGameFloatingAnimationHost::rva002A0F19(Anim2DTemplate *animTemplate, const ICoord2D *pos, Int value, Real durationInSeconds, Real lead)
{
	if (animTemplate == 0)
		return;
	if (pos == 0)
		return;
	if (durationInSeconds <= 0.0f)
		return;

	const ICoord2D *originalPosition = pos;
    Anim2D *anim = new Anim2D(animTemplate, TheAnim2DCollection);
	Int randomExtent = GetGameClientRandomValue(20, 30, INGAMEUI_FILE, 7972);
	reinterpret_cast<InGameUiAnimExtentView *>(anim)->value2C = randomExtent;
	reinterpret_cast<InGameUiAnimExtentView *>(anim)->value30 = randomExtent;

	void *mem = operator new(sizeof(Rva0029B132));
	Rva0029B132 *entry = mem ? static_cast<Rva0029B132 *>(mem)->rva0029B132() : 0;
	// The consumed position argument becomes the insertion word in retail.
	pos = reinterpret_cast<const ICoord2D *>(entry);
    if (entry == 0)
		return;

	entry->m_anim = anim;
	entry->m_endFrame = reinterpret_cast<InGameUiFrameView *>(TheGameClient)->getFrame() + BfmeLogicFramesPerSecond * durationInSeconds;
	entry->m_10 = value;
	entry->m_x = originalPosition->x;
	entry->m_y = originalPosition->y;
	entry->m_20 = reinterpret_cast<InGameUiRandomFields *>(TheWritableGlobalData)->randomDA4.getValue() + 0.5f;

	Vector2 dir(0.0f, 0.0f);
	dir[0] = WWMath::Random_Float(-1.0f, 1.0f);
	dir[1] = WWMath::Random_Float(-1.0f, 1.0f);
	dir.Normalize();

	entry->m_vx = reinterpret_cast<InGameUiRandomFields *>(TheWritableGlobalData)->randomSpeedX.getValue() * dir[0];
	entry->m_vy = reinterpret_cast<InGameUiRandomFields *>(TheWritableGlobalData)->randomSpeedY.getValue() * dir[1];
	entry->m_1C = reinterpret_cast<InGameUiRandomFields *>(TheWritableGlobalData)->randomD98.getValue();
	entry->m_x += entry->m_vx * lead;
	entry->m_y += entry->m_vy * lead;

	m_8D0.push_front(reinterpret_cast<const int &>(pos));
}

#undef INGAMEUI_FILE
