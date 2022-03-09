#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderloader.h"
#include "shaders.h"
#include "shader.h"
#include "textureloader.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
float f;
int iter=5;
float scale=3.0;
glm::vec2 center(1,0);
int sdl_interval_mode=1;
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
int fractal=0;
int main(int argc, char *argv[]){
    SDL_Window *window=SDL_CreateWindow("Stackunderfl0w opengl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    float vertices[] = {
            1,  1, 0.0f,  // top right
            1, -1, 0.0f,  // bottom right
            -1, -1, 0.0f,  // bottom left
            -1,  1, 0.0f   // top left
    };
    float UVs[] = {
            1, 1,  // top right
            1, 0,  // bottom right
            0, 0,  // bottom left
            0,  1   // top left
    };
    GLuint vertexquadsbuffer;
    glGenBuffers(1, &vertexquadsbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexquadsbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , &vertices[0], GL_STATIC_DRAW);
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), &UVs[0], GL_STATIC_DRAW);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330");
    // Our state
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.4f, 1.00f);

    //GLuint programID=LoadShaders_text(simplevertex,simpletexturefragment);
    Shader *programID;
    Shader mandelbrotshader(fractalvertex,mandelbrotfragment);
    Shader coolmandelbrotshader(fractalvertex,coolmandelbrotfragment);
    Shader juliashader(fractalvertex,juliafragment);
    programID=&mandelbrotshader;
    GLuint Texture= loadtexture("pal.png",false);
    //GLuint Texture= loadtexture("font.png",false);
    GLuint TextureID  = glGetUniformLocation(programID->ID, "tex");
    SDL_Event windowEvent;
    bool running = true;
    double fps;
    while(running){
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        SDL_GetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
        glViewport( 0.f, 0.f, SCR_WIDTH, SCR_HEIGHT );
        SDL_PumpEvents();
        while(SDL_PollEvent(&windowEvent)){
            if (windowEvent.type == SDL_QUIT){
                running=false;
            }
            if (windowEvent.type == SDL_KEYUP &&
                windowEvent.key.keysym.sym == SDLK_ESCAPE){
                running=false;
            }
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                if(windowEvent.type == SDL_MOUSEMOTION){
                    center.x+=scale*windowEvent.motion.xrel/SCR_HEIGHT;
                    center.y-=scale*windowEvent.motion.yrel/SCR_HEIGHT;
                }
            }

            if(windowEvent.type == SDL_MOUSEWHEEL){
                if(windowEvent.wheel.y>0){
                    scale*=.9;
                } else{
                    scale/=.9;
                }
            }
        }


        programID->use();
        programID->setVec2("center",center);
        programID->setFloat("scale",scale);
        programID->setInt("iter",iter);
        programID->setFloat("ratio",(float)SCR_WIDTH/(float)SCR_HEIGHT);

        //glm::mat4 projection =glm::perspective(glm::radians((float)1.0), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.0f, 100.0f);
        //programID.setMat4("proj",projection);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexquadsbuffer);
        glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                2,                                // size : U+V => 2
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );
        glDrawArrays(GL_QUADS,0,sizeof(vertices));

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        {
            ImGui::Begin("Debug Menu!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)


            ImGui::SliderFloat("float", &f, -3.14f, 3.14f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderInt("Swap interval",&sdl_interval_mode,-1,1);
            SDL_GL_SetSwapInterval(sdl_interval_mode);

            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            ImGui::SliderFloat2("center", (float*)&center,-1,1); // Edit 3 floats representing a color

            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            ImGui::SliderInt("iterstions",&iter,5,500);
            ImGui::SliderFloat("Scale",&scale,1,5);
            ImGui::RadioButton("Mandelbrot",&fractal,0);
            ImGui::RadioButton("Julia",&fractal,1);
            ImGui::RadioButton("Cool Mandelbrot",&fractal,2);

            if (fractal==0){
                programID=&mandelbrotshader;
            }
            if (fractal==1){
                programID=&juliashader;
            }
            if (fractal==2){
                programID=&coolmandelbrotshader;
            }

            //cout<<te_eval(expr)<<endl;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);


    }


    return 0;
}
