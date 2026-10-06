// cl: /MD
// ??_GRva004BA1C8@@QAEPAXI@Z, retail 0x004BA2CD 28B: scalar deleting dtor calls the rowed ??1 at 0x004BA1C8.
// Evidence: body calls rowed dtor 0x004BA1C8 plus rowed operator delete 0x0002FD60; no callers; shares family
// with dtor/assign/copy at 0x004BA1C8/0x004BA291/0x004BA1D0.
class Rva004BA1C8 {
public:
	~Rva004BA1C8();
};

void Rva004BA1C8_Delete(Rva004BA1C8 *p) { delete p; }
