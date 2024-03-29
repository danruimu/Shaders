// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;
varying vec3 N;
varying vec3 L;
varying vec3 V;

vec4 light(vec3 N, vec3 V, vec3 L) {
	N = normalize(N); V = normalize(V); L = normalize(L);
	vec3 R = normalize(2.0 * dot(N,L)*N-L);
	float NdotL = max(0.0, dot(N,L));
	float RdotV = min(0.0, dot(R,V));
	float Idiff = NdotL;
	float Ispec = pow(RdotV, gl_FrontMaterial.shininess);
	return gl_FrontMaterial.emission + gl_FrontMaterial.ambient * gl_LightModel.ambient + gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * Idiff + gl_FrontMaterial.specular * gl_LightSource[0].specular * Ispec;
}

void main()
{
	gl_FragColor = light(N, V, L);
}
