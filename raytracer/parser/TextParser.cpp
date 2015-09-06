#include "TextParser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "SceneData.h"
#include "Transform.h"

void TextParser::matrixTransform(float* values) {
    mat4 transform = transforms.top();
    vec4 valvec = vec4(values[0], values[1], values[2], values[3]);
    vec4 newval = transform * valvec;
    for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void TextParser::rightMultiply(const mat4& matrix) {
    mat4& T = transforms.top();
    T = T * matrix;
}

bool TextParser::readValues(std::stringstream& s, const int numvals) {
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            std::cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

SceneData* TextParser::parse(const char* filename) {
    std::string str;
    std::ifstream in;
    in.open(filename);
    if (in.is_open()) {
        initInstructionsMap();
        sceneData = new SceneData();
        transforms.push(mat4(1.0));  // identity

        getline(in, str);
        while (in) {
            parseLine(str);
            getline(in, str);
        }
    } else {
        std::cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
    return sceneData;
};

void TextParser::parseLine(const std::string& line)
{
    if (isEmptyOrComment(line))
    {
        std::stringstream s(line);
        std::string instructionName;
        s >> instructionName;
        auto it = instructionsMap.find(instructionName);
        if (it != instructionsMap.end()) {
            ParseFunc func = it->second;
            (this->*func)(s);
        }
    }
}

bool TextParser::isEmptyOrComment(const std::string& line) const {
    return (line.find_first_not_of(" \t\r\n") != std::string::npos) && (line[0] != '#');
}

void TextParser::initInstructionsMap() {
    instructionsMap["size"] = &TextParser::parseSize;
    instructionsMap["maxdepth"] = &TextParser::parseMaxdepth;
    instructionsMap["output"] = &TextParser::parseOutput;
    instructionsMap["camera"] = &TextParser::parseCamera;
    instructionsMap["sphere"] = &TextParser::parseSphere;
    instructionsMap["maxverts"] = &TextParser::parseMaxverts;
    instructionsMap["maxvertnorms"] = &TextParser::parseMaxvertnorms;
    instructionsMap["vertex"] = &TextParser::parseVertex;
    instructionsMap["vertexnormal"] = &TextParser::parseVertexnormal;
    instructionsMap["tri"] = &TextParser::parseTri;
    instructionsMap["trinormal"] = &TextParser::parseTrinormal;
    instructionsMap["translate"] = &TextParser::parseTranslate;
    instructionsMap["rotate"] = &TextParser::parseRotate;
    instructionsMap["scale"] = &TextParser::parseScale;
    instructionsMap["pushTransform"] = &TextParser::parsePushTransform;
    instructionsMap["popTransform"] = &TextParser::parsePopTransform;
    instructionsMap["directional"] = &TextParser::parseDirectional;
    instructionsMap["point"] = &TextParser::parsePoint;
    instructionsMap["attenuation"] = &TextParser::parseAttenuation;
    instructionsMap["ambient"] = &TextParser::parseAmbient;
    instructionsMap["diffuse"] = &TextParser::parseDiffuse;
    instructionsMap["specular"] = &TextParser::parseSpecular;
    instructionsMap["shininess"] = &TextParser::parseShininess;
    instructionsMap["emission"] = &TextParser::parseEmission;
}

void TextParser::parseSize(std::stringstream& s) {
    readValues(s, 2);
    sceneData->width = (unsigned) values[0];
    sceneData->height = (unsigned) values[1];
}

void TextParser::parseMaxdepth(std::stringstream& s) {
    
}

void TextParser::parseOutput(std::stringstream& s) {
    
}

void TextParser::parseCamera(std::stringstream& s) {
    readValues(s, 10);
    sceneData->camera.lookFrom[0] = values[0];
    sceneData->camera.lookFrom[1] = values[1];
    sceneData->camera.lookFrom[2] = values[2];
    sceneData->camera.lookAt[0] = values[3];
    sceneData->camera.lookAt[1] = values[4];
    sceneData->camera.lookAt[2] = values[5];
    sceneData->camera.up[0] = values[6];
    sceneData->camera.up[1] = values[7];
    sceneData->camera.up[2] = values[8];
    sceneData->camera.fovy = values[9];
}

void TextParser::parseSphere(std::stringstream& s) {
    readValues(s, 4);
    SphereData* sphere = new SphereData(values, values[3]);
    addObjectsData(sphere);
    sceneData->spheres.push_back(sphere);
}

void TextParser::parseMaxverts(std::stringstream& s) {
    readValues(s, 1);
    sceneData->maxVerticies = (int) values[0];
}

void TextParser::parseMaxvertnorms(std::stringstream& s) {

}

void TextParser::parseVertex(std::stringstream& s) {
    readValues(s, 3);
    sceneData->verticies.push_back(glm::vec3(values[0], values[1], values[2]));
}

void TextParser::parseVertexnormal(std::stringstream& s) {

}

void TextParser::parseTri(std::stringstream& s) {
    readValues(s, 3);
    TriangleData* tri = new TriangleData(values);
    addObjectsData(tri);
    sceneData->triangles.push_back(tri);
}

void TextParser::parseTrinormal(std::stringstream& s) {

}

void TextParser::parseTranslate(std::stringstream& s) {
    readValues(s, 3);
    const mat4& translateM = Transform::translate(values[0], values[1], values[2]);
    rightMultiply(translateM);
}

void TextParser::parseRotate(std::stringstream& s) {
    readValues(s, 4);
    const mat4& rotateM = mat4(Transform::rotate(values[3], vec3(values[0], values[1], values[2])));
    rightMultiply(rotateM);
}

void TextParser::parseScale(std::stringstream& s) {
    readValues(s, 3);
    const mat4& scaleM = Transform::scale(values[0], values[1], values[2]);
    rightMultiply(scaleM);
}

void TextParser::parsePushTransform(std::stringstream& s) {
    transforms.push(transforms.top());
}

void TextParser::parsePopTransform(std::stringstream& s) {
    if (transforms.size() <= 1) {
        std::cerr << "Stack has no elements.  Cannot Pop\n";
    } else {
        transforms.pop();
    }
}

void TextParser::parseDirectional(std::stringstream& s) {

}

void TextParser::parsePoint(std::stringstream& s) {

}

void TextParser::parseAttenuation(std::stringstream& s) {

}

void TextParser::parseAmbient(std::stringstream& s) {
    readValues(s, 3);
    std::copy(values, values + 3, ambient);
}

void TextParser::parseDiffuse(std::stringstream& s) {

}

void TextParser::parseSpecular(std::stringstream& s) {

}

void TextParser::parseShininess(std::stringstream& s) {

}

void TextParser::parseEmission(std::stringstream& s) {

}

void TextParser::addObjectsData(ObjectData* object) {
    std::copy(ambient, ambient + 3, object->ambient);
    object->transform = transforms.top();
}
