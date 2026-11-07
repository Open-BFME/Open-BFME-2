# Particle tag reference exports and startup ordering

Both trials used 86e0e0b722, which contains the 38 generic KEY/NAME renames
from 21a0899a82. Both source trials were reverted before publication.

## Twelve default tag references

The trial replaced the DefaultModuleTag statics with a typedef to the retail
ModuleTag instantiation. The existing key/name helpers read the renamed static
references through the typedef. MSVC 7.1 produced all twelve export names.
Scoped verification initially passed 306 code rows, 50 data rows and 58 EH
records. The pre-push scoped DIR32 check rejected the commit.

| Scope | CRT actions before | CRT actions after | Changed positions |
| --- | ---: | ---: | ---: |
| Published generic rename, Modules | 121 | 121 | 0 |
| Published generic rename, Factories | 55 | 55 | 0 |
| Default-tag trial, Modules | 121 | 121 | 36 |
| Default-tag trial, Factories | 55 | 55 | 36 |

The same compiler-generated initializer labels can refer to different stores.
Follow each relocation in the ordered COFF .CRT sections to its code section.
Compare the bytes and every relocation's offset, type and target name, allowing
only the intended data symbol respelling. The table counts initializer actions
with a relocation, separately from the count of all CRT sections.

The native DIR32 comparison found zero address conflicts among 50 existing tag
names in the saved base objects, then 32 conflicts among 52 names after the
trial. For example, the default category-1 KEY points to retail VA 0x00E02C88
from the constructor at RVA 0x003AA801, while the relocated store from the
compiler thunk assigned to RVA 0x007AF4B7 points to 0x00E02C58. The latter is
Quad Draw's KEY storage in the base. Re-pinning compiler labels alone would
leave the changed sequence of startup stores.

The local trial is retained at 08dda6f296 for reproduction. Resolve the
initialization-order dependency described in LINK-615 or prove a source shape
that preserves the sequence before retrying. Check both units, including the
thunk targets and DIR32 address sets, before awaiting a new real link.

## Four plain Point and Ortho references

The original storage at 0x00A02CE8, 0x00A02CEC, 0x00A02D10 and 0x00A02D14
starts as four zero bytes each. The current Modules object defines these
names in its shared non-COMDAT .bss. Factories only references them.

A trial kept the two plain class tags and tried explicit instantiation in
Modules, plus declaration-only explicit specialization of the reference
members in Factories. MSVC 7.1 refused the latter with C2530 (an uninitialized
reference) and C2908 (specialization after instantiation). A follow-up needs
a declaration form that preserves one provider, the original storage and the
startup sequence. Re-run the scoped data and EH gates as well as the checks
above. These four names have no measured export closure.

Neither trial produced or ran a linked image.

## Point and Ortho follow-up

VC7.1 accepts an extern template declaration before the helper in Factories.
This keeps the four references undefined there, but explicit instantiation
in Modules creates four SELECT_ANY COMDATs and moves the startup actions
from zero-based positions 1/2 and 11/12 to 37/38 and 48/49. The build fails
the four corresponding initializer rows. Reverted.

A separate trial fully specialized each of the two ModuleTag classes with
public KEY and NAME declarations. It defined the four reference members in
Modules at the original source positions and kept Factories declaration-only.
Both freshly built objects preserve the code and data section graphs after
the four intended name substitutions and compiler-local label renumbering.
All 306 existing code rows and 58 EH records verify. The ordered CRT actions
(121 and 55) and each unit's DIR32 address sets are unchanged. The four
renamed symbols keep their offsets 208, 768, 928 and 1504 in Modules' 1,688-byte
non-COMDAT .bss and stay undefined in Factories.

The four new data rows fail size proof in data_rows.py. The existing probe
cannot decode their reference template arguments into a C++ expression,
and the separate COMDAT size rule does not apply to this shared .bss. This
candidate is reverted. A tooling follow-up needs a compiler-backed size
probe that identifies these exact symbols. Keep the code and data checks
independent and rerun both, plus the CRT, DIR32 and EH comparisons, after
that proof is available.

## Follow-up resolution

Verifier change 82fce552c0 recognizes the x86 compiler's CRT-registered
direct dword store to the exact public template-reference symbol in shared
.bss. It checks both DIR32 operands and the native startup thunk. The
retail zero bytes and symbol extent still have to verify separately.
With the specializations in place, the build verifies all 42 data rows in
scope, including the four new ones. Both fresh object comparisons confirm
the startup order and DIR32 homes. Real-link closure for these four names
is pending.

The default-tag follow-up tried a ModuleTag partial specialization keyed on the default module, template and particle types, with the two reference members defined at the original source positions. VC7.1 rejects the reference non-type parameters with C2755 even when both arguments are simple identifiers. The source trial was restored. This route supplies no evidence about startup ordering because the compiler produced no object.
