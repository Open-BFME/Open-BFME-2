// cl: /O1 /EHsc
// Open-BFME5 conversions.

extern "C" int (__cdecl *g_bfmeFmt1191)(char *dst, const char *fmt, ...);
extern "C" __declspec(dllimport) void * __cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) int __cdecl fclose(void *);
extern "C" __declspec(dllimport) int __cdecl fprintf(void *, const char *, ...);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);

class Rva0036CA00Str
{
public:
	Rva0036CA00Str() : m_item(0) {}
	~Rva0036CA00Str();
	void clear();

	void *m_item;
};

class Rva0013A820
{
public:
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	Rva0036CA00Str m_10;
	int m_14;
	int m_18;
	Rva0036CA00Str m_1C;
	Rva0036CA00Str m_20;
	int m_24;
	Rva0036CA00Str m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	Rva0036CA00Str m_3C;
	int m_40;
	Rva0036CA00Str m_44;

	void reset();
};

class BfmeD1191 : public Rva0013A820
{
public:
	BfmeD1191(const char *filename);
	~BfmeD1191();
	void bfmeDump1191(void);
	void rva0050C90D();
	char *m_bfme48;
};

BfmeD1191::BfmeD1191(const char *filename)
{
	reset();
	m_bfme48 = (char *)fopen(filename, "w+");
	GetLastError();
	fprintf(m_bfme48, "Thing,Class,Draw,Tag,Model,Verts,Polys,Skel,Anim,Frames,Texture,Width,Height,Depth,TexTotl,File,Line,Desc\n");
}

// ??1BfmeD1191@@QAE@XZ @0x0050C688
BfmeD1191::~BfmeD1191()
{
	fclose(m_bfme48);
}

void BfmeD1191::bfmeDump1191(void)
{
	char *s0 = m_00.m_item != 0 ? (char *)m_00.m_item + 8 : (char *)"";
	int (__cdecl *fn)(char *dst, const char *fmt, ...) = g_bfmeFmt1191;

	fn(m_bfme48, (char *)"%s,", s0);
	fn(m_bfme48, (char *)"%s,", m_04.m_item != 0 ? (char *)m_04.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%s,", m_08.m_item != 0 ? (char *)m_08.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%s,", m_0C.m_item != 0 ? (char *)m_0C.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%s,", m_10.m_item != 0 ? (char *)m_10.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%d,", m_14);
	fn(m_bfme48, (char *)"%d,", m_18);
	fn(m_bfme48, (char *)"%s,", m_1C.m_item != 0 ? (char *)m_1C.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%s,", m_20.m_item != 0 ? (char *)m_20.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%d,", m_24);
	fn(m_bfme48, (char *)"%s,", m_28.m_item != 0 ? (char *)m_28.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%d,", m_2C);
	fn(m_bfme48, (char *)"%d,", m_30);
	fn(m_bfme48, (char *)"%d,", m_34);
	fn(m_bfme48, (char *)"%d,", m_38);
	fn(m_bfme48, (char *)"%s,", m_3C.m_item != 0 ? (char *)m_3C.m_item + 8 : (char *)"");
	fn(m_bfme48, (char *)"%d,", m_40);
	fn(m_bfme48, (char *)"%s\n", m_44.m_item != 0 ? (char *)m_44.m_item + 8 : (char *)"");
}

// Native50C90D..50C91D16B calls diagnostic dump50C69D then tailcalls reset50C45A
// on the same receiver. Both complete callees already verify in their homes.
// This establishes dump/reset behavior and the consumed existing record view;
// the wrapper's original name is unknown. No adjacency-based type claim.
void BfmeD1191::rva0050C90D()
{
    bfmeDump1191();
    reset();
}
