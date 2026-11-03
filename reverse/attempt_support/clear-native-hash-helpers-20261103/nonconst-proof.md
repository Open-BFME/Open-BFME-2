# Clear ordinary nonconst vector accessor: bounded private proof

2026-11-03. Exactly **two** sanctioned tu_skeleton.Verifier.matched compiles:
current MAIN source control, then one candidate. Army confirmed its separate
ABI pair/process had finished before this pair began. Both compiles ran in the
idle `build/sole-private-proof-20261103` worktree; Verifier's temporary source
was outside main. No flags, imports, pragmas, exception promises, pins, ledger
or main Code/cache were changed. The two supplied canonical headers were hashed
equal between main/private, and the private control's complete 48 external
definitions, properties and symbol facts equal main's current normal object.
This is a directly measured control, not a blanket transitive-header assertion.

Only candidate source edit:

```cpp
template <> inline void *&_STL::vector<void*>::operator[](size_t n)
{ return *(this->_M_start + n); }
```

It replaces the existing declaration-only nonconst specialization. There is no
begin() body, new import, force-inline attribute, optimization switch or storage
workaround. Native exact owners independently supplied the visibility lead;
their existing import/force-inline hatches were not copied.

## Results

- Control and candidate: **15/15 unique native RVAs**, zero compile errors or
  missing rows. No parent EH graph was found in either scoped object.
- 48 -> 49 complete external definitions. No old provider is removed. Exactly
  one retained body changes: the int/Rva003FD14D* hashtable erase, **109 -> 86B**.
  All other retained complete code/data bytes and symbolic relocations match.
  Retained symbol properties are unchanged.
- Erase equals **all native 86 bytes at 557BB** after resolving its only REL32
  at +73 to `_free` at 30830. There is no unknown relocation. The prior audit's
  native chain from matched 212655 through the complete 1E2861 wrapper already
  establishes this target independently of template-name equality.
- `_M_find` stays **47B**, zero relocations, complete raw equality to 2888D4.
- The sole added definition is a **12B**, zero-relocation ordinary nonconst
  vector<void*> subscript, selection-2 COMDAT, `8b018b4c24048d0488c20400`.

## Added provider and guard scope

The saved index places Clear at **4782**. For the exact added nonconst accessor
name, the existing first holder is **385**, stlport_vector_voidptr.cpp, followed
by the same native copy at 441. The current position-385 symbol is still the
complete **32B native owner at 23C20**, zero relocations; its bytes were reread
and compared directly to retail. Thus the new 12B copy loses to that native
copy in this bounded saved order. It is not itself a claimed native 12B body,
and a discarded differing copy is not automatically a regression under the
documented retail-truth-3/4 rule.

Unmodified LinkGuard reports `linked=[]`, `judge=[]` for this Source because
the existing census records it **unlinked (0 bytes)**. The method naturally
short-circuits in that case. No guard prepare/fetch was run, and that empty
result is explicitly **not** a full link/provider proof. Root's ordinary joint
preview/batch checks and the next census remain required. No final strong/library
selection, new original type identity or TU approval is claimed.

`proof.json` archives source/object hashes, both private objects, full provider
facts, all native rows and exact relocation/native comparisons. Main source
and the main normal object were hash-unchanged at proof completion. Candidate
text is the pre-ABI snapshot: apply only the one accessor snippet to later main
work, not the whole scratch candidate after the separate ABI repair changes.

Bounded proof complete. No further compiles or variants.
