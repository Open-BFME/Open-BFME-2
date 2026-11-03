/* Target facts (RVAs): this is a non-polymorphic hash-table cursor with no virtual functions or evidenced base. first (0x00427195) writes the current node at +0 (0x004271C3/0x004271D5) and its table receiver at +4 (0x004271C7), then returns the cursor address. Eva::messageToName (0x001DEB8A) supplies the eight-byte home [ebp-8,ebp); for_each (0x004113F4) places successive by-value cursors at ebp+0x0C and ebp+0x14, proving sizeof 8.
   next (0x00411084) reads the node pointer at +0, follows its first word, calls advance (0x003F7925) when that link is null, stores the result at +0 and returns this. advance reads the node at +0 and table at +4, calls bucketIndex (0x00223149) with node+4, and scans the table's bucket vector at +4/+8. These are data pointers, not vptrs. No constructor or destructor row or vftable store is associated with this ledger class.
   The two methods retain their ledger names and are declared out of line. messageToName calls next at 0x001DEBC7 and for_each calls it at 0x0041141B. m_current and m_owner describe the node and table roles proved by first and next; they do not recover original field spellings. The placeholder class name does not identify an original STLport specialization. */
#pragma once

class Rva000411084
{
public:
    __declspec(noinline) void *next();
    void *advance();

    void *m_current;
    void *m_owner;
};
