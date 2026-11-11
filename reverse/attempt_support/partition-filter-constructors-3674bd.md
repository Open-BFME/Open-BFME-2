# Partition-filter constructor identity at 0x003674BD and 0x003674CA

At 954949d30d the original 13-byte constructor at 0x003674BD clears +4
and installs VA 0x00C172A8. Its three slots are the deleting destructor at
0x00395A19, PartitionFilterIsFlying::allow at 0x00260E01 and getPlayerMask
at 0x0036CC7A. The 29-byte constructor at 0x003674CA clears +4, places its
first argument at +8 and its flag at +0x0C, and installs VA 0x00BF8FE4.
Its middle slot is Rva00261058::allow at 0x0026109D. That method uses +8 as
Player*. AIGuardInnerTargetRva00369FDF.cpp already constructs the player
overload inline. The separately rowed 0x00261058 constructor takes Object*
and obtains its controlling player.

An isolated VC7.1 trial included PartitionFilter.h and used GapBodiesGE08.cpp's
flags. The flying filter derived from Rva000421C8, declared its existing
allow(Object*) override and had an empty constructor. The player filter used
the same base and initialized its Player* and bool in declaration order.
Passing each proposed constructor to tools/explain_mismatch.py with --source,
--rva and --size produced these results:

| Proposed constructor | RVA | Comparison |
| --- | --- | --- |
| ??0PartitionFilterIsFlying@@QAE@XZ | 0x003674BD | exact, 13/13 bytes |
| ??0Rva00261058@@QAE@PAVPlayer@@_N@Z | 0x003674CA | exact, 29/29 bytes |

Both official fold dry runs stop at the new owner's destructor:

```
python tools/rename.py class --fold Rva003674BD --into PartitionFilterIsFlying --dry-run
python tools/rename.py class --fold Rva003674CA --into Rva00261058 --dry-run
```

The native table's slot 0 calls 0x0049C38A. That seven-byte destructor
restores VA 0x00BC26E0, whose middle slot is purecall. The refusal treats
that base restore as the derived class's own table. A tooling test should
distinguish this verified teardown from an actual conflict with another
constructor's installation. The player overload also needs distinct
constructor signatures supported by the fold path; passing the first check
alone would not establish admission. Both existing constructor rows and
their one-slot emitters are unchanged.
