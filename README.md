This is an effort to implement Hello Triangle using the Mantle API by using the API reference and reverse engineering public Mantle demos.

The [reference](http://www.amd.com/Documents/Mantle-Programming-Guide-and-API-Reference.pdf) is used as primary resource, because it contains a full API reference and some sample code. Unfortunately it misses a lot of the constant definitions, like `GR_API_VERSION`, but these can be determined by disassembling the [Star Swarm Stress Test](http://store.steampowered.com/app/267130/) using a disassembler like [arkdasm](http://www.arkdasm.com/).
