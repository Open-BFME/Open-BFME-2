// cl: /MD
// ??_GRva00410688@@QAEPAXI@Z, retail 0x00410792 28B: scalar deleting dtor calls the rowed ??1 at 0x00410688 plus rowed operator delete 0x0002FD60.
class Rva00410688 {
public:
	~Rva00410688();
};

void Rva00410688_Delete(Rva00410688 *p) { delete p; }
