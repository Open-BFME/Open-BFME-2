### LINK-027: `StlSweepW5Rva00423EB0.cpp` destroys the nested word deque under a placeholder element

**Status: Open. Updated: 2026-10-26; inspected revision: 9f93879fe9.**

- **Evidence / affected units:** `StlSweepW5Rva00423EB0.cpp` (33 B, `__destroy_aux` 0x00423EB0)
  loses `??1Rva00423EB0Element@@QAE@XZ` and `_Deque_iterator_base<Rva00423EB0Element>::_M_increment`
  (census: not retail's body, wrong selected). Its element is a one-`wstring` placeholder, but its
  symbols.csv pins already say what retail calls: the element dtor is 0x00422D48, rowed as
  `??1?$deque@UBfmeWordValue4@@...` (`StlportNestedWordDeque.cpp`), and the iterator step is 0x0042198C,
  rowed as `_Deque_iterator_base<BfmePod40>::_M_increment` (40 B = sizeof the inner deque). Its only
  retail caller is 0x004244E2 inside `__destroy<Rva004244C1Element>` 0x004244C1
  (`StlSweepW5Rva004244C1.cpp`, links today through its own pin). So 0x00423EB0 is
  `__destroy_aux<_Deque_iterator<deque<BfmeWordValue4>>>`, the outer-deque teardown of the
  `StlportNestedWordDeque*.cpp` family.
- **Completed:** none; diagnosis only (no source trial).
- **Remaining / next check:** respell both StlSweepW5 units over the real `InnerDeque` element
  (`add_match.py ... --replace-rva`, or rehome into the family's approved unit per tu_map), build them,
  then decide whether 0x0042198C's `BfmePod40` row is the same `deque<BfmeWordValue4>` iterator.
  Verify with `link_check` on both StlSweepW5 units plus `StlportNestedWordDeque.cpp`.
- **Clearance:** pending.
- **Census confirmation:** not claimed.

**2026-10-26 bounded recheck, inspected `896af216804e`:** retail 0x00423EB0 still calls the 58-byte inner-deque destructor 0x00422D48 and 36-byte 40-byte-stride iterator increment 0x0042198C. With both current providers supplied, the sweep unit remains L2/S2, while `StlportNestedWordDeque.cpp` and `stlport_pod_deque_bodies.cpp` remain LINKS. No trial changed element/template names: they occur in the matched row name, so adopting the real nested-deque element requires naming-lane ledger changes outside this seat. Evidence: `build/link-worker-w5/retail-probe-final.log`, `before-extra-providers.log` and `after-cohort.log`. Remaining prerequisite and next useful check are unchanged; no clearance or census confirmation claimed.

**2026-10-29 recheck, base `8209faa185c4`:** preview against census `85f6b7f40c` still reports both placeholder COMDATs wrong-selected and 0 linked bytes. A nested-deque signature trial cannot use `add_match --replace-rva`: the existing row is not a scaffold and the tool requires a reviewable retraction. The trial was restored before byte or link verification. Plan retraction and readmission with the caller and existing owners/pins; no repair or census gain is claimed. [Trial boundary](../../reverse/attempt_support/stlsweep-00423eb0-20261029.md).
