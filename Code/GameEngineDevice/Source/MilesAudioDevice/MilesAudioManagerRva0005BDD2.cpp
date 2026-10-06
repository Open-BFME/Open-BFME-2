// cl: /DNDEBUG /MD
// ?isPlayingLowerPriority@MilesAudioManager@@QAE_NPAVAudioEventRTS@@@Z @0x0005BDD2 135B PROBE
// MilesAudioManager positional check with volume less loop.
// Evidence: unlock lane caller 0x0005D54F pin 0x00059AD0 row isPositionalAudio.
struct AudioEventInfo
{
	char m_pad00[0x44];
	int m_44;
};

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;
	char m_pad00[8];
	AudioEventInfo *m_eventInfo;
};

struct Rva000515E4Key
{
	int a;
	float b;
};

bool __cdecl Rva000515E4Less(const Rva000515E4Key *x, const Rva000515E4Key *y);

struct Rva0005BDD2Info
{
	char m_pad00[0x44];
	int m_44;
};

struct Rva0005BDD2AudioEvent
{
	char m_pad00[8];
	Rva0005BDD2Info *m_info;
};

struct Rva0005BDD2PlayingAudio
{
	char m_pad00[0x1c];
	Rva0005BDD2AudioEvent *m_event;
};

struct Rva0005BDD2Node
{
	Rva0005BDD2Node *m_next;
	char m_pad04[4];
	void *m_ref;
};

struct Rva0005BDD2ListHead
{
	void *m_next;
};

class MilesAudioManager
{
public:
	float rva00059AD0(void *event, int a);
	float rva0005A9F8(void *ref, int a, int b);
	bool isPlayingLowerPriority(AudioEventRTS *event);
private:
	char m_pad00[0xa40];
	Rva0005BDD2ListHead *m_a40;
	Rva0005BDD2ListHead *m_a44;
};

bool MilesAudioManager::isPlayingLowerPriority(AudioEventRTS *event)
{
	Rva000515E4Key key1;
	key1.a = event->m_eventInfo->m_44;
	key1.b = rva00059AD0(event, 1);
	bool positional = event->isPositionalAudio();
	Rva0005BDD2ListHead **headAddr = positional ? &m_a44 : &m_a40;
	Rva0005BDD2Node *node = (Rva0005BDD2Node *)(*(Rva0005BDD2ListHead **)headAddr)->m_next;
	if (node == (Rva0005BDD2Node *)*headAddr)
		return false;
	do {
		void *ref = (void *)&node->m_ref;
		Rva0005BDD2PlayingAudio *playing = *(Rva0005BDD2PlayingAudio **)ref;
		Rva0005BDD2AudioEvent *ev = playing->m_event;
		Rva0005BDD2Info *info = ev->m_info;
		Rva000515E4Key key2;
		key2.a = info->m_44;
		key2.b = rva0005A9F8(ref, 1, 1);
		if (Rva000515E4Less(&key2, &key1))
			return true;
		node = node->m_next;
	} while (node != (Rva0005BDD2Node *)*headAddr);
	return false;
}
