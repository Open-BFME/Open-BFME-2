// ?rva000533CB@MilesAudioManager@@UAEXXZ
// partial score=0.85 date=2026-10-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs
//
// Donor: Open-BFME-1 Zero Hour MilesAudioManager.cpp::unselectProvider.
// Target identity: this 121-byte boundary at 0x53352 is called from the
// selected-provider branch of setHardwareAccelerated at 0x604A3. Its body
// notifies TheVideoPlayer, closes the current Miles listener and provider,
// then clears selectedProvider. The target also updates the 3D speaker type
// when byte +0x6A6 is set. The provider array/id, count, selection, listener,
// and speaker-type offsets below are directly visible in retail accesses;
// donor names are retained only where the caller and call sequence support
// them.

typedef unsigned char Bool;
typedef void *HPROVIDER;
typedef void *H3DLISTENER;

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_speaker_type(
	HPROVIDER provider, int speakerType);
extern "C" __declspec(dllimport) void __stdcall AIL_close_3D_listener(
	H3DLISTENER listener);
extern "C" __declspec(dllimport) void __stdcall AIL_close_3D_provider(
	HPROVIDER provider);

class VideoPlayer
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25();
	virtual void notifyVideoPlayerOfNewProvider(Bool available);
};

extern VideoPlayer *TheVideoPlayer;

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *mutex, int flags);
	~MilesMutexGuard();
private:
	void *m_mutex;
	bool m_flag;
};

struct MilesProviderInfo
{
	void *name;
	HPROVIDER id;
	int isValid;
};

enum { MAXPROVIDERS = 64 };

class MilesAudioManager
{
public:
	virtual void v00();
	virtual void rva000533CB(void);

private:
	void unselectProvider(void);
	char m_pad04[0x6A2];
	Bool m_flag6A6;
	char m_pad6A7[0x25];
	MilesProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
	void *m_mutex;			// +0x9D4
	char m_pad9D8[0x08];
	H3DLISTENER m_listener;
	char m_pad9E4[0x20C];
	int m_speakerType;
};

void MilesAudioManager::unselectProvider(void)
{
	if (m_selectedProvider >= m_providerCount)
		return;

	VideoPlayer *player = TheVideoPlayer;
	if (player)
		player->notifyVideoPlayerOfNewProvider(0);

	if (m_flag6A6)
		AIL_set_3D_speaker_type(m_provider3D[m_selectedProvider].id,
			m_speakerType);

	AIL_close_3D_listener(m_listener);
	m_listener = 0;
	AIL_close_3D_provider(m_provider3D[m_selectedProvider].id);
	m_selectedProvider = 0xffffffff;
}
// Native 0x000533CB..0x00053448 (125B, RET), the MilesAudioManager vtable
// (0x00BC55B0) slot after 0x000515B3, directly after unselectProvider: under
// the cache mutex (+0x9D4) it flips the +0x6A6 speaker override for the
// selected provider and applies it, speaker type 1 while set, else the
// configured +0xBF0 type with 1 promoted to 5. Name stays address derived.
void MilesAudioManager::rva000533CB(void)
{
	MilesMutexGuard guard(&m_mutex, 0);
	if (m_selectedProvider < m_providerCount)
	{
		m_flag6A6 = !m_flag6A6;
		AIL_set_3D_speaker_type(m_provider3D[m_selectedProvider].id,
			m_flag6A6 ? 1 : (m_speakerType == 1 ? 5 : m_speakerType));
	}
}
// ?TheVideoPlayer@@3PAVVideoPlayer@@A: the global at VA 0xe0aba8 is ?TheVideoPlayer@@3PAVVideoPlayerInterface@@A.
#pragma comment(linker, "/alternatename:?TheVideoPlayer@@3PAVVideoPlayer@@A=?TheVideoPlayer@@3PAVVideoPlayerInterface@@A")
