struct VertexShaderInput
{
    float4 position : POSITION;
    float4 color    : COLOR;
};

struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR;
};

PixelShaderInput VSMain(VertexShaderInput input)
{
    PixelShaderInput output;

    input.position.w = 1.0f;

    output.position = input.position;
    output.color    = input.color;

    return output;
}

float4 PSMain(PixelShaderInput input) : SV_TARGET
{
    return input.color;
}