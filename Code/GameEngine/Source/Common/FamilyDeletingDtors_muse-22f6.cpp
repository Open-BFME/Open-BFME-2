// cl: /MD
// ??_GRva0030A120@@UAEPAXI@Z @0x0030A243 28B calls rowed ??1Rva0030A120@@UAE@XZ at 0x0030A120 then delete.
// Slot 0 of vtable 0x008086E0 per tf.py show chain lane. Same 28B scalar-deleting
// shape as FamilyDeletingDtors_muse-p7k-0128 precedent with public virtual UAE.
class Rva0030A120 { public: __declspec(noinline) virtual ~Rva0030A120(); private: int m_famgen; };
Rva0030A120::~Rva0030A120() { m_famgen = 0; }
void famgenDelete(Rva0030A120 *p) { delete p; }
