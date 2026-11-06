"""Read-only Windows validation; not a production dependency."""
import ctypes
import json
import re
from pathlib import Path

directory = Path(__file__).resolve().parent
dll = ctypes.WinDLL("dbghelp.dll", use_last_error=True)
undecorate = dll.UnDecorateSymbolName
undecorate.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.c_uint32)
undecorate.restype = ctypes.c_uint32


def native_name(name):
    prefix = next((p for p in ("__ehhandler$", "__unwindfunclet$") if name.startswith(p)), "")
    name = name[len(prefix):]
    if prefix:
        name = re.sub(r"\$[0-9]+$", "", name)
    return name


def decode(name):
    name = native_name(name)
    buf = ctypes.create_string_buffer(65536)
    count = undecorate(name.encode("ascii"), buf, len(buf), 0)
    if not count:
        return None, f"DbgHelp error {ctypes.get_last_error()}"
    out = buf.value.decode("ascii", errors="replace")
    if out == name or out.startswith("?"):
        return None, "returned undecorated input"
    return out, None


results = []
for row in json.loads((directory / "prototype-results.json").read_text()):
    item = {"old": row["old"], "new": row.get("new")}
    if "new" not in row:
        item["status"] = "prototype-refused"
    else:
        before, e1 = decode(row["old"])
        after, e2 = decode(row["new"])
        item.update(before=before, after=after)
        if e1 or e2:
            item.update(status="undecoratable", error=[e1, e2])
        else:
            expected = re.sub(r"\bstruct Coord3D\b(?!::)", "class Coord3D", before)
            item.update(expected=expected, status="pass" if expected == after else "mismatch")
    results.append(item)
(directory / "dbghelp-results.json").write_text(json.dumps(results, indent=2))
from collections import Counter
print(dict(Counter(r["status"] for r in results)))
for row in results:
    if row["status"] != "pass":
        print(json.dumps(row))
