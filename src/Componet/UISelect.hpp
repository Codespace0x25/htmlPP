// Componet/UISelect.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UISelect : public Comment::Component {
public:
    UISelect(const std::string& name)
        : Component("select") {
        setAttr("name", name);
        setAttr("class", "ui-select");
    }

    void addOption(const std::string& label, const std::string& value = "", bool selected = false) {
        auto* option = new Comment::Component("option");
        if (!value.empty())
            option->setAttr("value", value);
        if (selected)
            option->setAttr("selected", "selected");
        option->addChild(new TextComponent(label));
        addChild(option);
    }
};
