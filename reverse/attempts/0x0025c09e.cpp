// ??0Rva0025C09E@@QAE@HHMMMMH@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /MD /GX /Oy- /arch:SSE /G6
// ?rva0025C09E@Rva0025C09E@@QAEHHMMMMH@Z @0x0025C09E (58B): 7-arg ctor
// initializing 1 int + 4 floats + 1 int. Retail (frame, /Oy-): stores
// [ecx+4]=F32[ebp+16], [ecx+8]=F32[ebp+20], [ecx+0]=I32[ebp+12],
// [ecx+12]=F32[ebp+24], [ecx+16]=F32[ebp+28], [ecx+20]=I32[ebp+32];
// [ebp+8] unused. Single-precision movss; int moves via eax; ret 28.
// Address-derived; no callees.
class Rva0025C09E
{
public:
	Rva0025C09E(int ignored, int a, float b, float c, float d, float e, int f);
private:
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	int m_14;
};

// ?rva0025C09E@Rva0025C09E@@QAEHHMMMMH@Z (14-char mangling guessed for
// (int,int,float,float,float,float,int); the byte gate is the proof –
// rename on mismatch via --replace-existing)
Rva0025C09E::Rva0025C09E(int ignored, int a, float b, float c, float d, float e, int f)
{
	(void)ignored;
	m_04 = b;
	m_08 = c;
	m_00 = a;
	m_0C = d;
	m_10 = e;
	m_14 = f;
}
