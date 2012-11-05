// simple geometry shader

// these lines enable the geometry shader support.
#version 120
#extension GL_EXT_geometry_shader4 : enable
varying in vec3 vNormal[gl_VerticesIn];
uniform float speed;
uniform float time;

void main( void )
{
	vec3 n = vec3(0,0,0);
	for(int i=0; i<gl_VerticesIn; i++) n += vNormal[i];
	n /= gl_VerticesIn;

	vec4 trans = vec4(speed*time*n, 0);

	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		gl_FrontColor  = gl_FrontColorIn[ i ];
		gl_Position    = gl_ModelViewProjectionMatrix * (gl_PositionIn[ i ]+trans);
		gl_TexCoord[0] = gl_TexCoordIn  [ i ][ 0 ];
		EmitVertex();
	}
}
