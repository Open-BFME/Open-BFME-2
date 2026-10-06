// cl: /MD
// ??_GRva0022D214@@QAEPAXI@Z @0x0022D8E8 28B: scalar deleting dtor calls rowed ??1Rva0022D214 at 0x0022D214 plus rowed operator delete 0x0002FD60. Evidence: chain packet you-just-landed callee plus 28B push-esi call-test-je delete shape.
class Rva0022D214 { public: ~Rva0022D214(); };
void famgenDelete(Rva0022D214 *p) { delete p; }
