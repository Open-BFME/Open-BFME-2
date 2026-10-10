// cl: /O1 /arch:SSE
// ?rva002D3772@RadarWindowOverrideSource@@QAEXHM@Z retail 0x002D3772 65 bytes. RadarWindowOverrideSource setter allocating an 8-byte pair then forwarding to rowed Rva002D3389 at inner+0xEC. Evidence: caller 0x002B361B passes int plus float from 0x00BCEAFC with this equal theRadarWindowOverrideSource; callee 0x002D3389 rowed.
void *__cdecl operator new(unsigned int);

class Rva002D3389
{
public:
	void rva002D3389(void *p);
};

extern int g_009BA4E8;
static __forceinline int LogicFrameRate() { return g_009BA4E8; }

struct Rva002D3772Pair
{
	Rva002D3772Pair(int a, float b);
	int m_scaled;
	int m_arg;
};

// ??0Rva002D3772Pair@@QAE@HM@Z present-unmatched
inline Rva002D3772Pair::Rva002D3772Pair(int a, float b)
{
	m_scaled = (int)((float)LogicFrameRate() * b);
	m_arg = a;
}

class RadarWindowOverrideSource
{
public:
	void rva002D3772(int a, float b);
private:
	char m_pad[0x10];
	char *m_inner;
};

void RadarWindowOverrideSource::rva002D3772(int a, float b)
{
	Rva002D3772Pair *p = new Rva002D3772Pair(a, b);
	((Rva002D3389 *)(m_inner + 0xEC))->rva002D3389(p);
}

// Complete neighbouring34B leaves return their receiver in EAX. The private
// timer-record identities are unknown; only their written prefixes are named.
class Rva002D2DB2 {
public:Rva002D2DB2 &initialize(int a,int b);
private:int duration,first,second,counter;
};
Rva002D2DB2 &Rva002D2DB2::initialize(int a,int b) {
 duration=LogicFrameRate()*5;
 first=a;second=b;counter=0;
 return *this;
}
class Rva002D2DD4 {
public:Rva002D2DD4 &initialize(float value);
private:int duration,kind;float amount;
};
Rva002D2DD4 &Rva002D2DD4::initialize(float value) {
 duration=LogicFrameRate()*6;
 kind=0x38;amount=value;
 return *this;
}
