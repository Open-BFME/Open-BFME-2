// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Native3EF5DA..3EF5E8 RET4: stack float copied to receiver24. Caller592B8
// passes overridden/default priority as float; no original owner name asserted.
class Rva003EF5DA {public:void rva003EF5DA(float);private:char pad0[0x24];float value24;};
void Rva003EF5DA::rva003EF5DA(float value){value24=value;}
