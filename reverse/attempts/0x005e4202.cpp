// ?rva005E4202@Rva005E4202@@QAEXXZ
// partial score=0.8515151515151516 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP=
class Rva005E3A76 {public:void rva005E3A76();};
class Rva005F422C {public:void rva005F422C();};
class Rva005F4891 {public:void rva005F4891();};
struct PeerParent1 {char*receiver;__forceinline ~PeerParent1(){reinterpret_cast<Rva005F422C*>(receiver-0x10)->rva005F422C();}};
struct PeerParent2 {char*receiver;__forceinline ~PeerParent2(){reinterpret_cast<Rva005F4891*>(receiver-0x10)->rva005F4891();}};
class Rva005E4202 {public:void rva005E4202();};
class Rva005E426F {public:void rva005E426F();};
void Rva005E4202::rva005E4202(){
 PeerParent1 parent={reinterpret_cast<char*>(this)};
 char*complete=reinterpret_cast<char*>(this)-0x24;
 char*view=complete?reinterpret_cast<char*>(this)-0x14:0;
 reinterpret_cast<Rva005E3A76*>(view+0x14)->rva005E3A76();
}
void Rva005E426F::rva005E426F(){
 PeerParent2 parent={reinterpret_cast<char*>(this)};
 char*complete=reinterpret_cast<char*>(this)-0x30;
 char*view=complete?reinterpret_cast<char*>(this)-0x14:0;
 reinterpret_cast<Rva005E3A76*>(view+0x14)->rva005E3A76();
}
