# Canonical BfmeFixedStorage128 adoption in ObjectCreationUpgrade

Private prerequisite proof,2026-11-03. Captured source SHA256:c49a744c87c912333c10522b94a8e0626afa1886e03604a3bf8f913f76edddc5. Candidate replaces the ENTIRE one-line private BfmeFixedStorage128 struct with the existing canonical ../../../../Include/Common/BfmeFixedStorage128.h at the same position. No words/m_bits token rewrite is performed anywhere. The separate Rva002AA292::m_bits field and _STL::_Base_bitset::words remain untouched.

Sanctioned private Verifier passes ALL23 source rows in both control and clean candidate. All FOUR complete parent EH graphs are EXACT. The46 ordinary external code/data definitions and symbolic relocation contexts compare IDENTICALLY: none added, removed or changed. A separate private compile-time assertion proves sizeof(BfmeFixedStorage128)==128 while retaining all23 matched rows. candidate.cpp contains only the canonical include replacement and no scratch size assertion.

The actual copy-constructor binding is unchanged: the single REL32 call at offset30 in rva004B41A9 uses ??0BfmeFixedStorage128@@QAE@ABU0@@Z in both objects. Reading the native operand at RVA0x004B41A9+30 resolves the complete existing constructor at RVA0x0004548B in both cases. No new pin, alias, application provider or table is introduced.

Root must reject application if the captured source hash changed, run normal source/strict/EH/link checks and retire the existing BfmeFixedStorage128 header entry only through header_adopt_lane.py accept. This helper did not edit source or retire debt. No tracked source, ledger, claims, network or shared match-cache mutation occurred. No new bytes, sourcefile or census gain is claimed by this private proof. Artifacts: candidate.cpp/control.cpp, proof.json, size-proof.json and private objects.

Tracked application matched the exact control hash before replacing only the
complete private declaration with its canonical include. The owning header
acceptance passes and retires one queue record; normal23/23, data and strict
verification pass. Neither the unrelated Rva002AA292::m_bits nor STL words
are renamed. No guard/data identity debt, pin or source path is changed.
This closes the generic name-collision blocker by using the actual canonical
type directly; it does not waive the adoption check or alter any verifier.
