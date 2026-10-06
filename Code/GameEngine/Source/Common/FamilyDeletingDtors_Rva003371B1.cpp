// cl: /MD
// ??_GRva003371B1@@QAEPAXI@Z @0x003373BD 28B: scalar deleting dtor calls rowed ??1Rva003371B1 at 0x003372B7 plus rowed operator delete 0x0002FD60. Evidence: chain packet you-just-landed callee plus 28B push-esi call-test-je delete shape.
class Rva003371B1 { public: ~Rva003371B1(); };
void famgenDelete(Rva003371B1 *p) { delete p; }
