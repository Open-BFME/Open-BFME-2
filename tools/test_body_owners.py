#!/usr/bin/env python3
"""Regression coverage for audited body ownership, including a new alias spelling."""
import unittest
import check_csv

OWNER = (b'target_rva,name,target_size,source,evidence\n'
         b'0x00000100,retained,12,Code/retained.cpp,Target ABI and caller evidence\n')
HEADER = b'name,export_rva,target_rva,target_size,source,status,notes\n'
ROW = b'retained,,0x00000100,12,Code/retained.cpp,matched,\n'

class BodyOwnerTests(unittest.TestCase):
    def check(self, owners=OWNER, rows=ROW):
        problems = []
        check_csv.check_body_owners(owners, HEADER + rows, problems)
        return problems

    def test_retained_owner(self):
        self.assertEqual(self.check(), [])

    def test_new_spelling_cannot_duplicate_audited_body(self):
        self.assertTrue(self.check(rows=ROW + b'new_alias,,0x00000100,12,Code/other.cpp,matched,\n'))

    def test_replaced_owner_requires_updated_evidence_record(self):
        renamed = ROW.replace(b'retained', b'renamed')
        self.assertTrue(self.check(rows=renamed))
        self.assertEqual(self.check(owners=OWNER.replace(b'retained', b'renamed'), rows=renamed), [])

    def test_rehome_requires_owner_update(self):
        self.assertTrue(self.check(rows=ROW.replace(b'Code/retained.cpp', b'Code/home.cpp')))

    def test_missing_owner(self):
        self.assertTrue(self.check(rows=b''))

    def test_duplicate_registry_owner(self):
        self.assertTrue(self.check(owners=OWNER + OWNER.splitlines(keepends=True)[1]))

    def test_unrelated_fold_is_outside_this_audit(self):
        twins = (b'fold_a,,0x00000200,12,Code/a.cpp,matched,\n'
                 b'fold_b,,0x00000200,12,Code/b.cpp,matched,\n')
        self.assertEqual(self.check(rows=ROW + twins), [])

    def test_historical_revision_without_registry(self):
        self.assertEqual(self.check(owners=b''), [])

    def test_registry_extent_and_status_are_checked(self):
        self.assertTrue(self.check(rows=ROW.replace(b',12,', b',13,')))
        self.assertTrue(self.check(rows=ROW.replace(b',matched,', b',unmatched,')))

if __name__ == '__main__':
    unittest.main()
