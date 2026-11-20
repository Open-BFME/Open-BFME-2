"""Canonical syntax is input provenance; native facts remain real source facts."""
from copy import deepcopy
from dataclasses import replace
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_generation_inputs as I
import header_generation_proof as P


NAME = "Canonical"
HEADER = "Code/Canonical.h"
DECL = "class Canonical {\npublic:\n void *value;\n Canonical(void *held);\n void helper();\n virtual ~Canonical() {}\n};\n"
CONTRACT = {"class": NAME, "key": "class", "size": 8, "bases": [],
            "fields": [{"offset": 0, "name": "__vfptr", "kind": "VPTR", "size": 4},
                       {"offset": 4, "name": "value", "kind": "P", "size": 4, "type": "void*"}],
            "vslots": {"0": "~Canonical()"}}
LAYOUT = {"fwd": False, "key": "class", "size": 8, "bases": [], "fields": [[4, "value", "void*", 4]],
          "statics": [], "methods": ["Canonical", "helper", "~Canonical"], "virtual": ["~Canonical"],
          "vslots": {"0": "~Canonical()"}, "vfptr": True}
TABLE = "??_7Canonical@@6B@"


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, check=True)


def put(root, path, body, tracked=True):
    path = root / path
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(body.encode("ascii") if isinstance(body, str) else body)
    if tracked:
        git(root, "add", "--", path.relative_to(root).as_posix())
    return path


class Case:
    def __init__(self, root):
        self.root, self.units, self.objects = root, {}, {}

    def source(self, source="Code/A.cpp", *, bound=True, emitting=True, record=True, deps=(), body=None):
        text = body if body is not None else ('#include "Canonical.h"\n' if bound else "void unrelated() {}\n")
        put(self.root, source, text)
        meta = I._receipt_path(self.root, source)
        output = meta.with_name(meta.name[:-len(".deps.json")] + ".obj")
        raw = b"object of " + source.encode()
        put(self.root, output.relative_to(self.root).as_posix(), raw, tracked=False)
        opened = (HEADER,) + tuple(deps) if bound else tuple(deps)
        md5 = lambda path: hashlib.md5(Path(path).read_bytes()).hexdigest()
        payload = {"path": source, "source": md5(self.root / source), "object": md5(output),
                   "deps": {path: md5(self.root / path) for path in opened}}
        meta.write_text(json.dumps(payload))
        facts = (frozenset({"real-owner"}), frozenset({"real-owner", TABLE} if emitting else {"real-owner"}))
        self.objects[raw] = (facts, {NAME: deepcopy(LAYOUT)} if record else {})
        pp = f'#line 1 "{source}"\n'
        if bound:
            pp += f'#line 1 "{HEADER}"\n' + DECL + f'#line 2 "{source}"\n'
        else:
            pp += text
        self.units[source] = {"state": I.CompilerInputs("command", "inventory", (), True),
                              "command": ["cl", "-c", "-Fo" + str(output), source], "env": {},
                              "stdout": pp.encode(), "stderr": b"".join(
                                  b"Note: including file: " + str(self.root / path).encode() + b"\n" for path in opened),
                              "returncode": 0, "object": output, "receipt": meta}
        return source

    def capture(self, *sources, contract=None):
        return P.capture(NAME, HEADER, deepcopy(CONTRACT) if contract is None else contract,
                         sources or tuple(self.units), root=self.root)


@pytest.fixture
def case(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    put(tmp_path, HEADER, DECL)
    case = Case(tmp_path)
    monkeypatch.setattr(I, "_compiler_inputs", lambda root, source, output, cache=None: case.units[source]["state"])
    monkeypatch.setattr(P, "_normal_command", lambda root, source, output:
                        (case.units[source]["command"], case.units[source]["env"]))
    monkeypatch.setattr(P, "_command_fingerprint", lambda *a: "command")
    def preprocess(command, env):
        source = next(arg for arg in command if arg.endswith(".cpp"))
        unit = case.units[source]
        return subprocess.CompletedProcess(command, unit["returncode"], unit["stdout"], unit["stderr"])
    monkeypatch.setattr(P, "_preprocess", preprocess)
    def opened(source, output):
        return {source.resolve()} | {Path(line[len(b"Note: including file: "):].decode()).resolve()
                                   for line in output.splitlines() if line.startswith(b"Note: including file:")}
    monkeypatch.setattr(P, "_opened_paths", opened)
    monkeypatch.setattr(P, "_object_evidence", lambda raw: deepcopy(case.objects[raw]))
    def unavailable(*args):
        raise P.InputRefused("diagnostic unavailable")
    monkeypatch.setattr(P, "_diagnostic_layouts", unavailable)
    return case


@pytest.mark.parametrize("wrapper", ["plain", "guard", "once", "once_guard"])
def test_literal_header_provenance_and_real_object_facts(case, wrapper):
    header = DECL
    if "guard" in wrapper:
        header = "#ifndef CANONICAL_H\n#define CANONICAL_H\n" + header + "#endif\n"
    if "once" in wrapper:
        header = "#pragma once\n" + header
    put(case.root, HEADER, header)
    source = case.source()
    got = case.capture(source)
    witness = got.witnesses[source]
    assert got.name == NAME and got.header == HEADER
    assert got.digest == hashlib.sha256((case.root / HEADER).read_bytes()).hexdigest()
    assert "Canonical(void *held)" in got.text and "void helper()" in got.text
    assert witness.source == source and witness.object_path == str(case.units[source]["object"])
    assert witness.object_digest == hashlib.sha256(case.units[source]["object"].read_bytes()).hexdigest()
    assert witness.facts == (frozenset({"real-owner"}), frozenset({"real-owner", TABLE}))
    assert witness.emitting is True and witness.header_bound is True
    assert witness.layout["fields"] == ((4, "value", "void*", 4),)
    assert got.profiles == {source: "command"}
    assert got.forced_inputs == {source: ()}
    assert got.search_inventories == {source: "inventory"}
    assert got.validate() is True


def test_nonconsumer_remains_real_source_witness_without_header_vote(case):
    a = case.source()
    b = case.source("Code/B.cpp", bound=False, emitting=False, record=False)
    got = case.capture(a, b)
    assert set(got.witnesses) == {a, b}
    assert got.witnesses[b].header_bound is False
    assert got.witnesses[b].emitting is False and got.witnesses[b].layout is None
    assert "real-owner" in got.witnesses[b].facts[0]


def test_only_actual_objects_receipts_and_diagnostics_are_rebuildable(case):
    source = case.source()
    got = case.capture(source)
    unit = case.units[source]
    assert got.rebuildable == frozenset({unit["object"].relative_to(case.root).as_posix(),
                                         unit["receipt"].relative_to(case.root).as_posix()})
    assert HEADER not in got.rebuildable and source not in got.rebuildable


def test_call_only_header_consumer_may_have_known_false_emission_and_no_record(case):
    source = case.source(emitting=False, record=False)
    emitter = case.source("Code/Emitter.cpp")
    got = case.capture(source, emitter)
    assert got.witnesses[source].header_bound is True
    assert got.witnesses[source].emitting is False
    assert got.witnesses[source].layout is None


def test_call_only_cohort_cannot_admit_a_declaration_without_native_layout(case):
    source = case.source(emitting=False, record=False)
    with pytest.raises(P.InputRefused, match="native layout witness"):
        case.capture(source)


@pytest.mark.parametrize("diagnostic", ["absent", "mismatch", "matching"])
def test_nonpolymorphic_consumer_requires_complete_native_layout_even_without_vtable(case, monkeypatch, diagnostic):
    declaration = "class Canonical { public: int value; };\n"
    put(case.root, HEADER, declaration)
    source = case.source(emitting=False, record=False)
    case.units[source]["stdout"] = f'#line 1 "{HEADER}"\n{declaration}'.encode()
    contract = {"class": NAME, "key": "class", "size": 4, "bases": [], "vslots": {},
                "fields": [{"offset": 0, "name": "value", "kind": "i4", "size": 4, "type": "int"}]}
    # Use the owning kind decoder, rather than inventing a fixture spelling.
    import class_contract
    contract["fields"][0]["kind"] = class_contract.kind("int")
    layout = {"fwd": False, "key": "class", "size": 4, "bases": [],
              "fields": [[0, "value", "int", 4]], "vslots": {}, "vfptr": False}
    if diagnostic == "mismatch":
        contract["size"] = 8
        contract["fields"].append({"offset": 4, "name": "invented", "kind": class_contract.kind("int"), "size": 4,
                                   "type": "int"})
    monkeypatch.setattr(P, "_diagnostic_layouts", lambda root, unit:
                        ({} if diagnostic == "absent" else {NAME: layout}, ()))
    if diagnostic == "matching":
        got = case.capture(source, contract=contract)
        assert got.witnesses[source].layout["size"] == 4
    else:
        with pytest.raises(P.InputRefused, match="layout|storage|record"):
            case.capture(source, contract=contract)


@pytest.mark.parametrize("recorded_type", ["void*", None, "int*"])
def test_pointer_width_does_not_authorize_changing_canonical_pointee_type(case, recorded_type):
    declaration = DECL.replace("void *value", "int *value")
    put(case.root, HEADER, declaration)
    source = case.source()
    case.units[source]["stdout"] = f'#line 1 "{HEADER}"\n{declaration}'.encode()
    raw = case.units[source]["object"].read_bytes()
    case.objects[raw][1][NAME]["fields"][0][2] = "int*"
    contract = deepcopy(CONTRACT)
    contract["fields"][1]["type"] = recorded_type
    if recorded_type == "int*":
        assert case.capture(source, contract=contract).witnesses[source].layout["fields"][0][2] == "int*"
    else:
        with pytest.raises(P.InputRefused, match="field type"):
            case.capture(source, contract=contract)


def test_compiler_binary_receipt_input_is_hashed_without_parsing_as_cpp(case):
    binary = put(case.root, "vendor/profile/compiler.exe", b"MZ\0binary\0profile")
    source = case.source(deps=(binary.relative_to(case.root).as_posix(),))
    # A profile executable is a compile input, not a /showIncludes text input.
    case.units[source]["stderr"] = b"Note: including file: " + str(case.root / HEADER).encode() + b"\n"
    got = case.capture()
    assert "vendor/profile/compiler.exe" in got.files
    with binary.open("ab") as stream:
        stream.write(b"changed")
    with pytest.raises(P.InputRefused):
        got.validate()


def test_missing_emitter_record_uses_fresh_layout_only_never_diagnostic_owner_facts(case, monkeypatch):
    source = case.source(record=False)
    diagnostic = put(case.root, "build/diagnostic.obj", b"fresh layout diagnostic", tracked=False)
    calls = []
    def measure(root, unit):
        calls.append((root, unit))
        return {NAME: deepcopy(LAYOUT)}, (diagnostic,)
    monkeypatch.setattr(P, "_diagnostic_layouts", measure)
    got = case.capture(source)
    assert calls == [(case.root, source)]
    assert got.witnesses[source].layout["size"] == 8
    assert got.witnesses[source].object_path == str(case.units[source]["object"])
    assert got.witnesses[source].facts[0] == frozenset({"real-owner"})
    assert "build/diagnostic.obj" in got.files


def test_unknown_emitter_layout_stays_closed(case):
    case.source(record=False)
    with pytest.raises(P.InputRefused, match="diagnostic unavailable"):
        case.capture()


@pytest.mark.parametrize("change", ["offset", "size", "field_name", "slots", "key", "bases", "unparsed"])
def test_header_bound_native_class_must_equal_complete_contract(case, change):
    source = case.source()
    raw = case.units[source]["object"].read_bytes()
    record = case.objects[raw][1][NAME]
    if change == "offset":
        record["fields"][0][0] = 0
    elif change == "size":
        record["size"] = 12
    elif change == "field_name":
        record["fields"][0][1] = "other"
    elif change == "slots":
        record["vslots"]["1"] = "helper()"
    elif change == "key":
        record["key"] = "struct"
    elif change == "bases":
        record["bases"] = [["Base", 0]]
    else:
        record["unparsed"] = "ambiguous record"
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("change", ["path", "source", "object", "stale", "profile", "missing", "deps"])
def test_current_source_object_receipt_profile_binding_is_required(case, change):
    source = case.source()
    unit = case.units[source]
    if change == "missing":
        unit["receipt"].unlink()
    elif change in ("stale", "profile"):
        unit["state"] = replace(unit["state"], reusable=False, fingerprint="changed profile")
    else:
        meta = json.loads(unit["receipt"].read_text())
        if change == "deps":
            meta["deps"][HEADER] = "0" * 32
        else:
            meta[change] = "another-source" if change == "path" else "0" * 32
        unit["receipt"].write_text(json.dumps(meta))
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("forgery", ["source", "included", "foreign_marker", "unopened_marker", "namespace", "duplicate", "backward", "missing_markers"])
def test_actual_complete_span_provenance_cannot_be_forged(case, forgery):
    deps = ()
    body = None
    if forgery == "source":
        body = '#line 1 "Code/Canonical.h"\n#include "Canonical.h"\n'
    if forgery == "included":
        put(case.root, "Code/Forgery.h", '#line 1 "Code/Canonical.h"\n')
        deps = ("Code/Forgery.h",)
    source = case.source(deps=deps, body=body)
    unit = case.units[source]
    if forgery == "foreign_marker":
        unit["stdout"] = unit["stdout"].replace(b" void helper();", b'#line 5 "Code/Foreign.h"\n void helper();')
    elif forgery == "unopened_marker":
        unit["stderr"] = b""
    elif forgery == "namespace":
        unit["stdout"] = unit["stdout"].replace(b"class Canonical", b"namespace Other { class Canonical") + b"}\n"
    elif forgery == "duplicate":
        unit["stdout"] += f'#line 1 "{HEADER}"\n'.encode() + DECL.encode()
    elif forgery == "backward":
        unit["stdout"] = unit["stdout"].replace(b" void helper();", f'#line 1 "{HEADER}"\n void helper();'.encode())
    elif forgery == "missing_markers":
        unit["stdout"] = DECL.encode()
    with pytest.raises(P.InputRefused):
        case.capture()


def test_opened_header_with_suppressed_guard_definition_is_refused(case):
    put(case.root, HEADER, "#ifndef CANONICAL_H\n#define CANONICAL_H\n" + DECL + "#endif\n")
    source = case.source(body='#define CANONICAL_H\n#include "Canonical.h"\n')
    case.units[source]["stdout"] = b'#line 1 "Code/A.cpp"\nvoid f() {}\n'
    with pytest.raises(P.InputRefused, match="guard suppression"):
        case.capture()


@pytest.mark.parametrize("mutation", [b"void *value", b"void helper()", b"virtual ~Canonical()"])
def test_same_layout_does_not_replace_raw_declaration_token_proof(case, mutation):
    source = case.source()
    case.units[source]["stdout"] = case.units[source]["stdout"].replace(mutation, mutation + b" const")
    with pytest.raises(P.InputRefused, match="raw class tokens differ"):
        case.capture()


@pytest.mark.parametrize("macro", ["#define helper renamed\n", "#define public private\n", "#define Canonical Other\n",
                                  "#de\\\nfine helper renamed\n", "%:define helper renamed\n"])
def test_source_and_include_macro_token_collisions_are_refused(case, macro):
    put(case.root, "Code/Macros.h", macro)
    case.source(deps=("Code/Macros.h",))
    with pytest.raises(P.InputRefused, match="macro"):
        case.capture()


@pytest.mark.parametrize("flags", [["/Dhelper=other"], ["-D", "public=private"], ["-FIPrelude.h"],
                                  ["-FI", "Prelude.h"], ["@arguments.rsp"], ["-YuPrecompiled.h"]])
def test_command_macro_forced_and_opaque_inputs_stay_closed(case, flags):
    source = case.source()
    case.units[source]["command"][1:1] = flags
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("header", [
    "#if SELECTED\n" + DECL + "#endif\n",
    "#ifndef GUARD\n#define GUARD\n#endif\n" + DECL,
    DECL.replace("public:", "public:\n#if SELECTED\n int extra;\n#endif"),
    "namespace Other {\n" + DECL + "}\n",
    DECL.replace("void *value;", "typedef int Alias; void *value;"),
    DECL.replace("void *value;", "struct Nested {}; void *value;"),
    DECL.replace("void *value;", "void *value[1];"),
    DECL.replace("Canonical", "Cano\\\nnical"),
    DECL.replace("Canonical", "\\u0043anonical"),
    "#pragma once\n#pragma once\n" + DECL,
])
def test_unsupported_header_syntax_is_never_admitted(case, header):
    put(case.root, HEADER, header)
    case.source()
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("failure", ["returncode", "empty", "unreceipted"])
def test_incomplete_preprocessor_input_is_refused(case, failure):
    source = case.source()
    unit = case.units[source]
    if failure == "returncode":
        unit["returncode"] = 1
    elif failure == "empty":
        unit["stdout"] = b""
    else:
        path = put(case.root, "Code/Unexpected.h", "int extra;\n")
        unit["stderr"] += b"Note: including file: " + str(path).encode() + b"\n"
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("drift", ["source", "header", "object", "receipt", "profile", "search", "new_tracked"])
def test_native_capture_validation_refuses_input_drift(case, drift):
    source = case.source()
    got = case.capture()
    unit = case.units[source]
    if drift == "profile":
        unit["state"] = replace(unit["state"], fingerprint="other profile")
    elif drift == "search":
        unit["state"] = replace(unit["state"], inventory="new earlier include")
    elif drift == "new_tracked":
        put(case.root, "Code/Shadow.h", "int shadow;\n")
    else:
        path = {"source": case.root / source, "header": case.root / HEADER,
                "object": unit["object"], "receipt": unit["receipt"]}[drift]
        with path.open("ab") as stream:
            stream.write(b"\nchanged\n")
    with pytest.raises(P.InputRefused):
        got.validate()


def test_no_header_owner_or_optional_mutation_admission_surface(case):
    source = case.source()
    got = case.capture()
    assert HEADER not in got.witnesses
    with pytest.raises(TypeError):
        got.witnesses[HEADER] = got.witnesses[source]
    with pytest.raises(TypeError):
        got.witnesses[source].layout["size"] = 1
    with pytest.raises(P.InputRefused, match=r"real tracked C/C\+\+ source"):
        P.capture(NAME, HEADER, CONTRACT, [HEADER], root=case.root)


def test_real_generator_output_admits_only_its_complete_assertion_suffix(case, monkeypatch):
    import header_adopt_lane as lane
    contract = deepcopy(CONTRACT)
    contract.update(size_by="bytes", key_by="bytes")
    contract["fields"][0]["type"] = "void*"
    contract["fields"][1]["type"] = "void*"
    monkeypatch.setattr(lane, "owner_strength", lambda *a, **k: None)
    monkeypatch.setattr(lane, "mangling_contradictions", lambda *a, **k: [])
    generated = lane.generate(contract, "data", {}, HEADER, (["virtual ~Canonical() {}"], []), [
        {"role": "ctor", "access": "public", "text": "Canonical(void *held);", "sig": ("ctor",)},
        {"role": "method", "access": "public", "text": "void helper();", "sig": ("helper",)},
    ])
    put(case.root, HEADER, generated)
    source = case.source()
    parsed, expected, words, guard = P._elide_header(generated.encode(), NAME, contract)
    assert "typedef" not in parsed and "_vprobe" not in parsed
    assert any(word.endswith("_vprobe") for word in words)
    # Use the real emitted target declaration, including actual method ordering.
    case.units[source]["stdout"] = (f'#line 1 "{HEADER}"\n' + parsed + "\n").encode()
    got = case.capture(source, contract=contract)
    assert got.witnesses[source].header_bound is True
    prefix = lane.assertion_prefix(NAME, parsed)
    case.units[source]["command"].insert(1, "-D" + prefix + "_sizeof=other")
    with pytest.raises(P.InputRefused, match="command macro"):
        case.capture(source, contract=contract)


@pytest.mark.parametrize("change", ["size", "probe", "field", "extra"])
def test_assertion_suffix_cannot_admit_modified_or_extra_typedefs(case, change):
    import header_adopt_lane as lane
    suffix = "\n".join(lane.size_assertions(CONTRACT, DECL))
    if change == "size":
        suffix = suffix.replace("== 8", "== 80")
    elif change == "probe":
        suffix = suffix.replace("virtual void", "void")
    elif change == "field":
        suffix = suffix.replace("->value", "->other")
    else:
        suffix += "\ntypedef int Alias;"
    put(case.root, HEADER, DECL + suffix + "\n")
    case.source()
    with pytest.raises(P.InputRefused, match="exact owning generator assertions"):
        case.capture()


def test_whole_coff_reader_refuses_truncated_bytes():
    with pytest.raises(P.InputRefused, match="whole COFF"):
        P._object_evidence(b"truncated object")


def test_preprocessing_command_cannot_diverge_from_current_object_profile(case, monkeypatch):
    case.source()
    monkeypatch.setattr(P, "_command_fingerprint", lambda *a: "other profile")
    with pytest.raises(P.InputRefused, match="command/profile differs"):
        case.capture()


@pytest.mark.parametrize("change", ["duplicate", "extent", "negative", "aggregate", "bool_size"])
def test_malformed_contract_cannot_be_declared_layout_equal(case, change):
    case.source()
    contract = deepcopy(CONTRACT)
    if change == "duplicate":
        contract["fields"].append(deepcopy(contract["fields"][-1]))
    elif change == "extent":
        contract["fields"][-1]["size"] = 8
    elif change == "negative":
        contract["fields"][-1]["offset"] = -4
    elif change == "aggregate":
        contract["fields"][-1]["kind"] = "S:Hidden"
    else:
        contract["size"] = True
    with pytest.raises(P.InputRefused):
        case.capture(contract=contract)


@pytest.mark.parametrize("kind", ["literal", "manufactured"])
def test_volatile_native_inputs_and_preprocessed_clock_output_refuse(case, kind):
    source = case.source(body='const char *clock = __TIME__;\n#include "Canonical.h"\n' if kind == "literal" else None)
    if kind == "manufactured":
        case.units[source]["stdout"] += b'const char *clock = "12:34:56";\n'
    with pytest.raises(P.InputRefused, match="volatile"):
        case.capture()


@pytest.mark.skipif(os.environ.get("BFME_NATIVE_HEADER_PROOF") != "1", reason="explicit isolated VC71 component probe")
def test_native_vc71_generated_declaration_components():
    """Real native components; full receipt/capture binding is tested separately.

    Original owner/emission facts come from the normal-command object. The
    separate fresh -Z7 diagnostic supplies layout only. All files are scratch.
    """
    import build
    import class_layouts
    import header_adopt_lane as lane
    root = P.ROOT
    scratch = root / "build" / "native-canonical-generation-proof"
    scratch.mkdir(parents=True, exist_ok=True)
    name = "NativeCanonicalGenerationProof"
    contract = deepcopy(CONTRACT)
    contract.update({"class": name, "size_by": "bytes", "key_by": "bytes", "vslots": {"0": "__vecDelDtor(uint)"}})
    for field in contract["fields"]:
        field["type"] = "void*"
    header = scratch / "canonical.h"
    rel_header = header.relative_to(root).as_posix()
    special = [{"role": "ctor", "access": "public", "text": name + "(void *held);", "sig": ("ctor",)},
               {"role": "method", "access": "public", "text": "void helper();", "sig": ("helper",)}]
    generated = lane.generate(contract, "data", {}, rel_header, (["virtual ~" + name + "() {}"], []), special)
    header.write_text(generated, encoding="ascii", newline="\n")
    source = scratch / "native_canonical.cpp"
    source.write_text('#include "canonical.h"\n' + name + "::" + name + "(void *held) : value(held) {}\n"
                      + "void " + name + "::helper() {}\n" + name + " *make(void *held) { return new " + name + "(held); }\n",
                      encoding="ascii", newline="\n")
    output = scratch / "original.obj"
    command, env = build.compiler_command(source, output)
    with (scratch / "compile.log").open("w+", encoding="latin-1") as log:
        done = build._run_compile(command, env, log, timeout=60)
        log.seek(0)
        diagnostic = log.read()
    assert done.returncode == 0, diagnostic
    original = output.read_bytes()
    facts, _original_layouts = P._object_evidence(original)
    assert "??0" + name + "@@QAE@PAX@Z" in facts[0]
    assert "?helper@" + name + "@@QAEXXZ" in facts[0]
    assert "??_7" + name + "@@6B@" in facts[1]
    layouts, paths = P._diagnostic_layouts(root, source.relative_to(root).as_posix())
    assert all(path.is_file() for path in paths)
    P._layout(name, contract, layouts[name])
    pp = [arg for arg in command if not arg.startswith(("-Fo", "/Fo"))]
    pp[pp.index("-c")] = "-E"
    expanded = P._preprocess(pp + ["-showIncludes"], env)
    assert expanded.returncode == 0, expanded.stderr.decode("latin-1")
    opened = P._opened_paths(source, expanded.stderr + b"\n" + expanded.stdout)
    assert header.resolve() in opened
    parsed, expected, words, _guard = P._elide_header(header.read_bytes(), name, contract)
    assert "typedef" not in parsed and any(word.endswith("_vprobe") for word in words)
    assert P._bound_span(P._expanded_tokens(expanded.stdout, root), name, rel_header, expected, True) is True
    assert output.read_bytes() == original
    (scratch / "preprocessed.txt").write_bytes(expanded.stdout)
    (scratch / "evidence.json").write_text(json.dumps({
        "scope": "native components only; no synthetic strict receipt or full capture admission",
        "source": str(source), "header": str(header), "normal_object": str(output),
        "normal_object_sha256": hashlib.sha256(original).hexdigest(),
        "exclusive": sorted(facts[0]), "defined": sorted(facts[1]), "layout": layouts[name],
        "diagnostic_paths": [str(path) for path in paths], "header_bound": True}, indent=2), encoding="utf-8")


# An owning generator can carry allocation methods and literal gap padding;
# neither grants array-data, operator-expression or changed-storage admission.
def allocation_gap_case(gap=True, member="static void *operator new(unsigned int size);"):
    import header_adopt_lane as lane
    contract = {"class": "AllocationRoundtrip", "key": "class", "key_by": "bytes",
                "size": 12 if gap else 4, "size_by": "bytes", "bases": [], "vslots": {},
                "fields": [{"offset": 0, "name": "value", "kind": "i4", "size": 4, "type": "uint"}]}
    carried, problems = lane.special_declarations("AllocationRoundtrip", ["unit.cpp"],
        read=lambda _: "class AllocationRoundtrip { public: unsigned int value; " + member + " };", index={})
    assert not problems
    header = lane.generate(contract, "data+methods", {}, "Code/AllocationRoundtrip.h", special=carried, owners={})
    return contract, header


@pytest.mark.parametrize("gap", [False, True])
@pytest.mark.parametrize("member", ["static void *operator new(unsigned int size);",
                                    "static void *operator new[](unsigned size);",
                                    "static void operator delete(void *block);",
                                    "static void operator delete[](void *block);"])
def test_owning_generator_allocation_method_roundtrip(gap, member):
    contract, header = allocation_gap_case(gap, member)
    parsed, tokens, words, guard = P._elide_header(header.encode(), "AllocationRoundtrip", contract)
    assert "operator" in words and member in parsed
    fields = [[0, "value", "uint", 4]] + ([[4, "m_pad4", "char[8]", 8]] if gap else [])
    native = {"fwd": False, "key": "class", "size": contract["size"], "bases": [],
              "fields": fields, "vfptr": False, "vslots": {}}
    assert P._layout("AllocationRoundtrip", contract, native) is native


@pytest.mark.parametrize("member", [
    "static int operator new(unsigned int size);", "static void *operator new(SizeAlias size);",
    "static void *operator new(unsigned int size=4);", "static void *operator new(unsigned int size, void *where);",
    "static void *operator new(unsigned int size) { return 0; }", "operator void *() const;",
    "bool operator<(const AllocationRoundtrip &) const;", "static void operator delete(void *p, unsigned int n);",
    "friend void operator delete(void *p);", "static void (*operator new)(unsigned int);",
])
def test_allocation_role_does_not_admit_unrelated_or_unsupported_declarations(member):
    contract, header = allocation_gap_case(False)
    header = header.replace("static void *operator new(unsigned int size);", member)
    with pytest.raises(P.InputRefused):
        P._elide_header(header.encode(), "AllocationRoundtrip", contract)


@pytest.mark.parametrize("replacement", ["char m_pad4[7];", "char m_pad4[9];", "unsigned char m_pad4[8];",
                                         "char other[8];", "char m_pad4[sizeof(int)*2];", "char m_pad4[0x8];",
                                         "char m_pad4[8] = {};", "static char m_pad4[8];", "char m_pad4[8][1];"])
def test_only_exact_owning_generator_gap_declaration_is_admitted(replacement):
    contract, header = allocation_gap_case()
    with pytest.raises(P.InputRefused):
        P._elide_header(header.replace("char m_pad4[8];", replacement).encode(), "AllocationRoundtrip", contract)


@pytest.mark.parametrize("mutation", ["offset", "width", "element", "missing", "extra", "overlap"])
def test_native_gap_extent_and_type_are_not_guessed(mutation):
    contract, header = allocation_gap_case()
    native = {"fwd": False, "key": "class", "size": 12, "bases": [], "vfptr": False, "vslots": {},
              "fields": [[0, "value", "uint", 4], [4, "m_pad4", "char[8]", 8]]}
    if mutation == "offset": native["fields"][1][0] = 3
    elif mutation == "width": native["fields"][1][3] = 7
    elif mutation == "element": native["fields"][1][2] = "int[2]"
    elif mutation == "missing": native["fields"].pop()
    elif mutation == "extra": native["fields"].append([8, "hidden", "int", 4])
    else: native["fields"].append([3, "overlap", "char", 1])
    with pytest.raises(P.InputRefused): P._layout("AllocationRoundtrip", contract, native)


def test_gap_does_not_accept_changed_contract_or_missing_owning_assertions():
    contract, header = allocation_gap_case()
    updated = deepcopy(contract)
    updated["fields"].append({"offset":4,"name":"invented","kind":"i4","size":4,"type":"uint"})
    with pytest.raises(P.InputRefused): P._elide_header(header.encode(), "AllocationRoundtrip", updated)
    plain = header[:header.index("typedef char canonical_")]
    plain += "\n#endif\n"
    with pytest.raises(P.InputRefused): P._elide_header(plain.encode(), "AllocationRoundtrip", contract)
    bad = deepcopy(contract);bad["fields"][0]["offset"] = 1
    with pytest.raises(P.InputRefused): P._elide_header(header.encode(), "AllocationRoundtrip", bad)


@pytest.mark.skipif(os.environ.get("BFME_NATIVE_HEADER_PROOF") != "1", reason="explicit isolated VC71 allocation/gap roundtrip")
def test_native_allocation_gap_roundtrip_preserves_storage_and_alignment(monkeypatch):
    import build, class_layouts
    import header_adopt_lane as lane
    root = P.ROOT
    scratch = root / "build" / "codex-thing-agent-20261120" / "roundtrip-native"
    scratch.mkdir(parents=True, exist_ok=True)
    monkeypatch.setattr(class_layouts, "CACHE", scratch / "cv")
    contract, header = allocation_gap_case()
    name = contract["class"]
    h = scratch / "allocation.h";h.write_text(header, encoding="ascii", newline="\n")
    source = scratch / "allocation.cpp"
    source.write_text('#include "allocation.h"\nvoid *' + name + '::operator new(unsigned int) { return 0; }\n'
        + 'struct NativeGapAlignment { char lead; ' + name + ' value; };\n'
        + 'NativeGapAlignment alignmentWitness;\n'
        + 'unsigned alignment() { return (unsigned)&((NativeGapAlignment *)0)->value; }\n'
        + 'unsigned width() { return sizeof(' + name + '); }\n', encoding="ascii", newline="\n")
    output = scratch / "ordinary.obj"
    command, env = build.compiler_command(source, output)
    with (scratch / "compile.log").open("w+", encoding="latin-1") as log:
        done = build._run_compile(command, env, log, timeout=60);log.seek(0);diagnostic=log.read()
    assert done.returncode == 0, diagnostic
    ordinary = output.read_bytes()
    facts, _ = P._object_evidence(ordinary)
    assert "??2" + name + "@@SAPAXI@Z" in facts[0]
    layouts, paths = P._diagnostic_layouts(root, source.relative_to(root).as_posix())
    P._layout(name, contract, layouts[name])
    assert layouts["NativeGapAlignment"]["fields"][1][0] == 4
    pp = [a for a in command if not a.startswith(("-Fo", "/Fo"))];pp[pp.index("-c")]="-E"
    expanded=P._preprocess(pp+["-showIncludes"],env)
    assert expanded.returncode == 0
    parsed, expected, words, guard=P._elide_header(h.read_bytes(),name,contract)
    assert P._bound_span(P._expanded_tokens(expanded.stdout,root),name,h.relative_to(root).as_posix(),expected,True)
    assert output.read_bytes() == ordinary

    # Valid native C++ with unchanged allocation/record size is still not
    # admitted when a method role, padding type or declared storage differs.
    ordinary_source = source.read_text(encoding="ascii")
    negative_source = ordinary_source.replace("void *" + name + "::operator new(unsigned int) { return 0; }\n", "")
    for label, changed in [
        ("body", header.replace("static void *operator new(unsigned int size);", "static void *operator new(unsigned int size) { return 0; }")),
        ("alias", header.replace("static void *operator new(unsigned int size);", "typedef unsigned int SizeAlias; static void *operator new(SizeAlias size);")),
        ("padding-type", header.replace("char m_pad4[8];", "unsigned char m_pad4[8];")),
        ("hidden-data", header.replace("char m_pad4[8];", "char m_pad4[4]; int hidden;")),
    ]:
        h.write_text(changed, encoding="ascii", newline="\n")
        candidate = scratch / ("negative-" + label + ".cpp")
        candidate.write_text(negative_source, encoding="ascii", newline="\n")
        bad_output = scratch / ("negative-" + label + ".obj")
        bad_command, bad_env = build.compiler_command(candidate, bad_output)
        with (scratch / ("negative-" + label + ".log")).open("w+", encoding="latin-1") as log:
            result = build._run_compile(bad_command, bad_env, log, timeout=60);log.seek(0);diagnostic=log.read()
        assert result.returncode == 0, (label, diagnostic)
        with pytest.raises(P.InputRefused): P._elide_header(h.read_bytes(), name, contract)
        if label in {"padding-type", "hidden-data"}:
            bad_layouts, _ = P._diagnostic_layouts(root, candidate.relative_to(root).as_posix())
            with pytest.raises(P.InputRefused): P._layout(name, contract, bad_layouts[name])
    h.write_text(header, encoding="ascii", newline="\n")
    assert output.read_bytes() == ordinary
