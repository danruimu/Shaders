// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;
uniform sampler2D lego;
varying float ynormal;

void main()
{
	if(ynormal >= 0) {
		gl_FragColor = gl_Color*texture2D(lego, gl_TexCoord[0].st);
	} else {
		gl_FragColor = gl_Color;
	}
}
