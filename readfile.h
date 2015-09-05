#pragma once

#include <stack>
#include <iostream>
#include "glm/glm.hpp"

void matransform (std::stack<glm::mat4> &transfstack, float * values) ;
void rightmultiply (const glm::mat4 & M, std::stack<glm::mat4> &transfstack) ;
bool readvals (std::stringstream &s, const int numvals, float * values) ;
void readfile (const char * filename) ;
