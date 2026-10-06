// cl: /MD
// ??_GRva0029E00D@@QAEPAXI@Z, retail 0x0029E0FE 28B: scalar deleting dtor calls the rowed ??1 at 0x0029E00D plus rowed operator delete 0x0002FD60.
class Rva0029E00D {
public:
	~Rva0029E00D();
};

void Rva0029E00D_Delete(Rva0029E00D *p) { delete p; }
