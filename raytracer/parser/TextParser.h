#ifndef HW3_STRINGPARSER_H
#define HW3_STRINGPARSER_H


#include <string>
#include <stack>
#include <unordered_map>
#include "glm/glm.hpp"
#include "ObjectData.h"

class SceneData;

class TextParser {
public:
    TextParser()
            : sceneData(nullptr)
    {
        ambient[0] = 0.2f;
        ambient[1] = 0.2f;
        ambient[2] = 0.2f;
    }

    ~TextParser() {
        sceneData = nullptr;
    }

    SceneData* parse(const char* filename);

private:
    typedef glm::mat4 mat4;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef void (TextParser::*ParseFunc)(std::stringstream&);

    void rightMultiply(const mat4& matrix);

    bool readValues(std::stringstream& s, const int numvals);

    void parseLine(const std::string& line);

    bool isEmptyOrComment(const std::string& line) const;

    void initInstructionsMap();

    void parseSize(std::stringstream& s);
    void parseMaxdepth(std::stringstream& s);
    void parseOutput(std::stringstream& s);
    void parseCamera(std::stringstream& s);
    void parseSphere(std::stringstream& s);
    void parsePlane(std::stringstream& s);
    void parseBox(std::stringstream& s);
    void parseMaxverts(std::stringstream& s);
    void parseMaxvertnorms(std::stringstream& s);
    void parseVertex(std::stringstream& s);
    void parseVertexnormal(std::stringstream& s);
    void parseTri(std::stringstream& s);
    void parseTrinormal(std::stringstream& s);
    void parseTranslate(std::stringstream& s);
    void parseRotate(std::stringstream& s);
    void parseScale(std::stringstream& s);
    void parsePushTransform(std::stringstream& s);
    void parsePopTransform(std::stringstream& s);
    void parseDirectional(std::stringstream& s);
    void parsePoint(std::stringstream& s);
    void parseAttenuation(std::stringstream& s);
    void parseAmbient(std::stringstream& s);
    void parseDiffuse(std::stringstream& s);
    void parseSpecular(std::stringstream& s);
    void parseShininess(std::stringstream& s);
    void parseEmission(std::stringstream& s);

    void addObjectsData(ObjectData* object);

    float values[10];
    std::stack<mat4> transforms;
    float ambient[3];
    std::unordered_map<std::string, ParseFunc> instructionsMap;
    MaterialData material;

    SceneData* sceneData;
};


#endif //HW3_STRINGPARSER_H
