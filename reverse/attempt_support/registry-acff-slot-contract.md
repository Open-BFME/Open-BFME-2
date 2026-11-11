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
