/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2021, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

// FRAGMENT SHADER - TERRAIN RENDERER

uniform vec2 uni_FogRange;
uniform vec3 uni_FogColor;

uniform vec4 uni_AlbedoColor;
uniform sampler2D uni_AlbedoTexture;
uniform sampler2D uni_DetailTexture;

uniform float uni_Roughness;
uniform float uni_Metalness;
uniform sampler2D uni_MaterialTexture;

uniform vec3 uni_EmissiveColor;
uniform sampler2D uni_EmissiveTexture;

uniform bool uni_TriplanarMode;
uniform float uni_TriplanarScale;

uniform float uni_AlphaScissor;

in VertexData
{
    vec4 Color;
    vec2 TexCoord0;
    vec2 TexCoord1;
    vec3 Normal;
    vec3 VertexCoord;
    vec3 VertexNormal;
    vec3 Position;
    vec3 ShadowCoords[4];
} data;

out vec4 out_FragColor;

vec3 Triplanar(vec3 position, vec3 normal)
{
    vec3 weights = normal * normal;

    vec3 sum = texture(uni_DetailTexture, position.yz).rgb * weights.x;
    sum += texture(uni_DetailTexture, position.zx).rgb * weights.y;
    sum += texture(uni_DetailTexture, position.xy).rgb * weights.z;

    return sum;
}

void main()
{
    vec4 albedo = data.Color * uni_AlbedoColor;

    albedo *= texture(uni_AlbedoTexture, data.TexCoord0);

    vec3 dirty = vec3(0.0);

    if (uni_TriplanarMode)
    {
        dirty = Triplanar(data.VertexCoord * uni_TriplanarScale, data.VertexNormal);
    }
    else
    {
        dirty = texture(uni_DetailTexture, data.TexCoord1).rgb;
    }

    albedo.rgb *= dirty;

    vec3 color = albedo.rgb;
    float alpha = albedo.a;

    if (uni_Lighting)
    {
        float shadow = CalculateShadow(data.ShadowCoords);

        shadow = mix(0.5, 1.0, shadow);

        vec3 normal = mix(-data.Normal, data.Normal, float(gl_FrontFacing));

        vec3 emissive = uni_EmissiveColor * texture(uni_EmissiveTexture, data.TexCoord0).rgb;

        vec3 params = texture(uni_MaterialTexture, data.TexCoord0).xyz;

        float ambientOcclusion = params.r;
        float roughness = uni_Roughness * params.g;
        float metalness = uni_Metalness * params.b;

        color = CalculateLighting(
                data.Position,
                normal,
                color,
                emissive,
                shadow,
                ambientOcclusion,
                roughness,
                metalness);
    }

    float dist = length(uni_CameraPosition - data.Position);
    float fogAmount = clamp((dist - uni_FogRange.x) / (uni_FogRange.y - uni_FogRange.x), 0.0, 1.0);

    color = mix(color, uni_FogColor, fogAmount);

    if (alpha < uni_AlphaScissor) discard;

    out_FragColor = vec4(color, alpha);
}