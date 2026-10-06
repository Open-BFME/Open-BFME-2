"""Native fold proof must cover the full emitted bodies and their call edges."""
import struct

from test_gate_exploits import RDATA, TEXT, coff, gate  # noqa: F401


VECTOR = ('??0?$_Vector_base@PAVWidget@@V?$allocator@PAVWidget@@@_STL@@'
          '@_STL@@QAE@ABV?$allocator@PAVWidget@@@1@@Z')
PROXY = ('??0?$_STLP_alloc_proxy@PAPAVWidget@@PAV1@V?$allocator@PAVWidget@@'
         '@_STL@@@_STL@@QAE@ABV?$allocator@PAVWidget@@@1@PAPAVWidget@@@Z')
VECTOR_OWNER = ('??0?$_Vector_base@HV?$allocator@H@_STL@@@_STL@@'
                'QAE@ABV?$allocator@H@1@@Z')
PROXY_OWNER = ('??0?$_STLP_alloc_proxy@PAHHV?$allocator@H@_STL@@@_STL@@'
               'QAE@ABV?$allocator@H@1@PAH@Z')
VECTOR_BODY = bytes.fromhex('5633c08bf150ff74240c8d4e088906894604e8000000008bc65ec20400')
PROXY_BODY = bytes.fromhex('8bc18b4c24088908c20800')


def fixture(gate, *, vector_body=VECTOR_BODY, proxy_body=PROXY_BODY,
            nested=PROXY, vector_chars=TEXT, called=0x2000, proxy_called=0x2100):
    gate.obj.write_bytes(coff(
        [('.text', TEXT, b'\xe8\0\0\0\0\xc3', [(1, 1, 20)]),
         ('.text$v', vector_chars, vector_body, [(19, 2, 20)]),
         ('.text$p', TEXT, proxy_body, [])],
        [('_f', 0, 1, 0x20, 2, 0),
         (VECTOR, 0, 2, 0x20, 2, 0),
         (nested, 0, 3, 0x20, 2, 0)]))
    gate.memory[0x1000] = b'\xe8' + struct.pack('<i', called - 0x1005) + b'\xc3'
    native = bytearray(VECTOR_BODY)
    native[19:23] = struct.pack('<i', proxy_called - 0x2017)
    gate.memory[0x2000] = bytes(native)
    gate.memory[0x2100] = PROXY_BODY
    gate.row('_f', 0x1000, 6)
    gate.row(VECTOR_OWNER, 0x2000, 29, source='Code/owner.cpp')
    gate.row(PROXY_OWNER, 0x2100, 11, source='Code/owner.cpp')


def test_complete_emitted_fold_and_nested_proxy_pass(gate):
    fixture(gate)
    assert gate.gate()


def test_changed_constructor_byte_fails(gate):
    fixture(gate, vector_body=b'\x57' + VECTOR_BODY[1:])
    assert not gate.gate()


def test_changed_proxy_byte_fails(gate):
    fixture(gate, proxy_body=b'\x8b\xc2' + PROXY_BODY[2:])
    assert not gate.gate()


def test_full_extent_is_required(gate):
    fixture(gate, vector_body=VECTOR_BODY + b'\x90')
    assert not gate.gate()


def test_interior_target_is_not_an_owner(gate):
    fixture(gate, called=0x2001)
    assert not gate.gate()


def test_changed_nested_call_target_fails(gate):
    fixture(gate, proxy_called=0x2200)
    gate.memory[0x2200] = PROXY_BODY
    assert not gate.gate()


def test_arbitrary_identical_callee_is_not_admitted(gate):
    fixture(gate, nested='_some_other_function')
    assert not gate.gate()


def test_data_symbol_is_not_an_emitted_callee(gate):
    fixture(gate, vector_chars=RDATA)
    assert not gate.gate()


def test_existing_conflicting_pin_is_never_overridden(gate):
    fixture(gate)
    gate.pins.append((VECTOR, '0x3000', 'wrong existing binding'))
    assert not gate.gate()


def test_missing_owner_fails(gate):
    fixture(gate)
    gate.rows = [row for row in gate.rows if row['name'] != VECTOR_OWNER]
    assert not gate.gate()
