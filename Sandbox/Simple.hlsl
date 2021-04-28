cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

struct VertexShaderInput
{
    float3 position : POSITION;
    float4 color    : COLOR;
};

struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR;
};

struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR;
};

VertexShaderOutput VSMain(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    float4 position = float4(input.position, 1.0f);

    position = mul(position, model);
    position = mul(position, view);
    position = mul(position, projection);
    output.position = position;

    output.color = input.color;

    return output;
}

float4 PSMain(PixelShaderInput input) : SV_TARGET
{
    return input.color;
}