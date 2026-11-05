# _STL.cpp: absorb stlport_narrow_filebuf_underflow.cpp (2026-11-05)

`tu_skeleton --merge --dry-run` over 338 approved rows accepted _STL.cpp plus
stlport_narrow_filebuf_underflow.cpp. 27 donors stay rejected: most on STLport
header redefinitions (char_traits, ios_base, basic_streambuf<char>,
basic_string dtor specialisations, _Messages), Rva00014D90ArrayPrefix defined
inside _STL (stl_atod, string_to_double), stlport_insert_grouping (unbalanced
brace), bytes (wide_time_get_readers, wide_filebuf_underflow,
moneypunct_dtors), and link selection (FstreamDefaultProtectionNameCtors
basic_filebuf<char>::seekoff, money_get_wide basic_string<ushort>::append).

Verification after the merge: `./build.sh _STL.cpp` 88/88 functions matched
(90 rows), 8+6 string refs verified; `find_declared_unmatched` clean;
`link_check --new-variants` clean. `reverse/ms_header_queue.tsv` only reorders
_STL.cpp's existing row (no key retired or added).

Path consumers: only `reverse/link_status.csv` (census output),
`reverse/stlport_trial.csv` (trial record) and the TU's provenance comment
name the old path; no tool, hook, include or debt key does.
