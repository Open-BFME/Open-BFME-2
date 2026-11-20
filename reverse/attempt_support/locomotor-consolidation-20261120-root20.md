# Locomotor translation unit consolidation

The owning plan at 136ee37e6f6 recorded 154 approved rows and left 14 mixed
files in place. The seed and 37 candidate donors verified 132 function rows,
four data rows and 16 exception-handling graphs. The initial dry run accepted
zero donors. Seventeen first diagnostics were missing early LocomotorTemplate
declarations. Four others were conflicting atof linkage.

The registered LocomotorTemplate header replaces the seed's narrow private
class. The disputed 12-byte row at 0x002BEDBE retains the verified OVERRIDE
resolver call and +0x10 read. The real template's m_surfaces is at +0x14.
The row's true owner and source placement require separate proof.

The seed also adopts the registered Rva001E415F frame setter and Rva001E702E
transform forwarder declarations. Their native +0x5C/+0x60 stores and +0x68
matrix address are explicit uses of the existing opaque receiver. These three
changes passed their owning queue acceptance checks.

The old allocator include changed the linkage of declarations throughout
stdlib.h. A scratch composition reproduced C2375 for atof when math.h followed
it. The seed now declares the direct C malloc and free symbols used by its
rows. The same math.h trial then passed. Each of the four seed changes
preserved all 46 native function rows, three data rows, three exact EH graphs
and the original external COMDAT contents and references.

The Object declaration conflict remains in another worker's class scope.

## Verified move

The refreshed dry run accepted seven complete donor files. The owning apply
moved the 12 planned rows and the compiler-emitted LocomotorTemplate deleting
destructor at 0x001E67A3. The latter's 28-byte body directly calls its matched
destructor at 0x001E4DB0 and operator delete. The map had left the thunk without
an approved unit. The move names the parent and all EH companions in its
commit message.

The consolidated Locomotor.cpp passed the native and strict checks for 59
function rows, three data rows and six EH graphs. The surviving 31-file
cohort passed all 132 function rows, four data rows and 16 EH graphs. The
owning tool regenerated the destination's MS header queue entry for the
existing direct malloc/free ABI and repointed the naming basis source field.

The path audit used the outgoing merge-base range after fetching master at
79303b3d61a. It matched the seven removed paths and their basenames across
source, tooling, hooks, configuration, documentation and registers. Code
hits were provenance comments in Locomotor.cpp. Other hits were naming
history, contract samples, attempt records, census records and TU routing
evidence. Current function, data and TU source columns contain zero removed
paths. Incoming master changes added zero code or documentation references.

## Remaining donors

The final search rejected 30 donors. Eight first diagnostics were missing
m_04 from the Locomotor view selected for the composition. Two apiece hit
the GlobalData and NameKeyGenerator guards for the short SubsystemInterface.
Other failures include incompatible Object and LocomotorStore fields,
duplicate Coord3D and sqr declarations, and byte changes in
LocomotorTerrainHeight.cpp and Rva001E7270Ctor.cpp. The original early
LocomotorTemplate and atof diagnostics cleared.

The registered Locomotor class lacks the disputed getLegalSurfaces member.
Native evidence for the actual class places the raw template pointer at +4
and LocomotorTemplate::m_surfaces at +0x14. A class-wide change needs the
true owner and approved home of the 0x002BEDBE body. The 14 mixed files
contain rows assigned to other translation units.

The owning plans, final checks and path audit are under
build/root-resume-20261120/locomotor-merge.
