/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class GrohlAudioProcessor  : public juce::AudioProcessor
{
public:
  //==============================================================================
  GrohlAudioProcessor();
  ~GrohlAudioProcessor() override;

  //==============================================================================
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

 #ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
 #endif

  void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

  //==============================================================================
  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram (int index) override;
  const juce::String getProgramName (int index) override;
  void changeProgramName (int index, const juce::String& newName) override;

  //==============================================================================
  void getStateInformation (juce::MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;
  
  juce::AudioProcessorValueTreeState apvts;
  
  juce::AudioParameterFloat* inputGain;
  juce::AudioParameterFloat* attack;
  juce::AudioParameterFloat* ratio;
  juce::AudioParameterFloat* treshold;
  juce::AudioParameterFloat* release;
  juce::AudioParameterFloat* makeUpGain;
  
private:
  
  juce::FileLogger logger{juce::File{"/tmp/grohl.log"}, "Hello"};
  
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrohlAudioProcessor)
};
