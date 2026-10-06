// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ?rva0005BA08@MilesAudioManager@@QAEXPAX@Z @0x0005BA08 330B.
// BFME 2 twin of ZH MilesAudioManager::initFilters (BFME 1 donor 0x006B1B40,
// MilesAudioManagerInitFilters.cpp): sets volume/pan, pitch-scaled playback
// rate, the "Mono Delay" filter and reverb levels on the reference's sample.
// Target facts: the sample comes from rowed rva00052696(ref); PlayingAudio
// keeps its event at +0x1C; the event holds its info reference at +8, a
// delay float at +0x64 and an int at +0x30; the info has reverb floats at
// +0xA8/+0xAC and a vector at +0xB8; the manager keeps the reverb flag at
// +0x6A7 and the delay filter provider at +0x9E4. Callees 0x0005A9F8 (float,
// three args) and 0x000581FA (two args) are unrowed and keep address names.

typedef float Real;
typedef void *HSAMPLE;
typedef void *HPROVIDER;

extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_volume_pan(
	HSAMPLE sample, Real volume, Real pan);
extern "C" __declspec(dllimport) int __stdcall AIL_sample_playback_rate(
	HSAMPLE sample);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_playback_rate(
	HSAMPLE sample, int rate);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_processor(
	HSAMPLE sample, int effect, HPROVIDER provider);
extern "C" __declspec(dllimport) void __stdcall AIL_set_filter_sample_preference(
	HSAMPLE sample, const char *name, Real *value);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_reverb_levels(
	HSAMPLE sample, Real dry, Real wet);

struct Rva0005BA08List
{
	void *m_begin;
	void *m_end;
	bool empty() const { return m_begin == m_end; }
};

struct Rva0005BA08AudioInfo
{
	char m_pad00[0xa8];
	Real m_reverbWet;
	Real m_reverbDry;
	char m_padB0[8];
	Rva0005BA08List m_list;
};

struct Rva0005BA08InfoRef
{
	Rva0005BA08AudioInfo *m_info;
};

class Rva002D94DD
{
public:
	Real rva002D94DD() const;
};

struct Rva0005BA08AudioEvent
{
	char m_pad00[8];
	Rva0005BA08InfoRef m_info;
	char m_pad0C[0x30 - 0x0c];
	int m_value30;
	char m_pad34[0x64 - 0x34];
	Real m_delay;
};

struct Rva0005BA08PlayingAudio
{
	char m_pad00[0x1c];
	Rva0005BA08AudioEvent *m_event;
};

class MilesAudioManager
{
public:
	void rva0005BA08(void *ref);

	void *rva00052696(void *p);
	Real rva00052F4C();
	Real rva0005A9F8(void *ref, int a, int b);
	void rva000581FA(const Rva0005BA08InfoRef &info, int value);

private:
	char m_pad000[0x6a7];
	bool m_reverbEnabled;
	char m_pad6A8[0x9e4 - 0x6a8];
	HPROVIDER m_delayFilter;
};

void MilesAudioManager::rva0005BA08(void *ref)
{
	HSAMPLE sample = rva00052696(ref);
	Rva0005BA08AudioEvent *&event = (*(Rva0005BA08PlayingAudio **)ref)->m_event;
	if (sample == 0)
		return;

	const Rva0005BA08InfoRef &info = event->m_info;
	Real volume = rva0005A9F8(ref, 1, 1);
	AIL_set_sample_volume_pan(sample, volume, 0.5f);

	Real pitch = ((const Rva002D94DD *)event)->rva002D94DD();
	if (pitch <= 0.0f)
	{
	}
	else
		AIL_set_sample_playback_rate(sample, (int)(AIL_sample_playback_rate(sample) * pitch));

	if (event->m_delay > 0.0f)
	{
		Real value = event->m_delay;
		AIL_set_sample_processor(sample, 1, m_delayFilter);
		AIL_set_filter_sample_preference(sample, "Mono Delay Time", &value);
		value = 0.0f;
		AIL_set_filter_sample_preference(sample, "Mono Delay", &value);
		AIL_set_filter_sample_preference(sample, "Mono Delay Mix", &value);
	}

	if (m_reverbEnabled)
	{
		Real wet = info.m_info->m_reverbWet;
		AIL_set_sample_reverb_levels(sample, info.m_info->m_reverbDry,
			wet * rva00052F4C());
	}
	else
		AIL_set_sample_reverb_levels(sample, 1.0f, 0.0f);

	if (!info.m_info->m_list.empty())
		rva000581FA(info, event->m_value30);
}
