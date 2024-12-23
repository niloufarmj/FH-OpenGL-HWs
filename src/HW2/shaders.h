#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <vector>

unsigned int loadShaders(const char* vertexPath, const char* fragmentPath);
std::string loadFile(const char *fname);

#endif // SHADER_H