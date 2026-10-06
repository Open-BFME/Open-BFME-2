// cl: /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManagerAllocatePlayingAudio.cpp. Donor supplies allocation purpose
// and PlayingAudio names; target boundary 0x5320F (114B) allocates 0x50 bytes,
// calls constructor 0xA8D5F, writes playing status at +0x18 and returns a counted
// reference. Constructor 0xA8D5F independently sets +0x18 to stopped (1).
// Refcount +4 and helper calls agree with already recovered owning references.
// Unaccessed PlayingAudio bytes stay opaque; this is not a complete layout.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

enum PlayingStatus
{
	PS_Playing,
	PS_Stopped,
	PS_Paused
};

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
	}

	void Release_Ref(void);

private:
	long m_refCount;
};

class PlayingAudio : public OpaqueRefCounted
{
public:
	PlayingAudio();
	virtual ~PlayingAudio();

	void *m_milesHandle;
	char m_unknown0c[8];
	int m_type;
	volatile PlayingStatus m_status;
	char m_tail[0x34];
};

// Counted-reference helpers are the existing frameless ICF-shared bodies.
#pragma optimize("y", on)
class PlayingAudioRef
{
public:
	PlayingAudioRef(void) : m_ptr(0) {}

	PlayingAudioRef(PlayingAudio *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}

	PlayingAudioRef(const PlayingAudioRef &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}

	~PlayingAudioRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	PlayingAudio *operator->(void) const
	{
		return m_ptr;
	}

private:
	PlayingAudio *m_ptr;
};

class MilesAudioManager
{
public:
	PlayingAudioRef allocatePlayingAudio(void);
};


#pragma optimize("y", off)
// ?allocatePlayingAudio@MilesAudioManager@@QAE?AVPlayingAudioRef@@XZ
PlayingAudioRef MilesAudioManager::allocatePlayingAudio(void)
{
	PlayingAudioRef audio = new PlayingAudio;
	audio->m_status = PS_Playing;
	return audio;
}
