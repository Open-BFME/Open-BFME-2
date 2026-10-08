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

