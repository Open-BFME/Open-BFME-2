// cl: /O1 /MD
// ??_GRva005E0DC0@@QAEPAXI@Z @0x005E11E8 28B; calls rowed ??1Rva005E0DC0@@QAE@XZ @0x005E0DC0 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual so QAEPAXI; chain from 0x005E0DC0 landing.
class Rva005E0DC0 { public: ~Rva005E0DC0(); };
// ?famgenDelete005E0DC0@@YAXPAVRva005E0DC0@@@Z present-unmatched
void famgenDelete005E0DC0(Rva005E0DC0 *p) { delete p; }
