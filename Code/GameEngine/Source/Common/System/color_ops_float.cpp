// cl: /DNDEBUG /MD
//
// ?Rva002D2ACAGet@@YAXHPAM000@Z
// RVA 0x002D2ACA size 114. Float version of GameGetColorComponents (prev row
// 0x002D2A9F): unpacks int color to 0..1 floats via 1/255 reciprocal at
// 0x007BB8F0 (unsigned fixup 2^32 at 0x007C26EC for the alpha x87 path).
// Evidence: 5 callers pass (color, 4 float outs); param order red,green,blue,
// alpha matches prev byte version; retail computes alpha first (x87 fild path
// for unsigned >>24) then R/G/B via SSE cvtsi2ss; no callees.

void __cdecl Rva002D2ACAGet(int color, float *red, float *green, float *blue, float *alpha)
{
	*alpha = ((unsigned int)color >> 24) * (1.0f / 255.0f);
	*red = ((color >> 16) & 0xff) * (1.0f / 255.0f);
	*green = ((color >> 8) & 0xff) * (1.0f / 255.0f);
	*blue = (color & 0xff) * (1.0f / 255.0f);
}
