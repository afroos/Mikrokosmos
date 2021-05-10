cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

Texture2D    textureData  : register(t0);
SamplerState samplerState : register(s0);

struct VertexShaderInput
{
    float3 position           : POSITION;
    float3 normal             : NORMAL;
    float2 textureCoordinates : TEXCOORD0;
};

struct VertexShaderOutput
{
    float4 position           : SV_POSITION;
    float3 normal             : NORMAL;
    float2 textureCoordinates : TEXCOORD0;
};

struct PixelShaderInput
{
    float4 position           : SV_POSITION;
    float3 normal             : NORMAL;
    float2 textureCoordinates : TEXCOORD0;
};

VertexShaderOutput VSMain(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    float4 position = float4(input.position, 1.0f);

    position = mul(position, model);
    position = mul(position, view);
    position = mul(position, projection);
    output.position = position;

    output.textureCoordinates = input.textureCoordinates;

    float4 normal = float4(normalize(input.normal), 0.0f);
    normal = mul(normal, model);
    output.normal = normalize(normal.xyz);

    return output;
}

float4 PSMain(PixelShaderInput input) : SV_TARGET
{
    float3 lightDirection = normalize(float3(1, -1, 0));
    float4 texelColor = textureData.Sample(samplerState, input.textureCoordinates);
    float lightMagnitude = 0.8f * saturate(dot( input.normal, -lightDirection)) + 0.2f;
    return texelColor * lightMagnitude;
}