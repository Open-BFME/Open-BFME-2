// cl: /MD
// ??_GRva0022CFE6@@QAEPAXI@Z @0x0022D1C3 28B: scalar deleting dtor calls rowed ??1Rva0022CFE6 at 0x0022CFE6 plus rowed operator delete 0x0002FD60. Evidence: chain packet you-just-landed callee plus 28B push-esi call-test-je delete shape.
class Rva0022CFE6 { public: ~Rva0022CFE6(); };
void famgenDelete(Rva0022CFE6 *p) { delete p; }
