// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// _bfme_updateTimedOps, retail 0x003FE74B (71 bytes), and
// ?update@TimedOp@@QAEIXZ, retail 0x003FE6E8 (99 bytes).
//
// Direct port of the Battle for Middle-earth timed-operation pump
// (reference/open-bfme-1/Code/GameEngine/Source/Common/TimedOperations.cpp
// updateTimedOperations): sample the head node, retire it through the
// explicit deleting-destructor call plus a separate operator delete when it
// reports bit 1, narrow the flags down to bit 2 once the list drains, and
// return bits 0 and 2. The update call on the head node is a direct
// non-virtual thiscall; only the destruction goes through the vtable.
//
// TimedOp::update stamps the start time on first call, scales the unsigned
// now/start ticks by milliseconds-to-seconds, and forwards to the embedded
// operation object (a direct thiscall into the pinned helper, which owns
// the null check). BFME2 drops the reference FatalError path.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class TimedOperationRef
{
public:
	unsigned int update(float elapsedSeconds, bool firstCall);

private:
	char m_pad[4];
};

class TimedOp
{
public:
	virtual ~TimedOp(void);
	unsigned int update(void);

	TimedOp *m_next; // +0x04
	TimedOperationRef m_operation; // +0x08
	bool m_started; // +0x0C
	unsigned int m_startTime; // +0x10
};

extern TimedOp *g_timedOperationHead;
// g_timedOperationHead: matched references place it at VA 0xe02ec0 (zero-filled .bss).
TimedOp * g_timedOperationHead;

// ?update@TimedOp@@QAEIXZ
unsigned int TimedOp::update(void)
{
	bool firstCall = false;
	unsigned int now = timeGetTime();

	if (!m_started)
	{
		m_startTime = now;
		firstCall = true;
		m_started = true;
	}

	float elapsedSeconds = now * 0.001f - m_startTime * 0.001f;

	return m_operation.update(elapsedSeconds, firstCall);
}

unsigned int _bfme_updateTimedOps(void)
{
	unsigned int flags = 0;

	if (g_timedOperationHead != 0)
	{
		flags = g_timedOperationHead->update();

		if ((flags & 2) != 0)
		{
			TimedOp *head = g_timedOperationHead;
			g_timedOperationHead = head->m_next;
			::delete head;

			if (g_timedOperationHead == 0)
				flags &= 4;
		}
	}

	return flags & 5;
}
