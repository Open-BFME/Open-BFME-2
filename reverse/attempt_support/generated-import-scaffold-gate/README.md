# Generated import scaffold false rejection

The existing `ji_0062af26` and `ji_0062af44` rows are anonymous generated
six-byte import placeholders, not recovered C++. They compile retail's FF25
jumps through the measured d3dx9_27.dll import table. A real stdcall ABI provider
may replace them without claiming new C++ coverage. `add_match --replace-rva`
refused their gen-import provenance, and conversion Rule B also counted them
as authored C++ being lost. The original normal refusals are reproduced in
`evidence.json`; the same real two-row Git fixture passes after this repair.

The shared proof requires canonical synthetic name/path/extent/status/notes,
the complete generator source grammar, and retail's exact FF25 slot, DLL and
named export. Rule B reads source from each assessed Git revision, not the
working tree. Another clean C++ owner at that address still prevents loss.
Malformed, missing, ordinal or forged evidence grants no exemption. Neither
other generated families nor arbitrary gen-import tags qualify.

Admission still invokes its unchanged normal byte gate and restores the old
row on failure. This tool-only commit has no Code, ledger, pin or hook changes.
The compiler-glue providers and substantive Glow recovery remain separate work.
The proof does not waive ABI, DLL/import-reference, full extent, identity or
linking checks for that work.

Validation: 156 tests passed, with one inherited open red-team fixture skipped.
All implemented exploit refusals remain passing, including genuine authored
C++ replaced by assembly. The concrete fixture uses the current separate
six-byte MASM sections; its assembly SHA and old/new fixture refs are recorded.
