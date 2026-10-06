// cl: /MD
// ??_GRva0022E1BC@@QAEPAXI@Z @0x0022E1A0 28B: scalar deleting dtor calls rowed ??1Rva0022E1BC at 0x0022E1BC plus rowed operator delete 0x0002FD60. Evidence: chain packet you-just-landed callee plus 28B push-esi call-test-je delete shape plus prev RvaTreeValueEraseFamily next Rva0022E1BCDtor.
class Rva0022E1BC { public: ~Rva0022E1BC(); };
void famgenDelete(Rva0022E1BC *p) { delete p; }
