# GateProxy canonical Module factory view

Apply the established declaration-only factory pattern: retain Primary4 and
ProxyPad8, use canonical Module8 at +4, and reduce the gap before the existing
integer at +0x4C. The complete allocation stays 0x50 and the returned Module
pointer stays +4. The constructor remains the existing 53-byte owner at
0x0024E2CC, with Module table VA 0x00BEF304 at +4.

Select BFME_SNAPSHOT_NAME_SLOT and declare the four required Snapshot/key roles
without bodies. Slot2 returns GateProxyBehavior's name. Its currently nonvirtual
name owner and static/address-named key owner remain separate identity debt;
no alias or pin supplies a missing implementation. The complete hierarchy is
not claimed by this partial factory view.

The complete 65-byte factory and EXACT EH pass private and final strict-current
verification. All non-debug sections, definitions, relocation targets and
unresolved names remain identical, with SafeSEH COFF indices resolved to their
unchanged handler names. No table or thunk is emitted. Normal checks and the
owning Module acceptance tool pass, retiring one key. Preview against
ccafe54d1d preserves LINKS/65 bytes; no census gain is claimed.
