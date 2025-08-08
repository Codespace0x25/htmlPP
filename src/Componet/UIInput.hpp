// Componet/UIInput.hpp
#pragma once
#include "Componet.hpp"

class UIInput : public Comment::Component {
public:
    UIInput(const std::string& name, const std::string& placeholder = "", const std::string& value = "")
        : Component("input") {
        setAttr("type", "text");
        setAttr("name", name);
        if (!placeholder.empty())
            setAttr("placeholder", placeholder);
        if (!value.empty())
            setAttr("value", value);
        setAttr("class", "ui-input");
    }
};
