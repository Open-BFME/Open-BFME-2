### WaterArea setter composition (2026-10-28)

Status: Blocked on census link-order evidence. The WaterArea seed now declares
the setter fields at +0x20, +0x24 and +0x28 and virtual slot 5; its six rows
byte-match and its EH graph is EXACT. At index `d92e7e6635`, the supported
dry merge compiles the three setter donors but rejects each: the donors are
census-linked and the seed lacks a census object, so the guard cannot judge
the merged object's earlier link order. No source paths moved. Refreshing the
published index retained the same revision. Carry the seed and its setter
consumers into the next scheduled census, then retry the guarded merge with
current selection evidence. No linked-byte gain is claimed.
