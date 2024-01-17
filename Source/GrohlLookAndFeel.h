//
//  GrohlLookAndFeel.h
//  Grohl
//
//  Created by Nodari L on 16.01.24.
//  Copyright © 2024 DummyDSP. All rights reserved.
//

#ifndef GrohlLookAndFeel_h
#define GrohlLookAndFeel_h

#include <JuceHeader.h>

class GrohlLookAndFeel : public juce::LookAndFeel_V4  {

public:
  void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                         float sliderPos, const float rotaryStartAngle,
                         const float rotaryEndAngle, juce::Slider& slider)
  {
    auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (juce::Slider::rotarySliderFillColourId);

    auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin (8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (outline);
    g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);

        g.setColour (fill);
        g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    juce::Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - 10) * std::cos (toAngle - juce::MathConstants<float>::halfPi),
                             bounds.getCentreY() + (arcRadius - 10) * std::sin (toAngle - juce::MathConstants<float>::halfPi));

    g.setColour (slider.findColour (juce::Slider::thumbColourId));
    g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(),
               thumbPoint.getX(), thumbPoint.getY(), 5.0f);
  }
  
  juce::Label* createSliderTextBox (juce::Slider& slider)
  {
      auto* l = LookAndFeel_V2::createSliderTextBox (slider);

      if (getCurrentColourScheme() == juce::LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == juce::Slider::LinearBar
                                                                                 || slider.getSliderStyle() == juce::Slider::LinearBarVertical))
      {
          l->setColour (juce::Label::textColourId, juce::Colours::black.withAlpha (0.7f));
      }
    ;
      return l;
  }


};

#endif /* GrohlLookAndFeel_h */
