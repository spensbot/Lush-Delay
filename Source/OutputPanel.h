/*
  ==============================================================================

    OutputPanel.h
    Created: 2 May 2020 7:31:30pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LushLookAndFeel.h"

//==============================================================================
/*
*/
class OutputPanel    : public Component
{
public:
    OutputPanel(AudioProcessorValueTreeState& p) : params(p)
    {
        addAndMakeVisible(dryButton);
        dryButton.setButtonText("DRY");
        dryButton.setClickingTogglesState(true);
        dryButtonAttachment.reset(new ButtonAttachment(params, Params::idDry, dryButton));
        
        addAndMakeVisible(wetSlider);
        wetSliderAttachment.reset(new SliderAttachment(params, Params::idWet, wetSlider));
        wetSlider.setSliderStyle(Slider::LinearVertical);
        wetSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        wetSlider.setPopupDisplayEnabled(true, true, getParentComponent());
        
        addAndMakeVisible(wetLabel);
        wetLabel.setText("Wet", dontSendNotification);
        wetLabel.setJustificationType(Justification::centred);
        wetLabel.attachToComponent(&wetSlider, false);
    }

    ~OutputPanel()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(LushLookAndFeel::colourPanel);
    }

    void resized() override
    {
        int labelHeight = 30;
        int padding = 5;
        int buttonHeight = 50;
        
        auto bounds = getLocalBounds();
        bounds.reduce(padding, padding);
        dryButton.setBounds(bounds.removeFromTop(buttonHeight));
        bounds.removeFromBottom(buttonHeight);
        bounds.removeFromTop(labelHeight);
        wetSlider.setBounds(bounds.reduced(0, padding));
    }
    

private:
    AudioProcessorValueTreeState& params;
    
    Slider wetSlider;
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> wetSliderAttachment;
    Label wetLabel;
    
    TextButton dryButton;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    std::unique_ptr<ButtonAttachment> dryButtonAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputPanel)
};

