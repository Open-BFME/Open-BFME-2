// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native call at 00347E9D passes the same state receiver, no stack arguments,
// to the shared D43D0 three-byte zero result. No original method name inferred.
// Complete relocation-free xor eax,eax/ret twin; zero unique-byte gain.
enum StateReturnType{STATE_CONTINUE=0,STATE_FAILURE=-2};
class Rva00347E4CMachine;
class Rva00347E4CState{public:
 StateReturnType onEnter();
 int rva000D43D0();
 unsigned char pad[0x18];Rva00347E4CMachine*machine;
};
int Rva00347E4CState::rva000D43D0(){return 0;}
