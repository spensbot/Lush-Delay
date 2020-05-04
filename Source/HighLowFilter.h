/*
  ==============================================================================

    HighLowFilter.h
    Created: 24 Apr 2020 5:24:04pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class HighLowFilter {
public:
    
    HighLowFilter()
    {
        
    }
    
    void prepare (const dsp::ProcessSpec& spec)
    {
        sampleRate = spec.sampleRate;
        processorChain.prepare(spec);
    }
    
    void process (dsp::AudioBlock<float>& processBlock)
    {
        processorChain.process(dsp::ProcessContextReplacing<float>(processBlock));
    }
    
    void reset ()
    {
        processorChain.reset();
    }

    void setLowPassFreq(float newFreq){
        auto& lowPassFilter = processorChain.get<lowPassIndex>();
        lowPassFilter.state->setCutOffFrequency(sampleRate, newFreq);
    }

    void setHiPassFreq(float newFreq){
        auto& hiPassFilter = processorChain.template get<hiPassIndex>();
        hiPassFilter.state->type = Parameters::Type::highPass;
        hiPassFilter.state->setCutOffFrequency(sampleRate, newFreq);
    }
    
private:
    float Q = 1.0f;
    
    double sampleRate = 44000.0;
    
    enum {
        hiPassIndex,
        lowPassIndex
    };
    
    using Filter = dsp::StateVariableFilter::Filter<float>;
    using Parameters = dsp::StateVariableFilter::Parameters<float>;
    using DuplicatedFilter = dsp::ProcessorDuplicator<Filter, Parameters>;

    dsp::ProcessorChain<DuplicatedFilter, DuplicatedFilter> processorChain;
};
