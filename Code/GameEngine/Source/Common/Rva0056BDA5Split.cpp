// cl: /Oy- /MD
// ?Rva0056BDA5Split@@YAXEEEPAE0@Z @0x0056BDA5 35B. Free byte splitter used by
// 0x003FF8B0 0x00448423. Evidence: splits low/high nibbles of arg1 and adds
// arg2/arg3 into two byte outs; EBP frame with cdecl ret.
void Rva0056BDA5Split(unsigned char a, unsigned char b, unsigned char c, unsigned char *out1, unsigned char *out2)
{
    *out1 = (unsigned char)(a >> 4);
    *out2 = (unsigned char)(a & 0xF);
    *out1 = (unsigned char)(*out1 + b);
    *out2 = (unsigned char)(*out2 + c);
}
