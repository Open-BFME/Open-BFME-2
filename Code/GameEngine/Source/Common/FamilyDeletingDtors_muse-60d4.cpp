// cl: /MD
// ??_GRva00153729@@QAEPAXI@Z, retail 0x0015388C 28B: scalar deleting dtor calls the rowed ??1 at 0x00153729.
// Evidence: push esi mov esi ecx call 0x153729 test flag delete ret 4 shape; QAE non-virtual dtor so QAEPAXI; chain from rowed dtor 0x153729; no callers yet.
class Rva00153729 {
public:
	~Rva00153729();
};
void Rva00153729_Delete(Rva00153729 *p) { delete p; }
