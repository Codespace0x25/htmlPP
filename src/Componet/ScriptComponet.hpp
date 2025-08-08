// Componet/ScriptComponent.hpp
#pragma once
#include "Componet.hpp"

class ScriptComponent : public Comment::Component {
public:
    ScriptComponent(const std::string& jsCode)
        : Component("script") {
        setJS(jsCode);
    }
};
