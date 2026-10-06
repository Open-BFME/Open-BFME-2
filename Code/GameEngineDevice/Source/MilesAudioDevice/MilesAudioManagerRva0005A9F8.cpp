// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ?rva0005A9F8@MilesAudioManager@@QAEMPAXHH@Z @0x0005A9F8 122B.
// Effective volume of a playing-audio reference: the event volume from
// 0x00059AD0, optionally scaled by the fade factor of rowed rva0005117B
// (fed the PlayingAudio's fade frame at +0x30), then floored at 0.01 when
// the event's +0x52 flag is set and its info at +8 fails rowed predicate
// rva001D990C(2). Called by initFilters twin 0x0005BA08 with (ref, 1, 1).
// Target facts: PlayingAudio keeps its event at +0x1C as in 0x0005BA08;
// the 0.01f literal is retail's 0x00BCF628. The BFME 1 counterpart inlines
// the fade clamp into its compute()/initFilters pair (0x006B1B40).

typedef float Real;

class Rva001D990C
{
public:
	bool rva001D990C(int v);
};

class Rva0005117B
{
public:
	float rva0005117B(float v);
};

struct Rva0005A9F8AudioEvent
{
	char m_pad00[8];
	Rva001D990C *m_info;
	char m_pad0C[0x52 - 0x0c];
	bool m_flag52;
};

struct Rva0005A9F8PlayingAudio
{
	char m_pad00[0x1c];
	Rva0005A9F8AudioEvent *m_event;
	char m_pad20[0x30 - 0x20];
	Real m_fadeFrame;
};

class MilesAudioManager
{
public:
	Real rva0005A9F8(void *ref, int a, int b);

	Real rva00059AD0(void *event, int a);
};

Real MilesAudioManager::rva0005A9F8(void *ref, int a, int b)
{
	Rva0005A9F8PlayingAudio *&playing = *(Rva0005A9F8PlayingAudio **)ref;
	Rva0005A9F8AudioEvent *event = playing->m_event;
	Real volume = rva00059AD0(event, a);
	if (b == 1)
		volume *= ((Rva0005117B *)this)->rva0005117B(playing->m_fadeFrame);

	event = playing->m_event;
	if (event->m_flag52 && volume < 0.01f && event->m_info != 0
		&& !event->m_info->rva001D990C(2))
		volume = 0.01f;
	return volume;
}
