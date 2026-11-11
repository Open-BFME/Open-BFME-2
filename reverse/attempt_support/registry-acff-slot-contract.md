# Registry entry secondary slots at RVA 0x0086D160

At bdfbd7b277 a trial replaced the private primary and secondary base views
in Rva0056AC26Derived.cpp with the existing Rva0056AC26.h. All five classes
derived directly from Rva0056AC26. ACFF declared slot1(int) and
slot4(int, int). Its slot1 forwarded the argument as Rva002B4BC9Arg*.

MSVC emitted 20 bytes for the primary table and 60 for the secondary. COFF
offsets 4 and 16 in the latter referenced ACFF's slot1 and slot4. The slot1
body was 11 bytes, a load of TheLivingWorldLogic and a tail jump to
Rva002B4BC9::rva002B4BC9. Slot4 had a declaration only. The scoped verifier
passed 17 of 18 rows, including the MI destructors. The missing row was the
previous pointer-taking b1Slot1 name. Table length alone cannot retire either
data row. The official move for the existing slot4 body refuses the proposed
integer argument types:

```
python tools/rename.py function --rva 0x0056ABD6 --to-class Rva0056ACFF --new '?slot4@Rva0056ACFF@@UAE_NHH@Z' --dry-run
```

The body uses LivingWorldArmy* and a region pointer. Check callers through
the common secondary table before assigning semantic parameter types to its
contract. A wholesale header adoption also requires the sibling overrides.
Reading the two table addresses installed by each retail destructor gives
these non-default targets (slot numbers start at zero; destructors omitted):

| Destructor RVA | Primary slot and target RVA | Secondary slot and target RVA |
| --- | --- | --- |
| 0056AC82 | 1 → 0050B5C6 | All inherited |
| 0056ACC5 | 1 → 004C9990, 2 → 0056AB35 | 12 → 0056AB88 |
| 0056ACDF | 1 → 0056AB97 | 14 → 0056ACF1 |
| 0056ACFF | 1 → 0056ABC0 | 1 → 0056ABCB, 4 → 0056ABD6 |
| 0056AE4A | 1 → 0056A9A3 | All inherited |

Restoring the original sources verifies 20/20 code rows and both data rows
across the derived destructor, AF94 constructor and ABD6 method units.

At fb267444e2, a second retail table supplies independent evidence for the
two arguments of secondary slot 4. The little-endian word at
RVA 0x0086D434 + 16 points to RVA 0x0056AB09. That row compares its two
argument words with fields at +16 and +20. The secondary receiver starts at
+8 in Rva0056B2DD, so these are complete-object offsets +24 and +28.
Rva0056B2DDConstructor.cpp stores its two arguments at exactly those offsets.
In LivingWorldTutorial.cpp, SessionTask::create case 5 obtains them from
getArmyParam(0) and getRegionParam(1), in that order. Case 9 constructs the
ACFF task. Its secondary slot 4 at RVA 0x0086D160 + 16 points to
0x0056ABD6, which independently passes the army and destination region to
ValidateArmyRegionEntry. The pair comparison itself never dereferences either
argument, so its int,int reconstruction is insufficient evidence of scalar
parameters. Both overrides support an army followed by a region.

The existing base contract emits slot4(int,int), including a ledgered
default implementation. Reconcile the base contract and the default row
together with the two overrides before adopting it in the derived unit.
The region getter currently returns void * in its recovered declaration;
these paths establish the roles and order, but not an original class name.

### Constructor emission after the class fold (d4ba4ff014)

The recovered constructor now has the same owner as the destructor. A trial
derived Rva0056ACFF from the canonical Rva0056AC26 and used the base
initializer Rva0056AC26(static_cast<Rva0056AC26Owner *>(owner)).
Leaving a manual secondary vptr store in the body produced 38 bytes: MSVC
wrote its own secondary pointer first, then the manual pointer at the same
offset. Keeping just that hand table is insufficient.

In a scratch copy of Rva0056AC26Base2.h, give slot1 the parameter
Rva002B4BC9Arg * and slot4 the parameters LivingWorldArmy *, Rva00318C32Ret *.
Retain both bool return types. In the constructor TU, remove both arrays.
Declare the destructor, ac26Slot1() and both typed overrides in Rva0056ACFF.
Leave the constructor body empty after the base initializer. The official
symbol build verifies all 31 bytes. COFF relocation offsets are 8 (base
constructor), 14 (primary table for Rva0007DF07), and 21 (secondary table
for Rva0056AC26Base2).

Comparing each DIR32 target against the retail PE and exact symbol keys in
functions.csv or symbols.csv gives 5/5 primary and 13/15 secondary matches.
The missing keys are ?slot1@Rva0056ACFF@@UAE_NPAURva002B4BC9Arg@@@Z at
secondary +4 (retail RVA 0x0056ABCB) and
?slot4@Rva0056ACFF@@UAE_NPAULivingWorldArmy@@PAVRva00318C32Ret@@@Z at
+16 (0x0056ABD6). Both targets have existing bodies under other names.
The pointer-preserving to-class dry run for slot4, with the new constructor
object present, still refuses the destructor object's ACFF_B1 table because
it lacks slot 4. The constructor alone cannot authorize this move. Reconcile
both installers and the shared base before migrating the providers and the
two data rows. Restored production sources verify 20/20 code and 2/2 data
rows in the constructor, derived destructor and slot4 body units.

### Paired constructor and destructor trial at cb18cd71e8

The reproducible diff is `registry-acff-paired-installers.patch`. Apply with
`git apply --unidiff-zero` in a clean test checkout at that revision.
The diff includes the trial inputs under build/acff-slot-trial and the
ledger edits. The scratch base declares b1Slot1(Rva002B4BC9Arg *), retaining
the existing derived provider name, plus the typed slot4. Both installers use
one derived declaration. The official to-class transaction verified the
80-byte slot4 provider in the presence of both tables. The matching data rows
now name compiler-emitted tables. Both data rows and all 20 code rows pass
for the AF94 constructor, AC26 derived destructor and ABD6 method units.

The wider check includes those three units plus AF4BCtor, AB97Flag,
AB35Method, AC26Constructor and LivingWorldTutorial. ACDF's AF4B constructor
still imports the former primary and secondary names until both references
are updated. Updating those and compiling AC26Constructor against the same
trial interface raises the link preview from 6/8 to 7/8 at census 60189f9ced.
AC26Constructor still loses 352 bytes. Its two reported conflicts are
??_7Rva0056AC26Base2@@6B@ and ??_7Rva0056AC26@@6BRva0056AC26Base2@@@.
Other objects still emit the original shared base interface. The trial has
no production-wide shared contract migration and does not validate sibling
slot ordering. In particular, check ACC5 primary slot 2 against 0x0056AB35
before landing canonical inheritance in the shared destructor unit.
Restoring production inputs returns 8/8 and 2286/2286 bytes; the five source
units edited by the experiment then verify all 51 code rows and both data rows.
