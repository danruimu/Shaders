// simple vertex shader

varying vec3 N;
varying vec4 V;

void main()
{
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
	N = gl_NormalMatrix * gl_Normal;
	V = gl_ModelViewMatrix * gl_Vertex;
}
