# W3DTreeBufferUpdate: one native header adoption

Base fb05fff834b54b18eab6adc29ff9b20e4bf3734f already integrates master17de7e.
The picker served W3DTreeBuffer's five remaining header consumers. Only the
fieldless W3DTreeBufferUpdate.cpp view is ready: it declares the existing protected
updateTopplingTree(TTree*) and friendship with Rva000EDB47 and reads no layout of
W3DTreeBuffer. The actual strong provider is W3DTreeBuffer.cpp, retail0x000EA746,
1633bytes, ?updateTopplingTree@W3DTreeBuffer@@IAEXPAUTTree@@@Z. No name or ABI is invented.

The authored, opaque header gains only that same protected declaration, friendship
and a struct TTree forward declaration. The normal adopt command replaces the private
view with the canonical include. TTree bodies remain separate existing views; this
does not assert that their complete layouts agree. No field, base, vtable, special
member, symbol key, row, pin, alias or allowance changes.

Normal build before/after:61/61 code rows across the consumer and existing provider.
Native header_adopt_lane adopt passes; accept with the explicit current provider
passes and retires exactly the Update consumer's queue key. Its persisted acceptance
context stores paths, not a bypass or verdict. Ordinary object comparison preserves
all26 consumer runtime nodes and165 provider nodes, bytes, relocation targets, external
definitions, COMDAT choices and SafeSEH input sequence. Provider raw COFF is unchanged.
Native header/debt/byte/link checks remain enabled in commit and publication hooks.

Other four queue keys remain: BaseHeightMapConstructor needs a complete constructor/
285800-byte storage view; BaseHeightMapRva000687EF reads count at0x44540 and calls EAFA4;
FlatHeightMap writes terrain at0x44555 through its setter; W3DTreeBuffer.cpp is the full
provider with bases, fields and lifetimes. An opaque method-only header cannot replace
these. They were inspected, not subjected to speculative compiler trials or retired.

This completes one source/header-debt task, preserving existing code. It earns no new
recovered C++ body or unique linked-byte credit and proves no whole-image link, menu,
skirmish, save/load, CRC, crash, memory or performance improvement.
