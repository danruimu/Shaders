// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;
uniform int N;
vec4 black = {0.0, 0.0, 0.0, 1.0};
vec4 white = {0.75, 0.75, 0.75, 1.0};

void main()
{
	vec4 color;

	float tamN = 1.0 / float(N);

	float posX = gl_TexCoord[0].s;
	float posY = gl_TexCoord[0].t;

	// Nos aseguramos que posX y posY esten entre 0 y 1
	posX = fract(posX);
	posY = fract(posY);

	if(posX > 2*tamN) {
		posX = posX - (2 * tamN * floor(posX/(2*tamN)));
	}
	if(posY > 2*tamN) {
		posY = posY - (2 * tamN * floor(posY/(2*tamN)));
	}
	
	if(posX > tamN) {
		if(posY > tamN) color = white;
		else color = black;
	} else {
		if(posY <= tamN) color = white;
		else color = black;
	}

	gl_FragColor = color;
}
