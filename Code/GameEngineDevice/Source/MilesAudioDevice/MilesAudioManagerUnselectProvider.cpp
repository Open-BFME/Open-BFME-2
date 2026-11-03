// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
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

#include "../../../GameEngine/Include/GameClient/VideoPlayerClass.h"

extern class VideoPlayerInterface *TheVideoPlayer;

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

private:
	void unselectProvider(void);
	char m_pad04[0x6A2];
	Bool m_flag6A6;
	char m_pad6A7[0x25];
	MilesProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
	char m_pad9D4[0x0C];
	H3DLISTENER m_listener;
	char m_pad9E4[0x20C];
	int m_speakerType;
};

void MilesAudioManager::unselectProvider(void)
{
	if (m_selectedProvider >= m_providerCount)
		return;

	VideoPlayer *player = ((VideoPlayer *)TheVideoPlayer);
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
