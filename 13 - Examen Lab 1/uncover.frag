// simple fragment shader
// 'time' contains seconds since the program was linked.
uniform float time;
varying float Xndc;

void main()
{
	float timeRel = time - 1;
	if(Xndc > timeRel) discard;
	gl_FragColor = vec4(0,0,1,1);
}
