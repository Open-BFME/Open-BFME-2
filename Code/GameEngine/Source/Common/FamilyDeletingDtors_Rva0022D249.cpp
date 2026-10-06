// cl: /MD
// ??_GRva0022D249@@QAEPAXI@Z @0x0022D904 28B: scalar deleting dtor calls rowed ??1Rva0022D249 at 0x0022D249 plus rowed operator delete 0x0002FD60. Evidence: chain packet you-just-landed callee plus 28B push-esi call-test-je delete shape.
class Rva0022D249 { public: ~Rva0022D249(); };
void famgenDelete(Rva0022D249 *p) { delete p; }
