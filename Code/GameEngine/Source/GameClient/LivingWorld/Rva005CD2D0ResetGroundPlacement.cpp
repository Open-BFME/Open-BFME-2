// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native [005CD2D0,005CD2EF),31B, RET0. The known shared empty
// member ABI then reset5CCB5B precede a ground placement of record20->point1C
// through receiver10. Both neutral call names are existing pins.
class Rva000B3FD0Nop { public:void noop(); };
class Rva005CCB5B {public:void rva005CCB5B();};
class Rva002BF6A7 {public:void rva002BF61B(int);};
struct Rva005CD2D0Record { char pad[0x1c];int point; };
class Rva005CD284 {
 char pad0[0x10];Rva002BF6A7 *receiver;char pad14[0xc];Rva005CD2D0Record *record;
public:void rva005CD2D0();
};
void Rva005CD284::rva005CD2D0(){
 ((Rva000B3FD0Nop*)this)->noop();
 ((Rva005CCB5B*)this)->rva005CCB5B();
 receiver->rva002BF61B(record->point);
}
