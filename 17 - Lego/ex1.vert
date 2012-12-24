// simple vertex shader
uniform sampler2D lego;
varying float ynormal;

void main()
{
	gl_Position    = gl_Vertex;
	ynormal = gl_Normal.y;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_FrontColor  = vec4((gl_NormalMatrix*gl_Normal).z);
}
