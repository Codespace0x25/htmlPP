// Componet/UICheckbox.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UICheckbox : public Comment::Component {
public:
    UICheckbox(const std::string& label, const std::string& name)
        : Component("label") {
        auto* input = new Comment::Component("input");
        input->setAttr("type", "checkbox");
        input->setAttr("name", name);
        addChild(input);
        addChild(new TextComponent(" " + label));
        setAttr("class", "ui-checkbox");
    }
};
