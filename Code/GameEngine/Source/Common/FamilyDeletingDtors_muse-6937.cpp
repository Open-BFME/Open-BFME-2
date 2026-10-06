// cl: /MD
// ??_GRva005F8F96@@QAEPAXI@Z, retail 0x005CCCB4 28B: scalar deleting dtor calls the rowed ??1 at 0x005F8F96.
// Evidence: push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual dtor so QAEPAXI;
// chain from rowed dtor 0x005F8F96 which you landed; no callers yet.
class Rva005F8F96 {
public:
	~Rva005F8F96();
};

void Rva005F8F96_Delete(Rva005F8F96 *p) { delete p; }
