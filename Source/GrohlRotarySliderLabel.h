//
//  GrohlRotarySliderLabel.h
//  Grohl
//
//  Created by Nodari L on 17.01.24.
//  Copyright © 2024 DummyDSP. All rights reserved.
//

#ifndef GrohlRotarySliderLabel_h
#define GrohlRotarySliderLabel_h

#include <JuceHeader.h>

#include "Constants.h"

class GrohlRotarySliderLabel : public juce::Label {
public:
  GrohlRotarySliderLabel(juce::String& text, juce::Component *attachTo) {
    setText(text, juce::dontSendNotification);
    attachToComponent(attachTo, false);
    setJustificationType(juce::Justification::centred);
    setColour(juce::Label::textColourId, TEXT_COLOR);
  }
};

#endif /* GrohlRotarySliderLabel_h */
