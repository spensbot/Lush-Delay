/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LushDelayAudioProcessorEditor::LushDelayAudioProcessorEditor (LushDelayAudioProcessor& p)
    : AudioProcessorEditor (&p),
    processor (p),
    outputPanel(p.parameters),
    voiceEditPanel(p.parameters)
{
    setSize(600, 400);
    setLookAndFeel(&lushLookAndFeel);
    
    addAndMakeVisible(outputPanel);
    addAndMakeVisible(voiceEditPanel);
    addAndMakeVisible(bypassedVeil);
    addAndMakeVisible(debugDisplay);
    
    addAndMakeVisible(matchedBypassButton);
    matchedBypassButton.setButtonText("MATCHED BYPASS");
    matchedBypassButton.setClickingTogglesState(true);
    matchedBypassButtonAttachment.reset(new ButtonAttachment(p.parameters, Params::idBypass, matchedBypassButton));
    matchedBypassButton.addListener(this);
    
    bypass = p.parameters.getRawParameterValue(Params::idBypass);
    
    updateWindow();
}

LushDelayAudioProcessorEditor::~LushDelayAudioProcessorEditor()
{
    matchedBypassButton.removeListener(this);
    setLookAndFeel(nullptr);
}

//==============================================================================
void LushDelayAudioProcessorEditor::paint (Graphics& g)
{
    
}

void LushDelayAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    
    bypassedVeil.setBounds(bounds);
    
    int debugWidth = bounds.getWidth() / 5;
    if (debug){
        debugDisplay.setBounds(bounds.removeFromLeft(debugWidth));
    }
    
    int outputPanelWidth = 100;
    auto outputPanelBounds = bounds.removeFromRight(outputPanelWidth);
    outputPanel.setBounds(outputPanelBounds);
    outputPanelBounds.reduce(5, 5);
    int buttonHeight = 50;
    matchedBypassButton.setBounds(outputPanelBounds.removeFromBottom(buttonHeight));
    voiceEditPanel.setBounds(bounds);
}

void LushDelayAudioProcessorEditor::buttonClicked (Button *button)
{
    if (button == &matchedBypassButton){
        updateWindow();
    }
}

void LushDelayAudioProcessorEditor::updateWindow()
{
    bool isBypassed = matchedBypassButton.getToggleState();
    //bool isBypassed = bypass->load() > 0.5f ? true : false;
    
    if (isBypassed) {
        bypassedVeil.setVisible(true);
    } else {
        bypassedVeil.setVisible(false);
    }
}
