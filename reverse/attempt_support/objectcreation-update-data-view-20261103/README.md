# ObjectCreationUpgradeUpdate data-view class alignment

Scratch-only private prerequisite,2026-11-03. Control SHA256:274d52ba0ba537bc1630faf86bf5183feb7a5418eb7cacfd521b002e71b42eba. Reject application if current source no longer matches that captured input. Candidate changes only flat struct ObjectCreationUpgradeModuleData into public-members class __declspec(novtable) ObjectCreationUpgradeModuleData:public Snapshot, with m_pad000[0x120-sizeof(Snapshot)]. It retains all named fields, method bodies and already-selected Snapshot include context. No canonical ModuleData base is substituted, and no complete leaf/source recovery is claimed.

Sanctioned private Verifier passes3/3 current rows for both control and candidate. Owning EH verify_row reports EXACT for both complete update parent graphs. Compiler assertions prove string members at0x120/0x124/0x128, angle0x138, fade0x14C, special-context byte0x150 and sizeof0x154. The assertions are appended to the scratch candidate and emit no runtime code.

The ordinary external set is17->17. Sixteen common definitions remain completely identical, including symbolic relocation contexts. The one unrowed helper getObjectCreationUpgradeModuleData changes its decorated pointer return from PBUObjectCreationUpgradeModuleData (struct) to PBVObjectCreationUpgradeModuleData (class). Its old/new code bytes and ordinary symbolic relocations are identical when excluding the decorated name, as helper-body-comparison.json records. This is nevertheless a real provider-name removal/addition, not an identical external-set proof. Root must check any current external consumer of that helper and migrate bindings coherently before landing. No new application table is emitted by this pointer-consumer view.

This shape supports later mechanical seed/Update class-view reconciliation; it does not merge files itself or prove the real ModuleData constructor/member lifetime/table. No tracked source, ledger, claim, network, shared build-cache or check mutation was performed. Current source passed find_declared_unmatched.py before the private proof. Root retains normal source verification, strict/EH/link and provider-consumer checks before commit/publication. Candidate.cpp, control.cpp, proof.json and private objects are scratch evidence only.

Tracked application used the assertion-free candidate after matching the exact
control SHA256. It independently retains3/3 rows and EXACT EH in private proof;
normal3/3 and strict receipt pass. Owning-source/cache dependent search across
18560 current sources finds old helper only in Update itself and no outside
old/new caller; private objects carry no helper runtime/root/undefined edge.
The historical index supplies provider facts only and lacks per-object reference
contributions; it is not used as sole caller proof. Old/new helper code and
ordinary relocations are identical apart from the real return-type spelling.
No row, pin or function identity is renamed in the ledgers. This closes the
bounded helper-consumer prerequisite, with final batch/census gates retained.
