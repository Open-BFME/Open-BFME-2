// ?rva00052FA0@MilesAudioManager@@QAEXPAX@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva00052FA0@MilesAudioManager@@QAEXPAX@Z @0x00052FA0 319B.
// Type-dispatched reverb/effects refresh for a PlayingAudio ref: types 0/1 via
// rowed get2DSampleHandleForPlayingAudio plus AIL_set_sample_reverb_levels,
// types 2/3 via pinned rva00052662 plus AIL_set_3D_sample_effects_level, type 4
// via pinned rva000A8B04 two-float receiver. Same +0x6A7 reverb gate, +0x1C event
// with +8 settings holding +0xA8/+0xAC floats, and +0x34 factor as 0x0005BA08
// prepSample and 0x00053AFA stream forwarder. Evidence: callers 0x0005BBD6
// 0x0005C393 0x0005C5EE 0x0005C7E2 0x0005F7AA 0x0005F987; neighbours 0x00052F4C
// 0x000530DF; VTABLE none; strings none.

typedef float Real;
typedef void *HSAMPLE;
typedef void *H3DSAMPLE;

extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_reverb_levels(
	HSAMPLE sample, Real dry, Real wet);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_effects_level(
	H3DSAMPLE sample, Real level);

class Rva000A8B04
{
public:
	void rva000A8B04(float first, float second);
};

struct AudioInfo
{
	char m_pad00[0xa8];
	Real m_wetA8;
	Real m_dryAC;
};

struct AudioEvent
{
	char m_pad00[8];
	AudioInfo *m_info08;
};

struct PlayingAudio
{
	char m_pad00[0x14];
	int m_type14;
	char m_pad18[4];
	AudioEvent *m_event1C;
	char m_pad20[0x34 - 0x20];
	Real m_f34;
};

class MilesAudioManager
{
public:
	void rva00052FA0(void *ref);

	float getGlobalReverbMultiplier();
	void *get2DSampleHandleForPlayingAudio(void *p);
	void *rva00052662(void *p);

private:
	char m_pad00[0x6a7];
	bool m_reverbEnabled;
};

void MilesAudioManager::rva00052FA0(void *ref)
{
	PlayingAudio *playing = *(PlayingAudio **)ref;
	int type = playing->m_type14;
	if (type < 0)
		return;
	if (type > 1)
	{
		if (type > 3)
		{
			if (type != 4)
				return;
			if (m_reverbEnabled)
			{
				AudioEvent *event = playing->m_event1C;
				AudioInfo *info = event->m_info08;
				Real base = info->m_wetA8;
				Real scaled = getGlobalReverbMultiplier() * base;
				PlayingAudio *playing2 = *(PlayingAudio **)ref;
				AudioEvent *event2 = playing2->m_event1C;
				AudioInfo *info2 = event2->m_info08;
				Real level = info2->m_dryAC;
				((Rva000A8B04 *)((char *)playing2 + 0x0c))->rva000A8B04(level, scaled);
			}
			else
				((Rva000A8B04 *)((char *)playing + 0x0c))->rva000A8B04(1.0f, 0.0f);
		}
		else
		{
			H3DSAMPLE sample3D = rva00052662(ref);
			if (sample3D == 0)
				return;
			Real effLevel;
			if (m_reverbEnabled)
			{
				AudioEvent *event = playing->m_event1C;
				AudioInfo *info = event->m_info08;
				Real base = info->m_wetA8;
				effLevel = getGlobalReverbMultiplier() * playing->m_f34 * base;
			}
			else
				effLevel = 0.0f;
			AIL_set_3D_sample_effects_level(sample3D, effLevel);
		}
	}
	else
	{
		H3DSAMPLE sample = get2DSampleHandleForPlayingAudio(ref);
		if (sample == 0)
			return;
		if (m_reverbEnabled)
		{
			AudioEvent *event = playing->m_event1C;
			AudioInfo *info = event->m_info08;
			Real base = info->m_wetA8;
			Real scaled = getGlobalReverbMultiplier() * base;
			AudioEvent *event2 = (*(PlayingAudio **)ref)->m_event1C;
			AudioInfo *info2 = event2->m_info08;
			Real dry = info2->m_dryAC;
			AIL_set_sample_reverb_levels(sample, dry, scaled);
		}
		else
			AIL_set_sample_reverb_levels(sample, 1.0f, 0.0f);
	}
}
