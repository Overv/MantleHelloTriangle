Introduction
------------

This is an effort to implement Hello Triangle using the Mantle API by using the
API reference and reverse engineering public Mantle demos.

The [reference](http://www.amd.com/Documents/Mantle-Programming-Guide-and-API-Reference.pdf)
is used as primary resource, because it contains a full API reference and some
sample code. Unfortunately it misses a lot of the constant definitions, like
`GR_API_VERSION`, but these can be determined by creating a proxy mantle64.dll
that logs calls and the contents of structs. This approach is currently used
on the [Star Swarm Stress Test](http://store.steampowered.com/app/267130/) to
figure out what calls and data are needed to render a triangle on the screen.

The intermediate language used for Mantle shaders is a subset of AMD IL, for
which CodeXL contains [a compiler](http://developer.amd.com/community/blog/2014/05/16/codexl-game-developers-analyze-hlsl-gcn/).
The disassembly it outputs is incorrect, but the bytecode itself is valid.
Mantle appears to accept bytecode from this compiler, but nothing has been
rendered with it yet.

Status
------

The code is currently capable of creating a window using the SDL library and
clearing it to red using Mantle, while printing useful debug info.

![Preview of running program](http://i.imgur.com/sx12ubq.png)

There are two versions of the code: `main.cpp` and `verbose.cpp`. The code in
`main.cpp` is a minimalistic version of the code that makes it easier to see
what the steps to rendering something with Mantle are. The code in
`verbose.cpp`, which can be enabled with the `VERBOSE` preprocessor definition,
contains extra checks and prints extensive debug info as shown above.

Once enough info and shader bytecode has been extracted from the aforementioned
Mantle demo, the code here will be updated to render a (textured) triangle.

License
-------

    Copyright (c) 2015 Alexander Overvoorde

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
