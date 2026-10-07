// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE /G7
// Target evidence: Ghidra boundary 0x00177F34..0x00177F82, with a terminal ret.
// Five cdecl stack arguments are visible: output, byte stride, two floats, count.
// The body writes two floats per step, then transforms the pair using 1.0f. The
// target's pool value at VA 0x00BBB8D8 is independently confirmed as 1.0f. The
// address-derived name preserves identity uncertainty.

extern "C" void Rva00177F34(float *output, int stride, float first,
                            float second, int count)
{
    register int remaining = count;
    if (remaining == 0)
        return;

    float zero = 0.0f;
    float one = 1.0f;
    do {
        output[0] = first;
        output[1] = second;

        if (first != 0.0f) {
            first = zero;
            second = one - second;
        } else {
            first = one;
        }

        output = reinterpret_cast<float *>(
            reinterpret_cast<char *>(output) + stride);
    } while (--remaining != 0);
}
