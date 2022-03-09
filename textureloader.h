//
// Created by Pat on 3/14/2020.
//

#ifndef GL_TEXTURELOADER_H
#define GL_TEXTURELOADER_H

GLuint loadtexture(const char *file_name,bool flip);

GLuint loadtexture_no_filter(const char *file_name,bool flip);

GLuint loadtexture1D(const char *file_name,bool flip);

GLuint loadtexture_transparent(const char *file_name);

GLuint loadtexture_transparent_no_filter(const char *file_name,bool flip);


#endif //GL_TEXTURELOADER_H
