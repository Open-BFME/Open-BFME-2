// cl: /MD /EHsc /O1 /G7
// Three caller-identified EH factories. 0x000A8AA6 forwards one integer to
// 0x0010FA6B; the null-guarded float forwards at 0x000A8AD8 and 0x000A8AEE
// call 0x0010FC58 and 0x0010FCDB. Each body retains its source object through
// AudioEventInfoRef, allocates a 16-byte derived event record, then passes it
// (or null) to the address-derived helper pinned at 0x0010F8D0. The callers
// and decoded target call sites establish these relationships; owner names
// and broader event semantics remain unproven.

void *__cdecl operator new(unsigned int size) throw();

class AudioEventInfo
{
public:
	void *m_vtable;
	volatile long m_refCount;
};

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
	void Release_Ref();
};

class Rva0036CA00Str;

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(const AudioEventInfo *info);
	operator const Rva0036CA00Str &() const
	{
		return *reinterpret_cast<const Rva0036CA00Str *>(this);
	}
	~AudioEventInfoRef()
	{
		if (m_info)
			reinterpret_cast<OpaqueRefCounted *>(const_cast<AudioEventInfo *>(m_info))->Release_Ref();
	}

	const AudioEventInfo *m_info;
};

class Rva0036CA00Str
{
	void *m_item;
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str();
};

struct CountBase
{
	volatile int m_count;
	__forceinline CountBase() : m_count(0) {}
	virtual void dummy();
};

class Rva001164D3 : public CountBase
{
public:
	Rva001164D3(const Rva0036CA00Str &s);
	~Rva001164D3();
private:
	Rva0036CA00Str m_str;
};

class Rva0010EE67 : public Rva001164D3
{
public:
	Rva0010EE67(const Rva0036CA00Str &s, int value);
private:
	int m_value;
};

class Rva0010EECE : public Rva001164D3
{
public:
	Rva0010EECE(const Rva0036CA00Str &s, float value);
private:
	float m_value;
};

class Rva0010EEF1 : public Rva001164D3
{
public:
	Rva0010EEF1(const Rva0036CA00Str &s, float value);
private:
	float m_value;
};

class Rva0010F8D0
{
public:
	void rva0010F8D0(Rva001164D3 *eventInfo);
};

class Rva0010FA6B
{
public:
	void rva0010FA6B(int value);
};

class Rva000A8AD8Target
{
public:
	void rva0010FC58(float value);
};

class Rva000A8AEETarget
{
public:
	void rva0010FCDB(float value);
};

void Rva0010FA6B::rva0010FA6B(int value)
{
	Rva0010EE67 *eventInfo;
	(eventInfo = new Rva0010EE67(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), value),
		((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

void Rva000A8AD8Target::rva0010FC58(float value)
{
	Rva0010EECE *eventInfo;
	(eventInfo = new Rva0010EECE(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), value),
		((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

void Rva000A8AEETarget::rva0010FCDB(float value)
{
	Rva0010EEF1 *eventInfo;
	(eventInfo = new Rva0010EEF1(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), value),
		((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

// Ghidra boundary at 0x0010FDE9 is 132 bytes. Its caller at 0x000A8B23
// forwards one integer; retail stores that value at this+0x1C, allocates a
// 16-byte event, constructs the rowed 0x0010EF42 subtype from an
// AudioEventInfoRef and the integer, then passes the object or null to the
// rowed helper at 0x0010F8D0. The method owner remains address-derived.
class Rva0010EF42 : public Rva001164D3
{
	int m_value0C;

public:
	Rva0010EF42(const Rva0036CA00Str &s, int value);
};

class Rva0010FDE9
{
	char m_pad00[0x1c];
	int m_value1c;

public:
	void rva0010FDE9(int value);
};

void Rva0010FDE9::rva0010FDE9(int value)
{
	m_value1c = value;
	Rva0010EF42 *eventInfo;
	(eventInfo = new Rva0010EF42(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), value),
		((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

// Native 0x0010FE6D..0x0010FEF3 takes a float and an integer (ret 8).
// Its 20-byte caller at0x000A8B37 forwards those two stack words unchanged.
// The rowed ctor0x0010EF61 stores them at +0x0C/+0x10 in a20-byte event.
// These target facts supersede the caller's former Bezier donor-name guess.
class Rva0010EF61 : public Rva001164D3
{
	float m_value0c;
	int m_value10;
public:
	Rva0010EF61(const Rva0036CA00Str &s, float value, int tag);
};

class Rva0010FE6D
{
public:
	void rva0010FE6D(float value, int tag);
};

void Rva0010FE6D::rva0010FE6D(float value, int tag)
{
	Rva0010EF61 *eventInfo;
	(eventInfo = new Rva0010EF61(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), value, tag),
		((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

// Native10FD5E..10FDE9 allocates20B and calls rowed float-pair ctor10EF14.
// The callerA8B0A forwards two floats; this is not the donor Shadow::setSize.
class Rva0010EF14 : public Rva001164D3
{
	float m_value0c;
	float m_value10;
public:
	Rva0010EF14(const Rva0036CA00Str &s, float first, float second);
};

class Rva0010FD5E
{
public:
	void rva0010FD5E(float first, float second);
};

void Rva0010FD5E::rva0010FD5E(float first, float second)
{
	Rva0010EF14 *eventInfo;
	(eventInfo = new Rva0010EF14(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), first, second),
		((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}


// Four no-argument siblings of 0010FA6B. Each native boundary is 122B;
// each allocates 12B, retains this through the same temporary and passes
// its distinct rowed subtype to 0010F8D0. The comma expression keeps the
// temporary alive until after submission, including the conditional-new
// cleanup and the three EH states proven by the matched integer sibling.
// Callers A8AB4/A8AC0/A8ACC establish the existing pinned owner spellings
// for the final three. The first owner remains address-derived.

class Rva0010EE4F : public Rva001164D3
{
public:
    Rva0010EE4F(const Rva0036CA00Str &s);
};

class Rva0010F9F1
{
public:
    void rva0010F9F1();
};

void Rva0010F9F1::rva0010F9F1()
{
    Rva0010EE4F *eventInfo;
    (eventInfo = new Rva0010EE4F(AudioEventInfoRef(
        reinterpret_cast<AudioEventInfo *>(this))),
        ((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

class Rva0010EE86 : public Rva001164D3
{
public:
    Rva0010EE86(const Rva0036CA00Str &s);
};

class Rva0010FAEA
{
public:
    void rva0010FAEA();
};

void Rva0010FAEA::rva0010FAEA()
{
    Rva0010EE86 *eventInfo;
    (eventInfo = new Rva0010EE86(AudioEventInfoRef(
        reinterpret_cast<AudioEventInfo *>(this))),
        ((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

class Rva0010EE9E : public Rva001164D3
{
public:
    Rva0010EE9E(const Rva0036CA00Str &s);
};

class MilesStream
{
public:
    void rva0010FB64();
};

void MilesStream::rva0010FB64()
{
    Rva0010EE9E *eventInfo;
    (eventInfo = new Rva0010EE9E(AudioEventInfoRef(
        reinterpret_cast<AudioEventInfo *>(this))),
        ((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

class Rva0010EEB6 : public Rva001164D3
{
public:
    Rva0010EEB6(const Rva0036CA00Str &s);
};

class Rva0010FBDE
{
public:
    void rva0010FBDE();
};

void Rva0010FBDE::rva0010FBDE()
{
    Rva0010EEB6 *eventInfo;
    (eventInfo = new Rva0010EEB6(AudioEventInfoRef(
        reinterpret_cast<AudioEventInfo *>(this))),
        ((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

// Native10FEF3..10FFA2 atomically replaces the dword at+24 and clears
// Miles stream user-data0 when the input is zero. Stream08 is reread before
// the imported API call. The20B event records the input and address24 via
// rowed ctor10EF8B; the original record and owner identities remain unknown.
extern "C" __declspec(dllimport) long __stdcall InterlockedExchange(
	volatile long *target, long value);
extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_user_data(
	void *stream, unsigned int index, int value);

class Rva0010EF8B : public Rva001164D3
{
	int m_value0c;
	int m_value10;
public:
	Rva0010EF8B(const Rva0036CA00Str &s, int first, int second);
};

class Rva0010FEF3
{
	char m_pad00[8];
	void *m_stream08;
	char m_pad0c[0x18];
	volatile long m_value24;
public:
	void rva0010FEF3(int value);
};

void Rva0010FEF3::rva0010FEF3(int value)
{
	if (value == 0) {
		InterlockedExchange(&m_value24, 0);
		if (*reinterpret_cast<void *volatile *>(&m_stream08))
			AIL_set_stream_user_data(
				*reinterpret_cast<void *volatile *>(&m_stream08), 0, 0);
	} else {
		InterlockedExchange(&m_value24, 1);
	}
	Rva0010EF8B *eventInfo;
	(eventInfo = new Rva0010EF8B(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), value,
		reinterpret_cast<int>(&m_value24)),
		((Rva0010F8D0 *)this)->rva0010F8D0(eventInfo));
}

// Native10FFA2..110094 reads packet int0/int4/float8, stores int4 at+1C,
// then submits a16B integer event and a20B float/integer event with6000.
// Target calls10EF42/10EF61 and temporary ref releases prove these fields
// and lifetimes; matched sibling factories supply only the C++ shape.
// Original owner, packet and event identities remain unknown.
struct Rva0010FFA2Packet
{
	int m_event0;
	int m_value4;
	float m_value8;
};

class Rva0010FFA2
{
	char m_pad00[0x1c];
	int m_value1c;
public:
	void rva0010FFA2(const Rva0010FFA2Packet *packet);
};

void Rva0010FFA2::rva0010FFA2(const Rva0010FFA2Packet *packet)
{
	m_value1c = packet->m_value4;
	Rva0010EF42 *first;
	(first = new Rva0010EF42(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), packet->m_event0),
		((Rva0010F8D0 *)this)->rva0010F8D0(first));
	Rva0010EF61 *second;
	(second = new Rva0010EF61(AudioEventInfoRef(
		reinterpret_cast<AudioEventInfo *>(this)), packet->m_value8, 6000),
		((Rva0010F8D0 *)this)->rva0010F8D0(second));
}
