// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;
vec4 black = {0.0, 0.0, 0.0, 1.0};
vec4 white = {0.75, 0.75, 0.75, 1.0};

void main()
{
	vec4 color;

	float posX = gl_TexCoord[0].s;
	float posY = gl_TexCoord[0].t;

	// Nos aseguramos que posX y posY esten entre 0 y 1
	posX = posX - floor(posX);
	posY = posY - floor(posY);

	if(posX >= 0.5) posX -= 0.5;
	if(posY >= 0.5) posY -= 0.5;
	
	if(posX >= 0.25) posX -= 0.25;
	if(posY >= 0.25) posY -= 0.25;
	
	if(posX > 0.125) {
		if(posY > 0.125) color = white;
		else color = black;
	} else {
		if(posY <= 0.125) color = white;
		else color = black;
	}

	gl_FragColor = color;
}
