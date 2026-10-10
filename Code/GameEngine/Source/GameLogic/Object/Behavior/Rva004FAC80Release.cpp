// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
// ?rva004FAC80@Rva004FAC80@@QAEXXZ @0x004FAC80 25B
// Evidence: Native4FAC80..4FAC99 RET, ctor4FAC6B calls member ctor330757 at+4; same ctor installs primary vptr and derived4FADF4 invokes it. Existing parent view establishes nonpolymorphic secondary base+4; ordinary nullable base conversion plus inline release helper gives native LEA NEG SBB AND and free30830; no integer pointer arithmetic. Member and complete class original names unresolved.
extern "C" void __cdecl free(void*);
class Rva004FAC80Primary {public:virtual void anchor();};
class Rva00330757Member {public:void*buffer;__forceinline void release(){if(buffer)free(buffer);}};
class Rva004FAC80:public Rva004FAC80Primary,public Rva00330757Member {public:void rva004FAC80();};
void Rva004FAC80::rva004FAC80(){static_cast<Rva00330757Member*>(this)->release();}
