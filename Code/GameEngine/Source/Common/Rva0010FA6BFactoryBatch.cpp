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
