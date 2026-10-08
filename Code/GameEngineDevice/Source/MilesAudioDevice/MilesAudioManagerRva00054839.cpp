// Native singleton VA 0x00DFE77C is GameClient.cpp's class GameClient pointer.
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// ?rva00054839@MilesAudioManager@@QAE_NPAVAudioEventRTS@@@Z @0x00054839 96B unlock: two-list search by event id
// Evidence: calls rowed ?isPositionalAudio@AudioEventRTS@@QBE_NXZ 0x002D9C37; lists at +0xA40/+0xA44 as consecutive pointers; compare [event+8]; callers 0x0005D56C in 0x0005D425; prev 0x000547F3 next 0x0005492A MilesAudioManager.
enum ObjectID
{
	ObjectID_Zero = 0
};

struct Holder
{
	unsigned char m_pad[0x48];
	unsigned char m_flag;
};

class Rva002D9576
{
public:
	int rva002D9576();
};

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;
	ObjectID getObjectID();
	unsigned char m_pad[8];
	union
	{
		int m_id;
		Holder *m_holder;
	};
};

struct PlayingAudio
{
	unsigned char m_pad[0x1c];
	AudioEventRTS *m_event;
};

struct ListNode
{
	ListNode *m_next;
	ListNode *m_prev;
	PlayingAudio *m_data;
};

class MilesAudioManager
{
private:
	unsigned char m_pad[0xa40];
	ListNode *m_playing;
	ListNode *m_playing3D;
public:
	bool rva00054839(AudioEventRTS *event);
	bool rva00054899(ObjectID arg1, int arg2);
	bool rva00055426(int arg);
};

struct AudioObjectContext;

class ClientFrameSubsystem
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual AudioObjectContext *slot16(int id);
};

struct AudioObjectID
{
	unsigned char m_pad[0x74];
	ObjectID m_id;
};

struct AudioObjectContext
{
	unsigned char m_pad[0xFC];
	AudioObjectID *m_object;
};

extern class GameClient *TheGameClient;

bool MilesAudioManager::rva00054839(AudioEventRTS *event)
{
	if (!event->isPositionalAudio())
	{
		for (ListNode *p = m_playing->m_next; p != m_playing; p = p->m_next)
		{
			if (p->m_data->m_event->m_id == event->m_id)
				return true;
		}
	}
	else
	{
		for (ListNode *p = m_playing3D->m_next; p != m_playing3D; p = p->m_next)
		{
			if (p->m_data->m_event->m_id == event->m_id)
				return true;
		}
	}
	return false;
}
bool MilesAudioManager::rva00054899(ObjectID arg1, int arg2)
{
	for (ListNode *p = m_playing->m_next; p != m_playing; p = p->m_next)
	{
		PlayingAudio *pa = p->m_data;
		AudioEventRTS *ev = pa->m_event;
		Holder *h = ev->m_holder;
		if (h->m_flag & 0x10)
		{
			if (ev->getObjectID() == arg1)
				return true;
			if (((Rva002D9576 *)p->m_data->m_event)->rva002D9576() == arg2)
				return true;
		}
	}
	for (ListNode *p = m_playing3D->m_next; p != m_playing3D; p = p->m_next)
	{
		PlayingAudio *pa = p->m_data;
		AudioEventRTS *ev = pa->m_event;
		Holder *h = ev->m_holder;
		if (h->m_flag & 0x10)
		{
			if (ev->getObjectID() == arg1)
				return true;
			if (((Rva002D9576 *)p->m_data->m_event)->rva002D9576() == arg2)
				return true;
		}
	}
	return false;
}

bool MilesAudioManager::rva00055426(int arg)
{
	if (arg == 0)
		return false;

	AudioObjectContext *context = reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->slot16(arg);
	ObjectID objectID = ObjectID_Zero;
	if (context != 0 && context->m_object != 0)
		objectID = context->m_object->m_id;

	return rva00054899(objectID, arg);
}
