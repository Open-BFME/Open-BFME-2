// cl: /O1 /G7 /arch:SSE /MD
// Native 0x004216A2..0x004216D3, 49 bytes: position helper used by
// Formation::optimizeUnits at 0x0042550E (WB 0x0113B070 FormationAssistant.cpp431)
// and its formation siblings. No original helper name or argument class identity
// is established; preserve the address-derived name and consuming float views.
// Target adds slot +0x18/+0x1C to the supplied base x/y and writes output z=0.
// The y and x temporaries remain live until the x/y/z stores, matching retail.
void __cdecl rva004216A2(float *out, const float *base, const float *other)
{
float y=other[7]+base[1];float x=other[6]+base[0];out[0]=x;out[1]=y;out[2]=0;
}
