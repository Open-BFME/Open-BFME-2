// cl: /O1 /G7 /DNDEBUG /MD
// ?rva0046333B@Rva0046333B@@QAE_NPAH00000@Z @0x0046333B 152B
// Evidence: Native46333B..4633D3 PUSH EBP entry and RET24 prove six integer out pointers. Secondary interface20 data minus1C flag80; virtual capacity28 reserved69 current51 and established pair46247D; contained node8 object template4 flag109bit0. Address-derived purpose and types remain structural inference; prior no-boundary verdict refuted by complete retail prologue and return. Full152 verified no pins.
struct Rva0046247DPair {void*a;void*b;};
class Rva0046247D {public:void*rva0046247D(Rva0046247DPair&);};
struct Data {char pad[0x80];bool enabled;};
struct Template {char pad[0x109];unsigned char kindof;};
struct Object {void*vptr;Template*type;};
struct Node {Node*next;void*prev;Object*object;};
class Rva0046333B {public:
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual int capacity();
virtual void d29();
virtual void d30();
virtual void d31();
virtual void d32();
virtual void d33();
virtual void d34();
virtual void d35();
virtual void d36();
virtual void d37();
virtual void d38();
virtual void d39();
virtual void d40();
virtual void d41();
virtual void d42();
virtual void d43();
virtual void d44();
virtual void d45();
virtual void d46();
virtual void d47();
virtual void d48();
virtual void d49();
virtual void d50();
virtual int current();
virtual void d52();
virtual void d53();
virtual void d54();
virtual void d55();
virtual void d56();
virtual void d57();
virtual void d58();
virtual void d59();
virtual void d60();
virtual void d61();
virtual void d62();
virtual void d63();
virtual void d64();
virtual void d65();
virtual void d66();
virtual void d67();
virtual void d68();
virtual int reserved(bool);
bool rva0046333B(int*,int*,int*,int*,int*,int*);
private:__forceinline Data*data(){return *reinterpret_cast<Data**>(reinterpret_cast<char*>(this)-0x1C);}
};
bool Rva0046333B::rva0046333B(int*a,int*b,int*c,int*d,int*e,int*f){
 *d=0;*e=0;*f=0;
 if(data()->enabled){
  *a=capacity();
  *b=reserved(false)+current();
  Rva0046247DPair pair;
  reinterpret_cast<Rva0046247D*>(reinterpret_cast<char*>(this)-0x20)->rva0046247D(pair);
  *c=0;
  Node**head=static_cast<Node**>(pair.b);
  for(Node*n=(*head)->next;n!=*head;n=n->next)if(n->object->type->kindof&1)++*c;
  return true;
 }
 *a=0;*b=0;return false;
}
