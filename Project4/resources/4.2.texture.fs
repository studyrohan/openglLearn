#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float scale;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	vec2 vec = vec2(1.0-TexCoord.x,TexCoord.y);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec), scale);
}