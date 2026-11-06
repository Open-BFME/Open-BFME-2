# HotKey interrupted adoption: rejected recovery draft

Inspected current revision: 8bb483ac9115. The archived chat06 seat2 changes are an interrupted application, with no completed byte/provider/acceptance verdict. They are not a completed shared-header adoption: neither source adds a canonical HotKey header.

In HotKey.cpp the proposal adds an _Rb_tree base to HotKeyMap while retaining its explicit header/count/comparator storage. This changes the assumed storage layout without target proof. In HotKeyAddHotKey.cpp it adds findAction with HotKeyStringTreeView, boundAction and HotKeyNode field accesses, although the draft only forward-declares HotKeyNode and does not supply those other declarations. These are direct source facts, not a compiler verdict. No Code or debt-register change was retained.

Rebuild the class contract from the existing native counted-handle/tree evidence (LINK-146) and use supported adoption/acceptance before reconsidering. The original reconstruction and its debt remain; this inspection does not reproduce or change the owning gate. No byte/link/runtime improvement is claimed.
