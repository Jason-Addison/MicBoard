#version 400

in vec4 colourPass;
out vec4 frag_colour;

void main()
{
	frag_colour = vec4(colourPass.xyz, 1);
}