# AptSkirmish profile destructor identity and provider conflict

2026-11-03; inspected header-adoption commit `f24e6ea67b`.

The shadow code-identity check reports one existing wrong binding in
`AptSkirmishDestructor.cpp`: logical funclet `$L1594` at 0x00796303 calls
`??1Rva0031455E@@UAE@XZ`, although its retail target is 0x0052163E.
The same base destructor is correct in the normal parent path, whose target
is 0x003148E6. The source used the base type for this member before header
adoption too; canonical preference headers do not change that type or call.

Target and provider facts:

- `TailJumpWrappers5B.cpp` owns `??1Rva0052163E@@UAE@XZ`, a five-byte tail jump
  to the rowed base destructor at 0x003148E6.
- `allowed_symbols.py` resolves the funclet through the verified parent EH
  graph, so the finding is not a stale compiler-local label.
- The pre-trial ordinary preview retains 351 -> 351 census-linked bytes.

The trial adds an empty `Rva0052163E : Rva0031455E` derived view and uses it
for the profile member. Its implicit destructor lets normal
destruction inline the base call while the unwind funclet references the
derived wrapper. Scoped build: 12/12 exact rows. Identity references remain
28, with owner bindings 25 -> 26 and wrong bindings 1 -> 0. The normal path
still calls the base at 0x003148E6; the funclet now calls the wrapper at
0x0052163E, both classified owner.

The ordinary link preview rejects this trial: duplicate
`??1Rva0052163E@@UAE@XZ`, 351 -> 0 bytes. It emits a COMDAT provider while
the existing wrapper TU already defines the symbol. The trial was reverted;
no changed production source or register exemption is retained.

Reproduction patch against `AptSkirmishDestructor.cpp` (this is a blocked
linking trial, not a scored near-match stash):

```diff
 class Rva0031455E { public: virtual ~Rva0031455E(); private: char storage[0x10-4]; };
+class Rva0052163E : public Rva0031455E {};
@@
- Rva0031455E profile;
+ Rva0052163E profile;
```

Preview index: `8661f15284`, 2026-11-03 20:03 UTC; underlying census
`23b85ddde5`, 18:36 UTC. These are previews, not new census measurements.

Next: reconcile the wrapper's provider ownership before changing the caller.
The committed TU map has no approved destination for 0x0052163E; establish
that evidence before moving its row. Preserve both distinct retail call
targets, the existing matched provider and consumers, and the caller's exact
EH graph. Do not fix the duplicate with an alias or suppressed verification.
