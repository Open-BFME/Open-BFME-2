// ?rva00058591@MilesAudioManager@@UAEXIIH@Z
// partial score=0.6 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00058591@MilesAudioManager@@UAEXIIH@Z
// Retail 0x00058591..0x0005876E (477 bytes); MilesAudioManager vtable entry
// at 0x007C55F4.
// Under the manager mutex (+0x9D4) clears the per-sound pause flag of every
// playing sound (+0xA40 list when affect has 0x02) and 3D sound (+0xA44 when
// affect has 0x04) whose event view type is in viewMask, and of every stream
// (+0xA48) whose event also has a sound class in affect, and lets each one
// resume (rowed pauseResumeSound); the flag is +0x4A when affect has 0x20 else
// +0x49. With affect 0x10 the view bits leave the +0x694 (0x20) or +0x690
// mask; the pending requests are cleared the same way (rowed 0x000577E3 with
// false) and unless keepMasks is set the per-view-type affect masks +0x6C0
// (0x20; affect without 0x20) or +0x6B4 lose affect for the views in viewMask.
// This is the resume half of Zero Hour's MilesAudioManager pause/resume pair
// with BFME 2's view-type mask; the name stays address-derived.
// Evidence (target): rowed callees MilesMutexGuard ctor 0x0004120E / dtor
// 0x0004122F PlayingAudioRef assignment (pinned fold 0x00239099)
// pauseResumeSound 0x00053113 AudioEventRTS::getSoundClass 0x002D9D39
// rva000577E3 0x000577E3 OpaqueRefCounted::Release_Ref 0x00050ED3; member
// offsets as in MilesAudioManager.cpp (lists +0xA40/+0xA44/+0xA48 mutex
// +0x9D4 masks +0x690/+0x694/+0x6B4/+0x6C0 PlayingAudio +0x1C/+0x49/+0x4A
// event view type +0x30).
// NEAR (banked): same control flow calls and constants; register allocation
// differs. Retail keeps the holder's pointer in edi from the zeroing through
// every reload after the assignment calls into the inline destructor at the
// end (no reload after pauseResumeSound / 0x000577E3), uses ebx for the list
// node and re-reads affect/viewMask from the stack; this source reloads the
// holder before the destructor, so edi goes to the node and ebx to viewMask
// (467 vs 477 bytes). Tried: const-ref pauseResumeSound, a raw pointer local,
// placing the body in MilesAudioManager.cpp after pauseResumeSound.
#include <list>

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass() const;
	char m_pad00[0x30];
	int m_viewType; // +0x30
};

struct PlayingAudio
{
	void *vfptr;
	long refs;
	char m_pad08[0x1C - 0x08];
	AudioEventRTS *m_event; // +0x1C
	char m_pad20[0x49 - 0x20];
	bool m_at49;            // +0x49
	bool m_at4A;            // +0x4A
};

class PlayingAudioRef
{
public:
	PlayingAudioRef() : m_ptr(0) {}
	~PlayingAudioRef() { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(m_ptr)->Release_Ref(); }
	PlayingAudioRef &operator=(const PlayingAudioRef &other);
	PlayingAudio *operator->() const { return m_ptr; }
	PlayingAudio *get() const { return m_ptr; }
private:
	PlayingAudio *m_ptr;
};

typedef _STL::list<PlayingAudioRef> PlayingAudioList;

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *mutex, int defer);
	~MilesMutexGuard();
private:
	void *m_mutex;
	bool m_held;
};

class MilesAudioManager
{
public:
	virtual void rva00058591(unsigned int affect, unsigned int viewMask, int keepMasks);
	void pauseResumeSound(PlayingAudioRef &playing);
	void rva000577E3(unsigned int affect, unsigned int viewMask, bool value);

private:
	char m_pad004[0x690 - 0x004];
	unsigned int m_at690;                // +0x690
	unsigned int m_at694;                // +0x694
	char m_pad698[0x6B4 - 0x698];
	unsigned int m_at6B4[3];             // +0x6B4
	unsigned int m_at6C0[3];             // +0x6C0
	char m_pad6CC[0x9D4 - 0x6CC];
	void *m_mutex;                       // +0x9D4
	char m_pad9D8[0xA40 - 0x9D8];
	PlayingAudioList m_playingSounds;    // +0xA40
	PlayingAudioList m_playing3DSounds;  // +0xA44
	PlayingAudioList m_playingStreams;   // +0xA48
};

void MilesAudioManager::rva00058591(unsigned int affect, unsigned int viewMask, int keepMasks)
{
	MilesMutexGuard guard(&m_mutex, 0);
	PlayingAudioRef playing;
	PlayingAudioList::iterator it;
	if (affect & 0x02)
	{
		for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
		{
			playing = *it;
			if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType)))
			{
				if (affect & 0x20)
					playing->m_at4A = false;
				else
					playing->m_at49 = false;
				pauseResumeSound(playing);
			}
		}
	}
	if (affect & 0x04)
	{
		for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it)
		{
			playing = *it;
			if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType)))
			{
				if (affect & 0x20)
					playing->m_at4A = false;
				else
					playing->m_at49 = false;
				pauseResumeSound(playing);
			}
		}
	}
	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
	{
		playing = *it;
		if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))
			&& (playing->m_event->getSoundClass() & affect))
		{
			if (affect & 0x20)
				playing->m_at4A = false;
			else
				playing->m_at49 = false;
			pauseResumeSound(playing);
		}
	}
	if (affect & 0x10)
	{
		if (affect & 0x20)
			m_at694 &= ~viewMask;
		else
			m_at690 &= ~viewMask;
	}
	rva000577E3(affect, viewMask, false);
	if (!keepMasks)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (viewMask & (1 << i))
			{
				if (affect & 0x20)
					m_at6C0[i] &= ~(affect & ~0x20);
				else
					m_at6B4[i] &= ~affect;
			}
		}
	}
}
