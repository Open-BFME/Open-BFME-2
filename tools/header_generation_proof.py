"""Fail-closed native provenance for one narrow canonical declaration input.

No header is an object owner. Facts and emission below always come from each
real source's current match object; diagnostic CodeView supplies layout only.
"""
from dataclasses import dataclass, field
import hashlib
import json
from pathlib import Path
import re
import struct
from types import MappingProxyType
from typing import Mapping

import header_generation_inputs as I


ROOT = Path(__file__).resolve().parents[1]
InputRefused = I.InputRefused
_COMMENT = re.compile(r'//[^\n]*|/\*.*?\*/', re.S)
_TOKEN = re.compile(r'\s+|[A-Za-z_][A-Za-z_0-9]*|(?:[0-9][A-Za-z_0-9.]*)|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|::|->\*|->|\.\*|\.\.\.|<<=?|>>=?|[+*/%&|^!=<>-]=|&&|\|\||\+\+|--|[{}()[\];,:~?=.+*/%&|^!<>-]')
_MARKER = re.compile(r'^[ \t]*#[ \t]*line[ \t]+([0-9]+)[ \t]+"((?:[^"\\]|\\.)*)"[ \t]*$')
_FORBIDDEN = re.compile(r"\b(?:namespace|template|typedef|using|union|enum|friend|operator|alignas|__declspec|__attribute__|__pragma|__identifier)\b")


def _freeze(value):
    if isinstance(value, dict):
        return MappingProxyType({k: _freeze(v) for k, v in value.items()})
    if isinstance(value, (list, tuple)):
        return tuple(_freeze(v) for v in value)
    if isinstance(value, set):
        return frozenset(value)
    return value


def _comments(text):
    # This first admission deliberately has no literals in the declaration.
    return _COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m[0]), text)


def _tokens(text):
    out, pos = [], 0
    while pos < len(text):
        match = _TOKEN.match(text, pos)
        if not match:
            raise InputRefused(f"unsupported token at declaration offset {pos}")
        if not match[0].isspace():
            out.append((match[0], pos, match.end()))
        pos = match.end()
    return out


def _generator_padding(contract):
    """Only the owning layout planner's literal gap arrays, never array fields."""
    import header_adopt_lane as lane
    try:
        plan, problems = lane.layout_plan(contract)
        if problems:
            raise InputRefused("canonical padding layout is unproved: " + "; ".join(problems))
        fields = [f for f in contract["fields"] if f.get("kind") != "VPTR"]
        polymorphic = bool(contract.get("vslots")) or any(f.get("kind") == "VPTR" for f in contract["fields"])
        cursor = max(4, max((lane.field_alignment(f) or 1 for f in fields), default=1)) if polymorphic else 0
        pads = {}
        for entry in plan:
            if entry[0] == "field":
                cursor = entry[1]["offset"] + entry[1]["size"]
            else:
                _, name, size = entry
                if type(size) is not int or size <= 0 or name in pads:
                    raise InputRefused("canonical generator padding is ambiguous")
                pads[name] = (cursor, size)
                cursor += size
        return pads
    except (KeyError, TypeError, ValueError) as exc:
        raise InputRefused("canonical padding layout cannot be proved: " + str(exc)) from exc


def _role_checked_syntax(text, name, contract):
    """Mask only verified allocation declarations and exact generated gap storage.

    The original complete tokens still bind native preprocessor provenance;
    method selection and ownership are still judged by RegisteredGeneration.
    """
    import header_adopt_lane as lane
    pads, seen = _generator_padding(contract), set()
    members = lane.class_members(text, name)
    if members is None:
        raise InputRefused("canonical member roles cannot be read")
    result, position = text, 0
    for _access, member in members:
        at = text.find(member, position)
        if at < 0:
            raise InputRefused("canonical member role has no unique lexical span")
        position = at + len(member)
        special = None
        if re.search(r"\boperator\b", member):
            records = lane.declaration_records("class " + name + " { public: " + member + " };", name)
            allocation = re.fullmatch(
                r"static\s+void\s*\*\s*operator\s+new\s*(?:\[\s*\])?\s*"
                r"\(\s*unsigned(?:\s+int)?(?:\s+[A-Za-z_][A-Za-z_0-9]*)?\s*\)\s*;", member)
            deallocation = re.fullmatch(
                r"static\s+void\s+operator\s+delete\s*(?:\[\s*\])?\s*"
                r"\(\s*void\s*\*(?:\s*[A-Za-z_][A-Za-z_0-9]*)?\s*\)\s*;", member)
            if (not allocation and not deallocation or not records or len(records) != 1
                    or records[0]["role"] != "method" or records[0]["inline"]):
                raise InputRefused("canonical operator is not a supported allocation method declaration")
            special = member
        elif "[" in member or "]" in member:
            found = re.fullmatch(r"char\s+([A-Za-z_][A-Za-z_0-9]*)\[([1-9][0-9]*)\]\s*;", member)
            if (found is None or lane.member_role(member, name) is not None
                    or found[1] not in pads or str(pads[found[1]][1]) != found[2] or found[1] in seen):
                raise InputRefused("canonical array is not exact owning-generator gap padding")
            seen.add(found[1])
            special = member
        if special is not None:
            result = result[:at] + re.sub(r"[^\n]", " ", special) + result[at + len(special):]
    if seen != set(pads):
        raise InputRefused("canonical generator gap padding is missing or ambiguous")
    return result, bool(seen)


def _elide_header(raw, name, contract):
    """Only a literal global class with a real whole-file guard/once wrapper."""
    if not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", name):
        raise InputRefused("qualified or ambiguous canonical class name is unsupported")
    if not raw.isascii() or b"\0" in raw or b"\\" in raw or b"??" in raw or b"%:" in raw:
        raise InputRefused("canonical header has encoding, splice, UCN or alternative-token ambiguity")
    text = raw.decode("ascii")
    if "/*" in text and "*/" not in text[text.find("/*") + 2:]:
        raise InputRefused("canonical header has an unterminated comment")
    code = _comments(text)
    if '"' in code or "'" in code:
        raise InputRefused("canonical declaration literals need a broader lexical proof")
    lines = code.splitlines(keepends=True)
    active = [i for i, line in enumerate(lines) if line.strip()]
    elided, guard = set(), None
    once = [i for i in active if re.fullmatch(r"[ \t]*#[ \t]*pragma[ \t]+once[ \t]*(?:\r?\n)?", lines[i])]
    if len(once) > 1:
        raise InputRefused("canonical header has repeated pragma once")
    if once:
        # A pragma inside the class is not an outer wrapper.
        if once[0] not in active[:1]:
            raise InputRefused("pragma once is not the canonical header's outer wrapper")
        elided.update(once)
        active = [i for i in active if i not in elided]
    if active and lines[active[0]].lstrip().startswith("#"):
        first = re.fullmatch(r"[ \t]*#[ \t]*ifndef[ \t]+([A-Za-z_][A-Za-z_0-9]*)[ \t]*(?:\r?\n)?", lines[active[0]])
        if first is None or len(active) < 4:
            raise InputRefused("canonical header has no proven literal whole-file guard")
        guard = first[1]
        define = re.fullmatch(r"[ \t]*#[ \t]*define[ \t]+" + re.escape(guard) + r"[ \t]*(?:\r?\n)?", lines[active[1]])
        closing = re.fullmatch(r"[ \t]*#[ \t]*endif[ \t]*(?:\r?\n)?", lines[active[-1]])
        if define is None or closing is None:
            raise InputRefused("canonical header guard does not wrap its whole file")
        elided.update((active[0], active[1], active[-1]))
    parsed = "".join(re.sub(r"[^\n]", " ", line) if i in elided else line for i, line in enumerate(lines))
    if "#" in parsed:
        raise InputRefused("canonical declaration has conditional, macro or other directives")
    tokens = _tokens(parsed)
    if len(tokens) < 5 or tokens[0][0] not in ("class", "struct") or tokens[1][0] != name or tokens[2][0] != "{":
        raise InputRefused("canonical declaration is not exactly one literal global baseless class")
    if (contract.get("class") != name or contract.get("key") != tokens[0][0] or contract.get("bases") != []
            or type(contract.get("size")) is not int or contract["size"] <= 0
            or not isinstance(contract.get("fields"), list) or not isinstance(contract.get("vslots"), dict)):
        raise InputRefused("canonical declaration identity/key/bases disagree with its contract")
    depth, end = 0, None
    for i, (token, _start, _end) in enumerate(tokens[2:], 2):
        if token in ("class", "struct"):
            raise InputRefused("nested or elaborated aggregate declarations are unsupported")
        if token == "{":
            depth += 1
        elif token == "}":
            depth -= 1
            if depth == 0:
                end = i
                break
        if depth < 0:
            break
    if end is None or end + 1 >= len(tokens) or tokens[end + 1][0] != ";":
        raise InputRefused("canonical declaration has extra text or an unbalanced class body")
    class_tokens = tokens[:end + 2]
    class_text = parsed[:class_tokens[-1][2]]
    checked, padding = _role_checked_syntax(class_text, name, contract)
    if _FORBIDDEN.search(checked) or re.search(r"\b__(?!int(?:8|16|32|64)\b)\w+", checked):
        raise InputRefused("canonical declaration has an unsupported scope, alias, intrinsic or type role")
    suffix = tokens[end + 2:]
    if padding and not suffix:
        raise InputRefused("canonical generated padding lacks its owning assertion suffix")
    if suffix:
        import header_adopt_lane as lane
        asserted = "\n".join(lane.size_assertions(contract, class_text))
        if tuple(t[0] for t in suffix) != tuple(t[0] for t in _tokens(asserted)):
            raise InputRefused("canonical trailing declarations are not the exact owning generator assertions")
    # Native layout admission below supports primitive/pointer storage only.
    # Ban declarator/type machinery whose interpretation this input model lacks.
    if any(t[0] in ("[", "]", "...", "::") for t in _tokens(checked)):
        raise InputRefused("canonical declaration has unsupported array, variadic or qualified syntax")
    words = {t[0] for t in tokens if re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", t[0])}
    return class_text, tuple(t[0] for t in class_tokens), words, guard


def _normal_command(root, source, output):
    import build
    if Path(build.ROOT).resolve() != root:
        raise InputRefused("native command belongs to another checkout")
    return build.compiler_command(root / source, output)


def _command_fingerprint(command, env):
    import build
    return build._cmd_fingerprint(command, env)


def _preprocess(command, env):
    import census_receipts
    return census_receipts.capture_preprocessor(command, env)


def _opened_paths(source, output):
    import census_receipts
    return {Path(p).resolve() for p in census_receipts.opened_paths(source, output)}


def _marker_path(raw, root):
    import rename
    return rename._marker_path(raw, root)


def _line_directive(raw):
    import rename
    return rename.source_line_directive(raw)


def _expanded_tokens(output, root):
    """Tokens carry actual compiler-marker file and line provenance."""
    try:
        text = output.decode("ascii")
    except UnicodeError as exc:
        raise InputRefused("preprocessor output is not unambiguous ASCII") from exc
    file, line, out, marked = None, 0, [], False
    for physical in text.splitlines():
        marker = _MARKER.fullmatch(physical)
        if marker:
            file, line, marked = _marker_path(marker[2], root), int(marker[1]), True
            continue
        if physical.lstrip().startswith("#"):
            if re.match(r"\s*#\s*line\b", physical):
                raise InputRefused("malformed preprocessor provenance marker")
            # Pragmas outside the declaration can be emitted by normal headers.
            out.append(("#directive", file, line))
        else:
            out.extend((token, file, line) for token, _start, _end in _tokens(physical))
        line += 1
    if not marked:
        raise InputRefused("preprocessor omitted compiler line provenance")
    return out


def _bound_span(tokens, name, header, expected, opened):
    """At most one definition, with its entire token span at global header scope."""
    depth, definitions = 0, []
    index = 0
    while index < len(tokens):
        token = tokens[index][0]
        if (token in ("class", "struct") and index + 2 < len(tokens)
                and tokens[index + 1][0] == name and tokens[index + 2][0] == "{"):
            local, end = 1, index + 3
            while end < len(tokens) and local:
                local += (tokens[end][0] == "{") - (tokens[end][0] == "}")
                end += 1
            if local or end == len(tokens) or tokens[end][0] != ";":
                raise InputRefused("preprocessor class definition has no complete closing span")
            definitions.append((depth, tokens[index:end + 1]))
        depth += (token == "{") - (token == "}")
        if depth < 0:
            raise InputRefused("preprocessor scope cannot be proven")
        index += 1
    if depth:
        raise InputRefused("preprocessor has an incomplete global scope")
    target = header.lower()
    attributed = [span for scope, span in definitions if any(t[1] == target for t in span)]
    if not opened:
        if attributed:
            raise InputRefused("canonical marker names a header the compiler did not open")
        return False
    if len(definitions) != 1 or len(attributed) != 1:
        raise InputRefused("opened canonical header does not supply exactly one class definition (guard suppression or duplicate)")
    scope, span = definitions[0]
    if scope != 0 or any(t[1] != target for t in span):
        raise InputRefused("canonical class span has foreign file or nonglobal scope provenance")
    if tuple(t[0] for t in span) != expected:
        raise InputRefused("canonical raw class tokens differ from the preprocessor's actual class")
    if any(t[2] <= 0 for t in span) or any(a[2] > b[2] for a, b in zip(span, span[1:])):
        raise InputRefused("canonical class has invalid or backward line provenance")
    return True


def _macro_collisions(raw, words, guard=None):
    if re.search(rb"\b__(?:TIME|DATE|TIMESTAMP)__\b", re.sub(rb"\\\r?\n", b"", raw)):
        raise InputRefused("volatile predefined macro cannot bind a separate native/preprocessor invocation")
    logical = I._logical_text(raw).replace("%:", "#")
    names = re.findall(r"(?m)^[ \t]*#[ \t]*(?:define|undef)[ \t]+([A-Za-z_][A-Za-z_0-9]*)", logical)
    hits = sorted(set(names) & words)
    if hits:
        raise InputRefused("canonical tokens collide with a source/include macro: " + ", ".join(hits[:3]))


def _command_collisions(command, env, words, guard):
    if env.get("CL") or env.get("_CL_"):
        raise InputRefused("implicit compiler options have no canonical token proof")
    check = set(words) | ({guard} if guard else set())
    index = 0
    while index < len(command):
        token = command[index]
        if token.startswith(("-FI", "/FI", "-Yu", "/Yu", "-Yc", "/Yc", "@")):
            raise InputRefused("forced/PCH/response inputs need a broader canonical proof")
        if token.startswith(("-D", "/D", "-U", "/U")):
            arg = token[2:]
            if not arg:
                index += 1
                arg = command[index] if index < len(command) else ""
            name = re.split(r"[=#]", arg, maxsplit=1)[0]
            if not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", name) or name in check:
                raise InputRefused("command macro is ambiguous or collides with canonical tokens/guard")
        index += 1


def _object_evidence(data):
    import rename
    import header_adopt_lane as lane
    import class_layouts
    problem = rename.coff_layout_problem(data)
    if problem:
        raise InputRefused("native object is not whole COFF: " + problem)
    facts = lane.exclusive_definitions(data)
    stream = class_layouts.type_stream(data)
    layouts = {}
    if stream:
        if not class_layouts.REVERSED_GROUPS or len(stream) < 4:
            raise InputRefused("native type stream/virtual overload decoder is unavailable")
        pos = 4
        while pos < len(stream):
            if pos + 4 > len(stream):
                raise InputRefused("truncated CodeView record")
            length = struct.unpack_from("<H", stream, pos)[0]
            if length < 2 or pos + 2 + length > len(stream):
                raise InputRefused("invalid CodeView record extent")
            pos += 2 + length
        layouts = class_layouts.TypeStream(stream).classes()
    return (frozenset(facts[0]), frozenset(facts[1])), layouts


def _diagnostic_layouts(root, source):
    """Fresh source/profile diagnostic; its object never supplies ownership facts."""
    import class_layouts
    if Path(class_layouts.ROOT).resolve() != root:
        raise InputRefused("layout diagnostic belongs to another checkout")
    measured = class_layouts.compile_layouts(source, use_cache=False)
    stem = re.sub(r"[^\w.-]", "_", source)
    output = class_layouts.CACHE / (stem + ".obj")
    meta = class_layouts.CACHE / (stem + ".json")
    _facts, actual = _object_evidence(output.read_bytes())
    if measured != actual:
        raise InputRefused("diagnostic layout result differs from its actual fresh object")
    return actual, (output, meta)


def _layout(name, contract, record):
    import class_contract
    if (not isinstance(record, dict) or record.get("fwd") is not False or "unparsed" in record
            or record.get("bases") != [] or record.get("key") != contract.get("key")
            or type(record.get("size")) is not int or record["size"] != contract.get("size")
            or type(record.get("vfptr")) is not bool or not isinstance(record.get("fields"), list)
            or not isinstance(record.get("vslots"), dict)):
        raise InputRefused(f"{name}: no complete matching baseless native class record")
    allowed = set(class_contract.PRIMK.values()) | {"P", "VPTR"}
    wanted, got, expected_names, declared_types = set(), set(), set(), {}
    for entry in contract.get("fields", []):
        if (not isinstance(entry, dict) or entry.get("kind") not in allowed or entry.get("members")
                or type(entry.get("offset")) is not int or type(entry.get("size")) is not int
                or not isinstance(entry.get("name"), str) or entry["name"] in expected_names
                or entry["offset"] < 0 or entry["size"] <= 0
                or entry["offset"] + entry["size"] > contract["size"]):
            raise InputRefused("canonical layout proof supports only complete primitive/pointer fields")
        width = 4 if entry["kind"] in ("P", "VPTR") else int(entry["kind"][1:])
        if entry["size"] != width:
            raise InputRefused("canonical primitive/pointer extent is not its type width")
        expected_names.add(entry["name"])
        wanted.add((entry["offset"], entry["name"], entry["kind"], entry["size"]))
        if entry["kind"] != "VPTR":
            if not isinstance(entry.get("type"), str) or not entry["type"].strip():
                raise InputRefused("canonical storage lacks an explicit recorded field type")
            declared_types[entry["name"]] = re.sub(r"\s+", "", entry["type"])
    padding, seen_padding = _generator_padding(contract), set()
    if record["vfptr"]:
        got.add((0, "__vfptr", "VPTR", 4))
    regions = [(0, 4)] if record["vfptr"] else []
    names = set()
    for field in record["fields"]:
        if not isinstance(field, (list, tuple)) or len(field) != 4:
            raise InputRefused("native field record is incomplete")
        offset, member, type_name, size = field
        if isinstance(member, str) and member in padding:
            expected_offset, expected_size = padding[member]
            if (type(offset) is not int or type(size) is not int or member in names
                    or (offset, size) != (expected_offset, expected_size)
                    or type_name != f"char[{expected_size}]"):
                raise InputRefused("native generator padding offset/type/extent differs from contract")
            names.add(member)
            seen_padding.add(member)
            regions.append((offset, offset + size))
            continue
        kind = class_contract.kind(type_name) if isinstance(type_name, str) else None
        if (type(offset) is not int or type(size) is not int or size <= 0 or offset < 0
                or offset + size > record["size"] or not isinstance(member, str) or member in names
                or kind not in allowed - {"VPTR"}):
            raise InputRefused("native primitive/pointer field span is unsupported or ambiguous")
        names.add(member)
        if re.sub(r"\s+", "", type_name) != declared_types.get(member):
            raise InputRefused("native canonical field type differs from its explicit recorded declaration")
        got.add((offset, member, kind, size))
        regions.append((offset, offset + size))
    if seen_padding != set(padding):
        raise InputRefused("native generator padding is missing")
    regions.sort()
    if any(a[1] > b[0] for a, b in zip(regions, regions[1:])) or wanted != got:
        raise InputRefused("native canonical storage differs from contract")
    slots = {str(k): (v.get("member") if isinstance(v, dict) else v) for k, v in (contract.get("vslots") or {}).items()}
    if record["vslots"] != slots:
        raise InputRefused("native canonical virtual slots differ from contract")
    return record


@dataclass(frozen=True)
class Witness:
    source: str
    object_path: str
    object_digest: str
    facts: tuple[frozenset[str], frozenset[str]]
    emitting: bool
    layout: Mapping | None
    header_bound: bool


@dataclass(frozen=True)
class CanonicalInput:
    name: str
    header: str
    text: str
    digest: str
    witnesses: Mapping[str, Witness]
    files: Mapping[str, str]
    _snapshot: I.Snapshot = field(repr=False)
    rebuildable: frozenset[str] = field(default_factory=frozenset)

    def __post_init__(self):
        object.__setattr__(self, "witnesses", MappingProxyType(dict(self.witnesses)))
        object.__setattr__(self, "files", MappingProxyType(dict(self.files)))
        object.__setattr__(self, "rebuildable", frozenset(self.rebuildable))

    def validate(self):
        return self._snapshot.revalidate()

    @property
    def profiles(self):
        return MappingProxyType({source: state.fingerprint for source, (_path, state) in self._snapshot._compiler.items()})

    @property
    def forced_inputs(self):
        return MappingProxyType({source: state.forced for source, (_path, state) in self._snapshot._compiler.items()})

    @property
    def search_inventories(self):
        return MappingProxyType({source: state.inventory for source, (_path, state) in self._snapshot._compiler.items()})


def capture(name, header, contract, sources, root=ROOT):
    """Require a current real object for every source; refuse all unknown proof."""
    root, header = Path(root).resolve(), I._relative(header)
    tracked = I._tracked(root)
    if tracked.get(header) not in ("100644", "100755"):
        raise InputRefused("canonical header is not a tracked ordinary file")
    files, md5s, compiler, witnesses, rebuildable = {}, {}, {}, {}, set()

    def observe(path, retain=False):
        sha, md5, raw = I._hash(Path(path), retain=retain)
        key = I._key(root, Path(path))
        if key in files and files[key] != sha:
            raise InputRefused(f"native input changed during capture: {key}")
        files[key], md5s[key] = sha, md5
        return raw

    raw = observe(root / header, retain=True)
    text, expected, words, guard = _elide_header(raw, name, contract)
    units = tuple(sorted(set(sources)))
    if not units:
        raise InputRefused("canonical declaration has no actual source witnesses")
    inventory_cache = {}
    table = "??_7" + name + "@@6B"
    for source in units:
        source = I._relative(source)
        if tracked.get(source) not in ("100644", "100755") or not source.lower().endswith(I.H.SOURCE_SUFFIXES):
            raise InputRefused(f"native witness is not a real tracked C/C++ source: {source}")
        source_raw = observe(root / source, retain=True)
        receipt = I._receipt_path(root, source)
        try:
            meta = json.loads(observe(receipt, retain=True))
            if not isinstance(meta, dict) or meta.get("path") != source or not isinstance(meta.get("deps"), dict):
                raise InputRefused("receipt source/dependency binding is absent")
            output = receipt.with_name(receipt.name[:-len(".deps.json")] + ".obj")
            rebuildable.update((I._key(root, receipt), I._key(root, output)))
            object_raw = observe(output, retain=True)
            if meta.get("source") != md5s[source] or meta.get("object") != md5s[I._key(root, output)]:
                raise InputRefused("receipt does not bind the actual source and object bytes")
            state = I._compiler_inputs(root, source, output, inventory_cache)
            if not state.reusable:
                raise InputRefused("object is not strictly current for its compiler/profile/search inputs")
            command, env = _normal_command(root, source, output)
            if _command_fingerprint(command, env) != state.fingerprint:
                raise InputRefused("actual preprocessing command/profile differs from the current object command")
            _command_collisions(command, env, words, guard)
            compiler[source] = (str(output), state)
            deps = {}
            for path, digest in meta["deps"].items():
                if not isinstance(path, str) or not path or "\0" in path:
                    raise InputRefused("invalid native dependency path")
                host = Path(path) if Path(path).is_absolute() else root / path
                deps[host.resolve()] = observe(host, retain=True)
                if not isinstance(digest, str) or md5s[I._key(root, host)] != digest:
                    raise InputRefused("native receipt dependency bytes differ")
            # Receipts also bind compiler-profile executables/archives. Their
            # hashes matter, but only actual preprocessor-opened files are C++
            # text whose directives and macros can affect this declaration.
            if _line_directive(source_raw):
                raise InputRefused(f"user line provenance directive in {source}")
            _macro_collisions(source_raw, words, guard)
            pp = [arg for arg in command if not arg.startswith(("-Fo", "/Fo"))]
            if pp.count("-c") != 1:
                raise InputRefused("normal native command cannot be transformed exactly to -E")
            pp[pp.index("-c")] = "-E"
            done = _preprocess(pp + ["-showIncludes"], env)
            if done.returncode or not done.stdout:
                raise InputRefused("native preprocessor failed or returned empty output")
            import census_receipts
            if census_receipts._CLOCK_OUTPUT.search(done.stdout):
                raise InputRefused("volatile date/time preprocessor output cannot bind the actual object")
            opened = _opened_paths(root / source, done.stderr + b"\n" + done.stdout)
            if root / source not in opened:
                raise InputRefused("native preprocessor did not identify its source")
            for path in opened - {root / source}:
                if path not in deps:
                    raise InputRefused("preprocessor opened an input absent from the current object receipt")
                body = observe(path, retain=True)
                if _line_directive(body):
                    raise InputRefused("opened preprocessor input has forged line provenance")
                _macro_collisions(body, words, guard)
            bound = _bound_span(_expanded_tokens(done.stdout, root), name, header, expected,
                                (root / header).resolve() in opened)
            facts, layouts = _object_evidence(object_raw)
            emitting = any(symbol.startswith(table) for symbol in facts[1])
            record = layouts.get(name)
            diagnostic_paths = ()
            needs_layout = emitting or bound and not contract.get("vslots")
            if needs_layout and (record is None or record.get("fwd")):
                layouts, diagnostic_paths = _diagnostic_layouts(root, source)
                record = layouts.get(name)
                for path in diagnostic_paths:
                    observe(path)
                    rebuildable.add(I._key(root, path))
            if needs_layout and (record is None or record.get("fwd")):
                raise InputRefused("actual emitting/nonpolymorphic consumer has no complete bound class layout")
            if record is not None and not record.get("fwd"):
                if "unparsed" in record:
                    raise InputRefused("native class record is ambiguous or incompletely decoded")
                if bound:
                    _layout(name, contract, record)
            else:
                record = None
            witnesses[source] = Witness(source, str(output), files[I._key(root, output)], facts,
                                        emitting, _freeze(record) if record is not None else None, bound)
        except (Exception, SystemExit) as exc:
            raise InputRefused(f"{source}: canonical native proof refused: {exc}") from exc
    if not any(w.header_bound for w in witnesses.values()):
        raise InputRefused("no actual source binds the canonical declaration")
    if not any(w.header_bound and w.layout is not None for w in witnesses.values()):
        raise InputRefused("canonical declaration has no complete matching native layout witness")
    if contract.get("vslots") and not any(w.header_bound and w.emitting and w.layout is not None
                                          for w in witnesses.values()):
        raise InputRefused("canonical virtual declaration has no matching native emitting layout witness")
    snapshot = I.Snapshot(root, files, tuple(sorted(tracked)), compiler)
    snapshot.revalidate()
    return CanonicalInput(name, header, text, hashlib.sha256(raw).hexdigest(), witnesses, files, snapshot,
                          frozenset(rebuildable))
