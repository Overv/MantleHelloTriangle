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
Other values, like `GR_MAX_HEAPS` can be figured out by querying for the struct
size with functions like `grGetObjectInfo`.

The intermediate language used for Mantle shaders is a subset of AMD IL, for
which CodeXL contains [a compiler](http://developer.amd.com/community/blog/2014/05/16/codexl-game-developers-analyze-hlsl-gcn/).
The disassembly it outputs is incorrect, but the bytecode itself is valid.
Mantle appears to accept this code without problems.

Status
------

The code is capable of creating a window using the SDL library, clearing it to
black and rendering a per-vertex colored triangle using Mantle.

![Preview of running program](http://i.imgur.com/r5PxoRv.png)

The vertex shader reads the position (`float4`) and color (`float4`) from a
buffer using the `SV_VertexID` built-in variable. Each buffer is assigned a
memory view into GPU memory filled with the following data:

    float vertices[] = {
        // Positions
        0.0, 0.5, 0.0, 1.0,
        0.5, -0.5, 0.0, 1.0,
        -0.5, -0.5, 0.0, 1.0,

        // Colors
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0
    };

The next step is to clean up the code.

Shader compilation
------------------

Shaders are written in HLSL and compiled to AMD Intermediate Language using
the `CodeXLAnalyzer.exe` tool included in CodeXL using the `--il` flag. A batch
script for doing this is included in the `shaders` folder. The hex code on the
right side can then be converted to a binary file using the `output2binary.py`
script, which takes the IL output file name as parameter. The binaries can then
be loaded into Mantle using `grCreateShader`, as is demonstrated in the code.

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
