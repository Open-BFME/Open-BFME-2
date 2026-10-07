// cl: /DNDEBUG /MD
// Existing wrapper61F0F0 supplies the receiver in ECX and one pointer
// argument to the complete native RET4 at180FD0. Its existing callee pin
// names this operation. Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// game/GameEngine/Source/Common/Q1GlobalGuardedForwarders.cpp corroborates
// the empty receiver operation. Retail folds it with wide streambuf imbue.
// Keep this definition out of the caller TU: seeing the empty body lets
// this compiler eliminate the native guarded call even with noinline.
// Only the called ABI is represented; no receiver layout is inferred.
class Q1Receiver0134FAAC {
public:
    void m009EC960(void *value);
};
void Q1Receiver0134FAAC::m009EC960(void *value)
{
}
