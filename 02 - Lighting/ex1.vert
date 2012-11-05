// simple vertex shader

attribute vec4 matEmision;	//emissió material
attribute vec4 matAmbient;	//reflectivitat ambient material
attribute vec4 matDifosa;	//reflectivitat difosa material
attribute vec4 matSpecul;	//reflectivitat especular material
attribute float matShin;	//shininess del material
attribute vec4 iluAmbient;	//prop. ambient de la llum
attribute vec4 iluDifosa;	//prop. difosa de la llum
attribute vec4 iluSpecul;	//prop. especular de la llum
attribute vec4 iluAmbientModel;	//llum ambient del model
attribute vec3 normal;		//normal unitari en (eye space)
attribute vec4 dirLight;	//vect. uni. cap a la llum(eye space)
attribute vec3 h;	//h = (Vobs + dirLight)/mod(h)

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	//Obtenim les dades necessaries
	matEmision = gl_FrontMaterial.emission;
	matAmbient = gl_FrontMaterial.ambient;
	matDifosa = gl_FrontMaterial.diffuse;
	matSpecul = gl_FrontMaterial.specular;
	matShin = gl_FrontMaterial.shininess;
	iluAmbient = gl_LightSource[0].ambient;
	iluDifosa = gl_LightSource[0].diffuse;
	iluSpecul = gl_LightSource[0].specular;
	iluAmbientModel = gl_LightModel.ambient;
	
	//Obtenim N (normal), L (dirLight) i H (h)
	normal = normalize(gl_NormalMatrix * gl_Normal);
	dirLight = normalize(gl_LightSource[0].position - gl_ModelViewMatrix * gl_Vertex);
	vec4 V = gl_ModelViewMatrix * gl_Vertex;
	V = normalize(-V);
	h = (dirLight + V).xyz;
	h = normalize(h);

	/* Formula Blinn-Phong
	*  Ke + Ka*(Ma + Ia) + Kd*Id*(N*L)+ Ks*Is*(N*H)^s */
	vec4 aux = matEmision + matAmbient * (iluAmbientModel + iluAmbient);
	aux += (matDifosa * iluDifosa * (max(0.0, dot(normal, dirLight.xyz))));
	aux += (matSpecul * iluSpecul * pow((max(0.0, dot(normal, h))), matShin));

	gl_FrontColor  = aux;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
