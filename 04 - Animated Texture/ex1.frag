// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;
uniform sampler2D sampler;
uniform float speed;

void main()
{
	gl_FragColor = gl_Color * texture2D(sampler, vec2(gl_TexCoord[0].s + time*speed, gl_TexCoord[0].t + time*speed));
}
