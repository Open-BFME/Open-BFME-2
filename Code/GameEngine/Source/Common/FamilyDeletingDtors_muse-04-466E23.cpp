// cl: /MD
// ??_GRva00466E23@@QAEPAXI@Z @0x00466EC2 28B; calls rowed ??1Rva00466E23@@QAE@XZ @0x00466E23 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual dtor so QAEPAXI; chain from 0x00466E23 landing.
class Rva00466E23 { public: ~Rva00466E23(); };
void famgenDelete(Rva00466E23 *p) { delete p; }
