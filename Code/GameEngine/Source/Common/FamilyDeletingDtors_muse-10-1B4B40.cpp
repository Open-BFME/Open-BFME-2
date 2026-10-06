// cl: /MD
// ??_GBfmeVectorRecord001B4A39@@QAEPAXI@Z at 0x001B4B40 (28B). Scalar deleting dtor calls rowed ??1 at 0x001B4ACC plus rowed operator delete 0x0002FD60. Evidence: chain lane all callees rowed.
class BfmeVectorRecord001B4A39 {
public:
	~BfmeVectorRecord001B4A39();
};

void BfmeVectorRecord001B4A39_Delete(BfmeVectorRecord001B4A39 *p) { delete p; }
