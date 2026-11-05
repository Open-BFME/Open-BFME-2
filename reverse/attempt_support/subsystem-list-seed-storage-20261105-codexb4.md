# SubsystemInterfaceList seed canonical storage

Base: `9f51ea3231`. Scope: the approved System/SubsystemInterface.cpp seed,
its canonical list header and the 0x001B4FE9 notification consumer. No row
moves or census changes are claimed in this prerequisite.

Target evidence: 0x001B5140 collects subsystem pointers from the +0 records
and +0x0C pointer array into +0x18. 0x001B4FE9 dispatches those collected
objects. Both pointer arrays therefore use SubsystemInterface pointers in
the canonical header. The seed now includes that header rather than defining
a private list class. Its existing eight-byte record erase and the consumer's
void-pointer erase retain explicit storage views and their verified callees.
This is a layout-compatible type reconciliation, not donor-name evidence.

The native destructor EH states at 0x00769509, 0x00769511 and 0x0076951C
call the conditional-free helper at 0x0007FAB3. `pin_admission.py --add`
proved and admitted the complete vector<SubsystemInterface*> and
vector<pair<SubsystemInterface*,void*> > destructor folds there. Both emit
14 bytes, `8b 01 85 c0 74 07 50 e8 00 00 00 00 59 c3`, with the sole
relocation at offset 8 to `_free`. These are full-body and relocation proofs,
not masked call aliases. The byte gate also verifies the constructor folds.

Removed the stale donor-sweep _Vector_base<SubsystemInterface*> pin at
0x0002CC70: that retail body is a 63-byte element-destroying vector<AsciiString>
destructor, whereas the emitted base destructor is the 14-byte free-only body.
A COFF-symbol audit searched all 23,737 cached build/match objects. The only
occurrence was the seed's definition (section 106); there were no undefined
references. No alternatename was removed. `pin_consistency.py --check` passes.

Validation:

- `./build.sh` seed and 0x001B4FE9 consumer: 18/18 rows exact; strings,
  floats and imports pass. `eh_verify.py`: 2 exact, no missing/nonexact.
- `find_declared_unmatched.py`: both sources entirely rowed.
- `data_check.py`: zero shadow findings in the two sources.
- `link_check.py`: seed 630 -> 630 and consumer 77 -> 77 preview bytes.
- `header_adopt_lane.py accept --class SubsystemInterfaceList` retired the
  seed's one header queue entry through its owning lane.
- Header dependents: all 20 ledger sources pass, 223/223 byte-matched rows,
  5 data rows, 137 literals plus 10 empty-string references, 2 float literals
  and 19 imports verified. No red dependency chunks.

The notification donor's specialization ordering is a separate prerequisite
before the approved TU merge. The mixed Libraries TU is outside this merge.

Batch audit after preparing strict current receipts for all 20 sources exits 2:

```
link batch audit: INCONCLUSIVE baseline: index at c95fcfcfcd, outgoing base HEAD; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Carry these 20 verified providers and that consumer into the next scheduled
census. This is an unverified audit boundary, not a clean batch link result.
The explicit two-source preview above is the scope with retained linking evidence.
