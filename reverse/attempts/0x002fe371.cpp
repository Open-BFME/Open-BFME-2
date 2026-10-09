// ?invoke@Rva002FE371Forward@@QAEXPAVObject@@@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /arch:SSE /G7
// BF1 f989 Common/BfmeConv880.cpp is the source expression guide only.
// Native2FE371/17 calls actual2FE193 using receiverword8 and stackword4,
// restores the two cdecl call arguments, and RET4. Its original receiver
// identity and declared result remain unresolved. Object/AI declarations
// reuse the existing actual callee candidate, whose478B provider is not
// rowed; they are not new identity evidence from this wrapper.
class Object;
class AI {
public: static bool rva002FE193(Object *, Object *);
};
class Rva002FE371Forward {
public: void invoke(Object *argument);
private: unsigned char unknown0[8]; Object *word8;
};
void Rva002FE371Forward::invoke(Object *argument)
{
    AI::rva002FE193(word8, argument);
}
