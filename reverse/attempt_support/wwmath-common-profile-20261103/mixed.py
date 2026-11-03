exec(open('build/wwmath-profile-20261103/probe.py').read().split('variants={')[0])
for extra in ['-Ot','-Ob2','-Oi -Ot','-Os -Oy -Ob2','-Og -Ot -Ob2','-O2 -Os -Ob1','-O2 -Os -Oy','-O2 -Os -Og-']:
 flags='-O1 -G7 -arch:SSE -MD '+extra
 w=T.Verifier(names[0],flags=flags)
 got=w.matched(source,rows)
 print(extra,sorted(got or []),flush=True)
 if len(got or [])==len(rows):Path('build/wwmath-profile-20261103/winner.cpp').write_text(w.effective(source,rows))
