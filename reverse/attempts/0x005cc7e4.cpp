// ?dispose@Rva005CC7E4Mid@@QAEPAVRva005CC803@@I@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 5CC7E4..5CC803: known secondary-vtable slot at874E68,
// ECX-8 complete-object cleanup5CC803, flags-bit0 invokes delete2FD60.
// BF1 f989 stream deleting-dtor shape is a guide; stream identity is refuted.
// Callable contract only; original owner and complete class extent unknown.
void operator delete(void *);
class Rva005CC803 { public: ~Rva005CC803(); };
class Rva005CC7E4Mid { public: Rva005CC803 *dispose(unsigned int); };
Rva005CC803 *Rva005CC7E4Mid::dispose(unsigned int flags) {
    Rva005CC803 *object = reinterpret_cast<Rva005CC803 *>(
        reinterpret_cast<char *>(this) - 8);
    object->~Rva005CC803();
    if (flags & 1) ::operator delete(object);
    return object;
}
