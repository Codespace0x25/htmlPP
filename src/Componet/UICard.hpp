// Componet/UICard.hpp
#pragma once
#include "Componet.hpp"

class UICard : public Comment::Component {
public:
    UICard() : Component("div") {
        setAttr("class", "ui-card");
    }
};
