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

// Native5CDE31..5CDE69 is the two-argument sibling of 5CDE01: same state20
// test and same fallback receiver+C, but the true path calls the rowed
// RAMFile-write wrapper 0x5E5920 on this and the fallback is the rowed
// 0x5D1F14.  The 5E5920/5D1F14 call slots are 8-byte (ret 8).
class RAMFile { public: virtual int write(const void *, int); };
class Rva005E5884 { public: int rva005E5884(void *, int); };
class Rva005E5920 : public RAMFile
{
public:
	int rva005E5920(void *, int);
private:
	char m_pad04[4];
	Rva005E5884 *m_8;
};
class Rva005D1F14 { public: int rva005D1F14(int, int); };
class Rva005CDE31
{
public:
	virtual void rva005CDE31(void *buffer, int b);
private:
	char prefix[0x1c];
	Rva005E687F *state;
};
void Rva005CDE31::rva005CDE31(void *buffer, int b)
{
	if (state && !state->get())
		((Rva005E5920 *)this)->rva005E5920(buffer, b);
	else
		((Rva005D1F14 *)((char *)this + 0xc))->rva005D1F14((int)buffer, b);
}
