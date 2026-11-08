# Canonical AnimalAIUpdate class, 2026-11-08

The main AnimalAIUpdate.cpp now includes the existing complete Animal
header and removes its flat private class. Eight existing offset helpers
now take the canonical UpdateModuleInterface pointer, accurately naming
their secondary-relative origin. The update obtains that view at the
proven primary-object +0x10 offset. The module-name-key body is unchanged;
the separate placeholder literal-name getter retains its existing identity.

The canonical class makes semantic this a primary-object pointer while
the native update entry receives the secondary interface. Pointer and
reference base-conversion trials both emitted a null-preserving mask and
grew update from 2,916 to 2,931 bytes, matching 14/15 rows. The explicit
measured interface view removes those extra instructions and matches all
15 rows. The update prefix, parent-call receiver and all other code remain
identical. This is an ABI-view expression in normal C++, without assembly,
new aliases, compiler flags or a shared-header change.

Normal build.sh passes all 15 rows, 28 strings and one float; all three
parent EH graphs are exact. Frozen-source checks pass. Owning-tool
acceptance retires the final Animal header-queue row: none remain for this
source. Paired new-variant checking passes, and preview preserves
LINKS/3,167 bytes against c885072a48 (2026-11-08 19:18).

All 63 code COMDAT bodies, relocation bindings, flags and selection policies
remain equal, as do all 30 named data allocations, external definitions and
undefined references. No definition or table is added or removed. The
public-build object and privately verified candidate agree on these facts.
The packet records the source hash and unchanged parent call; final strict
preparation is required before publication.

This retires one class-header debt and private class copy in the main TU.
Constructor/destructor, state-machine and transfer donors remain separate
owners with their existing reconciliation prerequisites. Their composition,
literal-getter naming, source-file recovery and current-image/runtime
closure are not established by this header adoption. No row, source path,
pin, alias, hatch or new coverage claim changes.
