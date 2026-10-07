// ?rva000603ED@MilesAudioManager@@QAEXXZ
// partial score=0.99 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva000603ED@MilesAudioManager@@QAEXXZ @0x000603ED, 143B. The MilesAudioManager
// owner and list layout follow the adjacent MilesAudioManager.cpp unit. This
// pass releases handles and erases stream records whose event info is finished.

#include <list>

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
	void Release_Ref();
private:
	long refs;
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	OpaqueRefElement4() : referent(0) {}
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
	~OpaqueRefElement4()
	{
		if (referent)
			referent->Release_Ref();
	}
};

class AudioEventInfo
{
public:
	unsigned char m_pad[0xB0];
	int m_status;
};

class AudioEventRTS
{
public:
	unsigned char m_pad[8];
	AudioEventInfo *m_info;
};

class BfmePoolRef10
{
public:
	AudioEventRTS *operator->() const { return m_ptr; }
private:
	AudioEventRTS *m_ptr;
};

class PlayingAudio : public OpaqueRefCounted
{
public:
	unsigned char m_pad08[0x14 - 8];
	int m_type;
	int m_status;
	BfmePoolRef10 m_event;
};

class MilesAudioManager;
typedef _STL::list<OpaqueRefElement4> PlayingAudioList;

class MilesAudioManager
{
public:
	virtual void slot00();
	void rva000603ED();
	void releaseMilesHandles(PlayingAudio &);

private:
	unsigned char m_pad04[0xA40 - 4];
	PlayingAudioList m_playingSounds;       // +0xA40
	PlayingAudioList m_playing3DSounds;     // +0xA44
	PlayingAudioList m_playingStreams;      // +0xA48
};

void MilesAudioManager::rva000603ED()
{
	MilesAudioManager *manager = this;
	OpaqueRefElement4 current;
	PlayingAudioList::iterator it = manager->m_playingStreams.begin();
	while (it != manager->m_playingStreams.end())
	{
		current = *it;
		PlayingAudio *playing = static_cast<PlayingAudio *>(current.referent);
		if (playing)
		{
			if (playing->m_event->m_info->m_status == 1)
			{
				manager->releaseMilesHandles(*playing);
				it = manager->m_playingStreams.erase(it);
				continue;
			}
		}
		++it;
	}
}
