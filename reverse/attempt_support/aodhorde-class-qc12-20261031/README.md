# AODHordeContain class prerequisite, qc-12

Base: 0d2cdb9d27. Queue 5356 served OnContaining and Xfer. No source changed.
The generated contract is evidence, not an accepted ABI. Its two-entry primary
slot list is incomplete and must not be promoted to a canonical class.

Hand decisions for all four queued attributes:
- base-extent: HordeContain is at zero and occupies 0x30C. Native constructor
  47B3DB calls HordeContain 46F543 with unchanged this, then constructs the
  vector at this+30C. Native destructor independently destroys it there and
  calls HordeContain 46F901. Factory 24BB25 allocates 8E0, not a partial view size.
- name@188, name@18C, name@190: these are the inherited record vector's three
  storage words, not three independent AOD fields. HordeContainCtor.cpp owns
  the vector<Rva00472329Record> view at +188; its ctor calls/lifetimes and
  HordeContainIface11CSlots.cpp indexed users are the prerequisite for deciding
  canonical names. Existing m_188 and m_records spellings are structural names;
  no original field name is recovered by majority. Use the eventual canonical
  HordeContain member and avoid defining duplicate inherited storage in AOD.

Target facts (raw bodies attached): ctor and dtor both install eleven vfptrs
at 0/C/10/20/24/28/2C/30/34/FC/11C. Own members start at 30C; vector 12 bytes,
ID318, int31C, float coordinates320/324/328, floats32C/330/334, 60*16-byte
array338, integer6F8, 20*24-byte array6FC, integer8DC. Native Xfer47B2FB
independently accesses ID318, float334, integer31C and coordinates320.
These native facts do not recover the secondary interface identities or their
full virtual method surfaces. Existing dummy IfaceXX declarations/aliases in
the destructor are not a canonical hierarchy and are not copied into a header.

Tool result: header_adopt_lane.unheadered_bases(contract) = ['HordeContain'].
No canonical HordeContain or TransportContain header is registered on this base.
The real blocker is class:HordeContain, not undecided AOD layout attributes.
A shared AOD header must inherit that canonical ABI, then reconcile both served
consumers and byte/link-verify them. No adoption, byte gain or linking gain is
claimed. No hatch or tool edit. docs/linking_obstacles.md is held by another
worker (PC claim refused); this handoff is the proposed register entry.

Donor provenance: no external donor was used to decide these target offsets.
BFME1 committed pin remains 7a8a034afa7d; upstream master observed a0ae28a558fa.
No freshness success or pin update is recorded without full verification.
