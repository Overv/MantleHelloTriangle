Introduction
============

This is an effort to implement Hello Triangle using the Mantle API by using the
API reference and reverse engineering public Mantle demos.

The [reference](http://www.amd.com/Documents/Mantle-Programming-Guide-and-API-Reference.pdf)
is used as primary resource, because it contains a full API reference and some
sample code. Unfortunately it misses a lot of the constant definitions, like
`GR_API_VERSION`, but these can be determined by disassembling the [Star Swarm Stress Test](http://store.steampowered.com/app/267130/) using a disassembler like [arkdasm](http://www.arkdasm.com/).

Status
======

The code is currently capable of creating a window using the SDL library and
clearing it to red using Mantle, while printing useful debug info.

![Preview of running program](http://i.imgur.com/sx12ubq.png)

There are two versions of the code: `main.cpp` and `verbose.cpp`. The code in
`main.cpp` is a minimalistic version of the code that makes it easier to see
what the steps to rendering something with Mantle are. The code in
`verbose.cpp`, which can be enabled with the `VERBOSE` preprocessor definition,
contains extra checks and prints extensive debug info as shown above.