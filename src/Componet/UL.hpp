#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"
#include <vector>
#include <string>

class UL : public Comment::Component {
public:
  UL(const std::vector<std::string>& items)
    : Comment::Component("ul") 
  {
    for (const auto& item : items) {
      auto* li = new Comment::Component("li");
      li->addChild(new TextComponent(item));
      addChild(li);
    }
  }
};
