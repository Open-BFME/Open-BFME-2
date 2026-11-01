#!/usr/bin/env python3
"""Content-keyed private class inventory shared by surveys and contract discovery.

Read current source contents on every query, so dirty edits, same-stat rewrites,
rebases and deleted files cannot reuse stale declarations. Only changed contents
are reparsed. A cheap head index lets a first single-class query avoid parsing
unrelated bodies; a full survey fills the same declaration cache for later queries.
This is discovery evidence, never a replacement for compiled layout/byte checks.
"""
import collections
import hashlib
import re
from pathlib import Path

import class_layouts
import picker_cache

ROOT = Path(__file__).resolve().parents[1]
COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)
CODE = [__file__, class_layouts.__file__]
HEADS = picker_cache.FileMemo("class-inventory-heads", CODE)
VIEWS = picker_cache.FileMemo("class-inventory-views", CODE)


def parse(text):
    """Same namespace-scope bodies and normalized digests as class_views.survey."""
    out = {}
    for name, start, end, _ in class_layouts.class_body_spans(text):
        body = " ".join(COMMENT.sub("", text[start:end]).split())
        out.setdefault(name, hashlib.sha1(body.encode("latin-1")).hexdigest()[:10])
    return out


def inventory(sources, root=ROOT, wanted=None):
    """{class: {source: declaration digest}}, optionally restricted to wanted names.

    Cache keys use contents, not paths or timestamps. The cheap head scan can have
    false positives (comments, locals, templates), but only the full scope parser
    admits a body. Missing files are omitted just as by the uncached survey.
    """
    wanted = None if wanted is None else set(wanted)
    out = collections.defaultdict(dict)
    if wanted == set():
        return out
    needle = next(iter(wanted)) if wanted is not None and len(wanted) == 1 else None
    for source in sources:
        try:
            text = (Path(root) / source).read_text(encoding="latin-1")
        except OSError:
            continue
        # A parser-produced name is a contiguous spelling in its source. Avoid
        # filling a whole head index just to answer the first single-class query.
        if needle is not None and needle not in text:
            continue
        key = picker_cache.text_key(text)
        if wanted is not None:
            heads = HEADS.get(key, lambda: sorted({m.group("name") for m in class_layouts.HEAD.finditer(text)}))
            if wanted.isdisjoint(heads):
                continue
        declarations = VIEWS.get(key, lambda: parse(text))
        if wanted is None:
            HEADS.get(key, lambda: sorted(declarations))
        for name, digest in declarations.items():
            if wanted is None or name in wanted:
                out[name][source] = digest
    return out


def save():
    HEADS.save()
    VIEWS.save()
