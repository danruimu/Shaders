// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;

varying vec3 N;
varying vec4 V;

void main()
{
	vec4 matEmission, matAmbient, matDiffuse, matSpecular;
	float matShininess;
	vec4 lightModelAmbient, lightAmbient, lightDiffuse, lightSpecular;
	vec4 Vobs, L;
	vec3 Nobs, R;

	//Obtenim les dades necessaries
	matEmission = gl_FrontMaterial.emission;
	matAmbient = gl_FrontMaterial.ambient;
	matDiffuse = gl_FrontMaterial.diffuse;
	matSpecular= gl_FrontMaterial.specular;
	matShininess = gl_FrontMaterial.shininess;
	lightModelAmbient = gl_LightModel.ambient;
	lightAmbient = gl_LightSource[0].ambient;
	lightDiffuse = gl_LightSource[0].diffuse;
	lightSpecular = gl_LightSource[0].specular;

	//Calculem Nobs, Vobs, L i R
	Nobs = normalize(N);
	Vobs = normalize(-V);
	L = normalize(gl_LightSource[0].position - V);
	R = 2*dot(Nobs, L.xyz)*Nobs-L.xyz;
	
	//Formula de Phong
	//Ke+Ka(Ma+Ia)+KdId(N·L)+KsIs(R·V)^s
	vec4 color = matEmission+matAmbient*(lightModelAmbient+lightAmbient);
	color += matDiffuse*lightDiffuse*(max(0.0,dot(Nobs,L.xyz)));
	color += matSpecular*lightSpecular*pow(max(0.0,dot(R,Vobs.xyz)),matShininess);
	
	gl_FragColor = color;
}
