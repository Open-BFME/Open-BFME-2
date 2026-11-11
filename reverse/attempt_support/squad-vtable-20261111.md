# Squad snapshot name at RVA 0x00268CD6

At revision `471fc6303c`, the constructor at 0x00268CAC installs VA 0x00BF9D60. Slot 2 points to the six-byte getter returning "Squad". The registered Squad header declares this protected const virtual as `GetSnapshotName`. The real-link queue reports three mismatches in the four-slot table.

For the trial, replace the constructor unit's private inline lowercase getter with the out-of-line declaration `virtual const char *GetSnapshotName() const;`. In a prepared copy of SubsystemNameGetters2.cpp, enable STLport, include `../../Include/Common/SquadClass.h`, and replace the Rva00268CD6Named macro with the definition returning "Squad". The resulting constructor still matches all 42 bytes.

`rename.py function --rva 0x00268CD6 --to-class Squad --new '?GetSnapshotName@Squad@@MBEPBDXZ' --prepared SOURCE=FILE` proved the installer and slot. Both sources passed 43/43 functions and 42 string references. The required second check selected 1,436 dependent sources. Windows CreateProcess returned error 206 before that check started. The rename transaction rolled back. The restored pair also passed 43/43 functions and 42 string references.

Retry with transport that can pass the entire dependent set to the verifier. Slot 0 still needs the deleting-destructor provider at 0x0026AF6A and slot 1 the shared return at 0x000B3FD0. In a separate constructor-header trial the two calls targeted vector constructors instead of the verified vector-base bindings at 0x00211E58, with both /O1 and /O1 /Ob2. No slot or bridge retirement is claimed.
