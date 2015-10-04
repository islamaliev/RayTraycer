#include "TextParser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "glm/gtc/matrix_transform.hpp"
#include "SceneData.h"
#include "PointLightData.h"
#include "DirectionalLightData.h"
#include "TriangleData.h"
#include "SphereData.h"
#include "PlaneData.h"
#include "BoxData.h"

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
    instructionsMap["plane"] = &TextParser::parsePlane;
    instructionsMap["box"] = &TextParser::parseBox;
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
    readValues(s, 1);
    sceneData->maxDepth = (unsigned) values[0];
}

void TextParser::parseOutput(std::stringstream& s) {
    std::string outputFile;
    s >> outputFile;
    sceneData->outputFile = outputFile;
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

void TextParser::parsePlane(std::stringstream& s) {
    readValues(s, 9);
    PlaneData* plane = new PlaneData(values, &values[3], values[6], values[7], values[8]);
    addObjectsData(plane);
    sceneData->planes.push_back(plane);
}

void TextParser::parseBox(std::stringstream& s) {
    readValues(s, 4);
    BoxData* box = new BoxData(values, values[3]);
    addObjectsData(box);
    sceneData->boxes.push_back(box);
}

void TextParser::parseVertex(std::stringstream& s) {
    readValues(s, 3);
    sceneData->verticies.push_back(glm::vec3(values[0], values[1], values[2]));
}

void TextParser::parseVertexnormal(std::stringstream& s) {
    // vertexnormal x y z nx ny nz
}

void TextParser::parseTri(std::stringstream& s) {
    readValues(s, 3);
    TriangleData* tri = new TriangleData(values);
    addObjectsData(tri);
    sceneData->triangles.push_back(tri);
}

void TextParser::parseTrinormal(std::stringstream& s) {
    // trinormal v1 v2 v3
}

void TextParser::parseTranslate(std::stringstream& s) {
    readValues(s, 3);
    mat4 translateM(1.0f);
    translateM = glm::translate(translateM, glm::vec3(values[0], values[1], values[2]));
    rightMultiply(translateM);
}

void TextParser::parseRotate(std::stringstream& s) {
    readValues(s, 4);
    mat4 rotateM(1.0f);
    rotateM = glm::rotate(rotateM, (double) values[3], glm::vec3(values[0], values[1], values[2]));
    rightMultiply(rotateM);
}

void TextParser::parseScale(std::stringstream& s) {
    readValues(s, 3);
    mat4 scaleM(1.0f);
    scaleM = glm::scale(scaleM, glm::vec3(values[0], values[1], values[2]));
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
    readValues(s, 6);
    DirectionalLightData* light = new DirectionalLightData(values, values + 3);
    sceneData->directionalLights.push_back(light);
}

void TextParser::parsePoint(std::stringstream& s) {
    readValues(s, 6);
    PointLightData* light = new PointLightData(values, values + 3, attenuation);
    sceneData->pointLights.push_back(light);
}

void TextParser::parseAttenuation(std::stringstream& s) {
    readValues(s, 3);
    std::copy(values, values + 3, attenuation);
}

void TextParser::parseAmbient(std::stringstream& s) {
    readValues(s, 3);
    std::copy(values, values + 3, ambient);
}

void TextParser::parseDiffuse(std::stringstream& s) {
    readValues(s, 3);
    std::copy(values, values + 3, material.diffuse);
}

void TextParser::parseSpecular(std::stringstream& s) {
    readValues(s, 3);
    std::copy(values, values + 3, material.specular);
}

void TextParser::parseShininess(std::stringstream& s) {
    readValues(s, 1);
    material.shininess = values[0];
}

void TextParser::parseEmission(std::stringstream& s) {
    readValues(s, 3);
    std::copy(values, values + 3, material.emission);
}

void TextParser::addObjectsData(ObjectData* object) {
    std::copy(ambient, ambient + 3, object->ambient);
    object->material = material;
    object->transform = transforms.top();
}
