# Native allocator providers for two STLport 4.6 consumers

Control: BFME 2 84887c9bc04ca39bbc4981f3d554dde274b68489. Scope:
VectorObjectIDFillInsert.cpp and stlport_deque_int.cpp, LINK-150. The earlier
4.6 migration had been reverted because neither non-const allocator member
had a provider. Existing declaration-only growth helpers preserve retail's
call boundaries and must remain out of line.

Target facts: the complete allocator at RVA 00068E15 is 28 bytes. It tests
the count, multiplies a nonzero count by four, calls GameMemory's static
byte allocator at 000307F0 with hint zero, and returns null for count zero.
The two ObjectID growth helpers at 004F62A4 and 00148D00 call 00068E15.
The existing allocator<int> const owner in AptTimeLineStats.cpp emits the
same complete body and a single REL32 at offset 15 to the real GameMemory
symbol. The proof script reads retail instructions and current COFF objects.

Both 4.6 non-const specializations now have clean C++ definitions in
VectorObjectIDFillInsert.cpp and are admitted by add_match --icf-owner,
with fold-proof pointing to that provider. Both raw bodies and all relocation
identities equal the existing owner. The integer member needs an explicit
instantiation because its caller is in the other translation unit. The
declaration names and source locations of the existing const owners stay.
No pin, linker alias, generated placeholder, optimizer pragma or source path
is added. The existing deque aliases are unchanged.

The static GameMemory allocator is named directly with its existing decorated
symbol and cdecl signature. STLport 4.6's ordinary allocator<char> is an
instance member; calling it as a static member does not compile. A broad
bfmealloc-overlay trial instead changes five existing ObjectID rows. Its
dynamic-library configuration also tries to explicitly instantiate the
already specialized allocator<char>. Those trials are restored. The retained
ObjectID source uses its original flags and a direct GameMemory call.

An Integer-body trial in the deque itself preserves its other 23 rows but
uses `add esp,8` and separate returns under that unit's compiler context;
retail uses two pops and a shared return. That body is removed. Merely
defining the specialization in the ObjectID unit does not emit its unused
member; explicit instantiation emits the exact native body. No unrelated
algorithm or flag change is retained to force this result.

## Verification and boundaries

The controls pass 9/9 ObjectID rows and 23/23 deque rows. After the repair,
the joint byte build passes 34/34: 32 existing rows and two ICF-provider rows.
Every affected row is readmitted with add_match --replace-existing and
migrated=stlport-4.6; existing folded rows use their existing matched ICF
peers. The readmission resumes only unfinished rows after an initially
omitted --icf-owner argument; it never repeats the completed rows.

The four-unit ordinary preview with AptTimeLineStats.cpp and GameMemory.cpp
reports 4/4 LINKS against index 85f6b7f40c (2026-10-29 15:08). Both migrated
consumers retain their existing linked coverage. Its per-source sum changes
5,879 to 5,907 because the provider unit now also owns the shared 28-byte
range. That range was already covered by the existing owners: new unique
matched bytes are zero and no census-linked-byte gain is claimed.
Full affected-consumer verification and the next scheduled census remain
necessary. This resolves LINK-150's missing-provider prerequisite for these
two units; it does not clear every allocator type's 4.6 migration.

Final frozen-source checks pass: both sources have no unrowed definition;
strict preparation gives reusable receipts for all 34 rows. The joint build
with the unchanged AptTimeLineStats/GameMemory owners passes 114/114 functions,
seven data rows, 17 literals, one float and three named imports. The native
body/relocation/caller proof is rerun after that build. All 34 current ledger
rows carry the migration token. No headline is inferred from these checks.

Model GPT-6; ObjectID body t=6 minutes; integer body t=6 minutes; lane=R;
budget=30m per body. Ledger readmission and publication are separate checks.

## Reference freshness

The pull brings the independently verified b53c85e7 reference update and its
published full-gate/sweep evidence. Official BFME 1 master was checked again
at ff1b611adca6035b89238b47298bf9e4a58abcd3. There is no header or
inputs/reference change between that commit and the maintained b53c85e7
pin. The newer donor-source revision is not adopted or marked verified;
the local freshness-success stamp is not advanced. A future reference
maintenance pass still needs its complete verification before advancing.
