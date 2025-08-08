// Componet/UIHeader.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UIHeader : public Comment::Component {
public:
    UIHeader(const std::string& text, int level = 1)
        : Component("h" + std::to_string(level)) {
        addChild(new TextComponent(text));
        setAttr("class", "ui-header");
    }
};
