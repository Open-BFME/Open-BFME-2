// cl: /MD
// ??_GRva005D1846@@QAEPAXI@Z @0x005D1891 28B deleting dtor for non-virtual Rva005D1846 via placeholder scalar dtor plus delete.
// Evidence: chain from rowed ??1 0x005D1846; retail push esi call ??1 test delete ret 4; non-virtual so QAEPAXI@Z.
class Rva005D1846 { public: ~Rva005D1846(); };
void famgenDelete(Rva005D1846 *p) { delete p; }
