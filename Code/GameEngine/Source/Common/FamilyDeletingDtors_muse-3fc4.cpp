// cl: /MD
// ??_GBfmeStringRecord005D511F@@QAEPAXI@Z @0x005D5266 28B; calls rowed ??1BfmeStringRecord005D511F@@QAE@XZ @0x005D51B9 then delete 0x0002FD60.
// Evidence: retail push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual dtor so QAEPAXI; same shape as BfmeStringRecord00204A30 precedent.
// ??_GBfmeStringRecord005D511F@@QAEPAXI@Z @0x005D5266
class BfmeStringRecord005D511F { public: ~BfmeStringRecord005D511F(); };
void famgenDelete(BfmeStringRecord005D511F *p) { delete p; }
