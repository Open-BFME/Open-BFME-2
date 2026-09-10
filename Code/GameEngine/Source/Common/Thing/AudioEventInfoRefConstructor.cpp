// Ported from the BFME1 audio-event reconstruction.  The constructor's body
// is independently located and byte-verified in BFME2 at RVA 0x00051914.
typedef long Long;

extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(
	Long volatile *addend);

class AudioEventInfo
{
public:
	void *m_vtable;
	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(const AudioEventInfo *info);

	const AudioEventInfo *m_info;
};

AudioEventInfoRef::AudioEventInfoRef(const AudioEventInfo *info)
	: m_info(info)
{
	if (m_info)
		InterlockedIncrement(&const_cast<AudioEventInfo *>(m_info)->m_refCount);
}
