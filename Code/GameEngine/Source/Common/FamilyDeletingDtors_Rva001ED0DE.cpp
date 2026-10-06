// cl: /MD
// ??_GRva001ED0DE@@QAEPAXI@Z @0x001ED269 28B.
// Deleting dtor via rowed ??1 at 0x001ED0DE plus rowed delete 0x0002FD60.
// Evidence: callee rowed 0x001ED0DE; same 28B shape as rowed 0x001ECB91.
struct Rva001ED0DE { ~Rva001ED0DE(); };
void famgenDelete(Rva001ED0DE *p) { delete p; }
