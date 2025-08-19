// Componet/UIAudio.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UIAudio : public Comment::Component {
public:
  UIAudio(const std::string& URL, const bool controls = true)
    : Component("audio"),controls(controls) {
        setAttr("class", "ui-audio ui-audio-" + URL);
	if(controls){
	  setAttr("controls", "");
	}
    }
  bool controls;
};
