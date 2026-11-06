# Assisted lifetime split: source-reconciliation boundary

Read-only review. No Code/ledger changes, builds, claims, network or split
retry. Scope is the existing complete destructor 0x486E18/25 and scalar
deleting destructor 0x486EE1/28.

**No truthful two-body-only source reconciliation was established.** The
concrete native prerequisite is reconciling the current lifetime owner's fake
UpdateModule inheritance with the canonical layout, so it emits the SAME native
Assisted class/tables as the destination before a source move. That prerequisite
cannot be scoped to these two methods while its shared global fake base remains.
Do not solve it by suppressing providers or changing the guard.

## Exact current evidence

The existing handoff records a supported split trial with both carved rows
matching and all 57 residual rows preserved, then refusal on selected
destructor/table implementation context. No split was reapplied here.

Current mixed owner: Common/Rva0024A797Derived.cpp. It defines globally:

```cpp
class UpdateModule {
public: virtual ~UpdateModule();
private: char m_pad04[8];
};
class MiBase1 { public: virtual void f1(); };
class Rva00486E18_B2 { public: virtual void f2(); };
class AssistedTargetingUpdate : public UpdateModule,
    public MiBase1, public Rva00486E18_B2 {
public: virtual ~AssistedTargetingUpdate();
};
AssistedTargetingUpdate::~AssistedTargetingUpdate() {}
```

The real canonical UpdateModule is 0x20, includes both native interfaces itself,
and the native Assisted class adds no fields or bases. Main already has that
correct UpdateModule-only derived view and verified 13/47/3-slot tables.

Current cached common object SHA256:
`52266a47d0e2fa6fe4c5b765d13d54c92e9405059480d1a76c85adc6fc10e280`.
Current inspected main object SHA256:
`cb18e08a44b55577040fae312467b68a4bf58a5f7bf71d15468032f58c70e2e3`.
Local index metadata: 2026-11-06 20:25, commit 7bd55416c6.

Both objects emit the scalar deleting destructor with identical 28-byte bytes,
identical relocation names and normalized digest `2ad69f99756e`:

* +4 REL32 -> `??1AssistedTargetingUpdate@@UAE@XZ`.
* +17 REL32 -> `??3@YAXPAX@Z`.
* Both have the same weak `??_EAssisted... -> ??_GAssisted...` binding.
* Current index calls both scalar copies retail. The scalar algorithm is not
  the missing source prerequisite.

The current complete destructor is 25 bytes, digest `44d94abb6b9f`, with:

* +2 DIR32 -> `??_7AssistedTargetingUpdate@@6BUpdateModule@@@`.
* +9 DIR32 -> `??_7AssistedTargetingUpdate@@6BMiBase1@@@`.
* +16 DIR32 -> `??_7AssistedTargetingUpdate@@6BRva00486E18_B2@@@`.
* +21 REL32 -> canonical `??1UpdateModule@@UAE@XZ`.

Each of those first three old table definitions is only FOUR bytes (one slot).
Main's proper tables have different compiler names:
`...6BObjectModule@@@` (52 bytes), `...6BBehaviorModuleInterface@@@`
(188 bytes), and `...6B@` (12 bytes). Current index marks the complete dtor
unknown, not proved retail. Matching its 25-byte instruction skeleton does not
prove these three old table implementations interchangeable with native tables.

The approved ownership evidence exists: the fresh earlier in-memory plan
approved complete dtor via Z and scalar via C. The committed map still has an
older proposed/K complete-dtor entry; use the fresh owning-tool map, not that
stale projection, before any eventual move.

## Why the narrow apparent shortcuts are not source reconciliation

* Adding canonical UpdateModule.h to the mixed owner collides with its existing
  global UpdateModule definition. Replacing that global class changes it from
  12 to 32 bytes; unrelated siblings still add MiBase1/B2 and their offsets
  shift away from native +0xC/+0x10. It is a broader native cohort prerequisite.
* Flattening a new fake prefix or inventing different base names merely to
  reproduce table manglings avoids the canonical type rather than recovers it.
* Emitting a second ordinary canonical destructor in main while retaining the
  existing exclusive common definition creates a duplicate provider. Making one
  inline/weak to steer link selection changes COMDAT policy/selection and does
  not reconcile the definitions. link_check.duplicate documents exclusive/ANY
  pairs as duplicates as well; do not treat that as a safe intermediate state.
* Changing only table aliases/pins or manually moving rows would conceal the
  actual class-view discrepancy. No such route is proposed.

SplitLinkGuard's relevant checks are in tools/tu_skeleton.py: selected
implementations must stay unchanged unless both sides are independently okay;
unproven moved copies require raw private/weak-free context. The old destructor
really depends on its object-local short tables, so the documented refusal is
not proved a false reject by these two byte matches.

## Concrete next source direction, with scope limit

The eventual native declaration must be the existing canonical UpdateModule-only
Assisted view, with its exact same virtual surface and empty out-of-line
destructor. It should emit the current main's 13/47/3 tables and leave the scalar
28-byte implementation and weak binding unchanged. First make that source view
valid in its CURRENT owning TU and verify selected provider/table context there;
then use only the supported split/merge.

In the current file, doing so requires retiring/reconciling the shared 12-byte
UpdateModule facade or an independently supported source separation that the
normal ownership/link guard already accepts. No accepted two-body separation
exists in the inspected evidence. Therefore this bounded seat recommends
recording that concrete dependency and choosing other approved cleanup until
the broader canonical-base reconciliation is claimed. No new blind split retry
or arbitrary helper/inline suppression is justified by this review.

Inference boundary: a canonical source view should reproduce the verified
native lifetime bytes, as the earlier whole-native-TU probe already did. No
claim is made here that the wider mixed cohort will adopt without further work,
or that a future guarded split will pass before selected context is reconciled.
