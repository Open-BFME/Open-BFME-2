import os
import csv
import io
import runpy
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

SCRIPT = Path(__file__).resolve().parents[1] / 'delta_sources.py'
HEADER = b'name,export_rva,target_rva,target_size,source,status,notes\n'
A = b'a,,0x100,4,Code/a.cpp,matched,test\n'
B = b'b,,0x200,4,Code/b.cpp,matched,test\n'

class DeltaTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.git('init', '-q')
        self.git('config', 'user.email', 'test@example.invalid')
        self.git('config', 'user.name', 'test')
        (self.root / 'tools').mkdir()
        shutil.copyfile(SCRIPT, self.root / 'tools/delta_sources.py')
        (self.root / 'sentinel').write_text('test')
        self.git('add', 'sentinel')
        self.git('commit', '-qm', 'empty historical ledger')
        self.empty = self.git('rev-parse', 'HEAD').stdout.decode().strip()

    def git(self, *args):
        return subprocess.run(['git', '-C', str(self.root), *args], check=True, capture_output=True)

    def ledger(self, content, commit=False):
        path = self.root / 'reverse/functions.csv'
        path.parent.mkdir(exist_ok=True)
        path.write_bytes(content)
        self.git('add', 'reverse/functions.csv')
        if commit:
            self.git('commit', '-qm', 'ledger')
        return self.git('rev-parse', 'HEAD').stdout.decode().strip()

    def cli(self, *args):
        return subprocess.run([sys.executable, str(self.root / 'tools/delta_sources.py'), *args], capture_output=True)

    def refused(self, out):
        self.assertNotEqual(out.returncode, 0, out)
        self.assertEqual(out.stdout, b'')
        self.assertIn(b'delta_sources:', out.stderr)

    def test_unborn_head_staged(self):
        branch = self.git('symbolic-ref', 'HEAD').stdout.decode().strip()
        self.git('update-ref', '-d', branch)
        path = self.root / 'reverse/functions.csv'
        path.parent.mkdir()
        path.write_bytes(HEADER + A)
        self.git('add', 'reverse/functions.csv')
        out = self.cli('--staged')
        self.assertEqual((out.returncode, out.stdout), (0, b'Code/a.cpp\n'))
        self.refused(self.cli('--range', 'HEAD', 'HEAD'))

    def test_corrupt_head_commit(self):
        oid = self.git('rev-parse', 'HEAD').stdout.decode().strip()
        self.remove_object(oid)
        self.refused(self.cli('--staged'))

    def remove_object(self, oid):
        # Git writes loose objects read-only; Windows requires making the
        # isolated fixture's object writable before simulating corruption.
        path = self.root / '.git/objects' / oid[:2] / oid[2:]
        path.chmod(0o600)
        path.unlink()

    def test_absent_historical_and_index(self):
        out = self.cli('--staged')
        self.assertEqual((out.returncode, out.stdout), (0, b''))
        self.ledger(HEADER + A, True)
        out = self.cli('--range', self.empty, 'HEAD')
        self.assertEqual((out.returncode, out.stdout), (0, b'Code/a.cpp\n'))

    def test_invalid_old_and_new_refs(self):
        self.ledger(HEADER + A, True)
        for args in [('missing-ref', 'HEAD'), ('HEAD', 'missing-ref')]:
            with self.subTest(args=args): self.refused(self.cli('--range', *args))

    def test_reorder_deletion_and_new_row(self):
        self.ledger(HEADER + A + B, True)
        self.ledger(HEADER + B + A)
        out = self.cli('--staged')
        self.assertEqual((out.returncode, out.stdout), (0, b''))
        self.ledger(HEADER + B)
        out = self.cli('--staged')
        self.assertEqual((out.returncode, out.stdout), (0, b''))
        self.ledger(HEADER + B + A.replace(b'test', b'edited'))
        out = self.cli('--staged')
        self.assertEqual((out.returncode, out.stdout), (0, b'Code/a.cpp\n'))

    def test_legacy_note_quotes_preserve_authoritative_dialect(self):
        # Representative of functions.csv's existing notes: a closing quote
        # followed by unquoted prose, then literal quotes within that prose.
        row = (b'a,,0x100,4,Code/a.cpp,matched,'
               b'"retail class-name string ""W3DRopeDraw"""; '
               b'family evidence uses "W3DRopeDraw".\n')
        raw = HEADER + row
        expected = tuple(list(csv.reader(io.StringIO(raw.decode('utf-8'))))[1])
        self.assertEqual(len(expected), 7)
        self.ledger(raw)
        namespace = runpy.run_path(str(self.root / 'tools/delta_sources.py'))
        self.assertEqual(namespace['rows_at'](':reverse/functions.csv'), {expected})
        out = self.cli('--staged')
        self.assertEqual((out.returncode, out.stdout), (0, b'Code/a.cpp\n'))

    def test_invalid_csv_rejected(self):
        for raw in [b'', A, HEADER + b'a,b\n', HEADER + HEADER, HEADER + b'"unterminated', HEADER + A.replace(b'test', b'\xff'), HEADER + A.replace(b'test', b'"line\nline"')]:
            with self.subTest(raw=raw):
                self.ledger(raw)
                self.refused(self.cli('--staged'))

    def test_invalid_committed_csv(self):
        self.ledger(HEADER + b'a,b\n', True)
        self.refused(self.cli('--range', self.empty, 'HEAD'))

    def test_corrupt_index(self):
        (self.root / '.git/index').write_bytes(b'invalid index')
        self.refused(self.cli('--staged'))

    def test_missing_blob_is_not_absence(self):
        self.ledger(HEADER + A, True)
        oid = self.git('rev-parse', 'HEAD:reverse/functions.csv').stdout.decode().strip()
        self.remove_object(oid)
        self.refused(self.cli('--range', self.empty, 'HEAD'))
        self.refused(self.cli('--staged'))

    def test_unmerged_index(self):
        self.ledger(HEADER + A, True)
        oid = self.git('rev-parse', 'HEAD:reverse/functions.csv').stdout.decode().strip()
        self.git('update-index', '--force-remove', 'reverse/functions.csv')
        subprocess.run(['git', '-C', str(self.root), 'update-index', '--index-info'], input=f'100644 {oid} 1\treverse/functions.csv\n100644 {oid} 2\treverse/functions.csv\n'.encode(), check=True)
        self.refused(self.cli('--staged'))

    def test_symlink_ledger_rejected(self):
        path = self.root / 'reverse/functions.csv'
        path.parent.mkdir()
        # The guard checks Git's symlink mode, not the working-tree target.
        # Build that index entry directly so the test needs no OS privilege.
        oid = subprocess.check_output(
            ['git', '-C', str(self.root), 'hash-object', '-w', '--stdin'],
            input=b'../sentinel').decode().strip()
        self.git('update-index', '--add', '--cacheinfo',
                 f'120000,{oid},reverse/functions.csv')
        self.refused(self.cli('--staged'))

if __name__ == '__main__': unittest.main()
