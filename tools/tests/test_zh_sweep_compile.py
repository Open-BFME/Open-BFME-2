import sys
import unittest
import tempfile
import threading
import contextlib
import io
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import zh_sweep as zh


class CompilePoolTests(unittest.TestCase):
    def run_case(self, force):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            cache = root / 'objects'
            cache.mkdir()
            src = root / 'src'
            src.mkdir()
            names = ['good', 'cached', 'failed']
            sources = []
            for name in names:
                source = src / (name + '.cpp')
                source.write_text('// standalone fixture\n')
                sources.append(source)

            def obj(source):
                return cache / (zh.object_stem(source.relative_to(root)) + '.obj')

            for source in sources[1:]:
                obj(source).write_bytes(b'old')
                obj(source).with_suffix('.deps.json').write_text('old receipt')
            visits = []
            lock = threading.Lock()

            def compile_fixture(source, output):
                with lock:
                    visits.append(source.stem)
                if source.stem == 'failed':
                    output.write_bytes(b'partial invalid object')
                    raise SystemExit(1)
                output.write_bytes(b'new')
                output.with_suffix('.deps.json').write_text('new receipt')

            log = io.StringIO()
            with (patch.object(zh, 'ROOT', root),
                  patch.object(zh, 'ZH', root),
                  patch.object(zh, 'OBJ_DIR', cache),
                  patch.object(zh, 'SUBTREES', ['src']),
                  patch.object(zh.build, 'source_needs_stlport', return_value=False),
                  patch.object(zh.build, 'compile_source', side_effect=compile_fixture),
                  contextlib.redirect_stdout(log)):
                zh.do_compile(SimpleNamespace(force=force, limit=0, jobs=3))
            if force:
                self.assertCountEqual(visits, names)
                self.assertFalse(obj(sources[2]).exists())
                self.assertFalse(obj(sources[2]).with_suffix('.deps.json').exists())
                self.assertEqual(obj(sources[0]).read_bytes(), b'new')
                self.assertEqual(obj(sources[1]).read_bytes(), b'new')
                self.assertIn('2 built, 0 cached, 1 failed', log.getvalue())
            else:
                self.assertEqual(visits, ['good'])
                self.assertEqual(obj(sources[1]).read_bytes(), b'old')
                self.assertEqual(obj(sources[2]).read_bytes(), b'old')
                self.assertIn('1 built, 2 cached, 0 failed', log.getvalue())

    def test_forced_failure_discards_old_object_and_receipt(self):
        self.run_case(True)

    def test_cached_units_are_preserved_without_force(self):
        self.run_case(False)

    def test_invalid_pool_refused_before_cache_mutation(self):
        with patch.object(zh, 'OBJ_DIR', Path('does-not-exist-test-cache')):
            with self.assertRaises(SystemExit):
                zh.do_compile(SimpleNamespace(force=True, limit=0, jobs=0))


if __name__ == '__main__':
    unittest.main()
