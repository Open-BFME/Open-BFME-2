// cl: /O2 /MD /EHsc
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/Rva008921B0Atof.cpp
// supplies the adapter structure and empty scoped guard. The guard under
// /EHsc preserves a call rather than a tail jump; no exception handler emits.
// Native 6CD070..6CD07E forwards one cdecl char pointer, returning x87 double.
// Its call resolves to the rowed atof import thunk at 629970 (IAT BBA550).
// No original EA adapter name is established.
extern void ji_00629970();
typedef double (__cdecl *AtofCall)(const char *text);
class EmptyGuard { public: ~EmptyGuard() {} };
extern "C" double Rva006CD070Atof(const char *text)
{
    EmptyGuard guard;
    return ((AtofCall)(void *)ji_00629970)(text);
}
