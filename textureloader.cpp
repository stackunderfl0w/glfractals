//
// Created by Pat on 3/14/2020.
//
#include <GL/glew.h>

#include "textureloader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#include <gli/gli.hpp>
#include <stb/stb_image.h>
#include <iostream>

GLuint loadtexture(const char *file_name,bool flip)
{
    GLuint textureID;
    stbi_set_flip_vertically_on_load(flip);


    int width, height, nrChanels;

    unsigned char* pixels = stbi_load(file_name, &width, &height, &nrChanels, 0);

    if(pixels != nullptr)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        std::cout << "Could not load file " << file_name << std::endl;
    }

    stbi_image_free(pixels);

    return textureID;
}
GLuint loadtexture_no_filter(const char *file_name,bool flip)
{
    GLuint textureID;
    stbi_set_flip_vertically_on_load(flip);


    int width, height, nrChanels;

    unsigned char* pixels = stbi_load(file_name, &width, &height, &nrChanels, 0);

    if(pixels != nullptr)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Could not load file " << file_name << std::endl;
    }

    stbi_image_free(pixels);

    return textureID;
}
GLuint loadtexture1D(const char *file_name,bool flip)
{
    GLuint textureID;
    stbi_set_flip_vertically_on_load(flip);


    int width, height, nrChanels;

    unsigned char* pixels = stbi_load(file_name, &width, &height, &nrChanels, 0);

    if(pixels != nullptr)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage1D(GL_TEXTURE_2D, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        //glGenerateMipmap(GL_TEXTURE_1D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Could not load file " << file_name << std::endl;
    }

    stbi_image_free(pixels);

    return textureID;
}
GLuint loadtexture_transparent(const char *file_name)
{
    GLuint textureID;
    stbi_set_flip_vertically_on_load(true);


    int width, height, nrChanels;

    unsigned char* pixels = stbi_load(file_name, &width, &height, &nrChanels, 0);

    if(pixels != nullptr)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        std::cout << "Could not load file " << file_name << std::endl;
    }

    stbi_image_free(pixels);

    return textureID;
}
GLuint loadtexture_transparent_no_filter(const char *file_name,bool flip)
{
    GLuint textureID;
    stbi_set_flip_vertically_on_load(flip);


    int width, height, nrChanels;

    unsigned char* pixels = stbi_load(file_name, &width, &height, &nrChanels, 0);

    if(pixels != nullptr)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    else
    {
        std::cout << "Could not load file " << file_name << std::endl;
    }

    stbi_image_free(pixels);

    return textureID;
}