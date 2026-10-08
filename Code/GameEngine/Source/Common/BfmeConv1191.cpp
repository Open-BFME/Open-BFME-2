// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP=
// Open-BFME5 conversions.
// Native dump50C69D loads the fprintf IAT at00BBA5C4; use that import
// instead of an unresolved synthetic global. The ten four-byte handles use
// BFME2's shared AsciiString: their native destructor calls all target the
// complete releaseBuffer worker36410. All five home bodies retain exact bytes.
// Original diagnostic owner names remain address-derived donor views.

#include "ascii_string.h"
extern "C" __declspec(dllimport) void * __cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fclose(void *);
extern "C" __declspec(dllimport) int __cdecl fprintf(void *, const char *, ...);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);


class Rva0013A820
{
public:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	int m_14;
	int m_18;
	AsciiString m_1C;
	AsciiString m_20;
	int m_24;
	AsciiString m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	int m_40;
	AsciiString m_44;

	void reset();
};

class INIStatsRecord : public Rva0013A820
{
public:
	INIStatsRecord(const char *filename);
	~INIStatsRecord();
	void bfmeDump1191(void);
	void rva0050C90D();
	char *m_bfme48;
};

INIStatsRecord::INIStatsRecord(const char *filename)
{
	reset();
	m_bfme48 = (char *)fopen(filename, "w+");
	GetLastError();
	fprintf(m_bfme48, "Thing,Class,Draw,Tag,Model,Verts,Polys,Skel,Anim,Frames,Texture,Width,Height,Depth,TexTotl,File,Line,Desc\n");
}

// ??1BfmeD1191@@QAE@XZ @0x0050C688
INIStatsRecord::~INIStatsRecord()
{
	fclose(m_bfme48);
}

void INIStatsRecord::bfmeDump1191(void)
{
	const char *s0 = m_00.str();
	int (__cdecl *fn)(void *dst, const char *fmt, ...) = fprintf;

	fn(m_bfme48, (char *)"%s,", s0);
	fn(m_bfme48, (char *)"%s,", m_04.str());
	fn(m_bfme48, (char *)"%s,", m_08.str());
	fn(m_bfme48, (char *)"%s,", m_0C.str());
	fn(m_bfme48, (char *)"%s,", m_10.str());
	fn(m_bfme48, (char *)"%d,", m_14);
	fn(m_bfme48, (char *)"%d,", m_18);
	fn(m_bfme48, (char *)"%s,", m_1C.str());
	fn(m_bfme48, (char *)"%s,", m_20.str());
	fn(m_bfme48, (char *)"%d,", m_24);
	fn(m_bfme48, (char *)"%s,", m_28.str());
	fn(m_bfme48, (char *)"%d,", m_2C);
	fn(m_bfme48, (char *)"%d,", m_30);
	fn(m_bfme48, (char *)"%d,", m_34);
	fn(m_bfme48, (char *)"%d,", m_38);
	fn(m_bfme48, (char *)"%s,", m_3C.str());
	fn(m_bfme48, (char *)"%d,", m_40);
	fn(m_bfme48, (char *)"%s\n", m_44.str());
}

// Native50C90D..50C91D16B calls diagnostic dump50C69D then tailcalls reset50C45A
// on the same receiver. Both complete callees already verify in their homes.
// This establishes dump/reset behavior and the consumed existing record view;
// the wrapper's original name is unknown. No adjacency-based type claim.
void INIStatsRecord::rva0050C90D()
{
    bfmeDump1191();
    reset();
}
