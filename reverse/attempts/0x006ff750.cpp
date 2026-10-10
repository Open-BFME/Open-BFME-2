// ?callback006FF750@@YAPAVAptValue@@PAV1@H@Z
// partial score=0.9864 date=2026-10-10
// ?callback006FF750@@YAPAVAptValue@@PAV1@H@Z @0x006FF750 241B
// partial score=0.9864 date=2026-10-10 (cluster-idiom port; same single 4B swap as prior bank)
// Prior bank (old-TU idiom, check-macro) superseded here by Rva006ff5d0Cluster.cpp
// idiom (explicit asserts, m_nElements stack) so the body can land directly.
// 237/241 exact; only diff is +0x47: retail `test esi,esi; mov edi,eax`,
// ours `mov edi,eax; test esi,esi` (Create-return save vs nParams re-test order).
// Tried 2026-10-10: (a) ternary+barrier (this file, single swap); (b) explicit
// if/else-assign + barrier (identical output); (c) plain create, no barrier
// (WORSE: prologue scheduling breaks at +0x16). Prior seat tried 11
// allocation/branch/barrier forms + G6/G7 flag trials. Do NOT repeat those.
// Required context (already in Rva006ff5d0Cluster.cpp): EAStringC member decl
// `EAStringC &Rva006D4F00Append(const EAStringC &)` (= rowed 0x006D4F00),
// `void rva006FD4C0(EAStringC *)` (= rowed 0x006FD4C0), _ReadWriteBarrier.
// Next lead: what source form makes MSVC7.1 emit test-before-mov after the
// Create call (latency-hiding order) instead of mov-before-test.
AptValue *callback006FF750(AptValue *, int nParams)
{
    if (!(nParams <= 1)) {
        g_bfmeAptAssertAtE17734("nParams <= 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x5A7);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    AptString *result = (nParams ? AptString::Create() : AptString::Create());
    _ReadWriteBarrier();
    if (nParams) {
        AptValue *value = g_aptDateInterpreter.stack.At(0);
        if (value->isString()) {
            EAStringC temp;
            value->toString(temp);
            rva006FD4C0(&temp);
            result->string.Rva006D4F00Append(temp);
        }
    }
    return (AptValue *)result;
}
