#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"
#include <string>

class UIImage : public Comment::Component {
public:
  UIImage(const std::string &URL, const std::string alt = "", int hight = 0,
          int width = 0)
      : Component("img"), alt(alt), hight(hight), width(width) {
    setAttr("class", "ui-img");
    setAttr("src", URL);

    if (!alt.empty()) {
      setAttr("alt", alt);
    }
    if (hight > 0) {
      setAttr("height", std::to_string(hight));
    }
    if (width > 0) {
      setAttr("width", std::to_string(width));
    }
  }
  std::string alt;
  int hight;
  int width;
};
