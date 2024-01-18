/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "GrohlLookAndFeel.h"
#include "GrohlRotarySlider.h"
#include "GrohlRotarySliderLabel.h"
#include "Constants.h"

//==============================================================================
/**
*/
class GrohlAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GrohlAudioProcessorEditor (GrohlAudioProcessor&);
    ~GrohlAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
  GrohlAudioProcessor& audioProcessor;
  GrohlLookAndFeel grohlLNF;
  
  // Control sliders
  GrohlRotarySlider inputGain{" Db", -12.0f, 12.0f, 0.1f};
  GrohlRotarySlider attack{" ms", 0.0f, 100.0, 1, 10.0};
  GrohlRotarySlider ratio{":1", 1.0f, 8.0f, 1.0f, 4.0};
  GrohlRotarySlider treshold{" Db", -24.0f, 0.0f, 0.1f};
  GrohlRotarySlider release{" ms", 0.0f, 100.0, 1, 20.0};
  GrohlRotarySlider makeUpGain{" Db", -12.0f, 12.0f, 0.1f};
  
  juce::Label inputGainLabel;
  juce::Label attackLabel;
  juce::Label ratioLabel;
  juce::Label tresholdLabel;
  juce::Label releaseLabel;
  juce::Label makeUpGainLabel;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrohlAudioProcessorEditor)
};
