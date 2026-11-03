### LINK-076: `Rva006DF470Initialize.cpp` named 0x00A180C4 a second time
Status: Repair landed / awaiting verification. Updated: 2026-10-26; inspected revision:
`9f685c7696` (index 2026-10-26 19:02 at `5ce093a71a`).
Evidence / affected units: `Code/Libraries/Source/Apt/AptValue/Rva006DF470Initialize.cpp`
(27 matched rows) stored the identity 2x3 transform through
`?g_aptBoxAtE180C4@@3UBfmeM1208@@A`. `reverse/data_ledger.csv` lists that name only
as an alias of `_g_bfmeD1206` at 0x00A180C4, whose definition lives in
`Rva008AC6C0Accumulate.cpp`. The alias was the unit's only unresolved symbol.
Completed: the unit now declares the real `extern "C" BfmeQ1206 g_bfmeD1206` and
casts it to its `BfmeM1208` view, as `Rva006E1E30Cluster.cpp` does. 27/27 rows
pass; 16 funclet `$L` pins renumber, and the gate verifies them through the parent
EH data. Preview: LINKS, LINKED 0 -> 1,374.
Clearance: pending.
Census confirmation: awaiting the next census.
