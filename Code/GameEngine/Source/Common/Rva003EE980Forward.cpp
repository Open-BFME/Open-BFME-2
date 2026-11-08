// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva003EE980@Rva003EE980@@QAEXH@Z @0x003EE980 87B. Unlock lane: three-call
// forward with string g_Rva00E02E84 and triple-float struct from
// 0.95f; arg+0x44; caller at 0x004FF21E. Prev/next are the
// Rva003EE966/A1A family (// cl: /O1 /MD) plus /arch:SSE for movss.
#include <map>

typedef int Int;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class Rva004E35D5
{
public:
	void rva004E35D5(const AsciiString &key, Int a, bool b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35AF
{
public:
	void rva004E35AF(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35FF
{
public:
	void rva004E35FF(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

// Matched DIR32 witness places this one-pointer AsciiString at VA 0x00E02E84
// in the zero-filled .data tail; the shared BFME2 header establishes its
// four-byte layout and the retail initial bytes are zero. Its retail dynamic
// initializer (0x007AF9BB) constructs it from "UnifiedEffect" through the
// out-of-line AsciiString(const char *) at 0x0000654A, as in
// Rva003EE900Forward.cpp.
#pragma inline_depth( 0 )
AsciiString g_Rva00E02E84("UnifiedEffect");
// P32 TEST-BRANCH-ONLY diagnostic: retail builds every effect-name string before 0x007AF9D6 fills the
// LivingWorldRegionEffects FieldParse entries; this image runs that fill earlier (bridged), so fill again here.
void initializeRegionEffectFields();
// ?<s_p32RegionEffectFieldsDiag> absent-from-retail
static int s_p32RegionEffectFieldsDiag = (initializeRegionEffectFields(), 0);
#pragma inline_depth()

// P37 TEST-BRANCH-ONLY diagnostic (never lands): log rank 1's RankInfo and its SciencesGranted vector at every
// subsystem step, to find the step that corrupts it. Output: I:\p37_rank.log (the job dir) and OutputDebugString.
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *, unsigned long,
	unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount(void);
extern "C" __declspec(dllimport) void *__stdcall CreateFileA(const char *, unsigned long, unsigned long, void *,
	unsigned long, unsigned long, void *);
extern "C" __declspec(dllimport) int __stdcall WriteFile(void *, const void *, unsigned long, unsigned long *, void *);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);

class RankInfoStore;
extern RankInfoStore *TheRankInfoStore;
class SubsystemInterfaceList;
extern SubsystemInterfaceList *TheSubsystemList;

namespace {

enum { P37_COUNT, P37_SYS, P37_VPTR, P37_STORE, P37_RANKS, P37_INFO, P37_BEGIN, P37_END, P37_CAP, P37_FIRST,
	P37_NEXT, P37_FINAL, P37_FBEGIN, P37_FEND, P37_FCAP, P37_WORDS };

struct P37Probe
{
	unsigned int v[P37_WORDS];
	char name[48];
};

unsigned int p37Word(unsigned int address)
{
	return *(const unsigned int *)address;
}

int p37Read(P37Probe &p)
{
	for (int i = 0; i < P37_WORDS; ++i)
		p.v[i] = 0;
	p.name[0] = 0;
	__try
	{
		unsigned int list = (unsigned int)TheSubsystemList;
		if (list)
		{
			unsigned int first = p37Word(list), last = p37Word(list + 4);
			p.v[P37_COUNT] = (last - first) / 8;
			if (last != first)
			{
				unsigned int sys = p37Word(last - 8);
				p.v[P37_SYS] = sys;
				p.v[P37_VPTR] = p37Word(sys);
				unsigned int data = p37Word(sys + 8);
				if (data)
				{
					unsigned int length = *(const unsigned short *)(data + 4);
					unsigned int n = 0;
					for (; n < length && n < sizeof(p.name) - 1; ++n)
						p.name[n] = *(const char *)(data + 8 + n);
					p.name[n] = 0;
				}
			}
		}
		unsigned int store = (unsigned int)TheRankInfoStore;
		p.v[P37_STORE] = store;
		if (store)
		{
			unsigned int first = p37Word(store + 0x0C), last = p37Word(store + 0x10);
			p.v[P37_RANKS] = (last - first) / 4;
			if (last != first)
			{
				unsigned int info = p37Word(first);
				p.v[P37_INFO] = info;
				if (info)
				{
					p.v[P37_BEGIN] = p37Word(info + 0x38);
					p.v[P37_END] = p37Word(info + 0x3C);
					p.v[P37_CAP] = p37Word(info + 0x40);
					p.v[P37_NEXT] = p37Word(info + 4);
					unsigned int final = info;
					for (int hops = 0; hops < 8 && p37Word(final + 4); ++hops)
						final = p37Word(final + 4);
					p.v[P37_FINAL] = final;
					p.v[P37_FBEGIN] = p37Word(final + 0x38);
					p.v[P37_FEND] = p37Word(final + 0x3C);
					p.v[P37_FCAP] = p37Word(final + 0x40);
					// Last: a stale begin can fault, and the words above are already in.
					if (p.v[P37_BEGIN] && p.v[P37_BEGIN] != p.v[P37_END])
						p.v[P37_FIRST] = p37Word(p.v[P37_BEGIN]);
				}
			}
		}
		return 1;
	}
	__except (1)
	{
		return 0;
	}
}

void p37Put(char *&out, const char *text)
{
	while (*text)
		*out++ = *text++;
}

void p37Hex(char *&out, unsigned int value)
{
	for (int shift = 28; shift >= 0; shift -= 4)
		*out++ = "0123456789abcdef"[(value >> shift) & 15];
}

const char *const p37Labels[P37_WORDS] = { " n=", " sys=", " vptr=", " store=", " ranks=", " info=", " begin=",
	" end=", " cap=", " first=", " next=", " final=", " fbegin=", " fend=", " fcap=" };

unsigned long __stdcall p37Watch(void *)
{
	void *file = CreateFileA("I:\\p37_rank.log", 0x40000000, 1, 0, 2, 0x80, 0);
	P37Probe last, cur;
	int lastOk = -1;
	for (int i = 0; i < P37_WORDS; ++i)
		last.v[i] = 0xFFFFFFFF;
	for (unsigned int tick = 0; tick < 1200000; ++tick)
	{
		int ok = p37Read(cur);
		int changed = ok != lastOk;
		for (int i = 0; i < P37_WORDS && !changed; ++i)
			changed = cur.v[i] != last.v[i];
		if (changed)
		{
			char line[400];
			char *out = line;
			p37Put(out, "P37 t=");
			p37Hex(out, GetTickCount());
			p37Put(out, ok ? " ok" : " FAULT");
			for (int i = 0; i < P37_WORDS; ++i)
			{
				p37Put(out, p37Labels[i]);
				p37Hex(out, cur.v[i]);
			}
			p37Put(out, " name=");
			p37Put(out, cur.name);
			*out++ = '\r';
			*out++ = '\n';
			*out = 0;
			unsigned long written;
			if (file != (void *)-1)
				WriteFile(file, line, (unsigned long)(out - line), &written, 0);
			OutputDebugStringA(line);
			last = cur;
			lastOk = ok;
		}
		Sleep(1);
	}
	return 0;
}

int p37StartRankWatch()
{
	unsigned long id;
	CreateThread(0, 0, p37Watch, 0, 0, &id);
	return 0;
}

} // namespace

// ?<s_p37RankWatchDiag> absent-from-retail
static int s_p37RankWatchDiag = p37StartRankWatch();

class Rva003EE980
{
public:
	void rva003EE980(Int region);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE980::rva003EE980(Int region)
{
	char *p = (char *)region + 0x44;
	float f = 0.95f;
	float color[3];
	color[0] = f;
	color[1] = f;
	color[2] = f;
	m_owner.rva004E35D5(g_Rva00E02E84, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E84, (Int)p, (Int)&color[0]);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E84, 1);
}

// ?disableUnifiedEffect@Rva003EE9D7@@QAEXH@Z @0x003EE9D7 26B. Clearing twin of the
// forward above, and skeleton twin of Rva003EE900 (Rva003EE900Forward.cpp):
// one rowed 0x004E35D5 call on the owner map at this+8 with string
// g_Rva00E02E84 and (arg+0x44, 0).
class Rva003EE9D7
{
public:
	void disableUnifiedEffect(Int region);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE9D7::disableUnifiedEffect(Int region)
{
	m_owner.rva004E35D5(g_Rva00E02E84, (Int)((char *)region + 0x44), 0);
}
