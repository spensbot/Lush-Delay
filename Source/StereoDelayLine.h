/*
  ==============================================================================

    StereoDelayLine.h
    Created: 3 May 2020 2:34:44am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Params.h"


class StereoDelayLine
{
public:
    StereoDelayLine() {
        
    }
    
    ~StereoDelayLine() {
    }
    
    void prepare(const dsp::ProcessSpec& spec) {
        samplesPerMS = spec.sampleRate / 1000.0f;
        int bufferSamples = Params::MAX_BUFFER * samplesPerMS;
        
        bufferL.prepare(bufferSamples);
        bufferR.prepare(bufferSamples);
    }
    
    void process(const dsp::AudioBlock<float>& processBlock) {
        //LushDelayLine is only designed to handle stereo input.
        jassert(processBlock.getNumChannels() == 2);
        
        for (auto sampleIndex = 0 ; sampleIndex < processBlock.getNumSamples() ; sampleIndex++)
        {
            float sampleL = 0.0f;
            float sampleR = 0.0f;
            float numTaps_f = (float)numTaps;
            for (auto i=0 ; i<numTaps ; i++){
                int tapDelaySamples = taps[i];
                int delaySamplesL = delaySamples + offsetSamplesL + tapDelaySamples;
                int delaySamplesR = delaySamples + offsetSamplesR + tapDelaySamples;
                sampleL += bufferL.getSample(delaySamplesL) / numTaps_f;
                sampleR += bufferR.getSample(delaySamplesR) / numTaps_f;
            }
            
            float feedbackL = sampleL * fbDirect + sampleR * fbCross;
            float feedbackR = sampleR * fbDirect + sampleL * fbCross;
            
            bufferL.push(processBlock.getSample(0, sampleIndex) + feedbackL );
            bufferR.push(processBlock.getSample(1, sampleIndex) + feedbackR );
            
            processBlock.setSample(0, sampleIndex, sampleL);
            processBlock.setSample(1, sampleIndex, sampleR);
            
            bufferL.increment();
            bufferR.increment();
        }
    }
        
    void reset() {
        bufferL.reset();
        bufferR.reset();
    }
    
    void setDelay(float d) {
        delay = d;
        updateDelays();
    }
    void setTaps(float nt) {
        numTaps = nt;
        updateDelays();
    }
    void setSpread(float s) {
        spread = s;
        updateDelays();
    }
    void setOffset(float o){
        offset = o;
        updateDelays();
    }

    void setFBdirect(float fbd){fbDirect = fbd;}
    void setFBcross(float fbc){fbCross = fbc;}

private:
    float delay = 0.0f; //ms
    float offset = 0.0f; //percent delay
    float spread = 0.0f; //ms
    int numTaps = 1;
    float fbDirect = 0.0f;
    float fbCross = 0.0f;
    
    int delaySamples = 1;
    int offsetSamplesL = 0;
    int offsetSamplesR = 0;
    int taps[Params::MAX_TAPS];
    
    stm::RecircBuffer bufferL, bufferR;
    
    double samplesPerMS = 0.0;
    
    void updateDelays(){
        delaySamples = int(delay * samplesPerMS);
        
        auto balance = stm::Balancer::getLinearCentered(offset);
        float maxOffsetSamples = Params::MAX_OFFSET * float(delaySamples);
        offsetSamplesL = int(maxOffsetSamples * (1.0f - balance.right));
        offsetSamplesR = int(maxOffsetSamples * (1.0f - balance.left));
        
        updateTaps();
    }
    
    void updateTaps(){
        float highestPrime = stm::Primes::primes_f[numTaps - 1];
        float stepSamples = 0.0f;
        if (numTaps > 1){
            stepSamples = spread * samplesPerMS / highestPrime;
        }
        
        for (auto i = 0 ; i < Params::MAX_TAPS ; i++)
        {
            float currentPrime = stm::Primes::primes_f[i];
            taps[i] = int(currentPrime * stepSamples);
        }
    }
};




