// Textbook Lambertian reflectance. I'll do something more interesting when I have time.

varying vec3 N;
varying vec3 L;

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	vec4 eyePosition = gl_ModelViewMatrix * gl_Vertex;
	vec4 eyeLightPos = gl_LightSource[0].position;
	
	N = normalize(gl_NormalMatrix * gl_Normal);
	L = normalize(eyeLightPos.xyz - eyePosition.xyz);	
}
