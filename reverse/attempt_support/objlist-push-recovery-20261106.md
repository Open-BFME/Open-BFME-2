# ObjListPush interrupted-trial recovery

Base: 8bb483ac911; recovered chat09 seat1 draft. The source already owns the full 26-byte row at 0x005CD018, and the proposed callee already owns 37 bytes at 0x005CCED5. This is identity-debt repair, not missing code.

The archived explicit push_back specialization calls the existing stdcall callee with raw output, position and value pointers. Normal `./build.sh Code/GameEngine/Source/Common/Rva005CD018ObjListPush.cpp` fails 1/1: the proposed body is 21 bytes versus retail 26. Retail materializes the iterator argument on the stack; the trial instead pushes the raw node pointer. Callee relocation masking does not repair the instruction-shape difference.

The initial partial/stash verdict was retracted: check_csv correctly rejects a standard body stash for an already-landed C++ row. The stash was removed; the unchanged candidate remains in the stopped-fleet recovery archive (chat09/seat1 source and patch). The replacement verdict is blocked identity repair, not missing-body progress. Code is restored to its original reconstruction; its identity-register key remains. Establish the native iterator/return ABI without a hand alias or extra body before retrying. No real-link, current consumer or runtime improvement is claimed.
