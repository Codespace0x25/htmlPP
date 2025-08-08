#pragma once
#include "Componet.hpp"

class TextComponent : public Comment::Component {
public:
  TextComponent(const std::string& text)
    : Comment::Component(""), textContent(text) {}

  std::string render() const override {
    return textContent;
  }

private:
  std::string textContent;
};
