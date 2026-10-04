// ?rva001F34F6@@YAEPBURva001F34F6ByteView@@@Z
// partial score=1.0 date=2026-10-05
// Whole readByte.cpp donor @5cc75ddda6455c338a5068307e587a793f96d6b3.
// Blob eb7d42fbb3d74056c8b6e9483122a0e78cadea49; no includes.
// Exact 8-byte physical ABI draft. Standalone entry remains unproved:
// no independent target Ghidra entry, direct transfer, or address reference.
// Owner and byte meaning are unresolved; head models only the witnessed offset.
struct Rva001F34F6ByteView {unsigned char head[0x1C];unsigned char value;};
unsigned char rva001F34F6(const Rva001F34F6ByteView *view) {return view->value;}