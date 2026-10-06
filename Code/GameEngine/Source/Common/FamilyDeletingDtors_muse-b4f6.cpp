// cl: /MD
// ??_GRva00151DAB@@QAEPAXI@Z @0x00151eb1 28B.
// Scalar deleting dtor for Rva00151DAB whose ??1 is rowed at 0x00151DAB.
// Public non-virtual QAE so minimal shim plus delete emits the ??_G.

class Rva00151DAB { public: ~Rva00151DAB(); };
void famgenDelete(Rva00151DAB *p) { delete p; }
