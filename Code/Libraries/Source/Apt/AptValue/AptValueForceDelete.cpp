// cl: /MD
// APT0.19.03 Xbox final PDB/MAP names ForceDelete and the virtual interface.
// Target constructor6DCD20 installs vtable VA CEAED0 after which its type setter
// names AptValue/AptValue.inl. Slot8 of that table contains this26-byte body.
// Recovered ReleaseValues6E6D90 invokes slot8 for zero-refcount values. Target
// ForceDelete itself calls slots28/2C then scalar deleting destructor slot38.
// PreDestroy/DestroyGCPointers spellings come from donor, virtual offsets and
// deletion flag1 from target. No unused method identities or full layout claimed.
#include "../AptValue.h"
void AptValue::ForceDelete() { PreDestroy(); DestroyGCPointers(); delete this; }
