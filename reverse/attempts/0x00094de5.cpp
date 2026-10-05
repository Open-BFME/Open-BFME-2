// ?rva00094DE5@@YAXPAM@Z
// partial score=0.8 date=2026-10-05
// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG
// snapshot of 0x94DE5 attempt. Retail mixes SSE float loads with an x87
// float->double conversion feeding the _sqrt thunk; every C++ spelling tried
// (named len local, inline expr, const/non-const, math.h/manual decl, /G7 on/off,
// /arch:SSE/SSE2) flips the WHOLE function to x87+frameless as soon as any
// double op exists (bisected: double local or double call arg both flip).
// Landed precedent shake@W3DView only mixes across separate expressions.
// Next: MASM x87-shape port if fleet policy allows, else new codegen insight.
// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG
// ?rva00094DE5@@YAXPAM@Z @0x00094DE5 71B: squared-length probe over three
// floats that also feeds the CRT sqrt import thunk (pinned _sqrt at
// 0x0062921C); the result is discarded. Honest address-derived name;
// boundary verified (push ebp at 0x94DE5, pops + ret at end).

extern "C" double sqrt(double v);
void rva00094DE5(float *v)
{
	float len = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	sqrt(len);
}
