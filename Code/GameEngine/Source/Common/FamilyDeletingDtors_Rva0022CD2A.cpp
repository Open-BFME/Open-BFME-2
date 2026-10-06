// cl: /MD
// ??_GRva0022CD2A@@QAEPAXI@Z @0x0022D0E5 28B: scalar deleting dtor calls rowed ??1Rva0022CD2A at 0x0022CD2A plus rowed operator delete 0x0002FD60. Evidence: chain packet you-just-landed callee plus 28B push-esi call-test-je delete shape.
class Rva0022CD2A { public: ~Rva0022CD2A(); };
void famgenDelete(Rva0022CD2A *p) { delete p; }
