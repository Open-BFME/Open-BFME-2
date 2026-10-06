// ??0Gen_00920A20@@QAE@H@Z
// partial score=0.95 date=2026-10-06
// cl: /O2 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??0Gen_00920A20@@QAE@H@Z, retail 0x0013EA00 (43 bytes). Small mode ctor:
// stores 4 at +0/+4, branchless (arg == 1 ? 0 : 4) at +8 via sub-neg-sbb-and,
// zeros at +0xC/+0x10. The `this` pointer lives in EAX from byte 0 (mov
// eax,ecx) with ECX as zero scratch, which an int* alias produces; member
// access keeps `this` in ECX instead. Callers at 0x00131B8F, 0x00132109 and
// 0x00132887 name this exact mangling (LINK BONUS for 2 files).
class Gen_00920A20
{
public:
	Gen_00920A20(int mode);
};

Gen_00920A20::Gen_00920A20(int mode)
{
	int *p = (int *)this;
	p[3] = 0;
	p[4] = 0;
	int v = (mode - 1 ? 4 : 0);
	p[0] = 4;
	p[1] = 4;
	p[2] = v;
}
