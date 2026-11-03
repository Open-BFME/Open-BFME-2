# Vslot AG: emit the existing member-call ICF spelling

Base: 97f025c16c. Seat: halilkkaya-codex.

The rowed caller at 23DAF7 passes an adjusted receiver (+8), one float stack
word and one integer stack word to 23C7F5. The existing provider is spelled
stdcall Rva0023C7F5Get(int,int), while the caller requests the already pinned
Rva0023C7F5::rva0023C7F5(float,int). The native 70-byte target reads neither
ECX nor either stack argument and returns RET8. No original class identity
is inferred from this opaque spelling.

Define the member body as ordinary C++ beside the existing provider, using
the same GameLogic/Network view and exact computation. add_match --icf-owner
admits its full 70-byte body and every relocation against the existing owner.
The old two external COMDAT fingerprints are identical; exactly the requested
member definition is added and no old definition/reference disappears.
The existing pin stays at the same address; no pin, flag, header or escape
hatch is added. Both rows own one shared body: zero unique-byte gain.

Six-source checks pass 155 function rows, data, 80 literals, 17 empty-string
references, three floats and 24 imports. True base/tip A/B restores source
and the function ledger, and normally verifies both. The same five peers
retain LINKS and 9,873 bytes. Vslot AG stays blocked, U4 to U3: the member
name is resolved; its two RET4 helpers and bool/int return contract remain.
Scoped DIR32 passes 155 verified rows plus 62 witnesses, 213 symbols without
new or whitelisted conflicts. find_declared_unmatched and pin_consistency
for this symbol are clean. No real-link/census/runtime gain is claimed.

Scope: VslotSmallBodiesAG_Rva00131CF2, INI, LivingWorldAutoResolveBattleBonus,
BfmeConv1341, Rva0023C7F5Get and Rva005D4E6FCheck. Other-seat providers are
verified only. The published index is 984a4cdc4d (November 2 08:35). Snapshots
and checks: build/seat-link/mode-helper/.
