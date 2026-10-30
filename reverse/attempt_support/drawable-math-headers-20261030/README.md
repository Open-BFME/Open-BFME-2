# Drawable destructor math-header queue reconciliation

The current source already uses canonical Matrix3DData.h, which includes
canonical Vector4Data.h. Its existing Vector4::Set and Matrix3D::Make_Identity
definitions supersede the queue's old Set failure. Matrix3D acceptance passes
without a source change. Include Vector4Data.h explicitly as required by its
owning adoption guard, then verify and accept that key independently.

No layout, body, declaration, header, pin, row or path is changed. The complete
12-row source and parent EH stay exact. The final object is compared against
the verified pre-include object across all code/data definitions, non-debug
sections and symbolic relocations. Retire only passing queue keys through the
owning tool. Both Matrix3D and Vector4 acceptance pass and retire their keys,
leaving no header-queue entries for this source. This is header-debt reconciliation, not native coverage or a
census linking gain; the source's LINKS/643 authored bytes are retained.
