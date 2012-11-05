// simple vertex shader

uniform bool world;
varying vec3 N;
varying vec3 L;
varying vec3 V;

//gl_LightSource[0].position esta en eye space

void main()
{
	if(world) {	//world space
		vec4 camPosEye = {0.0,0.0,0.0,0.0};
		N = gl_Normal;
		V = gl_Vertex.xyz - (gl_ModelViewMatrixInverse * camPosEye).xyz;
		L = (gl_ModelViewMatrixInverse * gl_LightSource[0].position).xyz - V;
	} else {	//eye space
		N = gl_NormalMatrix * gl_Normal;
		V = (gl_ModelViewMatrix * gl_Vertex).xyz;
		L = gl_LightSource[0].position.xyz - V;
	}
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
}
