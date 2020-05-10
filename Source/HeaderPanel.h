/*
  ==============================================================================

    HeaderPanel.h
    Created: 2 May 2020 7:31:30pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include "LushLookAndFeel.h"
#include "DryWetControl.h"
#include "DelayVisualizer.h"

//==============================================================================
/*
*/
class HeaderPanel    : public Component
{
public:
    HeaderPanel(AudioProcessorValueTreeState& s)
        : state(s)
        , delayVisualizer(s)
        , dryWetControl(s, Params::idDry, Params::idWet)
    {
        addAndMakeVisible(dryWetControl);
        addAndMakeVisible(delayVisualizer);
        initLabel(titleLabel, "Lush Delay");
    }

    ~HeaderPanel()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll(LushLookAndFeel::colourHeader);
    }

    void resized() override
    {
        auto bounds = getLocalBounds().reduced(LushLookAndFeel::padding);
        auto topBounds = bounds.removeFromTop(90);
        titleLabel.setBounds(topBounds.removeFromLeft(getWidth() * 0.7f));
        dryWetControl.setBounds(topBounds);
        
        bounds.removeFromBottom(30);
        delayVisualizer.setBounds(bounds.reduced(50, 0));
    }

private:
    AudioProcessorValueTreeState& state;
    
    DelayVisualizer delayVisualizer;
    DryWetControl dryWetControl;
    Label titleLabel;
    
    void initLabel(Label& label, String text) {
        addAndMakeVisible(label);
        label.setText(text, dontSendNotification);
        label.setJustificationType(Justification::centredLeft);
        label.setFont(Font("Dancing Script", 65.0f, Font::plain));
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeaderPanel)
};
