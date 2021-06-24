#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Rubik.h"
#include "AllSolver/solve.h"
#include "AllSolver/random.h"
#include <iostream>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//--------------------------------------------------------------
const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 view;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = view * vec4(aPos, 6.0);\n"
    "   //gl_Position = view * vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "   TexCoord = aTexCoord;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "void main()\n"
    "{\n"
        "FragColor =  vec4(ourColor, 1.0f)*texture(texture1, TexCoord) ;\n"
    "   //FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";
//--------------------------------------------------------------
//variables
float camera_pos_x=0.0f,camera_pos_y=0.0f,camera_pos_z=0.0f;
glm::vec3 cameraPos   = glm::vec3(camera_pos_x,camera_pos_y,camera_pos_z);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float yaw = 0.0f;
float pitch = 0;
float cam_x=0,cam_y=0;
float cameraSpeed =1.8; 
string condition_input="N";
vector<string> reg_mov;
vector<string> solution_cubo;
///

Rubik c;
///-------------------------------------------------------------
void processInput(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //////////////////////////////////////////////////////////////////////////////////////
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        pitch -= (cameraSpeed );
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        pitch += (cameraSpeed );
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        yaw += (cameraSpeed );
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        yaw -= (cameraSpeed );
    }
    //////////////////////////////////////////////////////////////////////////////////////
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && condition_input=="N"){
        reg_mov.push_back("R");
        //cout<<"INICIA ANIMACION R"<<endl;
        condition_input="R";
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && condition_input=="N"){
        reg_mov.push_back("L");
        //cout<<"INICIA ANIMACION L"<<endl;
        condition_input="L";
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && condition_input=="N"){
        reg_mov.push_back("U");
        //cout<<"INICIA ANIMACION U"<<endl;
        condition_input="U";
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && condition_input=="N"){
        reg_mov.push_back("D");
        //cout<<"INICIA ANIMACION D"<<endl;
        condition_input="D";
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && condition_input=="N"){
        reg_mov.push_back("F");
        //cout<<"INICIA ANIMACION F"<<endl;
        condition_input="F";
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && condition_input=="N"){
        reg_mov.push_back("B");
        //cout<<"INICIA ANIMACION B"<<endl;
        condition_input="B";
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && condition_input=="N"){
        condition_input="A";
        //string tempo=to_cube_not(reg_mov);
        reg_mov.clear();
        
        //solution_cubo=get_solution(tempo);
        for(int i=0;i<solution_cubo.size();++i){
                cout<<solution_cubo[i]<<" ";
        }
        cout<<endl;
    }
}
//--------------------------------------------------------------
int main(){
    
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //-------------------------------------------------------------
     // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);
    //-------------------------------------------------------------

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load("/media/jhorel/DATA/Universidad/7mo semestre/grafica/texturas0/src/Tutorial_01/imagen.png", &width, &height, &nrChannels, 0);
    //unsigned char *data = stbi_load("/media/jhorel/DATA/Universidad/7mo semestre/grafica/texturas0/src/Tutorial_01/caras.png", &width, &height, &nrChannels, 0);
    if (data){   
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    //p.change_color_cara(0,1,0,0);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        glfwSetKeyCallback(window, processInput);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //camera
        glm::mat4 R = glm::yawPitchRoll(glm::radians(yaw), glm::radians(pitch), 0.0f);

        cameraFront = glm::vec3(R * glm::vec4(0, 0, -1, 0));
        cameraUp = glm::vec3(R * glm::vec4(0, 1, 0, 0));
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        // entradas
        if(condition_input=="R"){
            condition_input=c.animation_R();
        }
        if(condition_input=="U"){
            condition_input=c.animation_U();
        }
        if(condition_input=="D"){
            condition_input=c.animation_D();
        }
        if(condition_input=="F"){
            condition_input=c.animation_F();
        }
        if(condition_input=="B"){
            condition_input=c.animation_B();
        }
        if(condition_input=="L"){
            condition_input=c.animation_L();
        }
        if(condition_input=="A"){
            condition_input=c.aplicar_solucion(solution_cubo);
        }
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);   
        c.draw(window);
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}