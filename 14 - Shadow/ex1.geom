// simple geometry shader

// these lines enable the geometry shader support.
#version 120
#extension GL_EXT_geometry_shader4 : enable

void main( void )
{
	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		gl_FrontColor  = gl_FrontColorIn[ i ];
		gl_Position    = gl_PositionIn  [ i ];
		EmitVertex();
	}
	EndPrimitive();
	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		vec4 pos = gl_ModelViewProjectionMatrixInverse * gl_PositionIn[i];
		pos.y = -2.0;
		pos = gl_ModelViewProjectionMatrix * pos;
		gl_FrontColor  = vec4(0,0,0,1);
		gl_Position    = pos;
		EmitVertex();
	}
	EndPrimitive();	
}
