// cl: /MD
// ??_GRva00447B0E@@QAEPAXI@Z, retail 0x0044818B 28B: scalar deleting dtor calls the rowed ??1 at 0x00447B0E.
// Evidence: chain lane on landed 0x00447B0E; body calls rowed dtor 0x00447B0E plus rowed operator delete 0x0002FD60.
class Rva00447B0E {
public:
	~Rva00447B0E();
};

void Rva00447B0E_Delete(Rva00447B0E *p) { delete p; }
