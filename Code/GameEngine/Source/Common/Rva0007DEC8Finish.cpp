// ?Rva0007DEC8Add@@YAXPAMMMPBM@Z
// cl: /MD
//
// ?Rva0007DEC8Add@@YAXPAMMMPBM@Z @0x0007DEC8, 39B. Free SSE add of a 2-float
// vector: out[0]=b[0]+ax, out[1]=b[1]+ay, all through movss/addss.
// Callers 0x000831D4 0x002F8C64 0x006B31F1; it also unlocks 0x006B3100
// 0x002F8B00 0x0008304A.
//
// Retail loads b[0] and b[1] into xmm0/xmm1 back to back, then computes BOTH
// adds before EITHER store:
//
//   mov eax,[esp+10] ; movss xmm0,[eax] ; movss xmm1,[eax+4]
//   mov eax,[esp+4]
//   addss xmm0,[esp+8] ; addss xmm1,[esp+0xc]
//   movss [eax],xmm0 ; movss [eax+4],xmm1
//
// The natural `out[0]=b[0]+ax; out[1]=b[1]+ay;` interleaves add/store/add/store
// (add,store,add,store), and the `float x=..., y=...` form makes cl re-pair the
// two loaded values the other way round so the adds come out in the opposite
// order. Routing both results through one 2-float temp is what keeps the load
// pairing and the add order both aligned; the array form and the struct form are
// byte-identical here.
void Rva0007DEC8Add(float *out, float ax, float ay, const float *b)
{
	float r[2];
	r[0] = b[0] + ax;
	r[1] = b[1] + ay;
	out[0] = r[0];
	out[1] = r[1];
}
