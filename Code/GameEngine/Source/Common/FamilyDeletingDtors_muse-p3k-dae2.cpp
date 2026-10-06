// cl: /MD
// ??_GRva0027EA49@@QAEPAXI@Z, retail 0x005C66F0 28B: scalar deleting dtor calls the rowed ??1 at 0x0027EA49.
// Evidence: push esi mov esi ecx call test flag delete ret 4 shape; QAE non-virtual dtor so QAEPAXI.
class Rva0027EA49 {
public:
	~Rva0027EA49();
};

void Rva0027EA49_Delete(Rva0027EA49 *p) { delete p; }
