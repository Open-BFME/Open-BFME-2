# BFME 2 consolidation shard 2/5, session 11

Two remaining destinations from the full allocation were checked with passing allocation checks, fresh scoped consolidation snapshots, `--plan` and `--merge --dry-run`:

- `mapper.cpp`: no donor accepted. `TextureMapperSlot8.cpp` needs `_bfme_mapper_v8` declared on `TextureMapperClass`; `TextureMapperFXShaderConvert.cpp` hits duplicate `Debug`/`StringBase`; `TextureMapperApply.cpp` fails bytes. LinkGuard reports the seed and all three donors census-linked; class-view reconciliation is reported for the texture-mapper classes.
- `AIWallBuilder.cpp`: the sole donor `Rva004E9BC6Dtor.cpp` is refused by LinkGuard: merging removes `??1Holder0C@@QAE@XZ` from a donor that links at the census. The seed and donor are census-linked.

Together with session 10 and the earlier shard handoffs, the full allocated listing is accounted for. No source changes, claims or merges remain from these trials.
