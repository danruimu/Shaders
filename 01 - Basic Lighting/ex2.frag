// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;
varying float znormal;

void main()
{;
	gl_FragColor = gl_Color * znormal;
}
