// cl: /MD
// ??_GRva002E5711@@QAEPAXI@Z @0x002E5D46 28B; calls rowed ??1Rva002E5711@@QAE@XZ @0x002E5711 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual dtor so QAEPAXI; chain from 0x002E5711 landing.
class Rva002E5711 { public: ~Rva002E5711(); };
void famgenDelete(Rva002E5711 *p) { delete p; }
