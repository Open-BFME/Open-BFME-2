"""sig_check.py: declaration parsing and retail-evidence checks, offline."""
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import retail_body as rb  # noqa: E402
import sig_check as sc  # noqa: E402

BASE = 0x1000


def evidence(rets=(0,), live=None, stack_max=None, sites=(), compares=None, setcc=None,
             x87=True, st0_tail=False):
    return sc.Evidence(list(rets), live or {}, stack_max, list(sites), compares or {},
                       setcc or Counter(), x87, st0_tail)


def site(sets_ecx=False, cleanup=None, ret_use=None):
    return sc.Site(0, 0, sets_ecx, cleanup, ret_use)


def test_mangled_member_thiscall():
    d = sc.decl_from_mangled("?Set_Flag@LineGroupClass@@QAEXW4FlagsType@1@_N@Z")
    assert d.conv == "thiscall" and d.member
    assert [p.kind for p in d.params] == ["int", "bool"]
    assert d.ret.kind == "void"
    assert sc.arg_bytes(d) == 8


def test_mangled_free_cdecl_with_backref():
    d = sc.decl_from_mangled("?calcDistSquared@@YAMABUCoord3D@@0@Z")
    assert d.conv == "cdecl" and not d.member
    assert len(d.params) == 2 and d.ret.kind == "float"


def test_mangled_static_and_hidden_return():
    d = sc.decl_from_mangled("?Get_Point@INIClass@@QBE?BV?$TPoint3D@H@@PBD0ABV2@@Z")
    assert d.member and d.ret.kind == "hidden"
    assert sc.arg_bytes(d) == 16          # three pointers plus the hidden result pointer
    s = sc.decl_from_mangled("?isSlotLocalAlly@GameSlot@@CA_NXZ")
    assert not s.member and s.conv == "cdecl" and s.params == []


def test_text_params():
    kinds = [sc.text_param(t).kind for t in
             ("const Coord3D &pos", "Real scale", "UnsignedInt count", "Int i", "Bool on", "Foo f")]
    assert kinds == ["ptr", "float", "int", "int", "bool", "unknown"]
    assert sc.text_param("UnsignedInt count").signed is False
    assert sc.text_param("Int i").signed is True


SOURCE = """
class Widget { public: int get(int a) const; int get(int a, int b) const; };
int Widget::get(int a) const
{
    return a == 3;
}
int Widget::get(int a, int b) const
{
    return a + b;
}
"""


def test_find_definition_picks_overload_by_arity(tmp_path):
    path = tmp_path / "w.cpp"
    path.write_text(SOURCE)
    one, body = sc.decl_from_source(path, "Widget::get", "?get@Widget@@QBEHH@Z")
    assert one.member and one.conv == "thiscall" and len(one.params) == 1
    assert "a == 3" in body
    two, _ = sc.decl_from_source(path, "Widget::get", "?get@Widget@@QBEHHH@Z")
    assert len(two.params) == 2


def test_check_flags_cdecl_that_pops():
    d = sc.decl_from_mangled("?f@@YAXHH@Z")
    found = dict(sc.check(d, evidence(rets=(8,))))
    assert "conv" in found


def test_check_flags_wrong_thiscall_arg_bytes_and_free_reading_ecx():
    d = sc.decl_from_mangled("?Set_Flag@LineGroupClass@@QAEXW4FlagsType@1@_N@Z")
    assert "args" in dict(sc.check(d, evidence(rets=(4,), live={"ecx": BASE})))
    assert sc.check(d, evidence(rets=(8,), live={"ecx": BASE})) == []
    free = d._replace(conv="cdecl", member=False)
    assert "this" in dict(sc.check(free, evidence(rets=(0,), live={"ecx": BASE})))


def test_check_return_uses():
    void = sc.decl_from_mangled("?f@@YAXXZ")
    assert "return" in dict(sc.check(void, evidence(sites=[site(ret_use="al")])))
    real = sc.decl_from_mangled("?f@@YAMXZ")
    assert "return" in dict(sc.check(real, evidence(sites=[site(), site()])))
    assert "return" in dict(sc.check(real, evidence(x87=False)))
    integer = sc.decl_from_mangled("?f@@YAHXZ")
    assert "return" in dict(sc.check(integer, evidence(st0_tail=True)))


def test_check_signedness():
    d = sc.decl_from_mangled("?f@@YAXH@Z")       # f(int)
    found = dict(sc.check(d, evidence(compares={0: Counter(unsigned=2)})))
    assert "sign" in found
    assert sc.check(d, evidence(compares={0: Counter(signed=1)})) == []


def test_bool_inversion_against_source_body():
    assert sc.bool_check("return a == b;", Counter(setne=1))
    assert not sc.bool_check("return a == b;", Counter(sete=1))
    assert not sc.bool_check("if (x) return 1; return a == b;", Counter(setne=1))


def test_callee_evidence_on_bytes():
    code = (b"\x8B\x44\x24\x04"    # mov eax, [esp+4]       param 0
            b"\x83\xF8\x05"        # cmp eax, 5
            b"\x72\x02"            # jb +2                  unsigned compare
            b"\x8B\x01"            # mov eax, [ecx]         ecx live
            b"\xC2\x04\x00")       # ret 4
    insns, rets, live, stack_max, compares, setcc = sc.callee_evidence(BASE, len(code), data=code)
    assert rets == [4] and "ecx" in live and stack_max == 4
    assert compares[0]["unsigned"] == 1


def test_return_use_after_call():
    code = b"\xE8\x00\x00\x00\x00" + b"\x84\xC0" + b"\xC3"   # call; test al, al
    insns = rb.disasm(BASE, len(code), data=code)
    assert sc.return_use(insns, 0) == "al"
    code = b"\xE8\x00\x00\x00\x00" + b"\xD9\x5C\x24\x04" + b"\xC3"   # call; fstp [esp+4]
    insns = rb.disasm(BASE, len(code), data=code)
    assert sc.return_use(insns, 0) == "st0"
