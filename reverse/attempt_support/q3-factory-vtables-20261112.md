# Q3 factory primary tables (LINK-514)

BFME2 workshop 1.06. All addresses below are RVAs. Read each primary
table from the PE at the extent in the real-link queue at 91240d3f01.
Follow slot zero, disassemble its 38-byte scalar deleting destructor,
and read the table it writes to [esi] before calling 0x00658650.

| Factory table | Slots | Deleting destructor | Table written in destructor | First slot of that table |
|---|---:|---|---|---|
| 008E1078 | 22 | 00656B00 | 008E0FC8 | 006562B0 |
| 008E20E4 | 13 | 0065E770 | 008E1E30 | 0065D810 |
| 008E23AC | 5 | 0065EC40 | 008E2368 | 0065E8E0 |
| 008E25A8 | 13 | 0065F910 | 008E24A0 | 0065F140 |
| 008E2768 | 6 | 0065FEB0 | 008E2730 | 0065FA30 |
| 008E2950 | 13 | 00660B80 | 008E2870 | 006602C0 |
| 008E3538 | 26 | 00668000 | 008E34D0 | 00667300 |
| 008E3788 | 25 | 00669450 | 008E36D8 | 00668620 |

Across the indicated widths every entry after slot zero in the
destructor-installed table points to 0003B810 (purecall). Each destructor
conditionally passes size 12 to 0065D030. In the factory tables, slot
one points to 00656A30 in the first six, 00667FB0 in the seventh and
00669400 in the eighth. Equal object size and a shared secondary getter
do not establish a common primary virtual interface.

The five-slot case gives a bounded reconstruction target. The factory at
0065EC70 and complete constructor at 0065E910 install 008E23AC at +0
and 008E0FB4 at +4. The existing source gives them separate class names
(Rva0065EC70Object and Rva007F1DE0Object). The concrete primary slots
are 0065EC40, 00656A30, 0065E9C0, 0065EA80 and 0065E930.
The last currently has a free stdcall ledger identity. Check the actual
indirect caller and stack contract before assigning its prototype.

The supported class fold dry run finds no special-member installer on
the factory identity. Moving slot two to the complete-constructor
identity also fails the current table proof. A follow-up needs a shared
concrete declaration checked against both installer bodies, the distinct
destructor-installed interface, and the slot call contracts. Verify each
primary relocation and both source files before requesting retirement
of a bridge. All eight bridges remain open.
