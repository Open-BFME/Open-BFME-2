// cl: /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManagerStopAudio.cpp supplies stopAudio identity and three-list structure.
// Target: Ghidra 0x54284..0x543F5 (369B), sample/3D stop-import clusters and
// flags 2/4 support that identity independently. BFME2 adds indexed-handle
// stopping to the 2D branch, uses type 2 for direct 3D handles and a 72-byte
// handle-state record. Both indexed branches set its byte +1.
// Target-measured fields: mutex object +0x9D4, lists +0xA40/+0xA44/+0xA48,
// handle-state table +0xBD4; PlayingAudio handle +8, stream holder +0xC,
// type +0x14, status +0x18, event +0x1C. Stream helpers retain address-derived
// names: their targets differ from BFME1's direct Miles stream operations.
// Guard 0x4120E/0x4122F tracks ownership and calls virtual lock/unlock helpers;
// its name is descriptive, not an independently recovered original type.
// Ref assignment exactly shares the already recovered 0x239099 body.

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


extern "C" __declspec(dllimport) void *__stdcall AIL_register_EOS_callback(
	void *sample, void *callback);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(void *sample);
extern "C" __declspec(dllimport) void *__stdcall AIL_register_3D_EOS_callback(
	void *sample, void *callback);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(void *sample);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);

enum AudioAffect
{
	AudioAffect_Music = 0x01,
	AudioAffect_Sound = 0x02,
	AudioAffect_Sound3D = 0x04,
	AudioAffect_Speech = 0x08
};

enum PlayingAudioType
{
	PAT_Sample,
	PAT_3DSample = 2,
};

enum PlayingStatus
{
	PS_Playing,
	PS_Stopped,
	PS_Paused
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;
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

class MilesStreamRef
{
public:
	void rva000A8B4B(unsigned int value);
	void rva000A8AC0();
private:
	void *m_object;
};

class PlayingAudio : public OpaqueRefCounted
{
public:
	void *m_milesHandle;
	MilesStreamRef m_stream;
	char m_unknown10[4];
	PlayingAudioType m_type;
	volatile PlayingStatus m_status;
	AudioEventRTS *m_audioEventRTS;
};


#pragma optimize("y", on)
class PlayingAudioRef
{
public:
	PlayingAudioRef(void) : m_ptr(0) {}

	~PlayingAudioRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	PlayingAudioRef &operator=(const PlayingAudioRef &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				other.m_ptr->Add_Ref();
			if (m_ptr)
				m_ptr->Release_Ref();
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	operator PlayingAudio *(void) const { return m_ptr; }
	PlayingAudio *operator->(void) const { return m_ptr; }

private:
	PlayingAudio *m_ptr;
};

class MilesMutexGuard
{
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();
private:
    void *m_mutex;
    bool m_held;
};

typedef _STL::list<PlayingAudioRef> PlayingAudioList;

class MilesAudioManager
{
public:
	virtual void stopAudio(AudioAffect which);

private:
	char m_pad004[0x9d4 - 4];
	void *m_mutex;
	char m_pad9d8[0xa40 - 0x9d8];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
	char m_pada4c[0xbd4 - 0xa4c];
	unsigned char *m_handleState;
};


#pragma optimize("y", off)
void MilesAudioManager::stopAudio(AudioAffect which)
{
	MilesMutexGuard guard(&m_mutex, 0);
	PlayingAudioList::iterator it;
	PlayingAudioRef playing;

	if (which & AudioAffect_Sound)
	{
		for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
		{
			playing = *it;
			if (playing)
			{
                if (playing->m_type == PAT_Sample)
                {
                    AIL_register_EOS_callback(playing->m_milesHandle, 0);
                    AIL_stop_sample(playing->m_milesHandle);
                    playing->m_status = PS_Stopped;
                }
                else
                {
                    m_handleState[(unsigned int)playing->m_milesHandle * 72 + 1] = 1;
                }
			}
		}
	}

	if (which & AudioAffect_Sound3D)
	{
		for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it)
		{
			playing = *it;
			if (playing)
			{
				if (playing->m_type == PAT_3DSample)
				{
					AIL_register_3D_EOS_callback(playing->m_milesHandle, 0);
					AIL_stop_3D_sample(playing->m_milesHandle);
					playing->m_status = PS_Stopped;
				}
				else
				{
					m_handleState[(unsigned int)playing->m_milesHandle * 72 + 1] = 1;
				}
			}
		}
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
	{
		playing = *it;
		if (playing && (which & playing->m_audioEventRTS->getSoundClass()))
		{
			playing->m_stream.rva000A8B4B(0);
			playing->m_stream.rva000A8AC0();
			playing->m_status = PS_Stopped;
		}
	}
}
