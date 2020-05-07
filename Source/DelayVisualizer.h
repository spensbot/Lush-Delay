/*
  ==============================================================================

    DelayVisualizer.h
    Created: 4 May 2020 10:14:38am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LushLookAndFeel.h"

//==============================================================================
/*
*/
class DelayVisualizer    : public Component
{
public:
    DelayVisualizer()
    {
        crossFB = Drawable::createFromImageData(BinaryData::VisualizerCrossFB_svg, BinaryData::VisualizerCrossFB_svgSize);
        directFB = Drawable::createFromImageData(BinaryData::VisualizerDirectFB_svg, BinaryData::VisualizerDirectFB_svgSize);
        left = Drawable::createFromImageData(BinaryData::VisualizerLeft_svg, BinaryData::VisualizerLeft_svgSize);
        right = Drawable::createFromImageData(BinaryData::VisualizerRight_svg, BinaryData::VisualizerRight_svgSize);

        addAndMakeVisible(*crossFB);
        addAndMakeVisible(*directFB);
        addAndMakeVisible(*left);
        addAndMakeVisible(*right);
        
        initLabel(leftDelay, "100ms");
        initLabel(rightDelay, "150ms");
    }

    ~DelayVisualizer()
    {
    }

    void paint (Graphics& g) override
    {
        g.setColour(LushLookAndFeel::colourAccent);
        g.fillRoundedRectangle(topLabelBounds.toFloat(), 5);
        g.fillRoundedRectangle(bottomLabelBounds.toFloat(), 5);
    }

    void resized() override
    {
        updateBounds();
        
        auto boundsF = bounds.toFloat();
        
        crossFB->setTransformToFit (boundsF, RectanglePlacement::stretchToFit);
        directFB->setTransformToFit (boundsF, RectanglePlacement::stretchToFit);
        left->setTransformToFit (boundsF, RectanglePlacement::stretchToFit);
        right->setTransformToFit (boundsF, RectanglePlacement::stretchToFit);
        
        leftDelay.setBounds(topLabelBounds);
        rightDelay.setBounds(bottomLabelBounds);
    }
    
    void setCrossFB(float cfb){
        
    }
    void setDirectFB(float dfb){
        
    }
    void setPan(float p){
        
    }
    void setDelay(float d){
        
    }
    void setOffsetLR(float o){
        
    }

private:
    std::unique_ptr<Drawable> crossFB, directFB, left, right;
    Label leftDelay, rightDelay;
    float whRatio = 400.0f / 160.0f;
    Rectangle<int> bounds, topLabelBounds, bottomLabelBounds;
    
    void initLabel(Label& label, String text) {
        addAndMakeVisible(label);
        label.setText(text, dontSendNotification);
        label.setJustificationType(Justification::centred);
        label.setFont(Font(18.0f));
        //label.setColour(Label::backgroundColourId, Colours::black);
    }
    
    void updateBounds(){
        bounds = getLocalBounds();
        int height = bounds.getHeight();
        int width = bounds.getWidth();
        if (width / height > whRatio){
            //too much width
            int width = height * whRatio;
            int excessWidth = bounds.getWidth() - width;
            bounds.reduce(excessWidth/2, 0);
        } else {
            //too much height
            int height = width / whRatio;
            int excessHeight = bounds.getHeight() - height;
            bounds.reduce(0, excessHeight/2);
        }
        
        int labelHeight = 24;
        int labelWidth = 70;
        int reduceY = height * 0.18 - labelHeight/2;
        int reduceX = (width - labelWidth)/2;
        
        auto labelBounds = bounds.reduced(reduceX, reduceY);
        topLabelBounds = labelBounds.removeFromTop(labelHeight);
        bottomLabelBounds = labelBounds.removeFromBottom(labelHeight);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayVisualizer)
};
