// cl: /MD
// ??_GBfmeOwnVVD@@QAEPAXI@Z 0x0042E9D0 28B: scalar deleting dtor calls rowed ??1BfmeOwnVVD at 0x0042E85C plus rowed operator delete 0x0002FD60; vtable slot 1 of 0x0083C938
class BfmeOwnVVD {
public:
	~BfmeOwnVVD();
};

void BfmeOwnVVD_Delete(BfmeOwnVVD *p) { delete p; }
