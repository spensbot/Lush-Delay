/*
  ==============================================================================

    VoiceEditPanel.h
    Created: 2 May 2020 7:31:39pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VoiceEditPanel    : public Component
{
public:
    VoiceEditPanel(AudioProcessorValueTreeState& p) : params(p)
    {
        
    }

    ~VoiceEditPanel()
    {
    }

    void paint (Graphics& g) override
    {
        
    }

    void resized() override
    {
        
    }

private:
    AudioProcessorValueTreeState& params;
    
    Slider wetSlider;
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> wetSliderAttachment;
    Label wetLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceEditPanel)
};
