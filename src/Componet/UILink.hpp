// Componet/UILink.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UILink : public Comment::Component {
public:
    UILink(const std::string& label, const std::string& href = "#")
        : Component("a") {
        addChild(new TextComponent(label));
        setAttr("href", href);
        setAttr("class", "ui-link");
    }
};
