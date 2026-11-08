"""tools/rename.py class --fold, the initializer route: NEW names no vftable and has no virtual, but
retail builds a global rowed as NEW with placeholder OLD's constructor (P36: Rva005F00FB and
MappedImageCache, 0x00E06858). The retail bytes are a synthetic image read by the real decoder, as in
test_rename_this_cv.py; the other retail readers are injected as in test_rename_fold.py."""
import struct
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import build  # noqa: E402
import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

REAL_CHECK_AGREEMENT = rename.check_agreement

OLD, NEW = "Rva00501000", "ImageCache"
OWNER = "Code/Game/ImageGet.cpp"
G = 0x00A06858
G_VA = G + rename.IMAGE_BASE
EXTENT = 112
TABLE = 0x00800000
TABLE_VA = TABLE + rename.IMAGE_BASE
BASE_TABLE_VA = 0x00C00100
CTOR, DTOR, GDTOR = 0x00501000, 0x00502000, 0x00503000
BASE_CTOR, BASE_ARG = 0x00510000, 0x00511000
GET, CALLER = 0x00504000, 0x00505000
GET2, CALLER2 = 0x00506000, 0x00507000
INIT, THUNK = 0x007B0000, 0x007B1000
ATEXIT, EH_PROLOG = 0x00629000, 0x00629100
PURECALL = 0x0003B810
OTHER_DTOR = 0x00508000
TEXT_START, TEXT_END = 0x00500000, 0x007C0000


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


def le32(value):
    return struct.pack("<I", value & 0xFFFFFFFF)


def rel(op, at, target):
    return bytes([op]) + le32(target - (at + 5))


def ctor_body(at=CTOR, extra=b"", vptr=TABLE_VA, base=BASE_CTOR):
    """push esi; mov esi,ecx; call base; mov [esi],table; and [esi+0x3C],0; and [esi+0x50],0;
    extra; mov eax,esi; pop esi; ret"""
    head = b"\x56\x8B\xF1" + rel(0xE8, at + 3, base)
    return head + b"\xC7\x06" + le32(vptr) + b"\x83\x66\x3C\x00" + b"\x83\x66\x50\x00" + extra + b"\x8B\xC6\x5E\xC3"


# mov [ecx],base table; and [ecx+4],0; mov eax,ecx; ret
BASE_BODY = b"\xC7\x01" + le32(BASE_TABLE_VA) + b"\x83\x61\x04\x00" + b"\x8B\xC1\xC3"
DTOR_BODY = b"\x8B\xC1\xC3"
GDTOR_BODY = b"\x56\x8B\xF1" + rel(0xE8, GDTOR + 3, DTOR) + b"\x8B\xC6\x5E\xC2\x04\x00"


def getter_body(disp=0x3C):
    # mov eax,[esp+4]; mov eax,[ecx+eax*4+disp]; ret 4
    return b"\x8B\x44\x24\x04" + b"\x8B\x44\x81" + bytes([disp]) + b"\xC2\x04\x00"


def caller_body(at=CALLER, target=GET, g_va=G_VA):
    # push [esp+4]; mov ecx,&G; call target; ret
    return b"\xFF\x74\x24\x04\xB9" + le32(g_va) + rel(0xE8, at + 9, target) + b"\xC3"


def init_body(at=INIT, g_va=G_VA, ctor=CTOR, thunk=THUNK):
    return (b"\xB9" + le32(g_va) + rel(0xE8, at + 5, ctor) + b"\x68" + le32(thunk + rename.IMAGE_BASE)
            + rel(0xE8, at + 15, ATEXIT) + b"\x59\xC3")


def thunk_body(at=THUNK, g_va=G_VA, dtor=DTOR):
    return b"\xB9" + le32(g_va) + rel(0xE9, at + 5, dtor)


def image(**changes):
    """{rva: bytes} of the good case, with `changes` by name."""
    bodies = {
        "ctor": (CTOR, ctor_body()), "dtor": (DTOR, DTOR_BODY), "gdtor": (GDTOR, GDTOR_BODY),
        "base": (BASE_CTOR, BASE_BODY), "get": (GET, getter_body()), "caller": (CALLER, caller_body()),
        "init": (INIT, init_body()), "thunk": (THUNK, thunk_body()),
    }
    bodies.update(changes)
    return dict(bodies.values())


def functions(extra=""):
    return f"""name,export_rva,target_rva,target_size,source,status,notes
??0{OLD}@@QAE@XZ,,0x{CTOR:08X},@CTOR@,Code/Game/Ctor.cpp,matched,ctor
??1{OLD}@@UAE@XZ,,0x{DTOR:08X},{len(DTOR_BODY)},Code/Game/Ctor.cpp,matched,dtor
??_G{OLD}@@UAEPAXI@Z,,0x{GDTOR:08X},{len(GDTOR_BODY)},Code/Game/Ctor.cpp,matched,deleting dtor
??0Rva00510000@@QAE@XZ,,0x{BASE_CTOR:08X},@BASE@,Code/Game/Base.cpp,matched,base ctor
?fetch@{NEW}@@QAEPBXH@Z,,0x{GET:08X},@GET@,{OWNER},matched,getter
?caller@@YAPBXH@Z,,0x{CALLER:08X},{len(caller_body())},{OWNER},matched,caller
?init@@YAXXZ,,0x{INIT:08X},{len(init_body())},Code/Game/Inits.cpp,matched,initializer
?cleanup@@YAXXZ,,0x{THUNK:08X},{len(thunk_body())},Code/Game/Inits.cpp,matched,thunk
_atexit,,0x{ATEXIT:08X},18,Code/Game/Crt.cpp,matched,
__EH_prolog,,0x{EH_PROLOG:08X},31,Code/Game/Crt.cpp,matched,
{extra}"""


def data_rows(name=f"?Cache@@3V{NEW}@@A", size=EXTENT, address=G_VA, status="matched"):
    return ("name,address,address_kind,size,section,source,status,evidence,model\n"
            f"{name},0x{address:08X},va,{size},.data,{OWNER},{status},probe,m\n")


def ledger(name=f"?Cache@@3V{NEW}@@A", size=EXTENT):
    return ("address,size,section,kind,name,source,status,names,defs,refs\n"
            f"0x{TABLE:08X},8,.rdata,vtable,??_7{OLD}@@6B@,,literal,,0,3\n"
            f"0x{G:08X},{size},.data,global,{name},{OWNER},owned,,1,5\n")


NAME_BASIS = ("kind,old,new,basis,evidence,source,rva\n"
              f"class,Rva00600000,{NEW},inferred,agree:nl-test,{OWNER},\n")
NAME_AGREED = ("id,kind,old,new,rva,agents,key,status,detail\n"
               f"nl-test,class,Rva00600000,{NEW},,a;b,{OWNER}|class||Rva00600000,landed,two-agent agreement\n")
CENSUS = f"old,new,initializer,review\n{OLD},{NEW},0x{INIT:08X},read by hand\n"
CTOR_SRC = f"class {OLD}\n{{\npublic:\n\t{OLD}();\n\tvirtual ~{OLD}();\n}};\n{OLD}::{OLD}() {{}}\n{OLD}::~{OLD}() {{}}\n"
OWNER_SRC = f"class {NEW}\n{{\npublic:\n\tconst void *fetch(int);\nprivate:\n\tchar m_pad[{EXTENT}];\n}};\n{NEW} Cache;\n"
PREPARED = f"class {NEW}\n{{\npublic:\n\t{NEW}();\n\tconst void *fetch(int);\nprivate:\n\tchar m_pad[{EXTENT}];\n}};\n{NEW} Cache;\n".encode()


def make_tree(root, *, bodies=None, fn=None, rows=None, data=None, sources=None):
    bodies = image() if bodies is None else bodies
    text = fn or functions()
    text = (text.replace("@CTOR@", str(len(bodies[CTOR]))).replace("@BASE@", str(len(bodies.get(BASE_CTOR, BASE_BODY))))
            .replace("@GET@", str(len(bodies.get(GET, getter_body())))))
    files = {
        "reverse/functions.csv": text,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": rows or data_rows(),
        "reverse/data_ledger.csv": data or ledger(),
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/name_basis.csv": NAME_BASIS,
        "reverse/initializer_fold_census.csv": CENSUS,
        "reverse/name_agreed.csv": NAME_AGREED,
        "Code/Game/Ctor.cpp": CTOR_SRC,
        OWNER: OWNER_SRC,
        "Code/Game/Base.cpp": "class Rva00510000 { public: Rva00510000(); };\nRva00510000::Rva00510000() {}\n",
        "Code/Game/Inits.cpp": "void init() {}\nvoid cleanup() {}\n",
        "Code/Game/Crt.cpp": "void crt() {}\n",
    }
    files.update(sources or {})
    for rel_path, content in files.items():
        path = root / rel_path
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(content.encode("utf-8"))
    _git(root, "init", "-q")
    _git(root, "add", "-A")
    return root


def retail(monkeypatch, bodies=None, initializers=(INIT,), store=CTOR + 8, stores=None):
    bodies = image() if bodies is None else bodies
    blob = bytearray(b"\xCC" * (TEXT_END - TEXT_START))
    for at, code in bodies.items():
        if TEXT_START <= at < TEXT_END:
            blob[at - TEXT_START:at - TEXT_START + len(code)] = code

    def read(rva, size):
        for at, code in bodies.items():
            if at <= rva < at + len(code):
                return (code[rva - at:] + b"\xCC" * size)[:size]
        return b"\xCC" * size
    monkeypatch.setattr(build, "read_target_bytes", read)
    monkeypatch.setattr(rename, "retail_initializers", lambda ctx: list(initializers))
    monkeypatch.setattr(rename, "retail_text", lambda ctx: (TEXT_START, bytes(blob)))
    monkeypatch.setattr(rename, "retail_vtables", lambda ctx: {
        TABLE: ([GDTOR, PURECALL], stores if stores is not None else {store: 0})})
    monkeypatch.setattr(rename, "check_agreement", lambda ctx, kind, evidence, olds, news, rva: None)


def plan(root, prepared=None, new=NEW):
    return rename.plan_rename("class", ctx=rename.Context(root, object_scan=False), name=OLD, new=new, fold=True,
                              prepared={OWNER: PREPARED} if prepared is None else prepared)


def refused(tmp_path, monkeypatch, match, *, bodies=None, initializers=(INIT,), fn=None, rows=None, data=None,
            sources=None, new=NEW, stores=None):
    root = make_tree(tmp_path, bodies=bodies, fn=fn, rows=rows, data=data, sources=sources)
    retail(monkeypatch, bodies, initializers=initializers, stores=stores)
    with pytest.raises(Refusal, match=match):
        plan(root, new=new)


# ------------------------------------------------------------ the proof

def test_the_initializer_ties_old_to_the_globals_class(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    result = plan(root)
    assert result.fold == TABLE
    assert result.new == NEW
    tie = result.fold_tie
    assert tie["owner"] == OWNER and tie["entry"] == INIT and tie["g"] == G and tie["extent"] == EXTENT
    assert tie["ctor_new"] == f"??0{NEW}@@QAE@XZ"
    assert OWNER in result.verify
    assert f"retail initializer 0x{INIT:08X} builds" in result.evidence
    assert "sets up +0x3c, past its base chain's +0x8" in result.evidence
    fns = result.after["reverse/functions.csv"].decode()
    assert f"??0{NEW}@@QAE@XZ,,0x{CTOR:08X}" in fns and f"??1{NEW}@@UAE@XZ,,0x{DTOR:08X}" in fns
    assert result.after[OWNER] == PREPARED


def test_an_eh_framed_ctor_passing_this_up_a_chain_is_read(tmp_path, monkeypatch):
    # P36's shape: an __EH_prolog frame before `mov esi,ecx`; the base ctor stores +0 and +4 and gives
    # `this` to another object's ctor as a stack argument, which stores the pointer and goes no further.
    ctor = (b"\xB8" + le32(0x00BA0000) + rel(0xE8, CTOR + 5, EH_PROLOG) + b"\x51\x51\x53\x56\x57\x8B\xF1"
            + b"\x89\x75\xEC")                          # mov [ebp-0x14],esi
    ctor += b"\x8B\xCE" + rel(0xE8, CTOR + len(ctor) + 2, BASE_CTOR)
    store = CTOR + len(ctor)
    ctor += b"\xC7\x06" + le32(TABLE_VA)
    ctor += b"\x8D\x46\x3C\x8D\x4E\x50"                 # lea eax,[esi+0x3C]; lea ecx,[esi+0x50]
    ctor += b"\xEB\x06\x83\x20\x00\x83\xC0\x04\x3B\xC1\x75\xF6"     # for (; eax != ecx; eax += 4) *eax = 0;
    ctor += b"\x8D\x46\x64"                             # lea eax,[esi+0x64]: the loop's end
    ctor += b"\x8B\x4D\xF4\x5F\x8B\xC6\x5E\x5B\xC9\xC3"
    base = (b"\x56\x8B\xF1\x6A\x0C\xC7\x06" + le32(BASE_TABLE_VA))  # push esi; mov esi,ecx; push 0xC; mov [esi],t
    base += rel(0xE8, BASE_CTOR + len(base), 0x00512000) + b"\x59\x8B\xC8"     # call new; pop ecx; mov ecx,eax
    base += b"\x56" + rel(0xE8, BASE_CTOR + len(base) + 1, BASE_ARG)            # push esi; call node ctor
    base += b"\x89\x46\x04\x8B\xC6\x5E\xC3"             # mov [esi+4],eax; mov eax,esi; pop esi; ret
    node = b"\x8B\x44\x24\x04\x89\x41\x08\x8B\xC1\xC2\x04\x00"     # mov eax,[esp+4]; mov [ecx+8],eax; ...; ret 4
    new_op = b"\x33\xC0\xC3"
    bodies = image(ctor=(CTOR, ctor), base=(BASE_CTOR, base), node=(BASE_ARG, node), new_op=(0x00512000, new_op))
    fn = functions(f"??0Node@@QAE@PAX@Z,,0x{BASE_ARG:08X},{len(node)},Code/Game/Base.cpp,matched,\n"
                   f"??2@YAPAXI@Z,,0x{0x00512000:08X},{len(new_op)},Code/Game/Crt.cpp,matched,\n")
    root = make_tree(tmp_path, bodies=bodies, fn=fn)
    retail(monkeypatch, bodies, store=store)
    assert "past its base chain's +0x8" in plan(root).evidence


def eh_ctor():
    """`mov eax,<FuncInfo>; call __EH_prolog; push esi; mov esi,ecx`, then the good case's body."""
    head = b"\xB8" + le32(0x00BA0000) + rel(0xE8, CTOR + 5, EH_PROLOG) + b"\x56\x8B\xF1"
    body = head + rel(0xE8, CTOR + len(head), BASE_CTOR)
    store = CTOR + len(body)
    body += b"\xC7\x06" + le32(TABLE_VA) + b"\x83\x66\x3C\x00\x83\x66\x50\x00\x8B\xC6\x5E\xC9\xC3"
    return body, store


def test_the_one_eh_prolog_row_keeps_this(tmp_path, monkeypatch):
    body, store = eh_ctor()
    bodies = image(ctor=(CTOR, body))
    root = make_tree(tmp_path, bodies=bodies)
    retail(monkeypatch, bodies, store=store)
    assert plan(root).fold_tie["g"] == G


def test_a_second_eh_prolog_row_gives_no_exception(tmp_path, monkeypatch):
    # Neither row keeps ecx, so `mov esi,ecx` copies no `this` and the +0 store is no longer through it.
    body, store = eh_ctor()
    fn = functions("__EH_prolog,,0x00512100,31,Code/Game/Crt.cpp,matched,\n")
    bodies = image(ctor=(CTOR, body))
    root = make_tree(tmp_path, bodies=bodies, fn=fn)
    retail(monkeypatch, bodies, store=store)
    with pytest.raises(Refusal, match="not exactly once"):
        plan(root)


def test_a_placeholder_method_on_the_same_receiver_decides_nothing(tmp_path, monkeypatch):
    # The second getter (0x005F0185): a placeholder class, possibly a base's method, called on G.
    # It stays out of the proof whatever it touches.
    bodies = image(get2=(GET2, getter_body(0x7F)), caller2=(CALLER2, caller_body(CALLER2, GET2)))
    fn = functions(f"?fetch2@Rva00506000@@QAEPBXH@Z,,0x{GET2:08X},{len(getter_body())},{OWNER},matched,\n"
                   f"?caller2@@YAPBXH@Z,,0x{CALLER2:08X},{len(caller_body())},{OWNER},matched,\n")
    root = make_tree(tmp_path, bodies=bodies, fn=fn)
    retail(monkeypatch, bodies)
    assert plan(root).fold_tie["g"] == G


# ------------------------------------------------------------ the initializer's own shape

def test_a_second_initializer_refuses(tmp_path, monkeypatch):
    second = INIT + 0x100
    bodies = image(second=(second, init_body(second, g_va=G_VA + 0x70)))
    refused(tmp_path, monkeypatch, "2 retail initializers call a constructor", bodies=bodies,
            initializers=(INIT, second))


def test_work_after_the_ctor_refuses(tmp_path, monkeypatch):
    # a derived class's inlined constructor stores its own table after the base's returns
    body = b"\xB9" + le32(G_VA) + rel(0xE8, INIT + 5, CTOR) + b"\xC7\x05" + le32(G_VA) + le32(0x00C00200) + b"\xC3"
    refused(tmp_path, monkeypatch, "is not exactly `mov ecx,&G; call ctor`", bodies=image(init=(INIT, body)))


def test_work_before_the_ctor_refuses(tmp_path, monkeypatch):
    body = b"\x51" + init_body(INIT + 1)
    refused(tmp_path, monkeypatch, "is not exactly `mov ecx,&G; call ctor`", bodies=image(init=(INIT, body)))


def test_an_interior_address_refuses(tmp_path, monkeypatch):
    bodies = image(init=(INIT, init_body(g_va=G_VA + 4)), thunk=(THUNK, thunk_body(g_va=G_VA + 4)))
    refused(tmp_path, monkeypatch, "is not the exact start of one matched data row", bodies=bodies)


def test_another_caller_of_the_ctor_refuses(tmp_path, monkeypatch):
    # A class derived from OLD: its constructor calls OLD's. OLD is then a base, not G's class.
    derived = 0x00509000
    body = b"\x8B\xC1" + rel(0xE8, derived + 2, CTOR) + b"\xC3"
    refused(tmp_path, monkeypatch, "retail also reaches", bodies=image(derived=(derived, body)))


def test_a_ctor_named_by_address_elsewhere_refuses(tmp_path, monkeypatch):
    # an array of OLD: the vector constructor iterator is given its address
    other = 0x00509000
    body = b"\x68" + le32(CTOR + rename.IMAGE_BASE) + b"\xC3"
    refused(tmp_path, monkeypatch, "retail also reaches", bodies=image(other=(other, body)))


# ------------------------------------------------------------ the global's row

def test_a_placeholder_new_refuses(tmp_path, monkeypatch):
    name = "?Cache@@3VRva00600000@@A"
    fn = functions().replace(f"?fetch@{NEW}", "?fetch@Rva00600000")
    refused(tmp_path, monkeypatch, "Rva00600000 is a placeholder", fn=fn, rows=data_rows(name), data=ledger(name),
            new="Rva00600000")


# ------------------------------------------------------------ NEW's provenance: spelling never qualifies

def test_a_hand_named_class_refuses(tmp_path, monkeypatch):
    header = "kind,old,new,basis,evidence,source,rva\n"
    refused(tmp_path, monkeypatch, "a hand-named class does not qualify", sources={"reverse/name_basis.csv": header})


@pytest.mark.parametrize("record", [
    f"class,Rva00600000,{NEW},inferred,,{OWNER},",                          # no agreement at all
    f"class,Rva00600000,{NEW},inferred,mechanical:x,{OWNER},",              # not an agreement
    f"class,Rva00600000,{NEW},guess,agree:nl-test,{OWNER},",                # not an inferred record
])
def test_an_inferred_row_with_no_agreement_refuses(tmp_path, monkeypatch, record):
    basis = "kind,old,new,basis,evidence,source,rva\n" + record + "\n"
    refused(tmp_path, monkeypatch, "not a verified agreement", sources={"reverse/name_basis.csv": basis})


def test_a_failing_agreement_refuses(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)

    def failing(ctx, kind, evidence, olds, news, rva):
        assert (kind, evidence, olds, news, rva) == ("class", "agree:nl-test", {"Rva00600000"}, {NEW}, None)
        raise Refusal("agreement record nl-test does not agree to this rename: the record was disputed")
    monkeypatch.setattr(rename, "check_agreement", failing)
    with pytest.raises(Refusal, match="the record was disputed"):
        plan(root)


def test_a_verified_agreement_passes_and_says_what_it_is(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    calls = []
    monkeypatch.setattr(rename, "check_agreement", lambda *args: calls.append(args[1:]))
    result = plan(root)
    assert calls == [("class", "agree:nl-test", {"Rva00600000"}, {NEW}, None)]      # live, at plan time
    assert "verified now), not retail-evidenced" in result.evidence


def test_the_record_of_another_classs_rename_refuses(tmp_path, monkeypatch):
    # check_agreement's own test: the record's old and new must be this one's (a rename the record is not for)
    root = make_tree(tmp_path, sources={"reverse/name_agreed.csv": NAME_AGREED.replace(f",{NEW},,", ",Other,,")})
    retail(monkeypatch)
    monkeypatch.setattr(rename, "check_agreement", REAL_CHECK_AGREEMENT)
    with pytest.raises(Refusal, match="does not agree to this rename: new 'Other'"):
        plan(root)


def test_a_record_for_another_unit_refuses(tmp_path, monkeypatch):
    basis = NAME_BASIS.replace(f",{OWNER},", ",Code/Game/Elsewhere.cpp,")
    refused(tmp_path, monkeypatch, "not the global's owner", sources={"reverse/name_basis.csv": basis})


def test_an_agreement_for_another_unit_refuses(tmp_path, monkeypatch):
    agreed = NAME_AGREED.replace(f"{OWNER}|class", "Code/Game/Elsewhere.cpp|class")
    refused(tmp_path, monkeypatch, "not the global's owner", sources={"reverse/name_agreed.csv": agreed})


def test_an_agreement_for_another_address_refuses(tmp_path, monkeypatch):
    basis = NAME_BASIS.rstrip("\n") + "0x00777000\n"
    refused(tmp_path, monkeypatch, "which is no member row of", sources={"reverse/name_basis.csv": basis})


def test_a_canonical_label_with_no_agreement_refuses(tmp_path, monkeypatch):
    # A label nobody can check: Codex's P36 reproduction, canonical:wb with evidence `x` and no agreement.
    basis = f"kind,old,new,basis,evidence,source,rva\nclass,Rva00600000,{NEW},canonical:wb,x,{OWNER},\n"
    agreed = "id,kind,old,new,rva,agents,key,status,detail\n"
    refused(tmp_path, monkeypatch, "not a verified agreement", sources={
        "reverse/name_basis.csv": basis, "reverse/name_agreed.csv": agreed})


def test_a_module_or_export_scope_alone_does_not_qualify(tmp_path, monkeypatch):
    # class_protected would call this a retail name; provenance reads only the two arms
    basis = "kind,old,new,basis,evidence,source,rva\n"
    exports = f"ordinal,rva,target_rva,section,kind,name\n1,0x1,0x1,.text,code,?x@{NEW}@@QAEXXZ\n"
    refused(tmp_path, monkeypatch, "a hand-named class does not qualify", sources={
        "reverse/name_basis.csv": basis, "reverse/exports.csv": exports})


def test_a_registry_row_with_no_agreement_refuses(tmp_path, monkeypatch):
    # Codex: no agreement, one trailerless row in canonical_classes.csv. That file is not protected.
    registered = f"class,header,notes\n{NEW},Code/Game/ImageCache.h,\n"
    refused(tmp_path, monkeypatch, "a hand-named class does not qualify", sources={
        "reverse/canonical_classes.csv": registered, "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n"})


# ------------------------------------------------------------ the walk through branches (review)

def test_an_overwritten_receiver_after_a_branch_is_no_field(tmp_path, monkeypatch):
    # jmp next; mov ecx,[ecx+4]; mov eax,[ecx+0x3C]; ret: +0x3C belongs to a pointee, and +4 is the base's
    getter = bytes.fromhex("EB008B49048B413CC3")
    refused(tmp_path, monkeypatch, "touches a field .* sets up past its base chain's reach",
            bodies=image(get=(GET, getter)))


def test_a_receiver_overwritten_on_one_path_refuses(tmp_path, monkeypatch):
    # jne over `mov ecx,[ecx+4]`, then mov eax,[ecx+0x3C]: this on one path, a pointee on the other
    getter = bytes.fromhex("75038B49048B413CC3")
    refused(tmp_path, monkeypatch, "may or may not hold `this`", bodies=image(get=(GET, getter)))


def test_a_receiver_restored_on_every_path_is_read(tmp_path, monkeypatch):
    # mov edx,ecx; jne over `mov ecx,[ecx+4]`; mov ecx,edx; mov eax,[ecx+0x3C]; ret
    getter = bytes.fromhex("8BD175038B49048BCA8B413CC3")
    root = make_tree(tmp_path, bodies=image(get=(GET, getter)))
    retail(monkeypatch, image(get=(GET, getter)))
    assert "sets up +0x3c" in plan(root).evidence


def test_a_field_touched_only_after_a_loop_pointer_is_its_first(tmp_path, monkeypatch):
    # lea eax,[ecx+0x3C]; lea edx,[ecx+0x50]; (loop) cmp eax,edx; je end; add eax,4; jmp loop; end: ret
    getter = bytes.fromhex("8D413C8D51503BC2740583C004EBF7C3")
    root = make_tree(tmp_path, bodies=image(get=(GET, getter)))
    retail(monkeypatch, image(get=(GET, getter)))
    assert "sets up +0x3c" in plan(root).evidence


def test_a_branch_the_walk_cannot_follow_refuses(tmp_path, monkeypatch):
    # jmp eax, with `this` still live
    getter = bytes.fromhex("FFE0C3")
    refused(tmp_path, monkeypatch, "branches where the walk cannot follow", bodies=image(get=(GET, getter)))


def test_a_branch_into_an_instruction_refuses(tmp_path, monkeypatch):
    # jne into the middle of `mov eax,[ecx+0x3C]`
    getter = bytes.fromhex("75018B413CC3")
    refused(tmp_path, monkeypatch, "branches into an instruction", bodies=image(get=(GET, getter)))


def test_a_string_instruction_on_this_refuses(tmp_path, monkeypatch):
    # mov esi,ecx; rep movsd
    getter = bytes.fromhex("8BF1F3A5C3")
    refused(tmp_path, monkeypatch, "runs `.*` on `this`", bodies=image(get=(GET, getter)))


# ------------------------------------------------------------ the stack holds no live `this` (second review)

@pytest.mark.parametrize("name,code", [
    ("a byte overwrite", "51C604240059"),                   # push ecx; mov byte [esp],0; pop ecx
    ("a full overwrite", "51C704240000000059"),             # push ecx; mov dword [esp],0; pop ecx
    ("stack arithmetic", "5183C40483EC0459"),               # push ecx; add esp,4; sub esp,4; pop ecx
    ("pop into memory", "51518F042459"),                    # push ecx; push ecx; pop [esp]; pop ecx
    ("a load", "518B0C2459"),                               # push ecx; mov ecx,[esp]; pop ecx
    ("a push of the slot", "51FF34245959"),                 # push ecx; push [esp]; pop ecx; pop ecx
])
def test_a_saved_copy_of_this_is_never_read_back(tmp_path, monkeypatch, name, code):
    getter = bytes.fromhex(code + "8B413CC3")       # then mov eax,[ecx+0x3C]; ret
    refused(tmp_path, monkeypatch, "stack slot that has held `this`", bodies=image(get=(GET, getter)))


def test_a_stack_address_is_not_read_through(tmp_path, monkeypatch):
    # push ecx; lea eax,[esp+4]; mov ecx,[eax-4]; mov eax,[ecx+0x3C]; ret
    getter = bytes.fromhex("518D4424048B48FC8B413C59C3")
    refused(tmp_path, monkeypatch, "address of a stack slot|reads through a stack address",
            bodies=image(get=(GET, getter)))


def test_a_copied_stack_pointer_refuses(tmp_path, monkeypatch):
    # push ecx; mov eax,esp; mov ecx,[eax]; mov eax,[ecx+0x3C]; pop ecx; ret
    getter = bytes.fromhex("518BC48B088B413C59C3")
    refused(tmp_path, monkeypatch, "copies a stack address", bodies=image(get=(GET, getter)))


def test_the_address_of_a_saved_copy_is_not_passed_on(tmp_path, monkeypatch):
    # In the base chain: push ecx; lea eax,[esp]; push eax; call helper(&saved this)
    helper = 0x00512000
    base = b"\x51\x8D\x04\x24\x50" + rel(0xE8, BASE_CTOR + 5, helper) + b"\x59\x59\xC3"
    bodies = image(base=(BASE_CTOR, base), helper=(helper, b"\xC3"))
    fn = functions(f"?helper@@YAXPAX@Z,,0x{helper:08X},1,Code/Game/Base.cpp,matched,\n")
    refused(tmp_path, monkeypatch, "address of a stack slot", bodies=bodies, fn=fn)


def test_a_stack_argument_is_only_loaded_whole(tmp_path, monkeypatch):
    # The node ctor receiving `this`: overwriting the argument before loading it hides what it reads.
    node = bytes.fromhex("C7442404000000008B4424048941088BC1C20400")
    base = b"\x56\x8B\xF1\xC7\x06" + le32(BASE_TABLE_VA) + b"\x56" + rel(0xE8, BASE_CTOR + 10, BASE_ARG) + b"\x8B\xC6\x5E\xC3"
    bodies = image(base=(BASE_CTOR, base), node=(BASE_ARG, node))
    fn = functions(f"??0Node@@QAE@PAX@Z,,0x{BASE_ARG:08X},{len(node)},Code/Game/Base.cpp,matched,\n")
    refused(tmp_path, monkeypatch, "other than loading it whole", bodies=bodies, fn=fn)


# ------------------------------------------------------------ this + offset in ecx (second review)

def test_a_subobject_in_ecx_refuses_for_an_unrowed_callee(tmp_path, monkeypatch):
    # lea ecx,[ecx+4]; call 0x00512000; ret: the callee's reach through the subobject is unknown
    base = b"\x8D\x49\x04" + rel(0xE8, BASE_CTOR + 3, 0x00512000) + b"\xC3"
    refused(tmp_path, monkeypatch, "passes this\\+0x4 in ecx", bodies=image(base=(BASE_CTOR, base)))


def test_a_subobject_in_ecx_refuses_for_a_rowed_callee(tmp_path, monkeypatch):
    helper = 0x00512000
    base = b"\x8D\x49\x04" + rel(0xE8, BASE_CTOR + 3, helper) + b"\xC3"
    bodies = image(base=(BASE_CTOR, base), helper=(helper, b"\xC3"))
    fn = functions(f"?helper@X@@QAEXXZ,,0x{helper:08X},1,Code/Game/Base.cpp,matched,\n")
    refused(tmp_path, monkeypatch, "passes this\\+0x4 in ecx", bodies=bodies, fn=fn)


def test_a_subobject_in_ecx_refuses_as_a_tail_jump(tmp_path, monkeypatch):
    helper = 0x00512000
    base = b"\x8D\x49\x04" + rel(0xE9, BASE_CTOR + 3, helper)
    bodies = image(base=(BASE_CTOR, base), helper=(helper, b"\xC3"))
    fn = functions(f"?helper@X@@QAEXXZ,,0x{helper:08X},1,Code/Game/Base.cpp,matched,\n")
    refused(tmp_path, monkeypatch, "passes this\\+0x4 in ecx", bodies=bodies, fn=fn)


def test_a_tail_jump_to_no_row_refuses(tmp_path, monkeypatch):
    base = b"\x8D\x49\x04" + rel(0xE9, BASE_CTOR + 3, 0x00512000)
    refused(tmp_path, monkeypatch, "jumps off its row", bodies=image(base=(BASE_CTOR, base)))


# ------------------------------------------------------------ every path ends (second review)

def test_a_base_running_off_its_row_refuses(tmp_path, monkeypatch):
    refused(tmp_path, monkeypatch, "runs off its row's end", bodies=image(base=(BASE_CTOR, b"\x8B\x41\x04")))


def test_a_getter_running_off_its_row_refuses(tmp_path, monkeypatch):
    refused(tmp_path, monkeypatch, "runs off its row's end", bodies=image(get=(GET, b"\x8B\x41\x3C")))


def test_a_call_running_off_its_row_refuses(tmp_path, monkeypatch):
    helper = 0x00512000
    base = b"\xC7\x01" + le32(BASE_TABLE_VA) + rel(0xE8, BASE_CTOR + 6, helper)
    bodies = image(base=(BASE_CTOR, base), helper=(helper, b"\xC3"))
    fn = functions(f"?helper@@YAXXZ,,0x{helper:08X},1,Code/Game/Base.cpp,matched,\n")
    refused(tmp_path, monkeypatch, "runs off its row's end", bodies=bodies, fn=fn)


def test_a_conditional_running_off_its_row_refuses(tmp_path, monkeypatch):
    # jne over the ret, past the row's end
    refused(tmp_path, monkeypatch, "jumps off its row", bodies=image(get=(GET, bytes.fromhex("8B413C7501C3"))))


def test_an_int3_ends_nothing(tmp_path, monkeypatch):
    refused(tmp_path, monkeypatch, "stops at `int3`", bodies=image(get=(GET, bytes.fromhex("8B413CCCC3"))))


def test_a_tail_call_ends_a_path(tmp_path, monkeypatch):
    # mov eax,[ecx+0x3C]; jmp a rowed body with no `this` in ecx: mov ecx,eax first
    getter = b"\x8B\x41\x3C\x8B\xC8" + rel(0xE9, GET + 5, ATEXIT)
    root = make_tree(tmp_path, bodies=image(get=(GET, getter)))
    retail(monkeypatch, image(get=(GET, getter)))
    assert plan(root).fold_tie["g"] == G


# ------------------------------------------------------------ what is read through `this` (second review)

@pytest.mark.parametrize("code,what", [
    ("B80400000003C1C7404000000000C3", "add"),      # mov eax,4; add eax,ecx; mov [eax+0x40],0
    ("0BC8C741400000000" + "0C3", "or"),            # or ecx,eax; mov [ecx+0x40],0
    ("0FC8C3", "bswap"),                            # bswap eax on a this copy
])
def test_arithmetic_on_this_refuses(tmp_path, monkeypatch, code, what):
    if what == "bswap":
        code = "8BC1" + code                        # mov eax,ecx first
    base = b"\xC7\x01" + le32(BASE_TABLE_VA) + bytes.fromhex(code)
    refused(tmp_path, monkeypatch, f"runs `{what}` on `this`", bodies=image(base=(BASE_CTOR, base)))


# ------------------------------------------------------------ third review

@pytest.mark.parametrize("code", [
    "668BC9",               # mov cx,cx
    "668D09",               # lea cx,[ecx]
    "6683C100",             # add cx,0
    "32C9",                 # xor cl,cl
])
def test_a_partial_operation_on_this_refuses(tmp_path, monkeypatch, code):
    base = bytes.fromhex(code + "8B413CC3")     # then mov eax,[ecx+0x3C]; ret
    refused(tmp_path, monkeypatch, "on part of a register holding `this`", bodies=image(base=(BASE_CTOR, base)))


def test_a_stack_pointer_copied_before_the_taint_refuses(tmp_path, monkeypatch):
    getter = bytes.fromhex("8B413C8BD4518B4AFC8B810001000083C404C20400")
    refused(tmp_path, monkeypatch, "copies a stack address", bodies=image(get=(GET, getter)))


def test_the_temporary_exception_never_restores_this(tmp_path, monkeypatch):
    # An empty rowed ctor over the reserved slot overwrites nothing: `pop ecx` would restore `this`.
    temp = 0x00512000
    getter = bytes.fromhex("8B413C518D0C24") + rel(0xE8, GET + 7, temp) + bytes.fromhex("598B8100010000C20400")
    bodies = image(get=(GET, getter), temp=(temp, b"\xC3"))
    fn = functions(f"??0Temp@@QAE@XZ,,0x{temp:08X},1,Code/Game/Base.cpp,matched,\n")
    refused(tmp_path, monkeypatch, "pops a stack slot that has held `this`", bodies=bodies, fn=fn)


def test_a_constructed_temporary_may_travel(tmp_path, monkeypatch):
    # P36's shape: the temporary's address goes to the base ctor, its bytes are never read
    temp = 0x00512000
    ctor = b"\x51\x56\x8B\xF1\x8D\x4C\x24\x04" + rel(0xE8, CTOR + 8, temp)
    ctor += b"\x8D\x44\x24\x04\x50" + b"\x8B\xCE" + rel(0xE8, CTOR + 20, BASE_CTOR)
    store = CTOR + len(ctor)
    ctor += b"\xC7\x06" + le32(TABLE_VA) + b"\x83\x66\x3C\x00\x83\x66\x50\x00\x8B\xC6\x5E\x59\xC3"
    base = b"\xC7\x01" + le32(BASE_TABLE_VA) + b"\x83\x61\x04\x00" + b"\x8B\xC1\xC2\x04\x00"
    bodies = image(ctor=(CTOR, ctor), base=(BASE_CTOR, base), temp=(temp, b"\xC3"))
    fn = functions(f"??0Temp@@QAE@XZ,,0x{temp:08X},1,Code/Game/Base.cpp,matched,\n")
    root = make_tree(tmp_path, bodies=bodies, fn=fn)
    retail(monkeypatch, bodies, store=store)
    # the epilogue's `pop ecx` reads the slot, so this ctor must not pop it: see below
    with pytest.raises(Refusal, match="pops a stack slot that has held `this`"):
        plan(root)
    ctor = ctor[:-2] + b"\x83\xC4\x04\xC3"          # add esp,4; ret: nothing reads it
    bodies = image(ctor=(CTOR, ctor), base=(BASE_CTOR, base), temp=(temp, b"\xC3"))
    (root / "reverse/functions.csv").write_bytes((root / "reverse/functions.csv").read_bytes().replace(
        f"0x{CTOR:08X},{len(ctor) - 2}".encode(), f"0x{CTOR:08X},{len(ctor)}".encode()))
    retail(monkeypatch, bodies, store=store)
    assert plan(root).fold_tie["g"] == G


def dtor_row(size):
    return functions().replace(f"0x{DTOR:08X},{len(DTOR_BODY)}", f"0x{DTOR:08X},{size}")


def test_a_dtor_reaching_past_the_global_refuses(tmp_path, monkeypatch):
    dtor = bytes.fromhex("8B8100010000C3")
    refused(tmp_path, monkeypatch, "reaches this\\+0x104, past G", bodies=image(dtor=(DTOR, dtor)), fn=dtor_row(len(dtor)))


def test_a_dtor_tail_calling_its_base_ends_the_walk(tmp_path, monkeypatch):
    dtor = bytes.fromhex("83610400") + rel(0xE9, DTOR + 4, 0x00512000)      # and [ecx+4],0; jmp unrowed base dtor
    bodies = image(dtor=(DTOR, dtor))
    root = make_tree(tmp_path, bodies=bodies, fn=dtor_row(len(dtor)))
    retail(monkeypatch, bodies)
    assert plan(root).fold_tie["g"] == G


def test_a_dtor_past_the_global_after_what_it_cannot_read_refuses(tmp_path, monkeypatch):
    # an indirect call it cannot follow, then a read past G: lenient reads on
    dtor = bytes.fromhex("8BF1FF108B8600010000C3")  # mov esi,ecx; call [eax]; mov eax,[esi+0x100]; ret
    refused(tmp_path, monkeypatch, "reaches this\\+0x104, past G", bodies=image(dtor=(DTOR, dtor)), fn=dtor_row(len(dtor)))


def test_reading_a_saved_copy_refuses_without_a_pop(tmp_path, monkeypatch):
    # mov ecx,[esp] alone must refuse: no later pop would catch it
    getter = bytes.fromhex("518B0C248B413C83C404C3")
    refused(tmp_path, monkeypatch, "reads a stack slot that has held `this`", bodies=image(get=(GET, getter)))


def test_a_row_that_does_not_decode_to_its_end_refuses(tmp_path, monkeypatch):
    # ret, then the first byte of an instruction the row cuts off
    refused(tmp_path, monkeypatch, "does not decode to its row's end", bodies=image(get=(GET, bytes.fromhex("8B413CC38B"))))


# ------------------------------------------------------------ the census is what bounds a false accept

def test_a_fold_missing_from_the_census_refuses(tmp_path, monkeypatch):
    census = "old,new,initializer,review\n"
    refused(tmp_path, monkeypatch, "has no row with a review in reverse/initializer_fold_census.csv", sources={
        "reverse/initializer_fold_census.csv": census})


def test_a_census_row_for_another_initializer_refuses(tmp_path, monkeypatch):
    census = CENSUS.replace(f"0x{INIT:08X}", "0x007B0100")
    refused(tmp_path, monkeypatch, "has no row with a review in reverse/initializer_fold_census.csv", sources={
        "reverse/initializer_fold_census.csv": census})


def test_a_census_row_with_no_review_refuses(tmp_path, monkeypatch):
    census = f"old,new,initializer,review\n{OLD},{NEW},0x{INIT:08X},  \n"
    refused(tmp_path, monkeypatch, "has no row with a review", sources={"reverse/initializer_fold_census.csv": census})


def census_problems(root):
    return rename.fold_census_problems(rename.Context(root, object_scan=False))


def landed_functions():
    """The ledger after the fold was really applied: every OLD row respelled NEW."""
    return functions().replace(f"{OLD}@@", f"{NEW}@@")


def test_the_census_and_the_list_agree(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    assert census_problems(root) == []


def test_an_admitted_fold_nobody_listed_is_a_problem(tmp_path, monkeypatch):
    root = make_tree(tmp_path, sources={"reverse/initializer_fold_census.csv": "old,new,initializer,review\n"})
    retail(monkeypatch)
    assert "is admitted but not listed" in census_problems(root)[0]


def test_a_landed_fold_is_recognised(tmp_path, monkeypatch):
    root = make_tree(tmp_path, fn=landed_functions())
    retail(monkeypatch)
    assert census_problems(root) == []


def test_an_empty_review_is_a_problem(tmp_path, monkeypatch):
    census = f"old,new,initializer,review\n{OLD},{NEW},0x{INIT:08X},\n"
    root = make_tree(tmp_path, sources={"reverse/initializer_fold_census.csv": census})
    retail(monkeypatch)
    assert any("has no review" in problem for problem in census_problems(root))


def test_rows_that_disappeared_are_not_a_landing(tmp_path, monkeypatch):
    # Codex: P36's special members filtered out, its fold never applied. The census empties, but nothing landed.
    fn = "\n".join(line for line in functions().splitlines() if f"{OLD}@@" not in line) + "\n"
    root = make_tree(tmp_path, fn=fn)
    retail(monkeypatch)
    problems = census_problems(root)
    assert len(problems) == 1 and "is neither admitted nor landed" in problems[0] and "is not rowed" in problems[0]


def test_a_row_nobody_ever_reviewed_is_not_a_landing(tmp_path, monkeypatch):
    # Codex: a row for a class that was never in the ledger passed as landed.
    census = CENSUS + "RvaNeverReviewed,WrongClass,0x00123456,looks fine\n"
    root = make_tree(tmp_path, sources={"reverse/initializer_fold_census.csv": census})
    retail(monkeypatch)
    problems = census_problems(root)
    assert len(problems) == 1 and "RvaNeverReviewed" in problems[0] and "neither admitted nor landed" in problems[0]


def test_a_half_applied_fold_is_not_a_landing(tmp_path, monkeypatch):
    # the constructor is rowed NEW but another row still names OLD
    fn = functions().replace(f"??0{OLD}@@", f"??0{NEW}@@")
    root = make_tree(tmp_path, fn=fn)
    retail(monkeypatch)
    assert any("still name" in problem for problem in census_problems(root))


def test_the_census_finds_what_the_proof_admits(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    assert rename.initializer_fold_census(rename.Context(root, object_scan=False)) == {(OLD, NEW, INIT)}


def test_the_census_does_not_depend_on_the_list(tmp_path, monkeypatch):
    # a new admission shows up in the census before anyone lists it
    root = make_tree(tmp_path, sources={"reverse/initializer_fold_census.csv": "old,new,initializer,review\n"})
    retail(monkeypatch)
    assert rename.initializer_fold_census(rename.Context(root, object_scan=False)) == {(OLD, NEW, INIT)}


def test_the_census_leaves_out_what_the_proof_refuses(tmp_path, monkeypatch):
    bodies = image(get=(GET, getter_body(0x04)))
    root = make_tree(tmp_path, bodies=bodies)
    retail(monkeypatch, bodies)
    assert rename.initializer_fold_census(rename.Context(root, object_scan=False)) == set()


def test_an_indexed_base_chain_refuses(tmp_path, monkeypatch):
    # the base writes [ecx+eax*4+0x10]: how far it reaches is unbounded
    base = b"\xC7\x01" + le32(BASE_TABLE_VA) + b"\x83\x64\x81\x10\x00" + b"\x8B\xC1\xC3"
    refused(tmp_path, monkeypatch, "reaches an unbounded offset", bodies=image(base=(BASE_CTOR, base)))


@pytest.mark.parametrize("name", [
    f"?Cache@@3PAV{NEW}@@A",                # a pointer to it
    "?Cache@@3VOther@@A",                   # another class
    f"?Cache@@3VInner@{NEW}@@A",            # a nested class
    f"?Cache@@3V?${NEW}@H@@A",              # a template
    "?Cache@@3IA",                          # no class
])
def test_a_global_not_typed_exactly_new_refuses(tmp_path, monkeypatch, name):
    refused(tmp_path, monkeypatch, "is not typed exactly as class", rows=data_rows(name), data=ledger(name))


def test_an_unmatched_data_row_refuses(tmp_path, monkeypatch):
    refused(tmp_path, monkeypatch, "is not the exact start of one matched data row", rows=data_rows(status="partial"))


def test_a_ledger_extent_that_disagrees_refuses(tmp_path, monkeypatch):
    refused(tmp_path, monkeypatch, "the data ledger does not give", data=ledger(size=EXTENT - 8))


def test_a_ledger_name_that_disagrees_refuses(tmp_path, monkeypatch):
    refused(tmp_path, monkeypatch, "the data ledger does not give", data=ledger("?g_00E06858@@3IA"))


def test_a_ctor_reaching_past_the_extent_refuses(tmp_path, monkeypatch):
    rows, data = data_rows(size=0x40), ledger(size=0x40)
    refused(tmp_path, monkeypatch, "past G's 0x40 bytes", rows=rows, data=data)


# ------------------------------------------------------------ the atexit thunk

def test_a_thunk_calling_another_classs_dtor_refuses(tmp_path, monkeypatch):
    bodies = image(thunk=(THUNK, thunk_body(dtor=OTHER_DTOR)))
    refused(tmp_path, monkeypatch, "is not exactly `mov ecx,&G; jmp dtor`", bodies=bodies)


def test_a_thunk_on_another_global_refuses(tmp_path, monkeypatch):
    bodies = image(thunk=(THUNK, thunk_body(g_va=G_VA + 0x70)))
    refused(tmp_path, monkeypatch, "is not exactly `mov ecx,&G; jmp dtor`", bodies=bodies)


def test_registering_through_something_else_refuses(tmp_path, monkeypatch):
    fn = functions().replace("_atexit,,", "_onexit,,")
    refused(tmp_path, monkeypatch, "not _atexit", fn=fn)


# ------------------------------------------------------------ OLD's constructor

def test_two_plus_0_stores_refuse(tmp_path, monkeypatch):
    # an inlined base stored its table first
    extra = b"\xC7\x06" + le32(0x00C00300)
    refused(tmp_path, monkeypatch, "not exactly once", bodies=image(ctor=(CTOR, ctor_body(extra=extra))))


def test_a_field_only_the_base_chain_reaches_refuses(tmp_path, monkeypatch):
    # The row is wrong: NEW is really a base of OLD. Its member touches +4, which the base ctor sets up.
    refused(tmp_path, monkeypatch, "touches a field .* sets up past its base chain's reach",
            bodies=image(get=(GET, getter_body(0x04))))


def test_a_field_the_base_chain_also_sets_up_refuses(tmp_path, monkeypatch):
    # the base ctor writes +0x3C and +0x50 too, so OLD's stores there prove nothing about OLD itself
    base = (b"\xC7\x01" + le32(BASE_TABLE_VA) + b"\x83\x61\x04\x00" + b"\x83\x61\x3C\x00" + b"\x83\x61\x50\x00"
            + b"\x8B\xC1\xC3")
    refused(tmp_path, monkeypatch, "touches a field .* sets up past its base chain's reach",
            bodies=image(base=(BASE_CTOR, base)))


def test_a_base_chain_that_cannot_be_read_refuses(tmp_path, monkeypatch):
    fn = "\n".join(line for line in functions().splitlines() if "Rva00510000" not in line) + "\n"
    refused(tmp_path, monkeypatch, "0x00510000 has no row", fn=fn)


def test_a_base_chain_calling_through_a_pointer_refuses(tmp_path, monkeypatch):
    base = b"\xC7\x01" + le32(BASE_TABLE_VA) + b"\x8B\x01\xFF\x10\xC3"     # mov eax,[ecx]; call [eax]; ret
    refused(tmp_path, monkeypatch, "passes `this` to an indirect call", bodies=image(base=(BASE_CTOR, base)))


def test_a_base_chain_taking_a_subobject_address_refuses(tmp_path, monkeypatch):
    # lea eax,[ecx+0x40]; push eax; call helper: how far the helper writes cannot be read
    helper = 0x00512000
    base = b"\x8D\x41\x40\x50" + rel(0xE8, BASE_CTOR + 4, helper) + b"\x59\xC3"
    bodies = image(base=(BASE_CTOR, base), helper=(helper, b"\xC3"))
    fn = functions(f"?helper@@YAXPAX@Z,,0x{helper:08X},1,Code/Game/Base.cpp,matched,\n")
    refused(tmp_path, monkeypatch, "passes this\\+0x40 on", bodies=bodies, fn=fn)


# ------------------------------------------------------------ a derived global, the row wrong or right

def test_a_derived_globals_own_state_refuses(tmp_path, monkeypatch):
    # G really is a class derived from OLD: its second member touches state OLD's ctor never reaches.
    extra_get, extra_caller = GET2, CALLER2
    bodies = image(get2=(extra_get, getter_body(0x68)))
    fn = functions(f"?more@{NEW}@@QAEPBXH@Z,,0x{extra_get:08X},{len(getter_body())},{OWNER},matched,\n")
    refused(tmp_path, monkeypatch, "past everything .* reaches .*may be a class derived from", bodies=bodies, fn=fn)


def test_a_wrong_row_retail_never_calls_on_the_global_refuses(tmp_path, monkeypatch):
    # The row names a real class that nothing in retail calls on G.
    bodies = image(caller=(CALLER, caller_body(g_va=G_VA + 0x70)))
    refused(tmp_path, monkeypatch, "calls no rowed member of", bodies=bodies)


def test_a_third_real_classs_member_on_the_global_refuses(tmp_path, monkeypatch):
    other, caller = 0x00509000, 0x0050A000
    bodies = image(other=(other, getter_body()), other_caller=(caller, caller_body(caller, other)))
    fn = functions(f"?draw@Third@@QAEPBXH@Z,,0x{other:08X},{len(getter_body())},Code/Game/Base.cpp,matched,\n"
                   f"?caller3@@YAPBXH@Z,,0x{caller:08X},{len(caller_body())},{OWNER},matched,\n")
    refused(tmp_path, monkeypatch, "retail also calls .*Third", bodies=bodies, fn=fn)


def test_a_member_that_touches_no_ctor_field_refuses(tmp_path, monkeypatch):
    # +0x20 is inside what the ctor reaches but it never sets it up
    refused(tmp_path, monkeypatch, "touches a field", bodies=image(get=(GET, getter_body(0x20))))


def test_a_view_deriving_one_from_the_other_refuses(tmp_path, monkeypatch):
    source = OWNER_SRC.replace(f"class {NEW}\n", f"class {OLD} {{ }};\nclass {NEW} : public {OLD}\n")
    refused(tmp_path, monkeypatch, "derives one of", sources={OWNER: source})


# ------------------------------------------------------------ the plan and the build

def test_the_owner_must_come_prepared(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    with pytest.raises(Refusal, match="needs exactly the global's owner"):
        plan(root, prepared={})


def test_another_prepared_source_refuses(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    with pytest.raises(Refusal, match="needs exactly the global's owner"):
        plan(root, prepared={OWNER: PREPARED, "Code/Game/Base.cpp": b"\n"})


def test_a_prepared_owner_spelling_old_refuses(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    with pytest.raises(Refusal, match=f"spells {OLD}"):
        plan(root, prepared={OWNER: PREPARED + f"// {OLD}\n".encode()})


def test_a_virtual_of_new_still_takes_the_slot_route(tmp_path, monkeypatch):
    fn = functions().replace(f"?fetch@{NEW}@@QAE", f"?fetch@{NEW}@@UAE")
    refused(tmp_path, monkeypatch, "is on no slot of", fn=fn)


def _tie_ctx(tmp_path, monkeypatch, symbols, verdict=(True, "")):
    import data_rows as data_rows_module
    import reloc_ledger
    root = make_tree(tmp_path)
    (root / "obj.obj").write_bytes(b"coff")
    monkeypatch.setattr(build, "obj_path", lambda path: root / "obj.obj")
    monkeypatch.setattr(reloc_ledger, "parse_coff", lambda data: ([], dict(enumerate(symbols))))
    monkeypatch.setattr(reloc_ledger, "Image", lambda: None)
    monkeypatch.setattr(data_rows_module, "Resolver", lambda rows: None)
    monkeypatch.setattr(data_rows_module, "load", lambda: [])
    monkeypatch.setattr(data_rows_module, "verify_row", lambda row, img, resolve, compile=True: verdict)
    return rename.Context(root, object_scan=False)


TIE = dict(owner=OWNER, ctor_new=f"??0{NEW}@@QAE@XZ", row=dict(name=f"?Cache@@3V{NEW}@@A"))


def test_the_rebuilt_owner_references_the_row(tmp_path, monkeypatch):
    ctx = _tie_ctx(tmp_path, monkeypatch, [dict(name=TIE["ctor_new"], section=0)])
    assert rename.fold_tie_problems(ctx, TIE) == []


def test_a_rebuilt_owner_with_no_reference_is_a_problem(tmp_path, monkeypatch):
    ctx = _tie_ctx(tmp_path, monkeypatch, [dict(name="_other", section=0)])
    assert "does not reference" in rename.fold_tie_problems(ctx, TIE)[0]


def test_a_rebuilt_owner_defining_a_local_ctor_is_a_problem(tmp_path, monkeypatch):
    ctx = _tie_ctx(tmp_path, monkeypatch, [dict(name=TIE["ctor_new"], section=3)])
    assert "defines its own" in rename.fold_tie_problems(ctx, TIE)[0]


def test_a_compiled_size_data_rows_does_not_prove_is_a_problem(tmp_path, monkeypatch):
    ctx = _tie_ctx(tmp_path, monkeypatch, [dict(name=TIE["ctor_new"], section=0)], verdict=(False, "size 100"))
    assert "size 100" in rename.fold_tie_problems(ctx, TIE)[0]


def test_a_failed_tie_restores_every_file(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    result = plan(root)
    monkeypatch.setattr(rename, "fold_tie_problems", lambda ctx, tie: ["its object defines its own constructor"])
    with pytest.raises(VerifyFailed, match="the rebuilt owner does not prove"):
        rename.apply_rename(result, ctx=rename.Context(root, object_scan=False), verify=lambda ctx, sources: True)
    assert (root / OWNER).read_text() == OWNER_SRC
    assert OLD in (root / "reverse/functions.csv").read_text()


def test_a_proven_tie_applies(tmp_path, monkeypatch):
    root = make_tree(tmp_path)
    retail(monkeypatch)
    result = plan(root)
    seen = []
    monkeypatch.setattr(rename, "fold_tie_problems", lambda ctx, tie: seen.append(tie["ctor_new"]) or [])
    rename.apply_rename(result, ctx=rename.Context(root, object_scan=False), verify=lambda ctx, sources: True)
    assert seen == [f"??0{NEW}@@QAE@XZ"]
    assert (root / OWNER).read_bytes() == PREPARED
    assert f"class {NEW}" in (root / "Code/Game/Ctor.cpp").read_text()
