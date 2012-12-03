// simple vertex shader
uniform bool eyespace;
uniform float time;
const float pi = 3.1416;

void main()
{
	vec4 posEye = gl_ModelViewMatrix * gl_Vertex;
	vec3 dist;
	if(eyespace) {
		dist = gl_Normal * (posEye.y*sin(2*pi*(1/(2*pi))*time));
	} else {
		dist = gl_Normal * (gl_Vertex.y*sin(2*pi*(1/(2*pi))*time));
	}
	vec4 newPos = vec4(gl_Vertex.xyz + dist, gl_Vertex.w);
	gl_Position    = gl_ModelViewProjectionMatrix * newPos;
	gl_FrontColor  = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
