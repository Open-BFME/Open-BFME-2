// cl: /O1 /Oy- /MD
// ?Rva0056BDA5Split@@YAXEDDPAE0@Z @0x0056BDA5 35B. Free byte splitter used by
// 0x003FF8B0 0x00448423. Native deserializer calls pass signed -1/-2
// offsets; O1 retains the exact 35B provider and existing hero decoder. Evidence: splits low/high nibbles of arg1 and adds
// arg2/arg3 into two byte outs; EBP frame with cdecl ret.
void Rva0056BDA5Split(unsigned char a, char b, char c, unsigned char *out1, unsigned char *out2)
{
    *out1 = (unsigned char)(a >> 4);
    *out2 = (unsigned char)(a & 0xF);
    *out1 = (unsigned char)(*out1 + b);
    *out2 = (unsigned char)(*out2 + c);
}
