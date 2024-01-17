//
//  GrohlRotarySlider.h
//  Grohl
//
//  Created by Nodari L on 16.01.24.
//  Copyright © 2024 DummyDSP. All rights reserved.
//

#ifndef GrohlRotarySlider_h
#define GrohlRotarySlider_h

#include <JuceHeader.h>

#include "Constants.h"

class GrohlRotarySlider : public juce::Slider {
  
public:
  GrohlRotarySlider(const juce::String& suffix = "", const float rangeStart = 0.0f, const float rangeEnd = 10.0f,
                    const float rangeStep = 1.0f) {
    
    setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setRange(rangeStart, rangeEnd, rangeStep);
    setValue(0.0f);
    setTextBoxStyle(juce::Slider::TextBoxBelow, true, 48, 24);
    
    setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(239, 146, 35));
    setColour(juce::Slider::thumbColourId, juce::Colour(239, 146, 35));
    setColour(juce::Slider::textBoxTextColourId , TEXT_COLOR);
    setColour(juce::Slider::textBoxOutlineColourId, PLUGIN_BACKGROUND_COLOR);
    
    if (suffix.length() > 0) {
      setTextValueSuffix(suffix);
    }

  }
};

#endif /* GrohlRotarySlider_h */
