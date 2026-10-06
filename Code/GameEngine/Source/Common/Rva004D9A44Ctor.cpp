// cl: /MD
// ??0Rva004D9A44@@QAE@ABVRva0036CA00Str@@ABVRva004D964E@@@Z @0x004D9A44 (30B):
// Two-member ctor: Rva0036CA00Str at +0 via rowed 0x000A8C7C then Rva004D964E
// at +4 via rowed 0x004D964E, return-this ret-8. Evidence: chain lane, calls
// 0x004D964E just landed, push-push-call-push-lea-call shape, caller 0x004DBC52.
class Rva0036CA00Str
{
private:
	void *m_item;
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
};

class Rva002390CB
{
private:
	char m_pad[8];
public:
	__declspec(nothrow) Rva002390CB(const Rva002390CB &other);
};

class Rva004D964E
{
public:
	__declspec(nothrow) Rva004D964E(const Rva004D964E &other);
private:
	Rva002390CB m_00;
	Rva002390CB m_08;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	unsigned char m_20;
};

class Rva004D9A44
{
public:
	Rva004D9A44(const Rva0036CA00Str &a, const Rva004D964E &b);
private:
	Rva0036CA00Str m_str;
	Rva004D964E m_data;
};

Rva004D9A44::Rva004D9A44(const Rva0036CA00Str &a, const Rva004D964E &b) : m_str(a), m_data(b)
{
}
