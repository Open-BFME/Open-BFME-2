// cl: /MD /EHsc /DNDEBUG
//
// ?rva0009AACF@@YGXHM@Z @0x0009AACF 44B: free function clamping a float
// argument at >= 0 and forwarding the render pointer and float to the matched callee
// 0x0010E87A when the int is nonzero. Honest address-derived names;
// boundary verified (frame at 0x9AACF, ret 8 at end).

class RenderObjClass;
bool Rva0010E87A_SetOpacity(RenderObjClass *,float);

// ?rva0009AACF@@YGXHM@Z
void __stdcall rva0009AACF(int b, float a)
{
	if (0.0f >= a)
		a = 0.0f;
	if (b)
		Rva0010E87A_SetOpacity(reinterpret_cast<RenderObjClass *>(b), a);
}
