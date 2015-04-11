struct VOut {
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

Buffer<float4> positions : register(t0);
Buffer<float4> colors : register(t1);

VOut VShader(uint id : SV_VertexID) {
    VOut output;

    output.position = positions.Load(id);
    output.color = colors.Load(id);

    return output;
}