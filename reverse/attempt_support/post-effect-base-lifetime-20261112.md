# Post-effect base lifetime at RVA 0x0011646E

The shared abstract declaration emits the full table at RVA
`0x007CFB24` from the real destructor. In the constructor trial, the
member initializer reproduced all 13 retail bytes. The constructor
object also emitted a competing 28-byte scalar deleting destructor.
It calls the out-of-line destructor at RVA `0x0011647B`, where the
retail 29-byte scalar body inlines the vptr store.

Sharing an inline base destructor made the compiler inline that store
in `LookupTablePostEffect::~LookupTablePostEffect` at `0x00111B9A`,
whose retail body calls the out-of-line destructor. Both the body
and a cleanup row failed verification. The final source keeps the
verified constructor store and the out-of-line base destructor. The
constructor and derived objects emit no second copy of the base table
or scalar deleting destructor. A future constructor cleanup needs
matching scalar copies and the derived cleanup call and EH graph.
