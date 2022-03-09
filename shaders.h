//
// Created by Pat on 4/4/2020.
//


#ifndef INC_3DGRAPHER_SHADERS_H
#define INC_3DGRAPHER_SHADERS_H
const char *fractalvertex = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 uvs;
    //uniform mat4 proj;
    out vec2 UV;
    void main()
    {
        gl_Position =vec4(aPos.x, aPos.y, aPos.z, 1.0);
        UV=vec2(uvs.x,uvs.y);
    }
    )glsl";
const char *mandelbrotfragment = R"glsl(
#version 330

uniform sampler2D tex;
uniform vec2 center;
uniform float scale;
uniform int iter;
uniform float ratio;
out vec4 color;
in vec2 UV;

void main() {
    vec2 z, c;

    c.x = ratio * (UV.x - 0.5) * scale - center.x;
    c.y = (UV.y - 0.5) * scale - center.y;
    int i;
    z = c;
    for(i=0; i<iter; i++) {
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (z.y * z.x + z.x * z.y) + c.y;

        if((x * x + y * y) > 4.0) break;
        z.x = x;
        z.y = y;
    }

    //color = vec4(float(i)/iter,0,0,1);
    color = texture(tex, vec2((i == iter ? 0.0 : float(i)) / 100.0),0 );
    //color = vec4(3*float(i)/iter,2*float(i)/iter,1*float(i)/iter,1);

}

    )glsl";const char *coolmandelbrotfragment = R"glsl(
#version 330

uniform sampler2D tex;
uniform vec2 center;
uniform float scale;
uniform int iter;
uniform float ratio;
out vec4 color;
in vec2 UV;

void main() {
    vec2 z, c;

    c.x = ratio * (UV.x - 0.5) * scale - center.x;
    c.y = (UV.y - 0.5) * scale - center.y;
    int i;
    z = c;
    for(i=0; i<iter; i++) {
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (z.y * z.x + z.x * z.y) + c.y;

        if((x * x + y * y) > 4.0) break;
        z.x = x;
        z.y = y;
    }

    //color = vec4(float(i)/iter,0,0,1);
    //color = texture(tex, vec2((i == iter ? 0.0 : float(i)) / 100.0),0 );
    color = vec4(3*float(i)/iter,2*float(i)/iter,1*float(i)/iter,1);

}

    )glsl";
const char *juliafragment = R"glsl(
#version 330

uniform sampler2D tex;
uniform vec2 center;
uniform float scale;
uniform int iter;
uniform float ratio;
out vec4 color;
in vec2 UV;

void main() {
	vec2 z;
	z.x = ratio * (UV.x - 0.5)* scale;
	z.y = (UV.y - 0.5)* scale;

	int i;
	for(i=0; i<iter; i++) {
		float x = (z.x * z.x - z.y * z.y) + center.x;
		float y = (z.y * z.x + z.x * z.y) + center.y;

		if((x * x + y * y) > 4.0) break;
		z.x = x;
		z.y = y;
	}

	color = texture(tex, vec2((i == iter ? 0.0 : float(i)) / 100.0),0 );
}

    )glsl";
#endif //INC_3DGRAPHER_SHADERS_H
