from pathlib import Path
import csv,hashlib,json
ROOT=Path('W:/OpenBFME/Open-BFME-2')
D=Path('W:/OpenBFME/diagnostics/one-per-project-20261122-followup/bfme2/rva20-preflight')
source='Code/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudio.cpp'
header='Code/GameEngine/Include/Common/Rva0020DXXX.h'
contract='reverse/class_contracts/Rva0020DXXX.json'
inputs=[source,header,contract,'Code/GameEngine/Include/Common/Overridable.h',
 'Code/GameEngine/Source/Common/Overridable.cpp','Code/GameEngine/Source/Common/RvaTreeDtorFamily.cpp',
 'Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB04.cpp',
 'Code/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudioKeyMapBfmeAddKey.cpp',
 'Code/GameEngine/Source/GameLogic/System/Rva0020DXXXRva003EDD68.cpp',
 'tools/class_contract.py','tools/header_adopt_lane.py','tools/header_generation_proof.py']
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
hashes={p:{'sha256':sha(ROOT/p),'size':(ROOT/p).stat().st_size} for p in inputs}
expected={source:'013139e48ad27b3b0757b2662ca07c2f5b162cff89fdb17a6fc24502f4aab178',
 header:'f5d44e6544637b13315475088820a20647cc2df808708265c2166ae05002a775',
 contract:'056ce1b375665f1f1acab66748f44c5bc0226f9b51879a8d552f8496d8a716b0'}
for p,wanted in expected.items():assert hashes[p]['sha256']==wanted,p
rows=[];family=[];helper=[]
with (ROOT/'reverse/functions.csv').open(newline='',encoding='utf-8-sig') as f:
 for row in csv.DictReader(f):
  if row.get('source')==source and row.get('status')=='matched':
   rows.append({k:row[k] for k in ('name','target_rva','size','source','notes') if k in row})
  if 'Rva0020DXXX@@' in row.get('name',''):
   family.append({k:row[k] for k in ('name','target_rva','size','source','notes') if k in row})
  if row.get('target_rva','').lower() in {'0x003ed94f','0x001e3624','0x0020d7bc','0x0020d9d0'}:
   helper.append({k:row[k] for k in ('name','target_rva','size','source','notes') if k in row})
assert len(rows)==52,len(rows)
state=json.loads((ROOT/contract).read_text())
assert state['evidence']['retail_layout']['confidence']=='none'
summary={'verdict':'BLOCKED_NO_COMPLETE_CANONICAL_LAYOUT_OR_LIFETIME_IDENTITY',
 'head_observed':'4c9fb6b261a2f761d6b78385bf83d23750e2a4ef',
 'class':'Rva0020DXXX','header':header,'source':source,
 'served_anchor':'0x0007FAB3','served_size':0,'queue_key_count':1,
 'source_matched_rows':len(rows),'ready_adoptions':0,
 'native_cpp_calls':0,'native_pp_calls':0,'native_adopt_attempts':0,
 'repo_source_header_tool_metadata_claim_git_writes':0,
 'new_body_count':0,'new_cpp_bytes':0,'measured_link_gain':0,
 'generator_owned_header':False,'header_is_authored_call_only':True,
 'missing_prerequisites':['independent receiver/base and physical extent identity',
 'actual +0x10 container complete type and lifetime, including existing 8/12-byte views',
 'real +0x18..0x37 contents/lifetimes and +0x39/+0x3B meaning or justified unchanged opaque storage',
 'destructor/holder/vtable relationship independent of existing alternate-name binding',
 'only then complete owning contract and supported header-route proof']}
(D/'SUMMARY.json').write_text(json.dumps(summary,indent=2)+'\n')
(D/'INPUT-HASHES.json').write_text(json.dumps(hashes,indent=2)+'\n')
(D/'SCOPED-LEDGER-EVIDENCE.json').write_text(json.dumps({'evidence_kind':'current project rows and sources, not a fresh compiler/native-byte proof','source_rows':rows,'receiver_family':family,'existing_provider_rows':helper},indent=2)+'\n')
hdf='''# Rva0020DXXX — read-only whole-producer adoption preflight

BLOCKED. No honest whole-producer adoption or compiler trial is ready. The registered opaque four-method header cannot replace the concrete producer model. No source, header, generator, contract, ledger, pin, claim, Git or shared build/cache write was performed. No CPP/PP/adopt call was run. No other target was selected.

Scope: B2 observed HEAD 4c9fb6b261a2f761d6b78385bf83d23750e2a4ef (master aff975 integrated). Served item is class Rva0020DXXX / one remaining header_queue key / anchor 0x0007FAB3, size0. That served anchor is not the address or size of this classs destructor. An independent streamed current-ledger count corrected the initial parent estimate55: the whole LargeGroupAudio.cpp has52 matched rows and the known absent-from-retail destructor anchor, retained untouched. Root reported its own lease33ad...; this review did not fetch, acquire, transfer or release claims.

## Evidence and blocker

The authored Rva0020DXXX.h was registered by a2b400f290180aebcbcbcbc89b40638e24af20b3 on Nov11. It exposes registerSubject(int), rva0020D7F9(), rva0020D959(int), updateSubject(int). It is explicitly call-only, not a generated full-layout header. Seven callers use it without inspecting storage. Adding the existing internal rva0020D834 prototype alone cannot repair the producers field and destructor requirements.

Saved class_contracts/Rva0020DXXX.json has retail_layout confidence none and facts {}; no independent native complete-layout witness. bases=[] and sizeof64 are majority outcomes. Seven views have size1; exactly one concrete producer view has size64. Only VPTR0 is in decided fields; +4,+8,+C,+10,+14,+38..+3C are recorded as outliers. queue=[] therefore is not proof of complete class identity.

LargeGroupAudio.cpp172 models Rva0020DXXX as canonical Overridable16 plus an 8-byte Rva003ED94FDtor at+10, opaque32 bytes+18..37, four char fields+38..3B and int+3C. Five ordinary methods directly use range+10/+14, flags+38/+3A and frame+3C. Lines439–452 explicitly state that element type, +39, the +18..37 gap and base size remain unproven. The existing local absent-from-retail anchor forces the implicit destructor; it must not be converted into claimed original behavior or replaced by a fresh emitter trick.

## Existing 53-byte destructor/provider boundary

Current matched row ??1Rva0020DXXX@@UAE@XZ at0020D9EC is53B in LargeGroupAudio.cpp. Its current C++ lifetime model invokes ??1Rva003ED94FDtor@@QAE@XZ at003ED94F on this+10, then the canonical ??1Overridable@@UAE@XZ at001E3624 on this. The 58B member provider is in RvaTreeDtorFamily.cpp1102ff: RvaTreeFamilyHolder plus int, bfmeClearMembers, member-holder teardown, /EHs. Overridable.cpp owns the35B base destructor. These current provider rows/sources establish existing routing and keep the prerequisites explicit; no fresh COFF/original-image byte verification was performed by this review.

The member-destructor address is also used by genuine12B aggregate/fold views (Rva003ED658 and Rva003ED94FDtor locals/default-ctor fold001F81BF). The producing local declaration is only8B. Equal destructor code/address does not establish a complete8/12B class identity.

Additional existing identity tension: row0020D7BC/61B is the new0x1C Rva0020D98D holder at LargeGroupAudio+34 and names vtable007E3FF4. The same tables slot0 is represented by opaque deleting wrapper0020D9D0/28B, which reaches0020D9EC under its old address-derived name. OpaqueScalarDeletingDtorsB04.cpp211 uses an existing /alternatename from that old destructor to Rva0020DXXX. This route supplies no independent justification to promote the64B range view into the complete physical holder class. Reconcile the actual constructor/vtable/caller/receiver identity first; do not merge names or pins from same-shape evidence.

## Required minimal prerequisite and normal tool boundaries

First recover independent target receiver/base/extent facts, the complete real+10 container and teardown contract, and the actual+18..37/later-field lifetimes. Existing canonical Overridable establishes its own16B contract, but that alone cannot identify this receiver as its actual derived object. Preserve the existing unrelated LargeGroupAudio, Rva0020D98D, Rva003ED658 and element views until their distinct physical contracts are proved. No original EA type/member spelling is invented here.

Only after those facts: normal class_contract.py --class Rva0020DXXX --write is the owning contract writer; header_adopt_lane.py adopt/accept is the owning source-adoption/queue-retirement path. Those commands were not run. Current registered run --class ... --generate --apply additionally uses header_generation_proof: initial admission explicitly supports baseless literal classes and primitive/pointer fields. The proposed Overridable base plus by-value lifetime-bearing helper is outside that admitted syntax. Do not hand-write contract decisions, strip the base, flatten the owning member, adjust its padding to pass, extend a baseline, or bypass the roundtrip proof. A full generated or authored replacement needs its normal independently justified owning route and all established consumers/providers checked; this packet authorizes none.

The current native queue refusal (canonical header laid out no field) is a real prerequisite diagnostic. Native tools are not missing a simple prototype or field-token spelling correction. Keep the opaque registered header and existing producer unchanged; Root records the served size0 header item blocked and performs its own fenced release. No new C++ body, data, source adoption, linked bytes, performance, memory or runtime gain is claimed.

Hashes, the exact52 scoped rows, six receiver rows and existing provider rows are retained in INPUT-HASHES.json / SCOPED-LEDGER-EVIDENCE.json. Stop after this packet. PC remains on.
'''
(D/'HANDOFF.md').write_text(hdf,encoding='utf-8',newline='\n')
for p,wanted in expected.items():assert sha(ROOT/p)==wanted,p
files={p.name:{'sha256':sha(p),'size':p.stat().st_size} for p in sorted(D.iterdir()) if p.is_file() and p.name!='MANIFEST.json'}
(D/'MANIFEST.json').write_text(json.dumps({'verdict':summary['verdict'],'files':files},indent=2)+'\n')
print(json.dumps({'source_rows':len(rows),'handoff_sha256':sha(D/'HANDOFF.md'),'summary_sha256':sha(D/'SUMMARY.json'),'manifest_sha256':sha(D/'MANIFEST.json'),'actual_cpp_pp':0},indent=2))

