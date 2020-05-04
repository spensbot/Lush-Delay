/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OutputPanel.h"
#include "VoiceEditPanel.h"
#include "LushLookAndFeel.h"

//==============================================================================
/**
*/
class LushDelayAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener
{
public:
    LushDelayAudioProcessorEditor (LushDelayAudioProcessor&);
    ~LushDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked (Button *button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LushDelayAudioProcessor& processor;
    OutputPanel outputPanel;
    VoiceEditPanel voiceEditPanel;
    stm::DebugDisplay debugDisplay;
    stm::DisabledVeil bypassedVeil;

    LushLookAndFeel lushLookAndFeel;
    
    const bool debug = true;
    
    std::atomic<float>* bypass;
    
    TextButton matchedBypassButton;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    std::unique_ptr<ButtonAttachment> matchedBypassButtonAttachment;
    
    void updateWindow();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LushDelayAudioProcessorEditor)
};
