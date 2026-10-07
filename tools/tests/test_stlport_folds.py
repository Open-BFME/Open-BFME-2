"""Native fold proof must cover the full emitted bodies and their call edges."""
import struct
import pytest

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
            nested=PROXY, vector_chars=TEXT, called=0x2000, proxy_called=0x2100,
            caller_opcode=0xE8, caller_addend=0):
    gate.obj.write_bytes(coff(
        [('.text', TEXT, bytes([caller_opcode]) + struct.pack('<i', caller_addend)
          + b'\xc3', [(1, 1, 20)]),
         ('.text$v', vector_chars, vector_body, [(19, 2, 20)]),
         ('.text$p', TEXT, proxy_body, [])],
        [('_f', 0, 1, 0x20, 2, 0),
         (VECTOR, 0, 2, 0x20, 2, 0),
         (nested, 0, 3, 0x20, 2, 0)]))
    gate.memory[0x1000] = bytes([caller_opcode]) + struct.pack('<i', called - 0x1005) + b'\xc3'
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


def test_direct_tail_jump_to_emitted_fold_passes(gate):
    fixture(gate, caller_opcode=0xE9)
    assert gate.gate()


@pytest.mark.parametrize('addend', [1, -1, 4])
def test_caller_addend_is_not_discarded(gate, addend):
    fixture(gate, caller_addend=addend)
    assert not gate.gate()


def test_non_branch_caller_relocation_is_not_a_fold_call(gate):
    fixture(gate, caller_opcode=0xB8)
    assert not gate.gate()


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


LIST_DTOR = ('??1?$_List_base@PAVWidget@@V?$allocator@PAVWidget@@@_STL@@'
             '@_STL@@QAE@XZ')
LIST_CLEAR = ('?clear@?$_List_base@PAVWidget@@V?$allocator@PAVWidget@@@_STL@@'
              '@_STL@@QAEXXZ')
LIST_DTOR_OWNER = '??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ'
LIST_CLEAR_OWNER = '?clear@?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAEXXZ'
# Retail 0x004EC395 and 0x0023DAA5 with their call displacements zeroed.
LIST_DTOR_BODY = bytes.fromhex('568bf1e8000000008b3685f6740756e800000000595ec3')
LIST_CLEAR_BODY = bytes.fromhex(
    '56578bf98b078b303bf0740f8bc68b3650e8000000003b375975f18b0789008b3f897f045f5ec3')


def list_fixture(gate, *, dtor_body=LIST_DTOR_BODY, clear_body=LIST_CLEAR_BODY,
                 nested=LIST_CLEAR, free_called=0x2200, clear_called=0x2100):
    gate.obj.write_bytes(coff(
        [('.text', TEXT, b'\xe8\0\0\0\0\xc3', [(1, 1, 20)]),
         ('.text$d', TEXT, dtor_body, [(4, 2, 20), (16, 3, 20)]),
         ('.text$c', TEXT, clear_body, [(18, 3, 20)])],
        [('_f', 0, 1, 0x20, 2, 0),
         (LIST_DTOR, 0, 2, 0x20, 2, 0),
         (nested, 0, 3, 0x20, 2, 0),
         ('_free', 0, 0, 0x20, 2, 0)]))
    gate.memory[0x1000] = b'\xe8' + struct.pack('<i', 0x2000 - 0x1005) + b'\xc3'
    dtor = bytearray(LIST_DTOR_BODY)
    dtor[4:8] = struct.pack('<i', clear_called - 0x2008)
    dtor[16:20] = struct.pack('<i', free_called - 0x2014)
    gate.memory[0x2000] = bytes(dtor)
    clear = bytearray(LIST_CLEAR_BODY)
    clear[18:22] = struct.pack('<i', 0x2200 - 0x2116)
    gate.memory[0x2100] = bytes(clear)
    gate.memory[0x2200] = b'\xc3'
    gate.pins.append(('_free', '0x00002200', 'crt free'))
    gate.row('_f', 0x1000, 6)
    gate.row(LIST_DTOR_OWNER, 0x2000, 23, source='Code/owner.cpp')
    gate.row(LIST_CLEAR_OWNER, 0x2100, 39, source='Code/owner.cpp')


def test_list_dtor_and_nested_clear_fold_pass(gate):
    list_fixture(gate)
    assert gate.gate()


def test_changed_list_dtor_byte_fails(gate):
    list_fixture(gate, dtor_body=b'\x57' + LIST_DTOR_BODY[1:])
    assert not gate.gate()


def test_changed_list_clear_byte_fails(gate):
    list_fixture(gate, clear_body=LIST_CLEAR_BODY[:-2] + b'\x5f\xc3')
    assert not gate.gate()


def test_list_dtor_free_must_reach_the_bound_free(gate):
    list_fixture(gate, free_called=0x2300)
    gate.memory[0x2300] = b'\xc3'
    assert not gate.gate()


def test_list_clear_must_reach_its_owner(gate):
    list_fixture(gate, clear_called=0x2101)
    assert not gate.gate()


def test_list_member_outside_the_families_is_not_admitted(gate):
    list_fixture(gate, nested=('?_M_create_node@?$list@PAVWidget@@V?$allocator@'
                               'PAVWidget@@@_STL@@@_STL@@IAEPAU?$_List_node@PAVWidget@@@2@ABQAVWidget@@@Z'))
    assert not gate.gate()


def test_missing_list_clear_owner_fails(gate):
    list_fixture(gate)
    gate.rows = [row for row in gate.rows if row['name'] != LIST_CLEAR_OWNER]
    assert not gate.gate()
