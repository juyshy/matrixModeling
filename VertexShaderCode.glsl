#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;
// mat4 takes 4 locations: 2,3,4,5
in layout(location=2) mat4 transformationMatrix;

uniform mat4 fullTransformMatrix;

out vec3 theColor;

void main()
{
 vec4 v = vec4(position,  1.0);
 
 gl_Position = transformationMatrix * v;
 theColor = vertexColor;
}