# Remaining TU composition boundary

The current callback repair is committed and47/47 verified. It remains valid
independently of merging files. No guarded source move was applied.

A fresh supported merge dry run after the info repair accepts no donor:

* Update donor: the BFME1 Coord3D include conflicts with the seed's declaration,
  and getDamageTypeFlag is defined twice. These surfaces need reconciliation,
  preserving the native constructor's array lifetime and selected helpers.
* Module-data constructor/destructor: canonical GameClientRandomVariable
  conflicts with the seed's donor GameClient/ClientRandomValue.h declaration.
  Their module-data base/novtable policies remain a separate later boundary.

A private native-value-header trial in the seed explicitly selects the existing
canonical GameClientRandomVariableInlines.h and suppresses the old donor class
with its own guard. It fails compilation before byte verification: the seed's
donor ParticleSys.h uses that value class in union members ortho, spherical,
hemispherical, cylindrical and outward. VC7.1 C2620 rejects the native class's
nontrivial constructor in those donor unions. The trial was never written to
Code. Do not remove the canonical constructor or add a private copy to satisfy
the donor's obsolete structural assumption.

The next prerequisite is native particle/header adoption for the seed, including
the necessary Coord3D lifetime and manager access contracts, then the remaining
module-data base reconciliation. Existing canonical ParticleSystemManager and
ParticleSystem headers are leads, not proof that this larger adoption passes.
No class-wide adoption or shared-header edit was attempted in this pass.

The source planner snapshot was refreshed after the info repair. Its reports
remain investigation evidence; the fresh tu_skeleton map approved the actual47
rows. The extra mixed GapBodiesGE22 source retains its28 other rows. Existing
callback4874F4 coverage was investigated and retained, never called missing.

The verified two-source prerequisite stays separate from the blocked merge.
Publication must include its normal checks; current outside consumers and actual
image/runtime results remain unverified. No pins or hatches were added by it.
