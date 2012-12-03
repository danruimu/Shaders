// simple vertex shader

varying float znormal;

void main()
{
	znormal = (gl_NormalMatrix * gl_Normal).z;	
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_FrontColor  = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
