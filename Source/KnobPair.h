/*
  ==============================================================================

    KnobPair.h
    Created: 3 May 2020 9:32:42pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LushLookAndFeel.h"

//==============================================================================
/*
*/
class KnobPair    : public Component
{
public:
    KnobPair(AudioProcessorValueTreeState& s, String title, String topParamId, String topName, String bottomParamId, String bottomName)
        : state(s),
        topId(topParamId),
        bottomId(bottomParamId)
    {
        initSlider(topSlider, topId, topAttachment);
        initSlider(bottomSlider, bottomId, bottomAttachment);
        
        initLabel(titleLabel, title);
        titleLabel.setFont(Font(26.0f));
        initLabel(topLabel, topName);
        initLabel(bottomLabel, bottomName);
        initLabel(topValue, "");
        initLabel(bottomValue, "");
    }

    ~KnobPair()
    {
        
    }

    void paint (Graphics& g) override
    {
        g.setColour(LushLookAndFeel::colourPanel);
        g.fillRoundedRectangle(0.0f, 0.0f, getWidth(), getHeight(), cornerSize);
    }

    void resized() override
    {
        auto bounds = getLocalBounds().reduced(3);
        titleLabel.setBounds(bounds.removeFromTop(30));
        
        auto topBounds = bounds.removeFromTop(bounds.getHeight()/2);
        topSlider.setBounds(topBounds.removeFromLeft(topBounds.getWidth()*2/3));
        topLabel.setBounds(topBounds.removeFromTop(topBounds.getHeight()/2));
        topValue.setBounds(topBounds);
        
        bottomSlider.setBounds(bounds.removeFromRight(bounds.getWidth()*2/3));
        bottomLabel.setBounds(bounds.removeFromTop(bounds.getHeight()/2));
        bottomValue.setBounds(bounds);
    }

private:
    AudioProcessorValueTreeState& state;
    
    const float cornerSize = 20.0f;
    
    String topId, bottomId;
    
    Slider topSlider, bottomSlider;
    Label titleLabel, topLabel, bottomLabel, topValue, bottomValue;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> topAttachment, bottomAttachment;
    
    void initSlider(Slider& slider, String paramId, std::unique_ptr<SliderAttachment>& attachment) {
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        attachment.reset(new SliderAttachment(state, paramId, slider));
    }
    void initLabel(Label& label, String text) {
        addAndMakeVisible(label);
        label.setText(text, dontSendNotification);
        label.setJustificationType(Justification::centred);
        label.setFont(Font(20.0f));
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobPair)
};
