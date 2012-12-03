// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;

varying vec3 posV;

void main()
{	
	vec3 dX = dFdx(posV);
	vec3 dY = dFdy(posV);
	vec3 normal = normalize(cross(dX, dY));
	gl_FragColor = gl_Color * normal.z;
}

