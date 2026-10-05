// ?Rva009A9980@@YAXPBEHIIPAEHII@Z
// partial score=0.8 date=2026-10-05
// cl: /DNDEBUG /MD /O2
// Lane A 0x001BA3C0..0x001BA45B: demo-reloc Scale1D callback used by
// matched Rva009A9AD0Scale2D. Retail ret and eight stack arguments establish
// __cdecl ABI; arithmetic and source-step loop follow target disassembly.
// Near miss: VC7.1 uses an unconditional EBP save and different scheduling.
typedef unsigned char Byte;
void __cdecl Rva009A9980(const Byte *source, int sourcePitch,
    unsigned int sourceScale, unsigned int sourceWidth,
    Byte *dest, int destPitch, unsigned int destScale, unsigned int destWidth)
{
    unsigned int half = destScale >> 1;
    Byte left = *source;
    source += sourcePitch;
    Byte right = *source;
    unsigned int accumulator = 0;
    unsigned int leftWeight = destScale;
    unsigned int end = destWidth * destPitch;
    for (unsigned int i = 0; i < end; i += destPitch)
    {
        dest[i] = (Byte)((right * accumulator + half + left * leftWeight) / destScale);
        accumulator += sourceScale;
        while (accumulator > destScale)
        {
            left = *source;
            right = source[sourcePitch];
            source += sourcePitch;
            accumulator -= destScale;
        }
        leftWeight = destScale - accumulator;
    }
}
