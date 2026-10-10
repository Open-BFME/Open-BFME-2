// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Native5CDE01..5CDE31 is a complete48B message-dispatch entry; WB15C0B10
// independently supplies the same state20 test and two receiver paths.
// Target proves state pointer20, fallback receiver+C and wrapper receiver0.
// The wrapper5E5BF7 itself is still banked: its native tailcall cannot yet
// be reproduced. Its GameMessage pointer input and int return follow its
// complete RET4 body, WB15FF4F0 and this caller, not a guessed original name.
// WB vtable association proves this dispatch is virtual; original class and
// method identity remain unresolved and address-derived names are retained.
class GameMessage;
class Rva005CDA3D { public:int rva005E5BF7(GameMessage*); };
class Rva005E687F { public:unsigned char get()const; };
class Rva005D1F45 { public:int rva005D1FD3(GameMessage*); };
class Rva005CDE01 { public:virtual int rva005CDE01(GameMessage*);private:char prefix[0x1c];Rva005E687F*state; };
int Rva005CDE01::rva005CDE01(GameMessage*msg){
 if(state && !state->get())return((Rva005CDA3D*)this)->rva005E5BF7(msg);
 return((Rva005D1F45*)((char*)this+0xc))->rva005D1FD3(msg);
}
