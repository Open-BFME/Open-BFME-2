// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?get2DSampleHandleForPlayingAudio@MilesAudioManager@@QAEPAXPAX@Z @0x00052696 47B.
// Same +0xBD4 handle-state table (72-byte records) and PlayingAudio +8/+0x14
// layout as MilesAudioManagerStopAudio (handle +8, type +0x14). Arg is pointer
// to PlayingAudio* (PlayingAudioRef-like, offset 0). Type 0 returns handle,
// type 1 probes table entry byte +2 and returns entry+8, else NULL.
// Callers 0x0005307A 0x0005B9D2 0x0005BA18 0x0005BED3 0x0005C3A2.
struct HandleStateEntry
{
	char m_pad0[2];
	unsigned char m_b2;
	char m_pad3[5];
	void *m_p8;
	char m_padC[0x48 - 0xC];
};

struct PlayingAudio
{
	char m_pad0[8];
	void *m_handle8;
	char m_padC[0x14 - 0xC];
	int m_type14;
};

class MilesAudioManager
{
public:
	void *get2DSampleHandleForPlayingAudio(void *p);
private:
	char m_pad0[0xbd4];
	HandleStateEntry *m_tableBD4;
};

void *MilesAudioManager::get2DSampleHandleForPlayingAudio(void *p)
{
	PlayingAudio *q = *(PlayingAudio **)p;
	switch (q->m_type14)
	{
	case 0:
		return q->m_handle8;
	case 1:
		break;
	default:
		return 0;
	}
	unsigned int idx = (unsigned int)q->m_handle8;
	if (m_tableBD4[idx].m_b2 == 0)
		return m_tableBD4[idx].m_p8;
	return 0;
}
