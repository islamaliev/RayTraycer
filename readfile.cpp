#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include "Transform.h"
#include "variables.h"
#include "readfile.h"

void matransform(std::stack<mat4>& transfstack, float* values)
{
    mat4 transform = transfstack.top();
    vec4 valvec = vec4(values[0], values[1], values[2], values[3]);
    vec4 newval = transform * valvec;
    for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const mat4& M, std::stack<mat4>& transfstack)
{
    mat4& T = transfstack.top();
    T = T * M;
}

bool readvals(std::stringstream& s, const int numvals, float* values)
{
    for (int i = 0; i < numvals; i++)
    {
        s >> values[i];
        if (s.fail())
        {
            std::cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

void readfile(const char* filename)
{
    std::string str, cmd;
    std::ifstream in;
    in.open(filename);
    if (in.is_open())
    {
        std::stack<mat4> transfstack;
        transfstack.push(mat4(1.0));  // identity

        getline(in, str);
        while (in)
        {
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#'))
            {

                std::stringstream s(str);
                s >> cmd;
                int i;
                float values[10]; // Position and color for light, colors for others
                bool validinput; // Validity of input

                if (cmd == "directional" || cmd == "point")
                {
                    validinput = readvals(s, 6, values);
                    if (validinput)
                    {
                        lights.push_back(LightData(cmd == "directional", values));
                    }
                }
                else if (cmd == "maxverts")
                {
                    validinput = readvals(s, 1, values);
                    if (validinput)
                    {
                        maxverts = (int) values[0];
                    }
                }
                else if (cmd == "vertex")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        verticies.push_back(glm::vec3(values[0], values[1], values[2]));
                    }
                }
                else if (cmd == "ambient")
                {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            ambient[i] = values[i];
                        }
                    }
                } else if (cmd == "diffuse")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            diffuse[i] = values[i];
                        }
                    }
                } else if (cmd == "specular")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            specular[i] = values[i];
                        }
                    }
                } else if (cmd == "emission")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            emission[i] = values[i];
                        }
                    }
                } else if (cmd == "shininess")
                {
                    validinput = readvals(s, 1, values);
                    if (validinput)
                    {
                        shininess = values[0];
                    }
                } else if (cmd == "size")
                {
                    validinput = readvals(s, 2, values);
                    if (validinput)
                    {
                        w = (int) values[0];
                        h = (int) values[1];
                    }
                } else if (cmd == "camera")
                {
                    validinput = readvals(s, 10, values); // 10 values eye cen up fov
                    if (validinput)
                    {
                        eyeinit = vec3(values[0], values[1], values[2]);
                        center = vec3(values[3], values[4], values[5]);
                        upinit = vec3(values[6], values[7], values[8]);
                        upinit = Transform::upvector(upinit, center - eyeinit);
                        fovy = values[9];
                    }
                }
                else if (cmd == "tri")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        indecies.push_back((unsigned) values[0]);
                        indecies.push_back((unsigned) values[1]);
                        indecies.push_back((unsigned) values[2]);
                    }
                }
                else if (cmd == "sphere")
                {
                    validinput = readvals(s, 1, values);
                    if (validinput)
                    {
                        /*Object* obj = &(objects[numobjects]);
                        obj->size = values[0];

                        for (i = 0; i < 4; i++)
                        {
                            (obj->ambient)[i] = ambient[i];
                            (obj->diffuse)[i] = diffuse[i];
                            (obj->specular)[i] = specular[i];
                            (obj->emission)[i] = emission[i];
                        }
                        obj->shininess = shininess;

                        obj->transform = transfstack.top();*/
                    }
                }
                else if (cmd == "translate")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        const mat4& translateM = Transform::translate(values[0], values[1], values[2]);
                        rightmultiply(translateM, transfstack);
                    }
                }
                else if (cmd == "scale")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        const mat4& scaleM = Transform::scale(values[0], values[1], values[2]);
                        rightmultiply(scaleM, transfstack);
                    }
                }
                else if (cmd == "rotate")
                {
                    validinput = readvals(s, 4, values);
                    if (validinput)
                    {
                        const mat4& rotateM = mat4(Transform::rotate(values[3], vec3(values[0], values[1], values[2])));
                        rightmultiply(rotateM, transfstack);
                    }
                }
                else if (cmd == "pushTransform")
                {
                    transfstack.push(transfstack.top());
                } else if (cmd == "popTransform")
                {
                    if (transfstack.size() <= 1)
                    {
                        std::cerr << "Stack has no elements.  Cannot Pop\n";
                    } else
                    {
                        transfstack.pop();
                    }
                }

                else
                {
                    std::cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }

        eye = eyeinit;
        up = upinit;
//        amount = amountinit;
//        sx = sy = 1.0;  // keyboard controlled scales in x and y
//        tx = ty = 0.0;  // keyboard controllled translation in x and y
    } else
    {
        std::cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}
