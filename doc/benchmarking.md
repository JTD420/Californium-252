Benchmarking
============

Californium Core has an internal benchmarking framework, with benchmarks
for cryptographic algorithms (e.g. SHA1, SHA256, SHA512, RIPEMD160, Poly1305, ChaCha20), rolling bloom filter, coins selection,
thread queue, wallet balance.

Running
---------------------

For benchmarks purposes you only need to compile `californium_bench`. Beware of configuring without `--enable-debug` as this would impact
benchmarking by unlatching log printers and lock analysis.

    make -C src californium_bench

After compiling californium-core, the benchmarks can be run with:

    src/bench/bench_californium

The output will look similar to:
```
|             ns/byte |              byte/s | error % | benchmark
|--------------------:|--------------------:|--------:|:----------------------------------------------
|               64.13 |       15,592,356.01 |    0.1% | `Base58CheckEncode`
|               24.56 |       40,722,672.68 |    0.2% | `Base58Decode`
...
```

Help
---------------------

    src/bench/bench_californium --help

To print options like scaling factor or per-benchmark filter.

Notes
---------------------
More benchmarks are needed for, in no particular order:
- Script Validation
- Coins database
- Memory pool
- Cuckoo Cache
- P2P throughput

Going Further
--------------------

To monitor Californium Core performance more in depth (like reindex or IBD): https://github.com/chaincodelabs/californiumperf

To generate Flame Graphs for Californium Core: https://github.com/eklitzke/californium/blob/flamegraphs/doc/flamegraphs.md
