/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GrohlAudioProcessorEditor::GrohlAudioProcessorEditor (GrohlAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
  setResizable(true, true);
  juce::LookAndFeel::setDefaultLookAndFeel(&grohlLNF);
  setSize (830, 300);
  addAndMakeVisible(inputGain);
  addAndMakeVisible(attack);
  addAndMakeVisible(ratio);
  addAndMakeVisible(treshold);
  addAndMakeVisible(release);
  addAndMakeVisible(makeUpGain);
    
  inputGainLabel.setText("Input Gain", juce::dontSendNotification);
  inputGainLabel.attachToComponent(&inputGain, false);
  inputGainLabel.setJustificationType(juce::Justification::centred);
  inputGainLabel.setColour(juce::Label::textColourId, TEXT_COLOR);
  
  attackLabel.setText("Attack", juce::dontSendNotification);
  attackLabel.attachToComponent(&attack, false);
  attackLabel.setJustificationType(juce::Justification::centred);
  attackLabel.setColour(juce::Label::textColourId, TEXT_COLOR);
  
  ratioLabel.setText("Ratio", juce::dontSendNotification);
  ratioLabel.attachToComponent(&ratio, false);
  ratioLabel.setJustificationType(juce::Justification::centred);
  ratioLabel.setColour(juce::Label::textColourId, TEXT_COLOR);
  
  tresholdLabel.setText("Treshold", juce::dontSendNotification);
  tresholdLabel.attachToComponent(&treshold, false);
  tresholdLabel.setJustificationType(juce::Justification::centred);
  tresholdLabel.setColour(juce::Label::textColourId, TEXT_COLOR);
  
  releaseLabel.setText("Release", juce::dontSendNotification);
  releaseLabel.attachToComponent(&release, false);
  releaseLabel.setJustificationType(juce::Justification::centred);
  releaseLabel.setColour(juce::Label::textColourId, TEXT_COLOR);
  
  makeUpGainLabel.setText("Output Gain", juce::dontSendNotification);
  makeUpGainLabel.attachToComponent(&makeUpGain, false);
  makeUpGainLabel.setJustificationType(juce::Justification::centred);
  makeUpGainLabel.setColour(juce::Label::textColourId, TEXT_COLOR);
  
  inputGainLabelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "inputGain", inputGain);
  attackLabelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "attack", attack);
  ratioLabelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ratio", ratio);
  tresholdLabelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "treshold", treshold);
  releaseLabelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "release", release);
  makeUpGainLabelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "makeUpGain", makeUpGain);
}

GrohlAudioProcessorEditor::~GrohlAudioProcessorEditor()
{
}

//==============================================================================
void GrohlAudioProcessorEditor::paint (juce::Graphics& g)
{
  // (Our component is opaque, so we must completely fill the background with a solid colour)
//  g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
  g.fillAll(PLUGIN_BACKGROUND_COLOR);
}

void GrohlAudioProcessorEditor::resized()
{
  // Window's width and height
  auto width = getWidth();
  auto height = getHeight();
  
  inputGain.setBounds(10, 90, 120, 120);
  attack.setBounds(140, 90, 120, 120);
  ratio.setBounds(280, 90, 120, 120);
  treshold.setBounds(420, 90, 120, 120);
  release.setBounds(560, 90, 120, 120);
  makeUpGain.setBounds(700, 90, 120, 120);
  
}
