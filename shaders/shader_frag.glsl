#version 410

layout(std140) uniform Material // Must match the GPUMaterial defined in src/mesh.h
{
    vec3 kd;
	vec3 ks;
	float shininess;
	float transparency;
};

struct Light {
    vec4 color;
    vec4 pos;    // w unused
    vec4 normal; // w unused
    int type;
}; // 64B


layout(std140) uniform lightBuffer
{
    int light_count;
    Light lights[8];
};

uniform sampler2D colorMap;
uniform bool hasTexCoords;
uniform bool useMaterial;
uniform vec3 cameraPos;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

layout(location = 0) out vec4 fragColor;

Light getLight(int index)
{
    Light l = lights[index];

    vec3 LtoFrag = fragPosition - l.pos.xyz;

    if (l.type == 1) {
        l.normal.xyz = normalize(LtoFrag);
    }

    if (l.type == 1 || l.type == 3) {
        float dist = length(LtoFrag);
        //l.color.a = l.color.a / (1 + 0.09 * dist + 0.0032 * dist * dist);
    }

    return l;
}

vec3 normal()
{
    return normalize(fragNormal);
}

vec3 blinnPhong(int i) {
    Light light = getLight(i);

    vec3 N = normal();
    vec3 V = normalize(fragPosition - cameraPos);
    vec3 L = normalize(light.normal.xyz);
    vec3 H = normalize(L + V);

    float NdotL = max(-dot(N, L), 0.0);
    float NdotH = (NdotL > 0.0) ? max(dot(N, H), 0.0) : 0.0;

    vec3 lc = light.color.rgb;
    float li = light.color.a;

    vec3 diffuse  = kd * lc * NdotL;
    vec3 specular = ks * lc * pow(NdotH, shininess);

    return (diffuse + specular) * li;
}


vec4 color()
{
    vec3 color = vec3(0);
    for (int i = 0; i < light_count; i++) {
        color += blinnPhong(i);
    }
    return vec4(color, 1);
}

void main()
{
    if (hasTexCoords)       { fragColor = vec4(texture(colorMap, fragTexCoord).rgb, 1);}
    else if (useMaterial)   { fragColor = color();}
    else                    { fragColor = vec4(normal(), 1); } // Output color value, change from (1, 0, 0) to something else
}
