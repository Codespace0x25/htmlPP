#pragma once
#include "Componet.hpp"

class UIVideo : public Comment::Component {
public:
  UIVideo(const std::string &URL, bool controls = true)
      : Component("video"), controls(controls) {
    setAttr("class", "ui-video");
    setAttr("src", URL);
    if (controls) {
      setAttr("controls", "");
    }
  }

  bool controls;
};
