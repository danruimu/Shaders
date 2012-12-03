// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;
uniform int n; //1 de cada n línies no es mostraran

void main()
{	
	if(int(gl_FragCoord.y) % n != 0) discard;

	gl_FragColor = gl_Color;
}