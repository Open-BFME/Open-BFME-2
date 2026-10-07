// ?rva003ECAB3@Rva003ECAB3@@QAEXM@Z
// partial score=0.92 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva003ECAB3@Rva003ECAB3@@QAEXM@Z @0x003ECAB3 45B
// Evidence: called from 0x003ECBED in FUN_007ecb94; no callees; SSE scale of 17 floats by scalar; prev next share flags.

class Rva003ECAB3
{
public:
	void rva003ECAB3(float scale);

private:
	float m[17];
};

// ?rva003ECAB3@Rva003ECAB3@@QAEXM@Z
void Rva003ECAB3::rva003ECAB3(float scale)
{
	m[0] *= scale;
	int n = 16;
	float *p = &m[1];
	do
	{
		*p *= scale;
		p++;
	} while (--n != 0);
}
