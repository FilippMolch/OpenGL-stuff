//
// Created by Filipp on 16.10.2023.
//

#include "Shader.h"

Shader::Shader() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    fShStatus = false;
    vShStatus = false;

    shaderDel = true;
}

int Shader::loadShader(int shaderType, char *filePath) {

    std::ifstream shdr;
    shdr.open(filePath);

    if(!shdr) return WRONG_FILE_PATH;

    switch (shaderType) {

        case VERTEX_SHADER: {
            vertStream << shdr.rdbuf();

            std::string vertexShader_s = vertStream.str();
            const GLchar* vertexShader_s_c = vertexShader_s.c_str();

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShader_s_c, NULL);

            vShStatus = true;
            shdr.close();
            break;
        }

        case FRAGMENT_SHADER: {
            fragStream << shdr.rdbuf();

            std::string fragmentShader_s = fragStream.str();
            const GLchar* fragmentShader_s_c = fragmentShader_s.c_str();

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShader_s_c, NULL);

            fShStatus = true;
            shdr.close();
            break;
        }

        default: {
            shdr.close();
            return UNKNOWN_SHADER_TYPE;
        }
    }
    shdr.close();
    return 0;
}

GLchar* Shader::getError(int shaderType) {
    switch (shaderType) {
        case SHADER_PROGRAM:
            return pInfoLog;

        case VERTEX_SHADER:
            return vInfoLog;

        case FRAGMENT_SHADER:
            return fInfoLog;
    }
}

int Shader::compileShader() {
    int status = 0;

    if (vShStatus && fShStatus){
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vSuccess);
        if (!vSuccess){
            status += VERT_SHADER_COMPILE_ERROR;
            glGetShaderInfoLog(vertexShader, 512, NULL, vInfoLog);
        }

        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fSuccess);
        if (!fSuccess){
            status += FRAG_SHADER_COMPILE_ERROR;
            glGetShaderInfoLog(fragmentShader, 512, NULL, fInfoLog);
        }

        shaderDel = false;
        return status;
    }
    else{
        return VERT_OR_FRAG_SHADER_NOT_LOAD;
    }
}

int Shader::genProgram() {
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &pSuccess);
    if (!pSuccess){
        glGetProgramInfoLog(shaderProgram, 512, NULL, pInfoLog);
        return SHADER_PROGRAM_LINK_ERROR;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    shaderDel = true;
    return 0;
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

Shader::~Shader(){
    if (!shaderDel) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}