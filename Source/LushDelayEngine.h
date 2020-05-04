/*
  ==============================================================================

    LushDelayEngine.h
    Created: 2 May 2020 7:31:14pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include "LushDelayLine.h"

class LushDelayEngine: public AudioProcessorValueTreeState::Listener {
public:
    LushDelayEngine(AudioProcessorValueTreeState& s) : state(s), delayLine(s)
    {
        state.addParameterListener(Params::idDry, this);
        state.addParameterListener(Params::idWet, this);
        state.addParameterListener(Params::idBypass, this);
    }
    
    ~LushDelayEngine(){
        state.removeParameterListener(Params::idDry, this);
        state.removeParameterListener(Params::idWet, this);
        state.removeParameterListener(Params::idBypass, this);
    }
    
    void prepare(const dsp::ProcessSpec& spec) {
        dryWetMix.prepare(spec);
        matchedBypass.prepare(spec);
        dryBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
        delayLine.prepare(spec);
        
        updateParameters();
    }
    
    void process(AudioBuffer<float>& buffer) {
        // Create a copy of the input block to use as the dry signal.
        auto outBlock = juce::dsp::AudioBlock<float> (buffer);
        
        //Lush is designed as a stereo delay and only processes 2 buffers.
        jassert(outBlock.getNumChannels() == 2);
        
        auto numSamples = outBlock.getNumSamples();
        auto dryBlock = dsp::AudioBlock<float>(dryBuffer).getSubBlock(0, numSamples);
        dryBlock.copyFrom(outBlock);
        //outBlock.clear();
        
        delayLine.process(outBlock);
        
        dryWetMix.process(dryBlock, outBlock);
        matchedBypass.process(dryBlock, outBlock);
    }
    
    void reset() {
        dryWetMix.reset();
        matchedBypass.reset();
        delayLine.reset();
    }
    
    void parameterChanged(const String& parameterID, float newValue ) {
        
        if (parameterID == Params::idDry) {
            dryWetMix.setDryLinear(newValue);
        } else if (parameterID == Params::idWet) {
            dryWetMix.setWetDecibels(newValue);
        } else if (parameterID == Params::idBypass) {
            matchedBypass.setActive(newValue > 0.5 ? true : false);
        }
    }
    
private:
    AudioProcessorValueTreeState& state;
    stm::DryWetMix dryWetMix;
    stm::MatchedBypass matchedBypass;
    LushDelayLine delayLine;
    
    AudioSampleBuffer dryBuffer;
    
    void updateParameters(){
        dryWetMix.setDryDecibels(*state.getRawParameterValue(Params::idDry));
        dryWetMix.setWetDecibels(*state.getRawParameterValue(Params::idWet));
        matchedBypass.setActive(*state.getRawParameterValue(Params::idBypass));
    }
};
