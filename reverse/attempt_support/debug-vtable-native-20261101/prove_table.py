"""Read-only native Debug table/boundary proof; no compiled-cache mutation."""
import csv
import json
import struct
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import retail_body as rb

def stores(rva, size, value):
    needle = hex(value)
    return [{"rva": hex(i.rva), "instruction": i.mnem + " " + i.ops}
            for i in rb.disasm(rva, size) if i.mnem == "mov" and needle in i.ops]

proof = {"table_rva": "0x007BE810", "next_table_rva": "0x007BE8C8",
         "entry_count": (0x7BE8C8-0x7BE810)//4,
         "constructor_stores": stores(0x38440, 408, 0xBBE810),
         "destructor_stores": stores(0x38710, 66, 0xBBE810),
         "next_constructor_stores": stores(0x38670, 70, 0xBBE8C8)}
assert proof["entry_count"] == 46
assert all(proof[k] for k in ("constructor_stores", "destructor_stores", "next_constructor_stores"))
words = struct.unpack("<49I", rb.read_bytes(0x7BE810, 49*4))
want = {va-0x400000 for va in words}
names = {}
with (ROOT / "reverse/functions.csv").open(newline="") as f:
    for row in csv.DictReader(f):
        try: rva = int(row["target_rva"], 0)
        except ValueError: continue
        if rva in want:
            names.setdefault(rva, []).append({"name": row["name"], "source": row["source"]})
proof["slots"] = [{"slot": i, "rva": hex(va-0x400000),
                    "owners": names.get(va-0x400000, [])} for i, va in enumerate(words)]
assert words[9] == 0x438890 and words[16] == 0x439920 and words[45] == 0x4390D0
assert words[46] == 0x439950
out = ROOT / "build/debug-vtable-link-20261101/native-proof.json"
out.parent.mkdir(parents=True, exist_ok=True)
out.write_text(json.dumps(proof, indent=2) + "\n")
print(json.dumps({"entries": 46, "boundary": "independently installed next table", "slots_checked": len(words)}))
