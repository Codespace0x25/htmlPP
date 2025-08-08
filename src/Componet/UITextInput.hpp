// Componet/UITextInput.hpp
#pragma once
#include "Componet.hpp"

class UITextInput : public Comment::Component {
public:
    UITextInput(const std::string& name, const std::string& placeholder = "")
        : Component("input") {
        setAttr("type", "text");
        setAttr("name", name);
        if (!placeholder.empty()) setAttr("placeholder", placeholder);
        setAttr("class", "ui-textinput");
    }
};
