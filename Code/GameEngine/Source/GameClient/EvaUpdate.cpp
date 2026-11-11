// cl: /O1 /G7 /EHs /DNDEBUG /MD /arch:SSE /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Eva::update, retail 0x001DE156 (388 bytes). WorldBuilder's Eva::update
// (0x00ACBEB0) supplies the identity; Open-BFME-1 575ba2b EvaUpdate.cpp
// supplies the countdown/audio purpose only. The offsets, the audio dispatch
// slots (+0x6C remove, +0xD0 playing), the +0x68 location list with its +0x6C
// cycle position, the +0x8C location lifetime, the +0x10 delayed reports, the
// GameLogic +0x40 and living-world +0x100 frames and the per-status timer reads
// of the existing g_00DBA4FC owner are BFME2 retail observations. The class
// layout is the one Eva.cpp uses (status records 0x34 bytes at +0x5C, info
// records 0x30 bytes at +0x1C).
//
// Kept in its own unit: the rowed mode-gate leaf 0x001DCD1C is visible here
// (out of line), which keeps the world-frame result in the logic register as
// retail does (mov edi,[edi+0x40]); in Eva.cpp the same visibility would change
// reportEvaEvent, whose retail code reloads the delay after that call.

#include "../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include <list>
// list<int>'s iterator operator-- is inlined here; imported, this unit emits no
// non-retail out-of-line copy of it (STLport body verbatim).
namespace _STL {
template <> __declspec(dllimport) __forceinline
_List_iterator<int, _Nonconst_traits<int> > &_List_iterator<int, _Nonconst_traits<int> >::operator--()
{
	this->_M_decr();
	return *this;
}
}
#include <map>

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

// STLport vector view: inline size() divides the pointer difference.
template <class T> class EvaVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T *begin() const { return m_start; }
	T *end() const { return m_finish; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

// One event's info record (0x30 bytes).
struct Arg001DCDAF
{
	unsigned char m_data[0x30];
};

// One event's status record (0x34 bytes); update counts both timers down by
// the per-frame milliseconds.
extern float g_00DBA4FC;
class Rva001DCDAF
{
public:
	void tick() { m_blockedTime -= g_00DBA4FC; m_aboutToPlayTime -= g_00DBA4FC; }

	Real m_blockedTime;					// +0x00, > 0 blocks the event
	Real m_aboutToPlayTime;					// +0x04, >= 0 when about to play
	unsigned char m_pad08[0x34 - 0x08];
};

#include "../../Include/GameLogic/LivingWorldLogic.h"

struct EvaEventReport;
#include "../../Include/GameClient/Rva001DD70F.h"

class __single_inheritance AudioManager;
extern AudioManager *TheAudio;
class EvaAudioDispatch { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void remove(UnsignedInt);
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual Bool playing(UnsignedInt);
};

typedef _STL::list<int, _STL::allocator<int> > EvaLinkList;
namespace _STL {
template<> EvaLinkList::iterator EvaLinkList::erase(EvaLinkList::iterator);
}
typedef _STL::pair<const int, void *> EvaErasePair;
typedef _STL::_Rb_tree<int, EvaErasePair, _STL::_Select1st<EvaErasePair>, _STL::less<int>, _STL::allocator<EvaErasePair> > EvaEraseTree;
namespace _STL {
template<> void EvaEraseTree::erase(EvaEraseTree::iterator);
}

class Eva
{
public:
	virtual void update();
	void rva001DDF04();					// 0x001DDF04
	Bool internalReportEvaEvent(const EvaEventReport *report);	// 0x001DD468

private:
	unsigned char m_pad04[0x10 - 4];
	_STL::map<int, void *> m_delayedReports;		// +0x10, frame-keyed delayed reports
	EvaVectorView<Arg001DCDAF> m_allEventInfos;		// +0x1C (WB name)
	unsigned char m_pad28[0x5c - 0x28];
	EvaVectorView<Rva001DCDAF> m_eventStatus;		// +0x5C
	EvaLinkList m_queue;					// +0x68
	EvaLinkList::iterator m_queuePosition;			// +0x6C
	int m_70;
	int m_74;
	int m_78;
	Bool m_7C;
	unsigned char m_pad7d[0x8c - 0x7d];
	UnsignedInt m_locationLifetime;				// +0x8C
};

// The rowed leaf (0x001DCD1C, GameLogicModeGateChecks.cpp), visible and out of line.
inline __declspec(noinline) bool GameLogic::rva001DCD1C(void)
{
	return m_110 == 8 || (m_110 == 9 && m_114 != 3);
}

void Eva::update()
{
	if (!(m_eventStatus.size() == m_allEventInfos.size()))
		return;
	AudioManager *audio = TheAudio;
	UnsignedInt handle;
	if (audio && (handle = (UnsignedInt)m_74) >= 5) {
		if (TheGameLogic->rva001DCD1C()) {
			if (m_78 == 0) {
				((EvaAudioDispatch *)audio)->remove(handle);
				m_74 = 1;
				((Rva001DD70F *)((char *)this + 0x10))->rva001DD846();
				audio = TheAudio;
			}
		} else if (m_78 == 1) {
			((EvaAudioDispatch *)audio)->remove(m_74);
			m_74 = 1;
			((Rva001DD70F *)((char *)this + 0x10))->rva001DD846();
			audio = TheAudio;
		}
	}
	EvaLinkList *locations = &m_queue;
	while (!m_queue.empty()) {
		EvaLinkList::iterator first = locations->end();
		--first;
		if ((UnsignedInt)*first + m_locationLifetime >= TheGameLogic->getFrame())
			break;
		if (m_queuePosition == first)
			m_queuePosition = m_queue.end();
		locations->erase(first);
		audio = TheAudio;
	}
	if (m_7C && audio) {
		if (!((EvaAudioDispatch *)audio)->playing(m_74)) {
			GameLogic *logic = TheGameLogic;
			UnsignedInt frame = logic->rva001DCD1C() ? TheLivingWorldLogic->field100 : logic->getFrame();
			if (frame > 2)
				rva001DDF04();
		}
	}
	Rva001DCDAF *status = m_eventStatus.begin(), *end = m_eventStatus.end();
	while (status != end) {
		status->tick();
		++status;
	}
	while (!m_delayedReports.empty()) {
		if ((UnsignedInt)m_delayedReports.begin()->first > TheGameLogic->getFrame())
			break;
		internalReportEvaEvent((const EvaEventReport *)&m_delayedReports.begin()->second);
		m_delayedReports.erase(m_delayedReports.begin());
	}
}
