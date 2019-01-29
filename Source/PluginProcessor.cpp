/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PluginReverbAudioProcessor::PluginReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : convolverLeft(), convolverRight(), AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

PluginReverbAudioProcessor::~PluginReverbAudioProcessor()
{
}

//==============================================================================
const String PluginReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginReverbAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginReverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluginReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	leftConvInitialized = false;
	rightConvInitialized = false;
	_convolutionBuffer.clear();
	_convolutionBuffer.resize(samplesPerBlock);
}

void PluginReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void PluginReverbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	const size_t samplesToProcess = buffer.getNumSamples();

	const float* channelData0 = nullptr;
	const float* channelData1 = nullptr;

	channelData0 = buffer.getReadPointer(0);
	channelData1 = buffer.getReadPointer(1);

	if (leftConvInitialized) {
		convolverLeft.process(channelData0, &_convolutionBuffer[0], samplesToProcess);
		buffer.addFrom(0, 0, &_convolutionBuffer[0], samplesToProcess);
	}
	
	if (rightConvInitialized) {
		convolverRight.process(channelData1, &_convolutionBuffer[0], samplesToProcess);
		buffer.addFrom(1, 0, &_convolutionBuffer[0], samplesToProcess);
	}
	
}

//==============================================================================
bool PluginReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginReverbAudioProcessor::createEditor()
{
    return new PluginReverbAudioProcessorEditor (*this);
}

//==============================================================================
void PluginReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginReverbAudioProcessor();
}
