// cl: /MD
// ??0Rva004D971D@@QAE@ABV0@@Z @0x004D971D (33B):
// Copy ctor: Rva0036CA00Str at +0 via rowed 0x000A8C7C then Rva004D964E at +4
// via rowed 0x004D964E, edi holds src across calls, return-this ret-4.
// Evidence: chain lane, push-esi-edi plus add-edi-4 shape, caller 0x004D9ADA.
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

class Rva004D971D
{
public:
	Rva004D971D(const Rva004D971D &other);
private:
	Rva0036CA00Str m_str;
	Rva004D964E m_data;
};

Rva004D971D::Rva004D971D(const Rva004D971D &other) : m_str(other.m_str), m_data(other.m_data)
{
}
