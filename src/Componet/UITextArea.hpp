// Componet/UITextArea.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UITextArea : public Comment::Component {
public:
    UITextArea(const std::string& name, const std::string& placeholder = "")
        : Component("textarea") {
        setAttr("name", name);
        setAttr("class", "ui-textarea");
        if (!placeholder.empty())
            setAttr("placeholder", placeholder);
    }
};
