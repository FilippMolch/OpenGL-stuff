//
// Created by Filipp on 16.10.2023.
//

#ifndef OPENGL_TEST_SHADER_H
#define OPENGL_TEST_SHADER_H

#include <iostream>
#include <fstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <string>
#include <sstream>

#define VERTEX_SHADER 1
#define FRAGMENT_SHADER 2
#define SHADER_PROGRAM 8

#define UNKNOWN_SHADER_TYPE 3
#define WRONG_FILE_PATH 4

#define VERT_SHADER_COMPILE_ERROR 11
#define FRAG_SHADER_COMPILE_ERROR 22
#define VERT_AND_FRAG_SHADER_COMPILE_ERROR 33
#define SHADER_PROGRAM_LINK_ERROR 44

#define VERT_OR_FRAG_SHADER_NOT_LOAD 7

class Shader {
public:
    int loadShader(int shaderType, char* filePath);
    int compileShader();
    GLchar* getError(int shaderType);
    int genProgram();
    void use();

    Shader();
    ~Shader();

private:

    GLchar fInfoLog[512];
    GLchar vInfoLog[512];
    GLchar pInfoLog[512];

    GLint vSuccess, fSuccess, pSuccess;

    GLuint shaderProgram;
    GLuint fragmentShader, vertexShader;
    std::stringstream vertStream, fragStream;

    bool fShStatus, vShStatus;
    bool shaderDel;
};

#endif //OPENGL_TEST_SHADER_H
