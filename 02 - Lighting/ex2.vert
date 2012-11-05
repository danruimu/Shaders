// simple vertex shader

attribute vec4 matEmission;	//emissió del material
attribute vec4 matAmbient;	//refl. ambient material
attribute vec4 matDiffuse;	//refl. difosa material
attribute vec4 matSpecular;	//refl. especular material
attribute float matShininess;	//shininess del material
attribute vec4 lightAmbientModel;	//ilu. ambient model
attribute vec4 lightAmbient;	//ilu. ambient LIGHT0
attribute vec4 lightDiffuse;	//ilu. difosa LIGHT0
attribute vec4 lightSpecular;	//ilu.	especular LIGHT0
attribute vec3 N;	//vector normal unitari
attribute vec4 L;	//vector unitari cap a font de llum
attribute vec4 V;	//vector unitari cap a la càmara
attribute vec3 R;	//R = 2(N·L)N-L

void main()
{
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;

	//Obtenim dades necessaries
	matEmission = gl_FrontMaterial.emission;
	matAmbient = gl_FrontMaterial.ambient;
	matDiffuse = gl_FrontMaterial.diffuse;
	matSpecular = gl_FrontMaterial.specular;
	matShininess = gl_FrontMaterial.shininess;
	lightAmbientModel = gl_LightModel.ambient;
	lightAmbient = gl_LightSource[0].ambient;
	lightDiffuse = gl_LightSource[0].diffuse;
	lightSpecular = gl_LightSource[0].specular;

	//Calculem N, L, V i R
	N = normalize(gl_NormalMatrix * gl_Normal);
	L = normalize(gl_LightSource[0].position - gl_ModelViewMatrix * gl_Vertex);
	V = gl_ModelViewMatrix * gl_Vertex;
	V = normalize(-V);
	R = 2 * dot(N, L.xyz) * N - L.xyz;
	
	//Formula de Phong
	//Ke+Ka(Ma+Ia)+KdId(N·L)+KsIs(R·V)^s
	vec4 color = matEmission + matAmbient * (lightAmbientModel + lightAmbient);
	color += matDiffuse * lightDiffuse * max(0.0, dot(N, L.xyz));
	color += matSpecular * lightSpecular * pow(max(0.0, dot(R, V.xyz)), matShininess);

	gl_FrontColor  = color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
