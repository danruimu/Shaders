// simple geometry shader

// these lines enable the geometry shader support.
#version 120
#extension GL_EXT_geometry_shader4 : enable
varying in vec3 vNormal[gl_VerticesIn];
uniform float speed;
uniform float angSpeed;
uniform float time;

void main( void )
{
	float t = mod(time,10.0);
	vec3 n = vec3(0,0,0);
	for(int i=0; i<gl_VerticesIn; i++) n+=vNormal[i];
	n /= gl_VerticesIn;
	n = normalize(n);
	
	vec3 bari = vec3(0,0,0);
	for(int i=0; i<gl_VerticesIn; i++) bari+=gl_PositionIn[i];
	bari /= gl_VerticesIn;

	float angRot = angSpeed * t;
	vec4 trans = vec4(speed*t*n, 0);
	mat3 rotZ = mat3(vec3(cos(angRot),sin(angRot),0),vec3(-sin(angRot),cos(angRot),0),vec3(0,0,1));

	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		gl_FrontColor  = gl_FrontColorIn[ i ];
		vec4 pos = gl_PositionIn[ i ]-vec4(bari,0);
		pos = vec4(rotZ *pos.xyz, pos.w);
		pos = pos + vec4(bari,0);
		pos += trans;
		gl_Position    = gl_ModelViewProjectionMatrix * pos;
		gl_TexCoord[0] = gl_TexCoordIn  [ i ][ 0 ];
		EmitVertex();
	}
}
