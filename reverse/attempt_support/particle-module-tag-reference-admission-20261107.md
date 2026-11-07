# Particle ModuleTag reference exports

Retail exports 54 KEY and NAME reference members. Existing generic ModuleTag
specializations in FXParticleSystemModules.cpp and FXParticleSystemFactories.cpp
already define 38 of those objects under s_key and s_name spellings. Each exact
export spelling maps to a separate zero-filled four-byte retail slot. The
existing derived ledger records each old owner at that address. Both objects
emit the references in writable uninitialized COMDAT sections. The two
additional RenderObjectUpdate references are for a different template signature
with no matching export.

The two-source trial renamed the generic static members to KEY and NAME
and preserved the separate plain and default tag storage names. The build
found all 38 proposed definitions. It refused the data rows because
data_rows.py cannot name the reference-valued template arguments and name
backreferences in its C++ sizeof probe. This prevented the later function,
EH, and link checks from running. The trial and the 38 rows were reverted.

Before landing the names, prove the exact sizes with the supported data
gate and compare the native initializers and two object files. The reference
slots must stay zero before startup, and the compiler's writes must keep their
original destinations, referents and order.
