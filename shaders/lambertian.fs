// Textbook Lambertian reflectance.

varying vec3 N;
varying vec3 L;

uniform sampler2D texMap;

void main() {
	 vec3 normal = normalize(N);
	 vec3 light = normalize(L);
	 vec4 diffuse = max(dot(normal, light), 0.0) * gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	 vec4 texColor = texture2D(texMap, vec2(gl_TexCoord[0]));
	 gl_FragColor = diffuse * texColor;
}
