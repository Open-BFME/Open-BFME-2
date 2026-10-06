// cl: /MD
// ??_GRva004FF2F4@@QAEPAXI@Z at 0x004FF318 (28B). Scalar deleting dtor calls rowed ??1 at 0x004FF2F4 plus rowed operator delete 0x0002FD60. Evidence: chain lane all callees rowed.
class Rva004FF2F4 {
public:
	~Rva004FF2F4();
};

void Rva004FF2F4_Delete(Rva004FF2F4 *p) { delete p; }
