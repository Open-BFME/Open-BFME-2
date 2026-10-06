// cl: /MD
// ??_GRva0041E875@@QAEPAXI@Z @0x0041E8F6 28B.
// Deleting dtor of Rva0041E875 (dtor at 0x0041E875): calls ??1 then
// operator delete if flags&1. Evidence: calls rowed ??1 0x0041E875 and
// operator delete 0x0002FD60; shape matches retail push esi/call/test/ret 4
// and E7F2Clear notes 0x0041E8F6 as its deleting dtor.
class Rva0041E875
{
public:
	~Rva0041E875();
};
void famgenDelete(Rva0041E875 *p)
{
	delete p;
}
