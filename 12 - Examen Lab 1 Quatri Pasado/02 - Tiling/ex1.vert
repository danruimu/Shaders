// simple vertex shader

uniform int tiles;

void main()
{
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec4 textura = gl_MultiTexCoord0;
	textura.s *= tiles;
	textura.t *= tiles;
	gl_TexCoord[0] = textura;
}
