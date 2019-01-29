/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginReverbAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PluginReverbAudioProcessorEditor (PluginReverbAudioProcessor&);
    ~PluginReverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    PluginReverbAudioProcessor& processor;

	TextButton openButton; //Boton para abrir la busqueda de IRs
	void openButtonClicked(); //Funcion que se ejecuta cuando se clic

	AudioFormatManager audioManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginReverbAudioProcessorEditor)
};
