# Category registration slots and the private data probe

Seventeen existing registration slots at 0x009FDD1C through 0x009FDD5C
each hold a distinct four-byte zero-initialized pointer. Retail names
eight slots CategoryModuleClassBase::s_default and nine
CategoryModuleClass::s_first. The original provider is FXParticleSystem.cpp.

The source trial produced all 17 names. Scoped code verification passed
392/392. Normalizing only the intended names and compiler-local labels
preserves the 1,393-section COFF graph. The 77 ordered CRT actions and 129
scoped DIR32 address sets are unchanged. The code was restored after the
trial.

The private sizeof probe emitted DataRowPrivateProbe<...Owner<1 >>.
VC7.1 tokenizes the adjacent closings as a shift. The failed 17 data rows
are a probe-syntax refusal before byte or size checks. A native fixture
reproduces the refusal on a private array in a class template, then proves
its eight bytes and arithmetic type with separate closing tokens. The
otherwise identical fixture without a friend still fails both probes.
