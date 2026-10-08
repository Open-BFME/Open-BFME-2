# ObjectFilter kind-of predicate

The served structural lead was the synthetic unwind parent
`gen_uw_l144_00360fdb` in `Code/gen_small/uw_gen_001.cpp`. The whole 2,008-line
generated unit was inspected and preserved. Its artificial 96-byte parent is
not the native function at the proposed address. Native 0x00361B12..0x00361CA5
is a complete 403-byte thiscall function returning a boolean and popping three
argument words.

WB 0x00ED3050 independently names ObjectFilter::testKindOf in ObjectFilter.cpp,
with assertions at lines 405..478. Its registry initialization, player alignment
and relationship checks, rejected-mask test, required-mask modes and default
mode agree with native. This is target/WB reconstruction, not a claimed donor
transfer. Const pointer spelling is a local ABI view; the original parameter
declarations are unavailable.

Retail fixes the 0x94-byte registry stride and fields: required mask +0x48,
rejected mask +0x64, mode +0x80, relationship bits +0x84, alignment +0x90.
Player access is template +0x34, template flag +0x1BC, player ID +0x54 and
team +0x2EC. The WB team offset differs. Existing record constructor/destructor,
interning, Player::getRelationship and seven-word BitFlags providers supply
every call. The existing 69/116 template spellings remain provider ABI views;
both verified provider bodies operate on seven words. No pin or alias is added.

The native home ObjectFilterCollectionXfer.cpp was read completely (169 lines
before this recovery). Its three existing transfer bodies remain exact.
The initial predicate emitted 384 bytes: retaining relationship bits across
the player query and a required-mask pointer across switch arms differed from
retail. Reloading the field and declaring the mask within each case gives 405
bytes with only a final boolean-materialization difference. An ordinary boolean
result local removes those two extra bytes. The complete 403 bytes then match.

Official add_match verifies 4/4 home bodies, all 4 EH-bearing bodies are EXACT,
and the declaration gate is silent. No generated source, gate or baseline is
changed. Local evidence: build/object-filter-kindof-wb.txt,
build/object-filter-kindof-reload-diff.txt and
build/object-filter-kindof-temp-diff.txt.
