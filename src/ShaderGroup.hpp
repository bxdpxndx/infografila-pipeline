#ifndef ShaderGroup_hpp
#define ShaderGroup_hpp

#include <map>

#include "Shader.hpp"
#include "FlatShader.hpp"
#include "PhongShader.hpp"

class ShaderGroup {
private:
    std::map<std::string, Shader*> _shaders;

    ShaderGroup() {
        _shaders["flat"] = new FlatShader();
        _shaders["phong"] = new PhongShader();
    }

    ~ShaderGroup() {
        for (std::map<std::string, Shader*>::iterator it = _shaders.begin(); it != _shaders.end(); it++) {
            delete it->second;
        }
    }

public:
    Shader * getShader(std::string name) {
        return _shaders[name];
    }
    static ShaderGroup & instance() {
        static ShaderGroup _instance;
        return _instance;
    }
};

#endif
