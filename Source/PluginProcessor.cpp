/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GrohlAudioProcessor::GrohlAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
  apvts(*this, nullptr, "Parameters", {
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"inputGain", 1}, "InputGain" , juce::NormalisableRange<float>(-24.0f, 6.0f, 0.1f), 0.0f),
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"attack", 1}, "Attack", juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f), 10.0f),
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"ratio", 1}, "Ratio", juce::NormalisableRange<float>(1.0f, 8.0f, 1.0f), 4.0f),
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"treshold", 1}, "Treshold", juce::NormalisableRange<float>(-24.0f, 0.0f, 0.1f), 0.0f),
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"release", 1}, "Release", juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f), 10.0f),
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"makeUpGain", 1}, "MakeUpGain", juce::NormalisableRange<float>(-24.0f, 6.0f, 0.1f), 0.0f),
  }
  )
#endif
{
  // Set initial values for all parameters
  inputGain = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("inputGain"));
  jassert(inputGain != nullptr);
  
  makeUpGain = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("makeUpGain"));
  jassert(makeUpGain != nullptr);
  
  ratio = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("ratio"));
  jassert(ratio != nullptr);
  
  treshold = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("treshold"));
  jassert(treshold != nullptr);
  
  release = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("release"));
  jassert(release != nullptr);
  
  makeUpGain = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("makeUpGain"));
  jassert(makeUpGain != nullptr);
}

GrohlAudioProcessor::~GrohlAudioProcessor()
{
}

//==============================================================================
const juce::String GrohlAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GrohlAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GrohlAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GrohlAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GrohlAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GrohlAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GrohlAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GrohlAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GrohlAudioProcessor::getProgramName (int index)
{
    return {};
}

void GrohlAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GrohlAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GrohlAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GrohlAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GrohlAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels  = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  auto _inputGain = juce::Decibels::decibelsToGain(inputGain->get());
  auto _makeUpGain = juce::Decibels::decibelsToGain(makeUpGain->get());
  logger.logMessage("GrohlAudioProcessor::processBlock::inputGain - "+std::to_string(_inputGain));
  logger.logMessage("GrohlAudioProcessor::processBlock::makeUpGain - "+std::to_string(_makeUpGain));
  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
      buffer.clear (i, 0, buffer.getNumSamples());

  // This is the place where you'd normally do the guts of your plugin's
  // audio processing...
  // Make sure to reset the state if your inner loop is processing
  // the samples and the outer loop is handling the channels.
  // Alternatively, you can process the samples with the channels
  // interleaved by keeping the same state.
  if (_inputGain != 0) {
    buffer.applyGain(_inputGain);
  }
  
//  for (int channel = 0; channel < totalNumInputChannels; ++channel) {
//    auto* channelData = buffer.getWritePointer (channel);
//
//    for (int sampleIdx= 0; sampleIdx< buffer.getNumSamples(); ++sampleIdx) {
//      auto sample = buffer.getSample(channel, sampleIdx);
//      channelData[sampleIdx] = sample + _inputGain;
//    }
//  }
  if (_makeUpGain != 0) {
    buffer.applyGain(_makeUpGain);
  }
}

//==============================================================================
bool GrohlAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GrohlAudioProcessor::createEditor()
{
    return new GrohlAudioProcessorEditor (*this);
}

//==============================================================================
void GrohlAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GrohlAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GrohlAudioProcessor();
}
