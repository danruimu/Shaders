// simple vertex shader
varying vec3 vNormal;

void main()
{
	vNormal = gl_Normal;
	gl_Position    = gl_Vertex;
	gl_FrontColor  = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
