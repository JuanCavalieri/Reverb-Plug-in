/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginReverbAudioProcessorEditor::PluginReverbAudioProcessorEditor (PluginReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), openButton("Buscar IR")
{
	audioManager.registerBasicFormats(); //Permite que el objeto audioManager lea los archivos basicos (WAV y AIFF)
	openButton.onClick = [this] { openButtonClicked(); }; //Funcion Lambda: Cuando se clickea el boton openButton se ejecuta esta funcion
	addAndMakeVisible(&openButton); //Agrego y hago visible el boton openButton a la interfaz
    setSize (400, 300);
}

PluginReverbAudioProcessorEditor::~PluginReverbAudioProcessorEditor()
{
}

//==============================================================================
void PluginReverbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));


}

void PluginReverbAudioProcessorEditor::resized()
{
	openButton.setBounds(10, 10, 380, 50); //Seteo los limites del boton openButton
}

void PluginReverbAudioProcessorEditor::openButtonClicked() {
	
	// Creo un objeto FileChooser para seleccionar un archivo de audio
	FileChooser chooser("Selecciona una RI", File::getSpecialLocation(File::userDesktopDirectory), "*.wav", true, false);

	// Creo un objeto archivo
	File archivoWav;

	// Creo un objeto para leer archivos
	AudioFormatReader *reader = nullptr;

	// Creo un AudioBuffer para almacenar provisoriamente las muestras del archivo
	AudioBuffer<float> buffer;
	const float* leftSamples = nullptr;
	const float* rightSamples = nullptr;

	//int * const* bufferint = nullptr;

	// Chequeo que se haya seleccionado un archivo
	// La funcion browseForFileToOpen abre un cuadro para seleccionar solo un archivo y devuelve true si se selecciona alguno
	if (chooser.browseForFileToOpen()) {

		archivoWav = chooser.getResult();

		reader = audioManager.createReaderFor(archivoWav);

		// Seteo el tamaño del buffer en funcion del tamaño de la respuesta al impulso
		buffer.setSize(2, reader->lengthInSamples);

		// Guardo las muestras del archivo en el buffer
		reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);

		leftSamples = buffer.getReadPointer(0);
		rightSamples = buffer.getReadPointer(1);

		processor.leftConvInitialized = processor.convolverLeft.init(processor.getBlockSize(), leftSamples, reader->lengthInSamples);
		processor.rightConvInitialized = processor.convolverRight.init(processor.getBlockSize(), rightSamples, reader->lengthInSamples);

		DBG("IR Cargada");

		
	}
}
