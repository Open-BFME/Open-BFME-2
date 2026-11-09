# Registration base destructor: exact C++ and admission prerequisite

Status: blocked on reviewed tool entry, 2026-11-09. Follows the verified
registration-base constructor fold. No additional Code or ledger edit applied.

The existing 7-byte row at 0x0052B588 is named
`?apply@Rva00052B588DwordImmSetter@@QAEXXZ`. Retail instead ties its store to the
registration base: table VA 0x00C686BC, owner deleting destructor 0x0052B668,
constructor 0x0052B894, and shared derived-destructor tail jump 0x005C47A3.
This is owner recovery, not a second class's ICF fold or a new pin.

Private verification through `tu_skeleton.Verifier` passes all 48 setter-file
rows after substituting the recovered destructor identity, plus the one
5-byte caller row. The staged candidates are banked alongside this file as
`registration-base-destructor-admission-20261109/setter.cpp.txt` and
`caller.cpp.txt`; hashes and facts are in `proof.json`. The candidates preserve
the existing 4-byte table and 29-byte deleting-destructor COMDATs exactly
(digests 1b8d5f1f7e49 and 5dae237d4a8c). They are not applied source or progress.

A separate structural probe adds the pure factory slot and also preserves all
48 bodies. Its 8-byte table has two relocations, through MSVC's existing weak
`??_E` default to its own `??_G` and to `__purecall`; the resolved eight bytes
equal retail at 0x008686BC. This larger probe is not the first landing step:
the other table emitters and four derived factories must be reconciled together.

The ordinary prepared function respell refuses the new destructor because it
is a special-member name. The inferred identity route likewise cannot turn an
ordinary method identifier into a destructor. Do not work around these checks
with a manual ledger edit or second pin.

The existing reviewed `retail_identity.Family` API can express the precise
migration without editing rename.py. A separate tooling change should add:

- `old="Rva00052B588DwordImmSetter"`, `new="Rva0052B668"`, table 0x00C686BC;
- `copy=0x0052B588`, `copy_store=2`, `table_stores={0x0052B588: 2}`;
- owner `??_GRva0052B668@@UAEPAXI@Z` at 0x0052B668, with its own table store
  at 0x0052B670 (`c706`);
- one exact spelling mapping from the current apply row to
  `??1Rva0052B668@@UAE@XZ`;
- facts: store 0x0052B588 (`c701`), jump 0x005C47A3 to 0x0052B588,
  call 0x005C43EA to 0x005C47A3, and both slots of the two-slot base table.

An in-memory instance of that Family passes manifest-held retail facts. Its
evidence string and all six facts are in the banked proof. This proves API
expressibility, not transaction/application success. The two prepared Code
consumers are Disp0DwordImmSettersAddr.cpp and Rva005C47A3Dtor.cpp; no source
move or pin is needed. Use normal `function --respell --identity --basis
retail` once the entry is reviewed. Extend test_rename_retail_identity.py with
mapping/application, changed native facts, absent/wrong rebuilt table bindings
and rollback; update its existing table_stores inventory assertion explicitly.
Land the tooling change separately with a Verifier-Change trailer and run
the existing exploit tests before applying the source migration.

Fresh read-only claim check found tools/retail_identity.py held by
`ancalgonn-swarm-seat6`; rename.py is held by that worker too. No foreign tool
scope was changed. The correct next step is the reviewed entry once its scope
is available, not another unchanged LINK-654 deferral.

The preceding constructor fold's commit hook reported shadow findings at the
registry getter's `_$E2` binding and its static registry name. A private build
of the saved pre-fold source proves every retained COMDAT unchanged, including
the getter and `_$E2` bytes/relocations. The same static symbol occupies the
same unrelocated 20-byte zero-initialized BSS section before and after.
These existing identity findings remain open; the fold did not introduce them.
Its normal hook also verified all six EH graphs exactly.
