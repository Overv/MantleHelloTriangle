struct VOut {
    float4 position : SV_POSITION;
};

VOut VShader(uint id: SV_VertexID) {
    VOut output;

    if (id == 0) {
        output.position = float4(0.0, 0.5, 0.0, 1.0);
    } else if (id == 1) {
        output.position = float4(0.45, -0.5, 0.0, 1.0);
    } else {
        output.position = float4(-0.45, -0.5, 0.0, 1.0);
    }

    return output;
}