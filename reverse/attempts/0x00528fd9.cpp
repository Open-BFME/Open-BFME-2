// ?reset@Rva00528FD9Owner@@QAEXXZ
// partial score=0.9 date=2026-10-05
// cl: /O1
// Target Ghidra528FD9..528FE0 7B: [this] forwards to169B528F30.
// Full callee ends528FD9 RET0 and resets flags/strings/six records.
// Callee is unrowed; pointer owner and original names remain unproved.
class Rva00528F30Target {public:void reset();};
class Rva00528FD9Owner {public:void reset();private:Rva00528F30Target*target;};
void Rva00528FD9Owner::reset(){target->reset();}
