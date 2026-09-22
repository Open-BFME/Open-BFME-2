// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?reset@Radar@@UAEXXZ, retail 0x002D7DB9, 28 bytes. Dedicated TU: the two
// callees live in other TUs (deleteListResources is a pinned row,
// clearAllEvents is pinned), so the body lives here alone.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp):
// delete the list resources, clear all events, then stop forcing the radar
// on. BFME1 spells the flag store as [esi+0x9]; retail writes [esi+0xD].
//
// Retail passes this-4 to both callees (lea edi,[esi-4]): reset is a method
// of the second MI base (the ctor near 0x002D7CF0 installs two vptrs,
// 0xC0363C at +0 and 0xC03604 at +4; the thunk at 0x002D7D4F adjusts this
// by -4 the same way), while deleteListResources/clearAllEvents live on
// the primary base. The sole caller (0x0004E30B, an SEH init body touching
// [esi+0x146C]) passes its own this through unadjusted, as a fellow
// second-base method would.
//
// The UAE spelling is BFME1's own: reset is public virtual there.

class RadarEventRef
{
public:
	virtual void m_spare0();
	virtual void m_deleter();
	__declspec(noinline) void release();
private:
	int m_refCount;  // +0x4 past the vptr
};

class RadarEventRefSlot
{
public:
	void clearRef();
private:
	RadarEventRef *m_ref;
};

struct RadarEventBody
{
	unsigned char m_state;  // +0x00
	unsigned char m_pad00[3];
	int m_04;               // +0x04
	int m_08;               // +0x08
	int m_0C;               // +0x0C
	int m_10;               // +0x10
	int m_14;               // +0x14
	int m_18;               // +0x18
	int m_keep1C;           // +0x1C (preserved, never stored)
	int m_20;               // +0x20
	int m_24;               // +0x24
	int m_28;               // +0x28
	int m_keep2C;           // +0x2C (preserved, never stored)
	float m_30;             // +0x30
	float m_34;             // +0x34
	float m_38;             // +0x38
	int m_3C;               // +0x3C
	int m_40;               // +0x40
	unsigned char m_44;     // +0x44
	unsigned char m_pad44[3];
	RadarEventRefSlot m_ref;  // +0x48
};

struct RadarEvent
{
	int m_tag;              // +0x00
	RadarEventBody m_body;  // +0x04
};

class Radar
{
public:
	virtual void reset();
protected:
	void deleteListResources();
	void clearAllEvents();
private:
	char m_pad[0x9];
	bool m_radarForceOn;  // +0xD past the vptr
	char m_pad0D[0x2C - 0xE];
public:
	RadarEvent m_events[64];  // +0x2C
private:
	int m_eventTrailer;  // +0x142C, immediately after the 64 events
};

void Radar::reset()
{
	Radar *core = (Radar *)((char *)this - 4);
	core->deleteListResources();
	core->clearAllEvents();

	m_radarForceOn = false;
}

// ?clearAllEvents@Radar@@IAEXXZ
void Radar::clearAllEvents()
{
	m_eventTrailer = 0;
	RadarEventBody *body = &m_events[0].m_body;
	int left = 0x40;
	do {
		RadarEventRefSlot *holder = &body->m_ref;
		((int *)body)[-1] = 11;
		body->m_state = 0;
		body->m_04 = 0;
		body->m_08 = 0;
		body->m_0C = 0;
		body->m_10 = 0;
		body->m_14 = 0;
		body->m_18 = 0;
		body->m_20 = 0;
		body->m_24 = 0;
		body->m_28 = 0;
		body->m_30 = 0.0f;
		body->m_34 = 0.0f;
		body->m_38 = 0.0f;
		body->m_3C = 0;
		body->m_40 = 0;
		body->m_44 = 0;
		holder->clearRef();
		body = (RadarEventBody *)((char *)body + 0x50);
	} while (--left != 0);
}

// ?release@RadarEventRef@@QAEXXZ
void RadarEventRef::release()
{
	if (--m_refCount != 0)
		return;
	m_deleter();
}

// ?clearRef@RadarEventRefSlot@@QAEXXZ
void RadarEventRefSlot::clearRef()
{
	if (m_ref == 0)
		return;
	m_ref->release();
	m_ref = 0;
}
