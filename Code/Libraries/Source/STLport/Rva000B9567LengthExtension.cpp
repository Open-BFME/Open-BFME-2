// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native B9567..B9574 RET0. Independently rowed B65FD computes the base
// contribution; this helper adds the receiver word at +18. The native saved
// ESI requires a declaration-only call boundary; combining both bodies lets
// the compiler retain this in volatile EDX because it knows that callee.
// The pointer views expose only the consumed prefix and are never allocated;
// original receiver and operation spelling remain unknown.
class Rva000B65FD {public:int rva000B65FD();};
class Rva000B9567 {
public:
    char unknown00[0x18]; int extra;
    int rva000B9567();
};
int Rva000B9567::rva000B9567()
{
    return reinterpret_cast<Rva000B65FD *>(this)->rva000B65FD()+extra;
}
