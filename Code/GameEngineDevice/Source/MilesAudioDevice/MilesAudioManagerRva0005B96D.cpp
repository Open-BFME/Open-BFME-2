// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ?adjustPlayingVolume@MilesAudioManager@@QAEXPAX@Z @0x0005B96D 155B.
// BFME 2 twin of BFME 1 MilesAudioManagerUpdateFadeVolume 0x006B1A00
// (game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerUpdateFadeVolume006B1A00.cpp):
// effective volume from rowed rva0005A9F8(ref 1 1), then type dispatch on
// PlayingAudio+0x14 (same +8 handle/+0x14 type layout as rowed get2DSampleHandleForPlayingAudio):
// types 0/1 refresh pan via AIL_sample_volume_pan then set volume/pan,
// types 2/3 resolve the 3D handle via pinned get3DSampleHandleForPlayingAudio then set 3D volume,
// type 4 forwards the volume to the +0xC sink (rowed rva000A8AEE float sink).
// Tail clears the +0x4F byte. Evidence: rowed callees 0x0005A9F8 0x000A8AEE
// 0x00052696, pinned 0x00052662, IAT mss32 names from PE imports.
typedef float Real;
typedef void *HSAMPLE;
typedef void *H3DSAMPLE;

extern "C" __declspec(dllimport) void __stdcall AIL_sample_volume_pan(
	HSAMPLE sample, Real *volume, Real *pan);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_volume_pan(
	HSAMPLE sample, Real volume, Real pan);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_volume(
	H3DSAMPLE sample, Real volume);

class Rva000A8AEE
{
	void *m_target;
public:
	void rva000A8AEE(float f);
};

struct PlayingAudio
{
	char m_pad00[8];
	void *m_handle08;
	Rva000A8AEE m_sink0C;
	char m_pad10[4];
	int m_type14;
	char m_pad18[4];
	void *m_event1C;
	char m_pad20[0x4f - 0x20];
	unsigned char m_flag4F;
};

class MilesAudioManager
{
public:
	void adjustPlayingVolume(void *ref);
	float rva0005A9F8(void *ref, int a, int b);
	void *get2DSampleHandleForPlayingAudio(void *p);
	// Row 0x00052662 (MilesAudioManager.cpp) takes the playing-audio ref by reference.
	void *get3DSampleHandleForPlayingAudio(class PlayingAudioRef &p);
};

void MilesAudioManager::adjustPlayingVolume(void *ref)
{
	Real volume = rva0005A9F8(ref, 1, 1);
	PlayingAudio *playing = *(PlayingAudio **)ref;
	int type = playing->m_type14;
	if (type == 0 || type == 1)
	{
		HSAMPLE sample = get2DSampleHandleForPlayingAudio(ref);
		Real pan;
		AIL_sample_volume_pan(sample, 0, &pan);
		AIL_set_sample_volume_pan(sample, volume, pan);
	}
	else if (type == 2 || type == 3)
	{
		H3DSAMPLE sample3D = get3DSampleHandleForPlayingAudio(*(PlayingAudioRef *)ref);
		if (sample3D != 0)
			AIL_set_3D_sample_volume(sample3D, volume);
	}
	else if (type == 4)
	{
		playing->m_sink0C.rva000A8AEE(volume);
	}
	(*(PlayingAudio **)ref)->m_flag4F = 0;
}
