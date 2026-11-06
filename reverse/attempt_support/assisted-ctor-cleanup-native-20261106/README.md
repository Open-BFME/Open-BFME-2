# Assisted constructor cleanup: compiler-owned native body

Existing generated coverage at78C15D/8 is cleanup for constructor486E8D/84,
not an uncovered regression. Canonical UpdateModule now gives a fully resolved
unmasked parent, EXACT EH graph and a real compiler-emitted cleanup. The graph,
not adjacency or byte search, maps current $L6272 to78C15D. All8 native bytes
match, with one in-row REL32 at+4 to the existing UpdateModule destructor at
24A797. The next section relocations belong to the separately rowed handler.

add_match --replace-rva recognizes the old uw_0078c15d scaffold and admits the
real parent-emitted label with gen-funclet;parent evidence. Normal16/16 plus
its80B data table pass, with no unresolved byte or relocation. No pin, alias,
wrapper, ASM or body/source move by hand. Generated uw_gen_011.cpp remains
untouched;201 other rows stay there and the old harness body is uncredited.
The stale destination not-merged comment is replaced with its true ownership.

The complete outgoing path-consumer audit covers this row and the earlier
17B builder move: no lost consumer, protected key or fold proof. Old gen-file
references remain valid for its other rows; historical evidence is preserved.
The committed TU-map source cell is an old generated projection; its approved
Assisted/P assignment is unchanged. Rebuild that map in memory through owning
tools, never hand-edit/regenerate it in this consolidation batch.

This retires a placeholder owner. Byte coverage is retained, and no actual
real-image/runtime or game-logic CRC result is claimed. The compiler-funclet
metric may still classify this as generated code; do not claim authored bytes
merely from a changed source path.
