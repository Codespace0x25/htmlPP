// Componet/UIAudio.hpp
#pragma once
#include "Componet.hpp"
#include "TextComponet.hpp"

class UIAudio : public Comment::Component {
public:
    UIAudio(const std::string& URL)
        : Component("audio") {
        setAttr("class", "ui-audio ui-audio-" + URL);
	if(controls){
	  setAttr("controls", "");
	}
    }
  bool controls = true;
};
