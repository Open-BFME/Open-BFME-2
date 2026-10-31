# Tokenizer native search-provider import (2026-10-31)

At d21f62cd71, the tokenizer retained five matched rows but failed the current d249ce458a index on two mutable-byte search COMDATs and their two selected-body findings. Its local /O1 search family is not the native /Od family. The native mutable helpers at RVA 0x25B80 and 0x26C60 are deliberately not replaced by declaration-only guesses.

The applied explicit declaration imports the already-rowed 120-byte basic_string<char>::find_first_not_of(const char*, unsigned, unsigned) at 0x2A3A0 from Common/BfmeS1155.cpp. This removes nine locally instantiated search/predicate definitions. Private before/after objects prove all 26 retained external code definitions and symbolic relocations identical, all five ledger rows byte-exact, and one EXACT EH graph. Every incoming reference from retained code into the removed closure names the existing native root method; other incoming edges are internal to the removed closure or debug references. No caller is redirected to a guessed address or different overload.

Normal build passes five rows. Strict two-source preparation and the existing provider are checked separately. Current two-source preview: both LINKS, 1,532 -> 1,769 authored bytes (+237 for the tokenizer); provider retains 1,532. This is bounded preview evidence, not a new census figure or unique C++ coverage claim. No row, pin, alias, class/header, source path or TU-map changes are made.

Rejected private alternatives: declaring only the two mutable helpers leaves a runtime predicate caller; importing only the predicate reshapes the unrowed string method. Neither alternative is applied. Original tokenization semantics and all retained code/lifetimes are unchanged.

The preceding scorekeeper prerequisite publication d21f62cd71 passed normal source checks but its batch audit was INCONCLUSIVE against the older index/outgoing dd63955d8b and missing current Common/0CreateAHeroManager21FE49.cpp consumer receipt. Carry that provider scope and this search-provider cohort into the next scheduled census. No maintainer-only measurement is run.
