### LINK-174: Shadow owner tables are incomplete rather than false pure (2026-11-01, halilkkaya-codex)

Status: Open contract / no false-pure declaration found. The native run at
007CEFA0 is deleting destructor 000EFAD2, empty 000B3FD0, real purecall
0003B810. Current canonical base and Rva007B1380 views emit only the first
slot, with no pure declaration to replace. Complete extent and folded-owner
contracts remain unproven; no guessed slots or names were added. Nine
unchanged units preview LINKS 5,880 B. [Native words, all current emitters,
remaining boundary and additional held scopes](../../reverse/attempt_support/purecall-slot-audit-20261101/shadow.md).
