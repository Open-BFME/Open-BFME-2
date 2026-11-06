# Fade native table prerequisite: independently approved deleting destructor

2026-11-06, inspected after67435ce87e. Game sources and TU approvals remain unchanged.

Native base table C70A5C has five slots (deleting destructor5966C0 and four pure callbacks); FadeInTextRender table C70A70 has596AE9,5967B3,596908,2A98A7,5C4ACD. Existing views truncate both. The two last getters are complete four-byte loads from+4C/+2C, with no relocations. A private complete common view verifies all20 rows across the three sources, including two hypothetical genuine ICF callbacks; it is not admitted source or progress. Its destructor lifetime call still lands on native releaseBuffer and its EH graph is EXACT.

Current selected-copy blocker: FadeInTextRender.cpp emits a28B base deleting-destructor wrapper that calls the complete destructor out of line. Rva0059675ADtor.cpp emits retail's29B body with an inline vptr store. Same-TU composition is the natural codegen repair.

The supported plan nevertheless refuses the destructor donor for one unapproved row: **the deleting destructor5966C0**, not its complete destructor596686. The child has its own approved C assignment to this TU. parent_of identifies the complete destructor, a genuine secondary ICF alias behind Disp0DwordImmSetter's primary address identity. fold_alias(parent) is true. donors() exempts that alias from foreign-row rejection but approved_here still vetoes the independently approved child through its unapproved parent.

Do not append inline evidence or alter the TU map: that classification comes from independent mapper inputs. A narrow separately committed verifier fix should honor the child's existing independent approval when its parent is only a folded identity, while still refusing an unapproved child, an unapproved real parent, and a child independently assigned elsewhere. Run meaningful regression tests and the gate-exploit suite. Then reclaim and retry the source/table/merge work through normal checks. No runtime, linked-byte or file-count gain is claimed here.
