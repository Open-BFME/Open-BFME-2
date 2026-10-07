// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Target 2D3869..2D387A is a complete 17-byte thiscall leaf. It saves
// receiver word 0, clears that word before any deallocation, then passes
// a nonnull saved pointer to the independently verified scalar operator
// delete at 2FD60 (mem_ops.cpp). Only this one-pointer prefix is known;
// the original owner, payload type and allocation extent are unknown.
void __cdecl operator delete(void *);
struct Rva002D3869OwnedPrefix {
    void *data;
    void release();
};
void Rva002D3869OwnedPrefix::release() {
    void *saved=data;
    data=0;
    if (saved) ::operator delete(saved);
}
