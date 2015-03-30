// Textbook Lambertian reflectance.

varying vec3 N;
varying vec3 L;

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	vec4 eyeVertexPosition = gl_ModelViewMatrix * gl_Vertex;
	vec4 eyeLightPosition = gl_LightSource[0].position;
	
	N = normalize(gl_NormalMatrix * gl_Normal);
	L = normalize(eyeLightPosition.xyz - eyeVertexPosition.xyz);
}
